/*
  
*/

#include <ResistorMeasureBoardPCF.h>

RTDBoard_PCF rtdBoardPCF(REFERENCE_RESISTOR_NTC);


unsigned long previousMillis = 0;
const long interval = 5000;


void setup ( void ) {
  Serial.begin ( 115200 );
  rtdBoardPCF.begin();
}

void loop ( void ) {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

	rtdBoardPCF.readAllValues();    //Read all input lines

    Serial.println(rtdBoardPCF.toString());
  }

  
}

