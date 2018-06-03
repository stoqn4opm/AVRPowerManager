# AVRPowerManager
![enter image description here](https://img.shields.io/badge/version-1.0-brightgreen.svg)

AVRPowerManager is an Arduino Library with the help of which one can shutdown a AVR Microcontroller trough code or special shutdown pattern read from the serial output of a 8 bit shift register, as the one present in the classic Nintendo NES controller. It uses Atmel's official `<avr/sleep.h>` C++ sleep modes interfaces.

# Usage

1. Get reference to the shared instance from type `AVRPowerManager ` with `AVRPowerManager::shared()`
2. Call the `AVRPowerManager::shared()->shutdownIfNeeded(int8_t inputFromShiftRegister)` in the main aplication loop and optionally pass input from the shift register. The library checks for simultaneous presses of "start" + "select" buttons from NES Controller to trigger shutdown or auto shutdowns in after 2 mins.
3. Drive pin 2 (INT0) **LOW** to wake up the microcontroller.
4. You can alter the behaviour for expected states and start states by changing the config in `AVRPowerManager.ccp` file.

For more information you can see the example from the library - "AVRPowerManagerNESController" which uses [HEF4021BP](https://github.com/stoqn4opm/HEF4021BP)

# Installation

For detailed instructions check the official guides [here](https://www.arduino.cc/en/Guide/Libraries)

### Manual Installation

1. Put the folder `AVRPowerManager` from the repo inside your "custom library" directory. 
	- this directory is different for macOS, Linux and Windows. (checkout the official guides to find out where this directory is)
2. You should now be able to see the new library AVRPowerManager in the libraries list.

### Using the `Add Zip Library` option of Arduino IDE

1. Choose the  `Add Zip Library` option from inside `Sketch > Include Library > Add Zip Library...`
2. Select the zip file from the repo `AVRPowerManager.zip`
3. You should now be able to see the new library AVRPowerManager in the libraries list.



- in case of issues always double check your connections!
