#ifndef EXTENDEDSERIAL_H_INCLUDED
#define EXTENDEDSERIAL_H_INCLUDED

#include <Arduino.h>
#include <iterator>
#include <string>

struct message{
    message() {header = true; size = 0; data.clear();};

    bool header;
    unsigned int size;
    std::string data;
};

void establishContact(HardwareSerial*, unsigned int = 250, unsigned int = 8);

void clearSerial(HardwareSerial*, bool = true);
bool recv(HardwareSerial*, message&);

#endif // EXTENDEDSERIAL_H_INCLUDED

