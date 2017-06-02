//
// Created by philipp on 11/24/16.
// Inspired by https://github.com/jeroendoggen/Arduino-serial-messaging/blob/master/SerialPacket/SerialPacket.h
//http://www.nelevation.com/support/nellycom-serial-control-protocol-specification/
//https://henryforceblog.wordpress.com/2015/03/12/designing-a-communication-protocol-using-arduinos-serial-library/
//https://www.eiman.tv/blog/posts/serprot/
//https://gist.github.com/jaimeyu/8251119

#ifndef ARDUINOV2_SERIALCOMMUNICATION_H
#define ARDUINOV2_SERIALCOMMUNICATION_H

#include "Arduino.h"
#include "SerialCommunication.h"

#define DEFAULT_BAUDRATE 9600

const uint8_t LENGTH_HEADER = 4;

// Packet Start
#define SOH                0x42

// COMMANDS
#define COMMAND_SWITCH_STATE      0x01
#define COMMAND_RESET    		   	  0x11
#define COMMAND_STOP       		   	0x12
#define COMMAND_SET_DIRECTION			0x13
#define COMMAND_SET_SPEED_STAIR		0x14
#define COMMAND_SET_SPEED_PARCOUR	0x15

enum MAINSTATES
{
	COMMAND_STATE_START = 0x20,
	COMMAND_STATE_DRIVE1 = 0x21,
	COMMAND_STATE_BEFORE_CURVE = 0x22

};

class SerialCommunication {
    public:
    SerialCommunication();

        void begin();
        void begin(uint8_t speed);

        void sendCommand(uint8_t commandID);
        void sendCommand(uint8_t commandID, uint8_t *payload);


        void readSerialData();

        struct serialPacket
        {
            uint8_t soh = SOH;
            uint8_t commandID;
            uint8_t type;
            uint8_t payloadLength;
            uint8_t* payload;
            uint8_t curLoc = 0;
        };

        serialPacket getIncomingPacket();

    private:
        serialPacket incomingPacket;

        boolean _inComingPacketComplete;

        void resetIncomingPacket();

        boolean verifyChecksum(serialPacket& packet);
        void generateChecksum(serialPacket &packet);

        void sendPacket(serialPacket &packet);
};

#endif //ARDUINOV2_SERIALCOMMUNICATION_H
