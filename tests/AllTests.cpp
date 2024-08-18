#include "gtest/gtest.h"
#include "BacktestEngine.hpp"
#include "MovingAverageCrossoverStrategy.hpp"
#include "MeanReversionStrategy.hpp"
#include "Portfolio.hpp"
#include "DataLoader.hpp"
// FLAG: LOTS OF THESE TESTS NO LONGER WORK AS I HAVE CHANGED A LOT OF FUNCTIONS AND TESTED THEM LOCALLY
// ALMOST ALL TEST CASES NEED TO BE UPDATED. FOR EXAMPLE, THE MEAN REVERSION STRATEGY'S EXECUTE FUNCTION
// IS NO LONGER USED.

// UPDATING ALL OF THESE TEST CASES IS HIGHEST PRIORITY.

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
    Portfolio portfolio(100000); 

    Trade trade1("AAPL", 150.0, 100, "2024-01-01");
    portfolio.addTrade(trade1);
    ASSERT_EQ(portfolio.getCashBalance(),85000.0); 

    portfolio.closeTrade("AAPL", 155.0, 100, "2024-01-15");
    ASSERT_EQ(portfolio.getCashBalance(),100500.0); 
    ASSERT_EQ(portfolio.getTotalProfitLoss(),500.0); 
}

TEST(DataLoaderTest, BasicOperations) {
    DataLoader dataLoader("data/test_data.csv","data/portfolio.csv"); 
    dataLoader.loadData();

    const auto& numericData = dataLoader.getNumericData();
    const auto& stringData = dataLoader.getStringData();

    ASSERT_NE(numericData.find("Open"), numericData.end());
    ASSERT_NE(numericData.find("Close"), numericData.end());

    ASSERT_NE(stringData.find("Date"), stringData.end());
    ASSERT_NE(stringData.find("Symbol"), stringData.end());

    ASSERT_GT(numericData.at("Open").size(), 0);
    ASSERT_GT(numericData.at("Close").size(), 0);
    ASSERT_GT(stringData.at("Date").size(), 0);
    ASSERT_GT(stringData.at("Symbol").size(), 0);

}

TEST(BacktestEngine, BasicOperations) {
    MovingAverageCrossoverStrategy strategy;
    BacktestEngine engine("data/test_data.csv", "data/portfolio.csv", &strategy, 100000.0);
    engine.run();

}

TEST(MovingAverageCrossoverStrategyTest, CrossoverTest) {
    Portfolio portfolio(100000);
    MovingAverageCrossoverStrategy strategy;
    strategy.initialize({{"shortWindow", 2}, {"longWindow", 3}});

    std::map<std::string, double> data1 = {{"Open", 100.0}, {"Close", 102.0}, {"Date", 20240101}};
    std::map<std::string, double> data2 = {{"Open", 102.0}, {"Close", 104.0}, {"Date", 20240102}};
    std::map<std::string, double> data3 = {{"Open", 104.0}, {"Close", 106.0}, {"Date", 20240103}};
    
    strategy.execute(portfolio, data1);
    strategy.execute(portfolio, data2);
    strategy.execute(portfolio, data3);

    EXPECT_EQ(portfolio.getCashBalance(), 100000 - 106 * 100);  

    std::map<std::string, double> data4 = {{"Open", 106.0}, {"Close", 108.0}, {"Date", 20240104}};
    strategy.execute(portfolio, data4);

    EXPECT_EQ(portfolio.getCashBalance(), 100000 - 106 * 100); 

    std::map<std::string, double> data5 = {{"Open", 110.0}, {"Close", 100.0}, {"Date", 20240105}};
    strategy.execute(portfolio, data5);
    std::cout<<"Sell executed.";

    EXPECT_EQ(portfolio.getCashBalance(), (100000 - 106 * 100) + 100 * 100);  
    EXPECT_EQ(portfolio.getTotalProfitLoss(),-600); 
}

TEST(MovingAverageCrossoverStrategyTest, NoCrossoverTest) {
    Portfolio portfolio(100000);
    MovingAverageCrossoverStrategy strategy;
    strategy.initialize({{"shortWindow", 2}, {"longWindow", 3}});

    std::map<std::string, double> data1 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240101}};
    std::map<std::string, double> data2 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240102}};
    std::map<std::string, double> data3 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240103}};
    
    strategy.execute(portfolio, data1);
    strategy.execute(portfolio, data2);
    strategy.execute(portfolio, data3);
    
    EXPECT_EQ(portfolio.getCashBalance(), 100000);
}


TEST(MovingAverageCrossoverStrategyTest, NoTradeTest) {
    Portfolio portfolio(100000);
    MovingAverageCrossoverStrategy strategy;
    strategy.initialize({{"shortWindow", 2}, {"longWindow", 3}});

    std::map<std::string, double> data1 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240101}};
    std::map<std::string, double> data2 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240102}};
    std::map<std::string, double> data3 = {{"Open", 100.0}, {"Close", 100.0}, {"Date", 20240103}};
    
    strategy.execute(portfolio, data1);
    strategy.execute(portfolio, data2);
    strategy.execute(portfolio, data3);
    EXPECT_EQ(portfolio.getCashBalance(), 100000); 
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

