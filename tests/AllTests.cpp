#include "gtest/gtest.h"
#include "BacktestEngine.hpp"
#include "MovingAverageCrossoverStrategy.hpp"
#include "MeanReversionStrategy.hpp"
#include "Portfolio.hpp"
#include "DataLoader.hpp"

//Test core functionality
TEST(TradeTest, BasicOperations) {
    //Create a trade and confirm its initialised
    Trade trade("AAPL", 150.0, 100, "2024-01-01");
    ASSERT_EQ(trade.getSymbol(), "AAPL");
    ASSERT_EQ(trade.getEntryPrice(), 150.0);
    ASSERT_EQ(trade.getQuantity(), 100);
    ASSERT_EQ(trade.getEntryDate(), "2024-01-01");

    //Close trade, check result
    trade.closeTrade(155.0, "2024-01-15");
    ASSERT_EQ(trade.getExitPrice(), 155.0);
    ASSERT_EQ(trade.getExitDate(), "2024-01-15");
    ASSERT_EQ(trade.getProfitLoss(), 500.0); //Profit = (155-150)*100
}

//Test basic portfolio operations
TEST(PortfolioTest, BasicOperations) {
    Portfolio portfolio(100000); 

    //Add a trade, check cahs balance
    Trade trade1("AAPL", 150.0, 100, "2024-01-01");
    portfolio.addTrade(trade1);
    ASSERT_EQ(portfolio.getCashBalance(),85000.0); //100000-150*100

    //Close the trade and check the updated balance and P/L
    portfolio.closeTrade("AAPL", 155.0, 100, "2024-01-15");
    ASSERT_EQ(portfolio.getCashBalance(),100500.0); //85000+155*100
    ASSERT_EQ(portfolio.getTotalProfitLoss(),500.0);
}

//Ensure dataloader works correctly
TEST(DataLoaderTest, BasicOperations) {
    DataLoader dataLoader("data/test_data.csv","data/portfolio.csv"); 
    dataLoader.loadData();

    //Verify numeric and string data maps populate as expected
    const auto& numericData = dataLoader.getNumericData();
    const auto& stringData = dataLoader.getStringData();

    ASSERT_NE(numericData.find("open"), numericData.end());
    ASSERT_NE(numericData.find("close"), numericData.end());

    ASSERT_NE(stringData.find("date"), stringData.end());
    ASSERT_GT(numericData.at("open").size(), 0);
    ASSERT_GT(numericData.at("close").size(), 0);
    ASSERT_GT(stringData.at("date").size(), 0);

}

//Test backtestengine with moving average
TEST(BacktestEngine, BasicOperations) {
    MovingAverageCrossoverStrategy strategy;
    BacktestEngine engine("data/test_data.csv", "data/portfolio.csv", &strategy, 100000.0);
    engine.run(); //Ensure no errors

}

//Test movingaverage with a crossover situation
TEST(MovingAverageCrossoverStrategyTest, CrossoverTest) {
    Portfolio portfolio(100000);
    MovingAverageCrossoverStrategy strategy;
    strategy.initialize({{"shortWindow", 2}, {"longWindow", 3}});

    //Simulate market data with an upward trend causing crossover
    std::map<std::string, double> data1 = {{"close", 102.0}};
    std::map<std::string, double> data2 = {{"close", 104.0}};
    std::map<std::string, double> data3 = {{"close", 106.0}};
    
    strategy.execute(portfolio, data1);
    strategy.execute(portfolio, data2);
    strategy.execute(portfolio, data3);

    //Portfolio should've bought
    EXPECT_EQ(portfolio.getCashBalance(), 100000 - 106 * 100);  

    //Triger sell
    std::map<std::string, double> data4 = {{"close", 100.0}};
    strategy.execute(portfolio, data4);

    //Verify sold
    EXPECT_EQ(portfolio.getCashBalance(), 100000 - 106 * 100 + 100*100); 
    EXPECT_EQ(portfolio.getTotalProfitLoss(), -600); // Loss of 600
}

//Tests movingaverage no crossover
TEST(MovingAverageCrossoverStrategyTest, NoCrossoverTest) {
    Portfolio portfolio(100000);
    MovingAverageCrossoverStrategy strategy;
    strategy.initialize({{"shortWindow", 2}, {"longWindow", 3}});

    //Flat market
    std::map<std::string, double> data1 = {{"close", 100.0}};
    std::map<std::string, double> data2 = {{"close", 100.0}};
    std::map<std::string, double> data3 = {{"close", 100.0}};

    strategy.execute(portfolio, data1);
    strategy.execute(portfolio, data2);
    strategy.execute(portfolio, data3);
    
    //No change
    EXPECT_EQ(portfolio.getCashBalance(), 100000);
}

//Test movingaverage with insufficient data
TEST(MovingAverageCrossoverStrategyTest, NoTradeTest) {
    Portfolio portfolio(100000);
    MovingAverageCrossoverStrategy strategy;
    strategy.initialize({{"shortWindow", 2}, {"longWindow", 3}});

    std::map<std::string, double> data1 = {{"close", 100.0}};
    std::map<std::string, double> data2 = {{"close", 101.0}};
    std::map<std::string, double> data3 = {{"close", 102.0}};
    
    strategy.execute(portfolio, data1);
    strategy.execute(portfolio, data2);
    strategy.execute(portfolio, data3);
    EXPECT_EQ(portfolio.getCashBalance(), 100000); 
}

//Test meanreversion with reversion
TEST(MeanReversionStrategyTest, ReversionEntryExit) {
    Portfolio portfolio(100000); 
    MeanReversionStrategy strategy;
    strategy.initialize({{"windowSize", 3}, {"threshold", 1.5}}); // Small window for faster mean calculation

    // Simulate a downward trend 
    std::map<std::string, double> data1 = {{"close", 100.0}};
    std::map<std::string, double> data2 = {{"close", 95.0}};
    std::map<std::string, double> data3 = {{"close", 90.0}};

    strategy.execute(portfolio, data1);
    strategy.execute(portfolio, data2);
    strategy.execute(portfolio, data3);

    //Expect a buy
    EXPECT_EQ(portfolio.getCashBalance(), 100000 - 90 * 100);

    // Simulate a price recovery to trigger a sell
    std::map<std::string, double> data4 = {{"close", 110.0}};
    strategy.execute(portfolio, data4);

    // Verify that the strategy closed the position
    EXPECT_EQ(portfolio.getCashBalance(), 100000 - 90 * 100 + 110 * 100);
    EXPECT_GT(portfolio.getTotalProfitLoss(), 0);
}

// Test meanreversion with insufficient data 
TEST(MeanReversionStrategyTest, InsufficientData) {
    Portfolio portfolio(100000);
    MeanReversionStrategy strategy;
    strategy.initialize({{"windowSize", 5}, {"threshold", 2.0}});

    // Provde insufficient data points
    std::map<std::string, double> data1 = {{"close", 100.0}};
    std::map<std::string, double> data2 = {{"close", 98.0}};
    std::map<std::string, double> data3 = {{"close", 95.0}};

    strategy.execute(portfolio, data1);
    strategy.execute(portfolio, data2);
    strategy.execute(portfolio, data3);

    // No trades should be made due to insufficient data for mean calculation
    EXPECT_EQ(portfolio.getCashBalance(), 100000);
    EXPECT_EQ(portfolio.getTotalProfitLoss(), 0.0);
}

// Test meanreversion where no reversion signal is expected
TEST(MeanReversionStrategyTest, NoReversionNoTrade) {
    Portfolio portfolio(100000);
    MeanReversionStrategy strategy;
    strategy.initialize({{"windowSize", 3}, {"threshold", 1.5}});

    // Flat market
    std::map<std::string, double> data1 = {{"close", 100.0}};
    std::map<std::string, double> data2 = {{"close", 101.0}};
    std::map<std::string, double> data3 = {{"close", 102.0}};

    strategy.execute(portfolio, data1);
    strategy.execute(portfolio, data2);
    strategy.execute(portfolio, data3);

    // Portfolio should remain unchanged 
    EXPECT_EQ(portfolio.getCashBalance(), 100000);
    EXPECT_EQ(portfolio.getTotalProfitLoss(), 0.0);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

