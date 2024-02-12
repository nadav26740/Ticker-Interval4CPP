#include <iostream>
#include <chrono>
#include "ticker.hpp"


void ticker_tester(DEFAULT_TIME_TYPE_TICKER delta_time);

//std::chrono::time_point tester_time_point;

int main(char* argv, int argn)
{
	Ticker* clocka = new Ticker();
	clocka->SetInterval(std::chrono::milliseconds(100));
	clocka->AddFunction(&ticker_tester);
	
	clocka->Start();
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	clocka->Stop();

	delete clocka;
	return EXIT_SUCCESS;
}

void ticker_tester(DEFAULT_TIME_TYPE_TICKER delta_time)
{
	std::cout << "Delta Time - " << delta_time.count() << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	//std::cout << "Runned! - " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - tester_time_point).count() << std::endl;
}