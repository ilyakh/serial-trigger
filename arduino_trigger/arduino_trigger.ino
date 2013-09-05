#define TARGET_PIN_NR 9

#define INTERVAL 40
#define SERIAL_BAUDRATE 76800


byte command;


void setup() {
  // selects the output pin (towards the ADC()
  pinMode( TARGET_PIN_NR, OUTPUT ); 
  // begins the communication on a proper baudrate
  // see (uri: 
  Serial.begin( SERIAL_BAUDRATE );
  
  // clears starup noise from the serial buffer
  clearSerialBuffer();
}


void loop() {

  if ( Serial.available() > 0 ) { 
    command = Serial.read();

    if ( command == 'A' ) {
      // reacts only to 'A', to make cancel out the noise
      digitalWrite( TARGET_PIN_NR, HIGH );
      delay( INTERVAL );
      digitalWrite( TARGET_PIN_NR, LOW );  

    }

    // clears all characters in the buffer to avoid 
    // time accumulation (does not exceed 40 ms for each trigger call)
    clearSerialBuffer(); 
  }
}


void clearSerialBuffer() {
  while( Serial.available() > 0 ) {
    Serial.read(); 
  }
}

