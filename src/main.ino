#define LEDPIN        13
#define TEMP_PIN_OUT  7
#define TEMP_PIN_IN   A0

void setup(){
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  pinMode(TEMP_PIN_OUT, OUTPUT);
  digitalWrite(TEMP_PIN_OUT, HIGH);
}

void loop() {
  digitalWrite(LEDPIN, HIGH);
  float temperatur_val = read_temp();
  int temperatur = map(temperatur_val, 0, 410, -50, 150);
  digitalWrite(LEDPIN, LOW);
  Serial.print(temperatur);
  Serial.print("C - ");
  Serial.print(temperatur_val);
  Serial.println(" read");
  delay(2000);
}

int read_temp(){
  int temp = 0;
  for(int i = 0; i < 10; i++){
    temp += analogRead(A0);
    delay(100);
  }
  return temp/10;
}
