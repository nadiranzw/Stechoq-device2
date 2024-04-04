#include <PZEM004Tv30.h>

#if !defined(pRX) && !defined(pTX)
#define pRX 26
#define pTX 25
#endif

#if !defined(pzemSerial)
#define pzemSerial Serial2
#endif 

#if defined(ESP32)
PZEM004Tv30 pzems[2];
#elif defined(ESP8266)
//PZEM004Tv30 pzems[i](Serial1);
#else
PZEM004Tv30 pzems(pzemSerial);
#endif

struct var{
  float volt, curr, freq, enrgy, power, pf;
};

struct var dev[2];

int i; // index 

void printSerialPZEM(){
  Serial.printf("Voltage    : %.2f\ V\n", dev[i].volt);
  Serial.printf("Current    : %.2f\ A\n", dev[i].curr);
  Serial.printf("Frequency  : %.2f\ Hz\n", dev[i].freq);
  Serial.printf("Energy     : %.2f\ kWh\n", dev[i].enrgy);
  Serial.printf("Power      : %.2f\ W\n", dev[i].power);
  Serial.printf("PF         : %.2f\ \n\n", dev[i].pf);
}


void setup(){
  Serial.begin(115200);

  for(int i=0; i<=2; i++){
    #if defined(ESP32)
    pzems[i] = PZEM004Tv30(pzemSerial, pRX, pTX, 0x10 + i);
    #endif
  }
}

void loop(){
  for (i=0; i<=2; i++){
    Serial.printf("---------PZEM %d\---------", i);
    Serial.print("Address: ");
    Serial.println(pzems[i].getAddress(), HEX);

    dev[i].volt = pzems[i].voltage();
    dev[i].curr = pzems[i].current();
    dev[i].freq = pzems[i].frequency();
    dev[i].enrgy = pzems[i].energy();
    dev[i].power = pzems[i].power();
    dev[i].pf = pzems[i].pf();

    if(isnan(dev[i].volt)){
        dev[i].volt = 0;
    } if (isnan(dev[i].curr)){
        dev[i].curr = 0;
    } if (isnan(dev[i].freq)){
        dev[i].freq = 0;
    } if (isnan(dev[i].enrgy)){
        dev[i].enrgy = 0;
    } if (isnan(dev[i].power)){
        dev[i].power = 0;
    } if (isnan(dev[i].pf)){
        dev[i].pf = 0;
    }

    printSerialPZEM();
    delay(2000);
  }
}