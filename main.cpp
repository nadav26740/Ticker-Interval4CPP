#include <iostream>
#include "ticker.hpp"


void ticker_tester(DEFAULT_TIME_TYPE_TICKER delta_time);

int main(char* argv, int argn)
{
	Ticker* clocka = new Ticker();
	clocka->SetMinimumTimeBetweenTicks(std::chrono::milliseconds(200));
	clocka->AddFunction(&ticker_tester);
	
	clocka->Start();
	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	clocka->Stop();

	delete clocka;
	return EXIT_SUCCESS;
}

void ticker_tester(DEFAULT_TIME_TYPE_TICKER delta_time)
{
	std::cout << "Runned! - " << delta_time.count() << std::endl;
}