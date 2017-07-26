
#ifndef __RESISTOR_MEASURE_BOARD_IO_H__
#define __RESISTOR_MEASURE_BOARD_IO_H__

#include "ResistorMeasureBoard.h"


class RTDBoard_IO : public RTDBoard {

  private:
	int muxPin0,
		muxPin1;
		
		int selectChannel(int channel);
	

  public:
    RTDBoard_IO(double reference, int pin0,int pin1);

    void readAllValues(int channel);
    void readAllValues();
	void begin();
};


#endif
