#include "ticker.hpp"

Ticker::Ticker()
{
    if(std::thread::hardware_concurrency() <= 0)
    {
        std::cerr << "Warning: Concurrent threads supported is 0 or lower" << std::endl;
    } 
}

Ticker::Ticker(std::time_t t_minimal_time_per_tick)
{
    m_minimum_time_per_tick = t_minimal_time_per_tick;
}

void Ticker::Clock()
{
    // TODO: move to high resoulation clock

    std::queue<void(*)(void)> funclist;
    std::chrono::system_clock::time_point t_point = std::chrono::system_clock::now();

    while (m_Running && !m_Force_Stop_Flag)
    {
        m_delta_time = std::time(nullptr) - std::chrono::system_clock::to_time_t(t_point);
        // getting all the function ptrs into the list
        m_function_list_mutex.lock();
        for (auto func_ptr : m_functions_list)
        {
            funclist.push(func_ptr);
        }
        m_function_list_mutex.unlock();

        while (!funclist.empty() && !m_Force_Stop_Flag)
        {
            funclist.back()();
            funclist.pop();
        }
    

    }
    
}
