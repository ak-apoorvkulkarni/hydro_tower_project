const int relayPin = 23 ;

// time values in milliseconds
const unsigned long ON_TIME  = 5UL * 60UL * 1000UL;        // 5 minutes
const unsigned long OFF_TIME = 4UL * 60UL * 60UL * 1000UL; // 4 hours

bool pumpState = false;   // false = OFF, true = ON
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);

  // relay OFF at start
  digitalWrite(relayPin, HIGH);   // active LOW relay
  pumpState = false;
  previousMillis = millis();

  Serial.println("Pump automation started");
  Serial.println("Pump OFF for 4 hours, then ON for 5 minutes");
}

void loop() {
  unsigned long currentMillis = millis();

  if (!pumpState && (currentMillis - previousMillis >= OFF_TIME)) {
    // turn pump ON
    digitalWrite(relayPin, LOW);   // active LOW relay
    pumpState = true;
    previousMillis = currentMillis;

    Serial.println("Pump ON");
  }

  if (pumpState && (currentMillis - previousMillis >= ON_TIME)) {
    // turn pump OFF
    digitalWrite(relayPin, HIGH);  // active LOW relay
    pumpState = false;
    previousMillis = currentMillis;

    Serial.println("Pump OFF");
  }
}