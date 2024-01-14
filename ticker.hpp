#pragma once
#ifndef TICKER_HPP
#define TICKER_HPP
#include <iostream>
#include <vector>
#include <time>
#include <threads>

class Ticker
{
private:
    /// @brief For timeline control so we will be able to stop and start the methood
    bool m_Running = false;
    bool m_Force_Stop_Flag = false;
    
    /// @brief the minimum time between ticks
    time_t m_minimum_time_per_tick = 0.1;
    
    /// @brief The time past since the last tick started
    time_t m_delta_time = 0;

    /// @brief Clock is the main thread here it will run on the queue of items
    std::thread m_clock;

public:
    Ticker();
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
    void RemoveFunction(const int index);

    virtual time_t GetMinimumTimePerTick() const;
    virtual bool GetTickerStatus() const;
};
#endif