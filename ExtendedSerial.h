#ifndef EXTENDEDSERIAL_H_INCLUDED
#define EXTENDEDSERIAL_H_INCLUDED

#include <Arduino.h>
#include <iterator>
#include <string>

namespace ES {
    struct message{
        message() {header = true; size = 0; data.clear();};
    
        bool header;
        unsigned int size;
        std::string data;
    };

    void clearSerial(HardwareSerial*, bool = true);
    void waitForContact(HardwareSerial*, unsigned int = 250, unsigned int = 8);
    bool recv(HardwareSerial*, ES::message&);
}

#endif // EXTENDEDSERIAL_H_INCLUDED

