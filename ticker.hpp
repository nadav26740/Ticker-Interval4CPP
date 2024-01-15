#pragma once
#ifndef TICKER_HPP
#define TICKER_HPP
#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <cmath>
#include <memory>
#include <vector>
#include <queue>
#include <mutex>

class Ticker
{
private:
    /// @brief For timeline control so we will be able to stop and start the methood
    bool m_Running = false;
    bool m_Force_Stop_Flag = false;
    
    /// @brief the minimum time between ticks
    std::time_t m_minimum_time_per_tick = 0.1;
        
    /// @brief The time past since the last tick started
    std::time_t m_delta_time = 0;  
    // TODO: move to high resolution clock Using chrono

    /// @brief Clock is the main thread here it will run on the queue of items
    std::unique_ptr<std::thread> m_clock;

    // List of function to run in every tick
    std::vector<void(*)(void)> m_functions_list;
    std::mutex m_function_list_mutex;

    /// @brief That's the main clock thread!
    void Clock();

public:
    /// @brief default construtctor that will create a clock without a minimal time per tick 
    Ticker();

    /// @brief Constructor that will create the object with minimal time per tick 
    /// @param t_minimal_time_per_tick paramater that will hold the time minimal times between ticks
    Ticker(std::time_t t_minimal_time_per_tick);

    // destructor will crush the clock thread
    ~Ticker();

    // ==== Timeline Methoods ====
    
    /// @brief will make the current ticker rotation his last
    void Stop();

    /// @brief Will start the ticker thread
    void Start();

    /// @brief Will make the ticker to stop immidetily buy crashing the thread (Not recommanded!)
    void ForceStop();

    // =========================

    // ==== control list methoods ====

    /// @brief Adding new function to the function queue
    /// @param func Function pointer to the new function
    /// @attention function need to be in this standart: void <function name>(time_t deltatime)
    ///  Where "deltatime" is the time gap from last running
    void AddFunction(const void (*t_func)(std::time_t));
    
    /// @brief Will search for function with the same ptr in the list and try to remove it
    /// @param t_func Function to search
    /// @warning If function hasn't found throw exception
    /// @version Unstable
    void RemoveFunction(const void (*t_func)(std::time_t));
    
    /// @brief Removing function using his index the list
    /// @param index index of element to remove
    void RemoveFunction(const int index);

    /// @brief Returning the minimal time between ticks
    /// @return std::time_t type that represent the minimal time between ticks 
    virtual std::time_t GetMinimumTimePerTick() const;
    
    /// @brief Returning if Clock Still running
    /// @return Bool type that represent the status of the clock
    virtual bool GetTickerStatus() const;
};
#endif