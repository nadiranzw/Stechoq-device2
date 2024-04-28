#include <PZEM004Tv30.h>

#if !defined(pRX) && !defined(pTX)
#define pRX 25
#define pTX 26
#endif

#if !defined(PZEM_SERIAL)
#define PZEM_SERIAL Serial2
#endif

#define num 3
PZEM004Tv30 pzems[num];

// Uncomment USE_SOFTWARE_SERIAL in order to enable Softare serial
// #define USE_SOFTWARE_SERIAL

#if defined(USE_SOFTWARE_SERIAL) && defined(ESP32)
    #error "Can not use SoftwareSerial with ESP32"
#elif defined(USE_SOFTWARE_SERIAL)
    #include <SoftwareSerial.h>
    SoftwareSerial pzemSWSerial(pRX, pTX);
#endif

int i;
struct var{
  float volt, curr, freq, enrgy, power, pf;
} dev[num];


void printSerial(){
  Serial.printf("Voltage    : %.2f\ V\n", dev[i].volt);
  Serial.printf("Current    : %.2f\ A\n", dev[i].curr);
  Serial.printf("Frequency  : %.2f\ Hz\n", dev[i].freq);
  Serial.printf("Energy     : %.2f\ kWh\n", dev[i].enrgy);
  Serial.printf("Power      : %.2f\ W\n", dev[i].power);
  Serial.printf("PF         : %.2f\ \n\n", dev[i].pf);
}


void setup() {
    Serial.begin(115200);

    // For each PZEM, initialize it
    for(int i = 0; i < num; i++){
    #if defined(USE_SOFTWARE_SERIAL)
            // Initialize the PZEMs with Software Serial
            pzems[i] = PZEM004Tv30(pzemSWSerial, 0x10 + i);
    #elif defined(ESP32)
            // Initialize the PZEMs with Hardware Serial2 on RX/TX pins 16 and 17
            pzems[i] = PZEM004Tv30(PZEM_SERIAL, pRX, pTX, 0x10 + i);
    #else
            pzems[i] = PZEM004Tv30(PZEM_SERIAL, 0x10 + i);
    #endif
    }
}

void loop() {
    for(i = 0; i < num; i++){
        Serial.print("PZEM ");
        Serial.print(i);
        Serial.print(" - Address:");
        Serial.println(pzems[i].getAddress(), HEX);
        Serial.println("===================");

        dev[i].volt = pzems[i].voltage();
        dev[i].curr = pzems[i].current();
        dev[i].freq = pzems[i].frequency();
        dev[i].power = pzems[i].power();
        dev[i].enrgy = pzems[i].energy();
        dev[i].pf = pzems[i].pf();

          if(isnan(dev[i].volt)){
            dev[i].volt = 0;
        } if (isnan(dev[i].curr)) {
            dev[i].curr = 0;
        } if (isnan(dev[i].power)) {
            dev[i].power = 0;
        } if (isnan(dev[i].enrgy)) {
            dev[i].enrgy = 0;
        } if (isnan(dev[i].freq)) {
            dev[i].freq = 0;
        } if (isnan(dev[i].pf)) {
            dev[i].pf = 0;
        }
        printSerial();
    }
    delay(2000);
}