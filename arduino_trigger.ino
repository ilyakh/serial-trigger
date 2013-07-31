#define TARGET_PIN_NR 9

#define VOLTAGE_LOW_LEVEL 0
#define VOLTAGE_HIGH_LEVEL 128

#define INTERVAL 40
#define SERIAL_BAUDRATE 9600


byte command;


void setup() {

  
 pinMode( TARGET_PIN_NR, OUTPUT ); 
 Serial.begin( SERIAL_BAUDRATE );
 
 clearSerialBuffer();
 
}


void loop() {
  
  if ( Serial.available() > 0 ) { 
    
    command = Serial.read();
    
    if ( command == 'A' ) {
      // pwm signal at lower voltage
      analogWrite( TARGET_PIN_NR, VOLTAGE_HIGH_LEVEL );
      delay( INTERVAL );
      analogWrite( TARGET_PIN_NR, VOLTAGE_LOW_LEVEL );
    
    } else {
      // digital signal at max voltage
      digitalWrite( TARGET_PIN_NR, HIGH );
      delay( INTERVAL );
      digitalWrite( TARGET_PIN_NR, LOW );  
    }
    
    clearSerialBuffer(); // clears all commands received while the trigger was on
    
  }
}


void clearSerialBuffer() {
 while( Serial.available() > 0 ) {
   Serial.read(); 
 }
}
