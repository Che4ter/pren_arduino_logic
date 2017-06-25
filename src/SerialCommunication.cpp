#include "SerialCommunication.h"

SerialCommunication::SerialCommunication()
{
    resetIncomingPacket();
}

/// <summary>
/// Begin using default settings:
///  - speed: 9600 baud
/// </summary>
void SerialCommunication::begin()
{
    begin (DEFAULT_BAUDRATE);
}

/// <summary>
/// Begin using custom settings
/// </summary>
void SerialCommunication::begin(uint8_t speed)
{
    Serial.begin(speed);
}

void SerialCommunication::sendCommand(uint8_t commandID)
{
    serialPacket packetToSend = serialPacket();
    packetToSend.commandID = commandID;
    packetToSend.payloadLength = 0;
    packetToSend.payload = 0;
}

void SerialCommunication::sendPacket(serialPacket &packet){

    uint8_t bufferSize = 0;
    bufferSize = LENGTH_HEADER + packet.payloadLength;
    uint8_t buffer[bufferSize];
    buffer[0] = packet.soh;
    buffer[1] = packet.commandID;
    buffer[2] = packet.payloadLength;

    for(uint8_t count = 0; count < packet.payloadLength; count++)
    {
        buffer[count + 3] = packet.payload[count];
    }

    Serial.write(*buffer);
}

void SerialCommunication::readSerialData() {

    //Check if there is any data available to read
    if(Serial.available() > 0 && _inComingPacketComplete == false){

        //read only one byte at a time
        uint8_t c = Serial.read();

        //Check if header is found
        if(c == SOH && incomingPacket.curLoc == 0){
            incomingPacket = serialPacket();
            incomingPacket.soh = c;
            incomingPacket.curLoc++;
        }
        else if(incomingPacket.curLoc == 1)
        {
            incomingPacket.commandID = c;
            incomingPacket.curLoc++;
        }
        else if(incomingPacket.curLoc == 2)
        {
            incomingPacket.type = c;
            incomingPacket.curLoc++;
        }
        else if(incomingPacket.curLoc == 3)
        {
            incomingPacket.payloadLength = c;
            incomingPacket.payload = new uint8_t[incomingPacket.payloadLength];
            incomingPacket.curLoc++;
        }
        else if(incomingPacket.curLoc >= 4 && incomingPacket.curLoc < (4 + incomingPacket.payloadLength))
        {
            incomingPacket.payload[incomingPacket.curLoc - 4] = c;
            incomingPacket.curLoc++;
        }
        else if(incomingPacket.curLoc >= (incomingPacket.payloadLength + 4))
        {
            _inComingPacketComplete = true;
        }
    }
}

void SerialCommunication::resetIncomingPacket()
{
    incomingPacket = serialPacket();
    _inComingPacketComplete = false;
}

SerialCommunication::serialPacket SerialCommunication::getIncomingPacket()
{
    serialPacket packet;

    if(_inComingPacketComplete == true)
    {
        packet = incomingPacket;
        resetIncomingPacket();
    }
    return packet;
}
