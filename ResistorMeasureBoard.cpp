#include "ResistorMeasureBoard.h"



int  RTDBoard::MAX_GAIN_NUMBER = 6;

double RTDBoard::MIN_UREF_VOLTAGE = 10.0;


int RTDBoard::GAIN_VOLTAGE[] {
  6144,
  4096,
  2048,
  1024,
  512,
  256
};

adsGain_t RTDBoard::GAIN_REGISTER[] {
  GAIN_TWOTHIRDS,
  GAIN_ONE,
  GAIN_TWO,
  GAIN_FOUR,
  GAIN_EIGHT,
  GAIN_SIXTEEN
};

RTDBoard::RTDBoard(double reference,int maxChannel) {
  REFERENCE_RESISTOR_VALUE = reference;
  CHANNEL_COUNT = maxChannel;
}


void RTDBoard::begin() {
  Wire.begin();
}


double RTDBoard::readAdcUOut_AutoGain() {
  double val;
  int i;
  for (i = 0; i < MAX_GAIN_NUMBER ; i++) {
    adc.setGain(GAIN_REGISTER[i]);
        val = (double)adc.getGainMV() * (double)((int16_t)adc.readADC_SingleEnded(0)) / 32767.0;
    if ( i == MAX_GAIN_NUMBER || val >= GAIN_VOLTAGE[i + 1]) {
      return val;
    }
  }
  return 0;
}

double RTDBoard::readAdcUref_AutoGain() {
  double val;
  int i;
  for (i = 0; i < MAX_GAIN_NUMBER ; i++) {
    adc.setGain(GAIN_REGISTER[i]);
    val = adc.readADC_Differential_0_1_mv();
	val = (double)adc.getGainMV() * (double)((int16_t)adc.readADC_Differential_0_1()) / 32767.0;
    if ( i == MAX_GAIN_NUMBER || val >= GAIN_VOLTAGE[i + 1]) {
      return val;
    }
  }
  return 0;
}

double RTDBoard::readAdcUrx_AutoGain() {
  double val;
  int i;
  for (i = 0; i < MAX_GAIN_NUMBER ; i++) {
    adc.setGain(GAIN_REGISTER[i]);
    val = (double)adc.getGainMV() * (double)((int16_t)adc.readADC_SingleEnded(2)) / 32767.0;
    if ( i == MAX_GAIN_NUMBER || val >= GAIN_VOLTAGE[i + 1]) {
      return val;
    }
  }
  return 0;
}


void RTDBoard::readAllValues(int channel) {

  //read U0
  data[channel].uOut           = readAdcUOut_AutoGain();
  data[channel].uOutRangemv    = adc.getGainMV();
  delay(25);

  //read uRef
  data[channel].uRef         = readAdcUref_AutoGain();
  data[channel].uRefRangemv  = adc.getGainMV();
delay(25);	
  //read uRx
  data[channel].uRx          = readAdcUrx_AutoGain();
  data[channel].uRxRangemv  = adc.getGainMV();
delay(25);


if(data[channel].uRef > MIN_UREF_VOLTAGE){
  // calc Rx
  data[channel].iRef =  data[channel].uRef * 1000.0f / REFERENCE_RESISTOR_VALUE;
  data[channel].rx   =  data[channel].uRx / data[channel].iRef * 1000.0f  ;
  data[channel].error = false;
}else{
   data[channel].iRef =  0;
  data[channel].rx   =  0;
  data[channel].error = true;
}

}

void RTDBoard::readAllValues() {
  for(int i=0; i < CHANNEL_COUNT; i++){
    readAllValues(i);
  }
}



String RTDBoard::toString() {
  String out = String();

  out += "Chan\t\t";
  out += "uOut\t";
  out += "Range\t";
  out += "iRef\t";
  out += "uRef\t";
  out += "Range\t";
  out += "uRx\t";
  out += "Range\t";
  out += "Rx\t\t";
  out += "Error\t";
  out += "\r\n";

  for (int i = 0; i < CHANNEL_COUNT; i++) {
    out += "Ch";
    out += i;
    out += "\t\t";

    out += data[i].uOut;
    out += "\t(";
    out += data[i].uOutRangemv;
    out += ")\t";
    out += data[i].iRef;
    out += "\t";
    out += data[i].uRef;
    out += "\t(";
    out += data[i].uRefRangemv;
    out += ")\t";
    out += data[i].uRx;
    out += "\t(";
    out += data[i].uRxRangemv;
    out += ")\t";
    out += data[i].rx;
    out += "\t\t";
    out += data[i].error;
    out += "\r\n";
  }
   return out;
}

