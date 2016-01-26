int StatusPin = 13;
int MousturePin = A0;
int Mousture = 0;
void setup() {
  pinMode(StatusPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Mousture = analogRead(MousturePin);
  Serial.println(Mousture);
  
  if (Mousture < 370){
    digitalWrite(StatusPin, HIGH); // to wet
  } else if (Mousture >=370 && Mousture < 600) {
    digitalWrite(StatusPin, LOW); // perfect
  } else {
    digitalWrite(StatusPin, HIGH); // to dry
  }

  delay(60 * 1000);
}
