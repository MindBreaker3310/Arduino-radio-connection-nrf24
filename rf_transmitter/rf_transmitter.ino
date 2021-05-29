// SimpleTx - the master or the transmitter

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN   9
#define CSN_PIN 10

const byte slaveAddress[5] = {'R','x','A','A','A'};


RF24 radio(CE_PIN, CSN_PIN); // Create a Radio


unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000; // send once per second

int randomNumber = 0;

void setup() {

    Serial.begin(9600);

    Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(slaveAddress);
}

//====================

void loop() {
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) {
        send();
        prevMillis = millis();
    }
}

//====================

void send() {

    // Define 
    String str = "This is my string"; 
    
    // Length (with one extra character for the null terminator) 
    int str_len = str.length() + 1; 
    
    // Prepare the character array (the buffer) 
    char dataToSend[str_len]; 
    
    // Copy it over 
    str.toCharArray(dataToSend, str_len);
     
    radio.write( &dataToSend, sizeof(dataToSend) );

    Serial.print("Data Sent ");
    Serial.println(dataToSend);
  
}
