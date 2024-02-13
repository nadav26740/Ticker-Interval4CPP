# CPP TICKER
cpp ticker is a library that has been written in cpp that made to make threading 
loops that will take less resource by running with delay between loops


## Usage
```cpp
    Ticker* clocka = new Ticker(); // Creating object
    clocka->SetInterval(std::chrono::milliseconds(100)); // setting the interval 
	clocka->AddFunction(&ticker_tester);    // Adding the function to the queue to run in loop
    clocka->RemoveFunction(&ticker_tester); // Removing Function with the same matching pointer
	clocka->Start();                        // Starting the thread and loop
    clocka->Stop();                         // Letting the thread finish the last loop and waiting until it finish
    clocka->ForceStop();                    // Forcing Stop - Making the loop finish the current running loop Imidiattly after!
```

## Document
- Interval - Is the minimum time between every loop
- Delta Time - Is the time that has been past since the start of last loop (First run Delta time = 0)
- Function List - Function list is the list for the queue of functions that will run in the loop
- Status - Is the Status of if the loop running or not
- DEFAULT_TIME_TYPE_TICKER - is define of varibale type we using for the time scale (time scale from Std::chrono)
## License
MIT License
A short, permissive software license. Basically, you can do whatever you want as long as you include the original copyright and license notice in any copy of the software/source.  There are many variations of this license in use.

### Must 
> Describes whether the original copyright must be retained.
> Including the full text of license in modified software.
