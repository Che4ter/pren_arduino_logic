//
// Created by philipp on 11/24/16.
//

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

void SerialCommunication::sendCommand(uint8_t commandID, uint8_t payload[])
{
    serialPacket packetToSend = serialPacket();
    packetToSend.commandID = commandID;
    packetToSend.payloadLength = sizeof(payload);
    packetToSend.payload = payload;
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
  //      Serial.println("read data");
    //    Serial.write(c);
      //  Serial.println("\ncurloc");

        //Serial.println(incomingPacket.curLoc);
        //Check if header is found
        if(c == SOH && incomingPacket.curLoc == 0){
        //    Serial.println("soh detected");

            incomingPacket = serialPacket();
            incomingPacket.soh = c;
            incomingPacket.curLoc++;
        }
        else if(incomingPacket.curLoc == 1)
        {
            incomingPacket.commandID = c;

          //  Serial.println("command id");
          //  Serial.println(c,HEX);

            incomingPacket.curLoc++;
        }
        else if(incomingPacket.curLoc == 2)
        {
            incomingPacket.type = c;

          //  Serial.println("tyoe");
           // Serial.println(c,HEX);

            incomingPacket.curLoc++;
        }
        else if(incomingPacket.curLoc == 3)
        {
            incomingPacket.payloadLength = c;
            incomingPacket.payload = new uint8_t[incomingPacket.payloadLength];
          //  Serial.println("payload length");
            //Serial.println(c,DEC);
            incomingPacket.curLoc++;
        }
        else if(incomingPacket.curLoc >= 4 && incomingPacket.curLoc < (4 + incomingPacket.payloadLength))
        {
            //Serial.print("read payload: ");
            //Serial.println(c,HEX);

            incomingPacket.payload[incomingPacket.curLoc - 4] = c;
        //    Serial.println(incomingPacket.payloadLength, DEC);

            incomingPacket.curLoc++;
        }
        else if(incomingPacket.curLoc >= (incomingPacket.payloadLength + 4))
        {
          //  Serial.println("package complete");
            _inComingPacketComplete = true;
        }
    }
}

void SerialCommunication::resetIncomingPacket()
{
   // Serial.println("reset Packet");
    incomingPacket = serialPacket();
    _inComingPacketComplete = false;
}

boolean SerialCommunication::verifyChecksum(serialPacket &packet)
{
    //to implement
    return true;
}

SerialCommunication::serialPacket SerialCommunication::getIncomingPacket()
{
    serialPacket packet;

    if(_inComingPacketComplete == true)
    {
       // Serial.println("get incoming packet");
        packet = incomingPacket;

        resetIncomingPacket();
    }
    return packet;
}
