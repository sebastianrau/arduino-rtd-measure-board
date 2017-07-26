
#ifndef __RESISTOR_MEASURE_BOARD_PCF_H__
#define __RESISTOR_MEASURE_BOARD_PCF_H__


#include "ResistorMeasureBoard.h"
#include "PCF8574.h"

#define I2C_ADDRESS_MUX   0x20


class RTDBoard_PCF : public RTDBoard {

  private:
    static int SLECT_MUX[];
    PCF8574 mux = PCF8574(I2C_ADDRESS_MUX);
    int selectChannel(int channel);

  public:
    RTDBoard_PCF(double reference);
    void begin();
    void readAllValues(int channel);
    void readAllValues();
};


#endif
