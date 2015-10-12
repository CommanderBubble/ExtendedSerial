#include "ExtendedSerial.h"

namespace ES {
    /** clearSerial
    * empties the input buffer for the Serial line.
    */
    void clearSerial(HardwareSerial* _Serial, bool _delay) {
        // while there are characters in the serial buffer,
        // loop and remove them until none are left. when
        // only 1 is left, delay for 1ms to ensure any
        // incoming data is also cleared.
        if (_delay)
            while (_Serial->available()) {
                if (_Serial->available() < 2) {
                    delay(1);
                }
                _Serial->read();
            }
        else
            while (_Serial->available())
                _Serial->read();
    }
    
    /** waitForContact
    * Waits for serial communication, and send an 'A' once every
    * X delay intervals, to let the other device know it is alive.
    */
    void establishContact(HardwareSerial* _Serial, unsigned int delayms, unsigned int intervals) {
        unsigned int i = intervals / 2;
    
        while (!_Serial->available()) {
            if (i >= intervals) {
                _Serial->print('A');
                i = 0;
            }
            delay(delayms);
            i++;
        }
    }

    /** recv
    * receives a message from the serial port
    *
    * The function expects ASCII data, incoming raw data will
    * be treated as garbage data.
    */
    bool recv(HardwareSerial* _Serial, message& output) {
        char in[1];
    
        while (true) {
    
        while (output.header) {
            if (_Serial->available()) {
                _Serial->readBytes(in, 1);
    
                if (in[0] == 0x20 and output.size != 0) {
                    output.header = false;
                    output.data.clear();
                } else {
                    if(isDigit(in[0]))
                        output.size = output.size * 10 + (in[0] - 48);
                    else
                        output.size = 0;
                }
            } else
                return false;
        }
    
        while (output.data.size() <= output.size)
            if (_Serial->available()) {
                _Serial->readBytes(in, 1);
    
                if (output.data.size() < output.size)
                    output.data.append(in, 1);
                else {
                    output.header = true;
                    output.size = 0;
    
                    if (in[0] == 0x00) {
                        return true;
                    } else
                        output.data.clear();
                }
            } else
                return false;
        }
    }
}
