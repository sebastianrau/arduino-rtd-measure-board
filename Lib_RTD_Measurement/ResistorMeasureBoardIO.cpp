#include "ResistorMeasureBoardIO.h"





RTDBoard_IO::RTDBoard_IO(double reference, int pin0, int pin1) : RTDBoard(reference,4)
{
  muxPin0 = pin0;
  muxPin1 = pin1;
}


void RTDBoard_IO::begin() {
  pinMode(muxPin0, OUTPUT);
  pinMode(muxPin1, OUTPUT);
  digitalWrite(muxPin0, 1);
  digitalWrite(muxPin1, 1);
  RTDBoard::begin();
}


int RTDBoard_IO::selectChannel(int channel) {
  if ( channel >= 0 && channel < CHANNEL_COUNT) {
    digitalWrite(muxPin0, channel & 0x01);
    digitalWrite(muxPin1, (channel >> 1) & 0x01);
    delay(20);
    return channel;
  }
  return -1;
}

void RTDBoard_IO::readAllValues(int channel) {
  selectChannel(channel);
  RTDBoard::readAllValues(channel);
}
void RTDBoard_IO::readAllValues() {
  for(int i=0; i < CHANNEL_COUNT; i++){
    readAllValues(i);
  }
}


