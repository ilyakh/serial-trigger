#define TARGET_PIN_NR 9

#define VOLTAGE_LOW_LEVEL 0
#define VOLTAGE_HIGH_LEVEL 128


#define INTERVAL 3000

void setup() {
 pinMode( TARGET_PIN_NR, OUTPUT ); 
}

void loop() {
  analogWrite( TARGET_PIN_NR, VOLTAGE_HIGH_LEVEL );
  
  delay( INTERVAL );
  
  analogWrite( TARGET_PIN_NR, VOLTAGE_LOW_LEVEL );
  
  delay( INTERVAL );
}
