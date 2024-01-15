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

Ticker::~Ticker()
{
}

void Ticker::Stop()
{
    m_Running = false;
    if(m_clock->joinable())
        m_clock->join();
}

void Ticker::Start()
{
    m_Running = true;
    m_clock = std::make_unique<std::thread>(&Ticker::Clock, this);
}

void Ticker::ForceStop()
{
    std::thread *clock = m_clock.release();
    m_Running = false;
    m_Force_Stop_Flag = false;
    delete clock;
}

void Ticker::Clock()
{
    // TODO: move to high resoulation clock

    std::queue<void(*)(DEFAULT_TIME_TYPE_TICKER)> funclist;
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
            funclist.back()(m_delta_time);
            funclist.pop();
        }
    

    }
    
}

void Ticker::AddFunction(void(*t_func)(DEFAULT_TIME_TYPE_TICKER))
{
    m_function_list_mutex.lock();
    m_functions_list.push_back(t_func);
    m_function_list_mutex.unlock();
}

void Ticker::RemoveFunction(void(*t_func)(DEFAULT_TIME_TYPE_TICKER))
{
    std::vector<void (*)(DEFAULT_TIME_TYPE_TICKER)>::iterator func_vec_itr = m_functions_list.begin();
    m_function_list_mutex.lock();
    while (func_vec_itr != m_functions_list.end())
    {
        if (*func_vec_itr == t_func)
        {
            m_functions_list.erase(func_vec_itr);
            m_function_list_mutex.unlock();
        }
    }
    m_function_list_mutex.unlock();
    throw std::out_of_range("the function hasn't been found in the list");
}

void Ticker::RemoveFunction(const int t_index)
{
    std::vector<void (*)(DEFAULT_TIME_TYPE_TICKER)>::iterator func_vec_itr = m_functions_list.begin();

    m_function_list_mutex.lock();
    if (t_index >= m_functions_list.size())
    {
        m_function_list_mutex.unlock();
        throw std::out_of_range("Index out of range");
    }

    func_vec_itr += t_index;
    m_functions_list.erase(func_vec_itr);
    m_function_list_mutex.unlock();
}

DEFAULT_TIME_TYPE_TICKER Ticker::GetMinimumTimePerTick() const noexcept
{
    return m_minimum_time_per_tick;
}

bool Ticker::GetTickerStatus() const noexcept
{
    return m_Running;
}
