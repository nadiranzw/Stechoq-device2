#include <PZEM004Tv30.h>

#if !defined(pRX) && !defined(pTX)
#define pRX 25
#define pTX 26
#endif

#if !defined(PZEM_SERIAL)
#define PZEM_SERIAL Serial2
#endif

#define NUM_PZEMS 3

PZEM004Tv30 pzems[NUM_PZEMS];

// Uncomment USE_SOFTWARE_SERIAL in order to enable Softare serial
// #define USE_SOFTWARE_SERIAL

#if defined(USE_SOFTWARE_SERIAL) && defined(ESP32)
    #error "Can not use SoftwareSerial with ESP32"
#elif defined(USE_SOFTWARE_SERIAL)
    #include <SoftwareSerial.h>
    SoftwareSerial pzemSWSerial(pRX, pTX);
#endif


void setup() {
    Serial.begin(115200);

    // For each PZEM, initialize it
    for(int i = 0; i < NUM_PZEMS; i++){
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
    for(int i = 0; i < NUM_PZEMS; i++){
        Serial.print("PZEM ");
        Serial.print(i);
        Serial.print(" - Address:");
        Serial.println(pzems[i].getAddress(), HEX);
        Serial.println("===================");

        float voltage = pzems[i].voltage();
        float current = pzems[i].current();
        float power = pzems[i].power();
        float energy = pzems[i].energy();
        float frequency = pzems[i].frequency();
        float pf = pzems[i].pf();

          if(isnan(voltage)){
            voltage = 0;
        } if (isnan(current)) {
            current = 0;
        } if (isnan(power)) {
            power = 0;
        } if (isnan(energy)) {
            energy = 0;
        } if (isnan(frequency)) {
            frequency = 0;
        } if (isnan(pf)) {
            pf = 0;
        }

        Serial.print("Voltage   : ");      Serial.print(voltage);      Serial.println(" V");
        Serial.print("Current   : ");      Serial.print(current);      Serial.println(" A");
        Serial.print("Power     : ");      Serial.print(power);        Serial.println(" W");
        Serial.print("Energy    : ");      Serial.print(energy,3);     Serial.println(" kWh");
        Serial.print("Frequency : ");      Serial.print(frequency, 1); Serial.println(" Hz");
        Serial.print("PF        : ");      Serial.println(pf);
        Serial.println();
    }

    Serial.println();
    delay(2000);