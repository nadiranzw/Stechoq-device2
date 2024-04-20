#include <PZEM004Tv30.h>

#if !defined(RX1) && !defined(TX1)
#define RX1 26
#define TX1 25
#endif

// #if !defined(RX2) && !defined(TX2)
// #define RX2 33
// #define TX2 32
// #endif

// #if !defined(RX3) && !defined(TX3)
// #define RX3 14
// #define TX3 27
// #endif

#if !defined(pzemSerial)
#define pzemSerial &Serial2
#endif 

#if defined(ESP32)
PZEM004Tv30 pzem1(pzemSerial, RX1, TX1, 0x10);
PZEM004Tv30 pzem2(pzemSerial, RX1, TX1, 0x11);
PZEM004Tv30 pzem3(pzemSerial, RX1, TX1, 0x12);
#elif defined(ESP8266)
// PZEM004Tv30 pzems(Serial1);
#else
PZEM004Tv30 pzem1(pzemSerial);
#endif

struct var{
  float volt, curr, freq, enrgy, power, pf;
};

struct var dev1;
struct var dev2;
struct var dev3;

int i; // index 

void printSerialPZEM(){
  Serial.println("---------PZEM 1---------");
  Serial.print("Address: ");
  Serial.println(pzem1.getAddress(), HEX);
  Serial.printf("Voltage    : %.2f\ V\n", dev1.volt);
  Serial.printf("Current    : %.2f\ A\n", dev1.curr);
  Serial.printf("Frequency  : %.2f\ Hz\n", dev1.freq);
  Serial.printf("Energy     : %.2f\ kWh\n", dev1.enrgy);
  Serial.printf("Power      : %.2f\ W\n", dev1.power);
  Serial.printf("PF         : %.2f\ \n\n", dev1.pf);
  Serial.println("---------PZEM 2---------");
  Serial.print("Address: ");
  Serial.println(pzem2.getAddress(), HEX);
  Serial.printf("Voltage    : %.2f\ V\n", dev2.volt);
  Serial.printf("Current    : %.2f\ A\n", dev2.curr);
  Serial.printf("Frequency  : %.2f\ Hz\n", dev2.freq);
  Serial.printf("Energy     : %.2f\ kWh\n", dev2.enrgy);
  Serial.printf("Power      : %.2f\ W\n", dev2.power);
  Serial.printf("PF         : %.2f\ \n\n", dev2.pf);
  Serial.println("---------PZEM 3---------");
  Serial.print("Address: ");
  Serial.println(pzem3.getAddress(), HEX);
  Serial.printf("Voltage    : %.2f\ V\n", dev3.volt);
  Serial.printf("Current    : %.2f\ A\n", dev3.curr);
  Serial.printf("Frequency  : %.2f\ Hz\n", dev3.freq);
  Serial.printf("Energy     : %.2f\ kWh\n", dev3.enrgy);
  Serial.printf("Power      : %.2f\ W\n", dev3.power);
  Serial.printf("PF         : %.2f\ \n\n", dev3.pf);
}


void setup(){
  Serial.begin(115200);
}

void loop(){
  dev1.volt = pzem1.voltage();
  dev1.curr = pzem1.current();
  dev1.freq = pzem1.frequency();
  dev1.enrgy = pzem1.energy();
  dev1.power = pzem1.power();
  dev1.pf = pzem1.pf();
  dev2.volt = pzem1.voltage();
  dev2.curr = pzem1.current();
  dev2.freq = pzem1.frequency();
  dev2.enrgy = pzem1.energy();
  dev2.power = pzem1.power();
  dev2.pf = pzem1.pf();
  dev3.volt = pzem1.voltage();
  dev3.curr = pzem1.current();
  dev3.freq = pzem1.frequency();
  dev3.enrgy = pzem1.energy();
  dev3.power = pzem1.power();
  dev3.pf = pzem1.pf();


  if(isnan(dev1.volt)){
      dev1.volt = 0;
  } if (isnan(dev1.curr)){
      dev1.curr = 0;
  } if (isnan(dev1.freq)){
      dev1.freq = 0;
  } if (isnan(dev1.enrgy)){
      dev1.enrgy = 0;
  } if (isnan(dev1.power)){
      dev1.power = 0;
  } if (isnan(dev1.pf)){
      dev1.pf = 0;
  }

  if(isnan(dev2.volt)){
      dev2.volt = 0;
  } if (isnan(dev2.curr)){
      dev2.curr = 0;
  } if (isnan(dev2.freq)){
      dev2.freq = 0;
  } if (isnan(dev2.enrgy)){
      dev2.enrgy = 0;
  } if (isnan(dev2.power)){
      dev2.power = 0;
  } if (isnan(dev2.pf)){
      dev2.pf = 0;
  }

  if(isnan(dev3.volt)){
      dev3.volt = 0;
  } if (isnan(dev3.curr)){
      dev3.curr = 0;
  } if (isnan(dev3.freq)){
      dev3.freq = 0;
  } if (isnan(dev3.enrgy)){
      dev3.enrgy = 0;
  } if (isnan(dev3.power)){
      dev3.power = 0;
  } if (isnan(dev3.pf)){
      dev3.pf = 0;
  }

  printSerialPZEM();
  delay(2000);
}