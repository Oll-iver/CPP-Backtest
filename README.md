# CPP-backtest
This repository contains a backtesting framework built in C++ for evaluating and testing trading strategies. It currently includes implementations for the Mean Reversion and Moving Average Crossover strategies and allows for easy setup of additional strategies.

## Installation
1. **Clone the repository**
   ```bash
   git clone https://github.com/Oll-iver/CPP-Backtest.git
   cd CPP-Backtest```
2. **Install dependencies**
   Make sure you have g++ (or any C++ compiler) and cmake installed. You may also need libgtest
3. **Build the project**
   Create a build directory and compile with CMake:
   ```bash
   mkdir build
   cd build
   cmake ,.
   make```  
4. **Install Google Test (optional, for testing)**  
  If Google Test is not already anstalled you can install it with any package manager eg sudo apt install libgtest-dev
5. **Run the program**
  ```bash
  ./CPP-Backtest
  ```

## Usage
This framework includes several strategies and you can add your own using the base SimpleStrategy class.
1. Mean Reversion Strategy
  This strategy assumes that prices will revert to a mean over time. When the price is significantly below it buys, when the price is above it sells.
2. Moving Average Crossover Strategy
   This strategy uses short and long moving averages to generate buy and sell signals. A buy signal occurs when the short moving average crosses above the long moving average, and a sell signal occurs when it crosses below.
3. Other strategies
  Using the SimpleStrategy class as a base you can create additional strategies easily. Implement your strategy by inheriting from SimpleStrategy and defining initialize and execute methods.

## Testing
1. Compile the tests
  ```bash
  cd build
  make
```
2. Run tests
  ```bash
  ./AllTests.cpp
```

## Contributing
Contributions such as fixes or other strategies are welcome
1. Fork the repository
2. Create a new branch
  ```bash
  git checkout -b name
```
3. Commit changes
  ```bash
  git commit -m "Message"
```
4. Push to your fork and submit a pull request.
  ```bash
  git push origin name
```
5. Submit a pull request to main repository.
