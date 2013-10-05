#define START_PIN 9
#define TAG_PIN   10
#define SENSOR_PIN A5

#define INTERVAL 100
#define SERIAL_BAUDRATE 9600

#define ENABLE_COMMAND   'A'
#define RESET_COMMAND    'Z'

#define FILTER_WIDTH  3

#define WHITE_THRESHOLD  250
#define BLACK_THRESHOLD  100

float average = 0.0;

byte command;

boolean recording = false;
boolean tagged = false;

boolean startIsAllowed = false;

int readings[FILTER_WIDTH];
int readingCounter = 0;

void setup() {
  pinMode( START_PIN, OUTPUT );
  digitalWrite( START_PIN, LOW ); 
  Serial.begin( SERIAL_BAUDRATE );

  clearSerialBuffer();
}


void loop() {


  if ( Serial.available() > 0 ) { 
    command = Serial.read();
  }  

  if ( command == ENABLE_COMMAND ) {  
    startIsAllowed = true;
  } 
  
  if ( command == RESET_COMMAND ) {
    startIsAllowed = false;
    tagged = false; 
    recording = false; 
  }

  clearSerialBuffer(); 

  addReading( analogRead( SENSOR_PIN ) );
  average = updateAverage();
  
  if ( !recording ) {
    if ( average >= WHITE_THRESHOLD ) {
      if ( startIsAllowed ) {
        sendStart();
        // recording starts only when the sensor reading is WHITE
        recording = true;
        tagged = true;
      }
    }
  } 
  else {
    if ( !tagged ) {
      if ( average >= WHITE_THRESHOLD ) {
        sendTag();
        tagged = true;
      }
    } else {
      if ( average < BLACK_THRESHOLD ) {
        tagged = false;
      } 
    }
  }
}

void sendStart() {
  digitalWrite( START_PIN, HIGH );
  delay( INTERVAL );
  digitalWrite( START_PIN, LOW );
}

void sendTag() {
  if ( recording ) {
    digitalWrite( TAG_PIN, HIGH );
    delay( INTERVAL );
    digitalWrite( TAG_PIN, LOW );
  }
}

void clearSerialBuffer() {
  while( Serial.available() > 0 ) {
    Serial.read(); 
  }
  command = '\0';
}

void addReading( int readingValue ) {
  readings[ readingCounter++ ] = readingValue;
  if ( readingCounter >= FILTER_WIDTH ) {
    readingCounter = 0;
  }
}

float updateAverage() {
  int sum = 0;
  for ( int i = 0; i < FILTER_WIDTH; i++ ) {
    sum += readings[i];
  }
  return sum / FILTER_WIDTH;
}



