/*
  
*/
#include <ResistorMeasureBoardIO.h>


RTDBoard_IO rtdBoardIO(REFERENCE_RESISTOR_NTC,D6,D7);

unsigned long previousMillis = 0;
const long interval = 1000;


void setup ( void ) {
  Serial.begin ( 115200 );
  rtdBoardIO.begin();
}

void loop ( void ) {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    rtdBoardIO.readAllValues();    //Read all input lines
	Serial.println(rtdBoardIO.toString());

  }

  
}
