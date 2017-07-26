
#ifndef __RESISTOR_MEASURE_BOARD_H__
#define __RESISTOR_MEASURE_BOARD_H__

#include "Arduino.h"
#include "Adafruit_ADS1015.h"

#define I2C_ADDRESS_MUX   0x20
#define I2C_ADDRESS_ADC   0x48

#define REFERENCE_RESISTOR_PT100   100.0
#define REFERENCE_RESISTOR_NTC     100000.0

typedef struct {
  double iRef;
  double uRef;
  double uRx;
  double rx;
  double uOut;
  int uOutRangemv;
  int uRefRangemv;
  int uRxRangemv;
  bool error;
} CHANNEL_DATA_T;


class RTDBoard {

  protected:
    

    static int GAIN_VOLTAGE[];
    static adsGain_t GAIN_REGISTER[];
    static int MAX_GAIN_NUMBER;

    static double A;
    static double B;

    int   CHANNEL_COUNT;
    double 	REFERENCE_RESISTOR_VALUE;

    Adafruit_ADS1115 adc =  Adafruit_ADS1115(I2C_ADDRESS_ADC);
    CHANNEL_DATA_T data[8];

    double readAdcUOut_AutoGain();
    double readAdcUref_AutoGain();
    double readAdcUrx_AutoGain();


  public:
    RTDBoard(double reference,int maxChannel);
    void begin();
    virtual void readAllValues(int channel);
    virtual void readAllValues();
    String toString();



    inline float getIref(int index) {
      return data[index].iRef;
    }
    inline float getUref(int index) {
      return data[index].uRef;
    }
    inline float getUrx(int index) {
      return data[index].uRx;
    }
    inline float getRx(int index) {
      return data[index].rx;
    }
    inline float getUout(int index) {
      return  data[index].uOut;
    }
    inline float getUrefRangemv(int index) {
      return data[index].uRefRangemv;
    }
    inline float getUrxRangemv(int index) {
      return data[index].uRxRangemv;
    }
    inline bool getError(int index) {
      return data[index].error;
    }
};


#endif
