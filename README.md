# ExtendedSerial
Extended Serial Library for the Arduino

This library provides a some simple wrappers for the arduino serial ports to enable reliabale message receiving, along with a few other small utilities. the library was designed to be as small as possible to allow inclusion on any board type.

#####Note#####
This library requires a version of the STL for Arduino, either from http://andybrown.me.uk/wk/2011/01/15/the-standard-template-library-stl-for-avr-with-c-streams/, https://github.com/maniacbug/StandardCplusplus or another implementation that provides `std::string`.

###Functions#
The following functions are curently available:

    void ES::clearSerial(HardwareSerial*, bool)

    void ES::waitForContact(HardwareSerial*, unsigned int, unsigned int)

    bool ES::recv(HardwareSerail*, ES::message&)

###clearSerial###
Usage: `ES::clearSerial(*HardwareSerial* _Serial = &Serial, bool _delay = true)`

This function takes a pointer to a HardwareSerial port and a bool determing whether to delay for 1ms when the serialport is empty to allow any outstanding data to flow in and be cleared.

###waitForContact###
Usage: `ES::waitForContact(HardwareSerial* _Serial = &Serial, unsigned int _delayms = 250, unsigned int _interval = 8)`

This function waits for data to appear on the specified serialport before allowing the program to continue - generally used in setup() to force the program to wait for any external components to be ready.

###recv###
Usage `ES::recv(HardwareSerial* _Serial, ES::message&)`

This function takes 2 arguments, the serialport to receive on, and a reference to a message struct, and returns a bool whether a valid message is available. To use it, create a persistant variable of type `ES::message` that will store the message being recieved, and call it. if it returns true, there is a vaild message available, else there is a partial message or no message available. any user code that modifies the contents of the `ES::message` struct will result in either a false positive, or a discarded valid message.

**Example**
    ES::message serialData;
    
    void loop() {
    
        if (recv(&Serial, serialData)) {
    
            //your work here
    
        }
    
    }
