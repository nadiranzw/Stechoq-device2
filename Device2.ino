#include <PZEM004Tv30.h>

#if !defined(RX1) && !defined(TX1)
#define RX1 26
#define TX1 25
#define RX2 14
#define TX2 27
#define RX3 33
#define TX3 32
#endif

#if !defined(PZEM_Serial)
#define PZEM_Serial Serial2
#endif

// --------PZEM digital pin to (RX,TX)--------
#if defined(ESP32)
PZEM004Tv30 pzem1(PZEM_Serial, RX1, TX1);
PZEM004Tv30 pzem2(PZEM_Serial, RX2, TX2);
PZEM004Tv30 pzem3(PZEM_Serial, RX3, TX3);
#elif defined(ESP8266)
#else
PZEM004Tv30 pzem1(PZEM_Serial); // default pin IO
PZEM004Tv30 pzem2(PZEM_Serial); // default pin IO
PZEM004Tv30 pzem3(PZEM_Serial); // default pin IO
#endif

float volt1, curr1, freq1, enrgy1;
float volt2, curr2, freq2, enrgy2;
float volt3, curr3, freq3, enrgy3;


void printSerialPZEM(){
  Serial.println("-------PZEM 1-------");
  Serial.printf("Voltage    : %2f\ V\n", volt1);
  Serial.printf("Current    : %2f\ A\n", curr1);
  Serial.printf("Frequency  : %2f\ Hz\n", freq1);
  Serial.printf("Energy     : %2f\ kWh\n", enrgy1);
  Serial.println("-------PZEM 2-------");
  Serial.printf("Voltage    : %2f\ V\n", volt2);
  Serial.printf("Current    : %2f\ A\n", curr2);
  Serial.printf("Frequency  : %2f\ Hz\n", freq2);
  Serial.printf("Energy     : %2f\ kWh\n", enrgy2);
  Serial.println("-------PZEM 3-------");
  Serial.printf("Voltage    : %2f\ V\n", volt3);
  Serial.printf("Current    : %2f\ A\n", curr3);
  Serial.printf("Frequency  : %2f\ Hz\n", freq3);
  Serial.printf("Energy     : %2f\ kWh\n", enrgy3);
  Serial.println("");
}

float zeroIfNan(float v){
  if (isnan(v)){
    v = 0;
    return v;
  }
}


void setup(){
  Serial.begin(115200);
  Serial.println("--------------------INSENS--------------------");
}

void loop(){
  volt1 = pzem1.voltage();
  volt1 = zeroIfNan(volt1);
  curr1 = pzem1.current();
  curr1 = zeroIfNan(curr1);
  freq1 = pzem1.frequency();
  freq1 = zeroIfNan(freq1);
  enrgy1 = pzem1.energy() / 1000; //kWh
  enrgy1 = zeroIfNan(enrgy1);

  volt2 = pzem2.voltage();
  volt2 = zeroIfNan(volt2);
  curr2 = pzem2.current();
  curr2 = zeroIfNan(curr2);
  freq2 = pzem2.frequency();
  freq2 = zeroIfNan(freq2);
  enrgy2 = pzem2.energy() / 1000; //kWh
  enrgy2 = zeroIfNan(enrgy2);
  
  volt3 = pzem3.voltage();
  volt3 = zeroIfNan(volt3);
  curr3 = pzem3.current();
  curr3 = zeroIfNan(curr3);
  freq3 = pzem3.frequency();
  freq3 = zeroIfNan(freq3);
  enrgy3 = pzem3.energy() / 1000; //kWh
  enrgy3 = zeroIfNan(enrgy3);

  printSerialPZEM();
}
