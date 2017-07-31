

#include "ResistorMeasureBoardPCF.h"

int RTDBoard_PCF::SLECT_MUX[] = {
  0b00000000,
  0b00100000,
  0b01000000,
  0b01100000,
  0b10000000,
  0b10100000,
  0b11000000,
  0b11100000
};


RTDBoard_PCF::RTDBoard_PCF(double reference) : RTDBoard(reference,8)
{
}


void RTDBoard_PCF::begin() {
  RTDBoard::begin();
}


int RTDBoard_PCF::selectChannel(int channel) {
  if ( channel >= 0 && channel < CHANNEL_COUNT) {
    mux.write8(SLECT_MUX[channel]);
    delay(100);
    return channel;
  }
  return -1;
}

void RTDBoard_PCF::readAllValues(int channel) {
  selectChannel(channel);
  RTDBoard::readAllValues(channel);
}
void RTDBoard_PCF::readAllValues() {
  for(int i=0; i < CHANNEL_COUNT; i++){
    readAllValues(i);
  }
}
