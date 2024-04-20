#include <PZEM004Tv30.h>

#if !defined(RX1) && !defined(TX1)
#define RX1 33
#define TX1 32
#endif

#if !defined(RX2) && !defined(TX2)
#define RX2 26
#define TX2 25
#endif

#if !defined(RX3) && !defined(TX3)
#define RX3 14
#define TX3 27
#endif

#if defined (ESP32)
  PZEM004Tv30 pzem1(&Serial2, RX1, TX1);
  PZEM004Tv30 pzem2(&Serial2, RX2, TX2);
  PZEM004Tv30 pzem3(&Serial2, RX3, TX3);
#elif defined(ESP8266)
  #include <SoftwareSerial.h>
  PZEM004Tv30 pzem1(RX1, TX1);
  PZEM004Tv30 pzem2(RX2, TX2);
  PZEM004Tv30 pzem3(RX3, TX3);
#else
  PZEM004Tv30 pzem1(&Serial2, RX1, TX1);
  PZEM004Tv30 pzem2(&Serial2, RX2, TX2);
  PZEM004Tv30 pzem3(&Serial2, RX3, TX3);
#endif

struct var{
  float volt, curr, freq, enrgy, power, pf;
};
struct var dev0;
struct var dev1;
struct var dev2;


void printSerialPZEM(){
  Serial.println("---------PZEM 1---------");
  Serial.print("Address: ");
  Serial.println(pzem1.getAddress(), HEX);
  Serial.printf("Voltage    : %.2f\ V\n", dev0.volt);
  Serial.printf("Current    : %.2f\ A\n", dev0.curr);
  Serial.printf("Frequency  : %.2f\ Hz\n", dev0.freq);
  Serial.printf("Energy     : %.2f\ kWh\n", dev0.enrgy);
  Serial.printf("Power      : %.2f\ W\n", dev0.power);
  Serial.printf("PF         : %.2f\ \n\n", dev0.pf);
  Serial.println("---------PZEM 2---------");
  Serial.print("Address: ");
  Serial.println(pzem2.getAddress(), HEX);
  Serial.printf("Voltage    : %.2f\ V\n", dev1.volt);
  Serial.printf("Current    : %.2f\ A\n", dev1.curr);
  Serial.printf("Frequency  : %.2f\ Hz\n", dev1.freq);
  Serial.printf("Energy     : %.2f\ kWh\n", dev1.enrgy);
  Serial.printf("Power      : %.2f\ W\n", dev1.power);
  Serial.printf("PF         : %.2f\ \n\n", dev1.pf);
  Serial.println("---------PZEM 3---------");
  Serial.print("Address: ");
  Serial.println(pzem3.getAddress(), HEX);
  Serial.printf("Voltage    : %.2f\ V\n", dev2.volt);
  Serial.printf("Current    : %.2f\ A\n", dev2.curr);
  Serial.printf("Frequency  : %.2f\ Hz\n", dev2.freq);
  Serial.printf("Energy     : %.2f\ kWh\n", dev2.enrgy);
  Serial.printf("Power      : %.2f\ W\n", dev2.power);
  Serial.printf("PF         : %.2f\ \n\n", dev2.pf);
}


void setup() {
  Serial.begin(115200);
}

void loop() {
  dev0.volt = pzem1.voltage();
  dev0.curr = pzem1.current();
  dev0.freq = pzem1.frequency();
  dev0.enrgy = pzem1.energy();
  dev0.power = pzem1.power();
  dev0.pf = pzem1.pf();
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


  if(isnan(dev0.volt)){
      dev0.volt = 0;
  } if (isnan(dev0.curr)){
      dev0.curr = 0;
  } if (isnan(dev0.freq)){
      dev0.freq = 0;
  } if (isnan(dev0.enrgy)){
      dev0.enrgy = 0;
  } if (isnan(dev0.power)){
      dev0.power = 0;
  } if (isnan(dev0.pf)){
      dev0.pf = 0;
  }

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

  printSerialPZEM();
  delay(2000);
}
