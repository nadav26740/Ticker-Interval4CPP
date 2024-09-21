# CPP TICKER
cpp ticker is a library that has been written in C++ that made to make threading 
loops that will take less resource by running with delay between loops

## How to add to project
Currently only way to add it to project is adding the "ticker.hpp" and "ticker.cpp" files
in the future it will be moved into one file with namespace!

## Usage
```cpp
    // If you using the allinone file
    using namespace Resta;

    Ticker* clocka = new Ticker(); // Creating object
    clocka->SetInterval(std::chrono::milliseconds(100)); // setting the interval 
	clocka->AddFunction(&ticker_tester);    // Adding the function to the queue to run in loop
    clocka->RemoveFunction(&ticker_tester); // Removing Function with the same matching pointer
	clocka->Start();                        // Starting the thread and loop
    clocka->Stop();                         // Letting the thread finish the last loop and waiting until it finish
    clocka->ForceStop();                    // Forcing Stop - Making the loop finish the current running loop Imidiattly after!
```

### How to Change time scale
To change the time scale of the clock change The DEFAULT_TIME_TYPE_TICKER type!

## Document
- Interval - Is the minimum time between every loop
- Delta Time - Is the time that has been past since the start of last loop (First run Delta time = 0)
- Function List - Function list is the list for the queue of functions that will run in the loop
- Status - Is the Status of if the loop running or not
- DEFAULT_TIME_TYPE_TICKER - is define of varibale type we using for the time scale (time scale from Std::chrono)

### IMPORTANT: To add function
Every function you adding need to be void function
and need to get one argument of type DEFAULT_TIME_TYPE_TICKER
This argument is the delta time from loop

#### Example:
```cpp
void [Function_name]](DEFAULT_TIME_TYPE_TICKER delta_time)
```


### Example
```cpp
    // If you using the allinone file
    using namespace Resta;

    // creating new ticker object
    Ticker* clocka = new Ticker();

    clocka->SetInterval(std::chrono::milliseconds(100)); // running loop every minimum of 100 miliseconds
    clocka->AddFunction(&Dummy_Function); // inserting new function into the loop

    clocka->Start(); // starting the thread
    std::this_thread::sleep_for(std::chrono::milliseconds(3000)); // waiting 3 seconds
    clocka->Stop(); // ending threads
    // the dummy function runned maximum of 30 times (3000ms / 100ms)

    delete clocka;
```


## License
MIT License
A short, permissive software license. Basically, you can do whatever you want as long as you include the original copyright and license notice in any copy of the software/source.  There are many variations of this license in use.

### Must 
>> Describes whether the original copyright must be retained.
>> Including the full text of license in modified software.
