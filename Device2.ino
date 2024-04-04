#include <PZEM004Tv30.h>

#if !defined(RX1) && !defined(TX1)
#define RX1 26
#define TX1 25
#endif

#if !defined(pzemSerial)
#define pzemSerial Serial2
#endif

#if defined(ESP32)
PZEM004Tv30 pzem1(pzemSerial, RX1, TX1);
#elif defined(ESP8266)
//PZEM004Tv30 pzem1(Serial1);
#else
PZEM004Tv30 pzem1(pzemSerial);
#endif

struct var {
  float volt, curr, freq, enrgy, power, pf;
};

struct var dev1;

void printSerialPZEM(){
  Serial.println("---------PZEM 1---------");
  Serial.printf("Voltage    : %.2f\ V\n", dev1.volt);
  Serial.printf("Current    : %.2f\ A\n", dev1.curr);
  Serial.printf("Frequency  : %.2f\ Hz\n", dev1.freq);
  Serial.printf("Energy     : %.2f\ kWh\n", dev1.enrgy);
  Serial.printf("Power      : %.2f\ W\n", dev1.power);
  Serial.printf("PF         : %.2f\ \n\n", dev1.pf);
}
        
void setup() {
  Serial.begin(115200);
  // Uncomment in order to reset the internal energy counter
  // pzem1.resetEnergy();
}

void loop() {
  Serial.print("Custom Address:");
  Serial.println(pzem1.readAddress(), HEX);

  dev1.volt = pzem1.voltage();
  dev1.curr = pzem1.current();
  dev1.freq = pzem1.frequency();
  dev1.enrgy = pzem1.energy();
  dev1.power = pzem1.power();
  dev1.pf = pzem1.pf();

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
  
  printSerialPZEM();
  delay(2000);
}