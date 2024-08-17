#include "gtest/gtest.h"
#include "BacktestEngine.hpp"
#include "MovingAverageCrossoverStrategy.hpp"
#include "MeanReversionStrategy.hpp"
#include "Portfolio.hpp"
#include "DataLoader.hpp"

TEST(TradeTest, BasicOperations) {
    Trade trade("AAPL", 150.0, 100, "2024-01-01");
    ASSERT_EQ(trade.getSymbol(), "AAPL");
    ASSERT_EQ(trade.getEntryPrice(), 150.0);
    ASSERT_EQ(trade.getQuantity(), 100);
    ASSERT_EQ(trade.getEntryDate(), "2024-01-01");

    trade.closeTrade(155.0, "2024-01-15");
    ASSERT_EQ(trade.getExitPrice(), 155.0);
    ASSERT_EQ(trade.getExitDate(), "2024-01-15");
    ASSERT_EQ(trade.getProfitLoss(), 500.0);
}


TEST(PortfolioTest, BasicOperations) {
    Portfolio portfolio(100000); // $100,000 initial cash

    Trade trade1("AAPL", 150.0, 100, "2024-01-01");
    portfolio.addTrade(trade1);
    ASSERT_EQ(portfolio.getCashBalance(),85000.0); // 100000 - (150 * 100)

    portfolio.closeTrade("AAPL", 155.0, 100, "2024-01-15");
    ASSERT_EQ(portfolio.getCashBalance(),100500.0); // 85000 + (155 * 100)
    ASSERT_EQ(portfolio.getTotalProfitLoss(),500.0); // (155 - 150) * 100
}

TEST(DataLoaderTest, BasicOperations) {
    DataLoader dataLoader("../data/test_data.csv");  // Adjust the path as necessary
    dataLoader.loadData();

    const auto& numericData = dataLoader.getNumericData();
    const auto& stringData = dataLoader.getStringData();

    // Check that the numeric columns are present
    ASSERT_NE(numericData.find("Open"), numericData.end());
    ASSERT_NE(numericData.find("Close"), numericData.end());

    // Check that the string columns are present
    ASSERT_NE(stringData.find("Date"), stringData.end());
    ASSERT_NE(stringData.find("Symbol"), stringData.end());

    // Example checks on data content
    ASSERT_GT(numericData.at("Open").size(), 0);
    ASSERT_GT(numericData.at("Close").size(), 0);
    ASSERT_GT(stringData.at("Date").size(), 0);
    ASSERT_GT(stringData.at("Symbol").size(), 0);

}

TEST(BacktestEngine, BasicOperations) {
    MovingAverageCrossoverStrategy strategy;
    BacktestEngine engine("../data/test_data.csv", &strategy, 100000.0);

    // Run the backtest
    engine.run();

}


TEST(MeanReversionStrategyTest, BasicOperation) {
    Portfolio portfolio(100000);
    MeanReversionStrategy strategy;
    strategy.initialize({{"windowSize", 3}, {"threshold", 2.0}});

    // Simulate price data that should trigger a buy
    std::map<std::string, double> data1 = {{"Open", 150.0}, {"Close", 145.0}, {"Date", 20240101}};
    strategy.execute(portfolio, data1, 0);
    EXPECT_EQ(portfolio.getCashBalance(), 100000); // No trade should happen yet

    std::map<std::string, double> data2 = {{"Open", 145.0}, {"Close", 140.0}, {"Date", 20240102}};
    strategy.execute(portfolio, data2, 0);
    EXPECT_EQ(portfolio.getCashBalance(), 100000); // Still no trade

    std::map<std::string, double> data3 = {{"Open", 140.0}, {"Close", 135.0}, {"Date", 20240103}};
    strategy.execute(portfolio, data3, 0);
    EXPECT_EQ(portfolio.getCashBalance(), 100000 - 140 * 100); // Trade should happen

    // Simulate price data that should trigger a sell
    std::map<std::string, double> data4 = {{"Open", 149.0}, {"Close", 153.0}, {"Date", 20240104}};
    strategy.execute(portfolio, data4, 1);
    EXPECT_EQ(portfolio.getCashBalance(), 86000 + 153 * 100); // Trade should happen (86000 because it's decreased by 14k from last trade.)
}

TEST(MeanReversionStrategyTest, NoAction) {
    Portfolio portfolio(100000);
    MeanReversionStrategy strategy;
    strategy.initialize({{"windowSize", 2}, {"threshold", 2.0}});

    // Simulate price data that should not trigger any trade
    std::map<std::string, double> data1 = {{"Open", 150.0}, {"Close", 150.0}, {"Date", 20240101}};
    strategy.execute(portfolio, data1, 0);
    EXPECT_EQ(portfolio.getCashBalance(), 100000); // No trade should happen

    std::map<std::string, double> data2 = {{"Open", 150.0}, {"Close", 150.0}, {"Date", 20240102}};
    strategy.execute(portfolio, data2, 0);
    EXPECT_EQ(portfolio.getCashBalance(), 100000); // No trade should happen

    std::map<std::string, double> data3 = {{"Open", 150.0}, {"Close", 150.0}, {"Date", 20240103}};
    strategy.execute(portfolio, data3, 0);
    EXPECT_EQ(portfolio.getCashBalance(), 100000); // No trade should happen
}

TEST(MovingAverageCrossoverStrategyTest, CrossoverTest) {
    Portfolio portfolio(100000);
    MovingAverageCrossoverStrategy strategy;
    strategy.initialize({{"shortWindow", 2}, {"longWindow", 3}});

    bool hasPosition = false;

    // Simulate data to calculate short and long moving averages
    std::map<std::string, double> data1 = {{"Open", 100.0}, {"Close", 102.0}, {"Date", 20240101}};
    std::map<std::string, double> data2 = {{"Open", 102.0}, {"Close", 104.0}, {"Date", 20240102}};
    std::map<std::string, double> data3 = {{"Open", 104.0}, {"Close", 106.0}, {"Date", 20240103}};
    
    strategy.execute(portfolio, data1, hasPosition);
    strategy.execute(portfolio, data2, hasPosition);
    strategy.execute(portfolio, data3, hasPosition);

    // At this point, a buy should have occurred
    EXPECT_EQ(portfolio.getCashBalance(), 100000 - 106 * 100);  // Expect cash balance after buying 100 shares at 106

    // Add more data points to trigger another crossover
    std::map<std::string, double> data4 = {{"Open", 106.0}, {"Close", 108.0}, {"Date", 20240104}};
    strategy.execute(portfolio, data4, true);

    // Ensure no additional buy occurs
    EXPECT_EQ(portfolio.getCashBalance(), 100000 - 106 * 100);  // Cash balance should not change

    // Now simulate prices that trigger a sell
    std::map<std::string, double> data5 = {{"Open", 110.0}, {"Close", 104.0}, {"Date", 20240105}};
    strategy.execute(portfolio, data5, true);

    // After the sell, the cash balance should reflect the sale at 104
    EXPECT_FALSE(hasPosition);
    EXPECT_EQ(portfolio.getCashBalance(), (100000 - 106 * 100) + 104 * 100);  // Cash balance after selling 100 shares at 104
}


// Test to ensure no trade happens if the crossover condition is not met
TEST(MovingAverageCrossoverStrategyTest, NoCrossoverTest) {
    Portfolio portfolio(100000);
    MovingAverageCrossoverStrategy strategy;
    strategy.initialize({{"shortWindow", 2}, {"longWindow", 3}});

    // Simulate data that does not create a crossover
    std::map<std::string, double> data1 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240101}};
    std::map<std::string, double> data2 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240102}};
    std::map<std::string, double> data3 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240103}};
    
    strategy.execute(portfolio, data1, 0);
    strategy.execute(portfolio, data2, 0);
    strategy.execute(portfolio, data3, 0);
    
    // The cash balance should remain the same as no trades should occur
    EXPECT_EQ(portfolio.getCashBalance(), 100000);
}


// Test to ensure no trade occurs if the short MA and long MA do not cross
TEST(MovingAverageCrossoverStrategyTest, NoTradeTest) {
    Portfolio portfolio(100000);
    MovingAverageCrossoverStrategy strategy;
    strategy.initialize({{"shortWindow", 2}, {"longWindow", 3}});

    bool hasPosition = false;

    // Simulate data that does not trigger a buy or sell
    std::map<std::string, double> data1 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240101}};
    std::map<std::string, double> data2 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240102}};
    std::map<std::string, double> data3 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240103}};
    
    strategy.execute(portfolio, data1, hasPosition);
    strategy.execute(portfolio, data2, hasPosition);
    strategy.execute(portfolio, data3, hasPosition);

    // No trade should have occurred
    EXPECT_FALSE(hasPosition);
    EXPECT_EQ(portfolio.getCashBalance(), 100000);  // Cash balance should remain unchanged
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

