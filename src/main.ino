const int READING_PIN =     13;     // LED to display metering
const int TEMP_PIN_OUT =    7;      // Pin for VCC to the thermometer
                                    // For Power Save it should not be online
                                    // all the time
const int TEMP_PIN_IN =     A0;     // Input of thermometer
const int MOISTURE_PIN_IN = A1;     // Input of moisture sensor

void setup(){
  Serial.begin(9600);
  pinMode(READING_PIN, OUTPUT);
  pinMode(TEMP_PIN_OUT, OUTPUT);
}

void loop() {
  // Temperatur
  float temperatur_val = read_temperature();
  int temperatur = map(temperatur_val, 0, 410, -50, 150);
  Serial.print("Temperatur: ");
  Serial.print(temperatur);
  Serial.println(" C");
  // Moisture
  int moisture_val = read_moisture();
  Serial.print("Moisture: ");
  Serial.println(moisture_val);
  delay(5000);
}

/**
 * Read temperature from the thermometer 10 times and return the everage
 * @return {float} the everage themperature of 10 reads
 */
float read_temperature(){
  display_read(TEMP_PIN_IN);
  digitalWrite(TEMP_PIN_OUT, HIGH); // start the thermometer
  delay(500);                       // wait 0.5 sek for warmup
  float temp = 0;
  for(int i = 0; i < 10; i++){
    delay(500);                     // wait for 0.5 sek
    temp += analogRead(TEMP_PIN_IN);// read the temperature
  }
  digitalWrite(TEMP_PIN_OUT, LOW);  // stop the thermometer
  display_read_ready(TEMP_PIN_IN);
  return temp/10;                   // return the everage temperature
}

/**
 * Read moisture from sensor
 * @return {float} moisture value
 */
int read_moisture(){
  display_read(MOISTURE_PIN_IN);
  int mois = analogRead(MOISTURE_PIN_IN);
  display_read_ready(MOISTURE_PIN_IN);
  return moisture_state(mois);
}

int moisture_state(int moisture_val){
  if (moisture_val < 370){
    return 1; // to wet
  } else if (moisture_val >=370 && moisture_val < 600) {
    return 2; // perfect
  } else {
    return 3; // to dry
  }
}

/**
 * display mattering is in process
 * @param  {int} int what          What is processed (Pin Constant)
 * @return {void}
 */
void display_read(int what){
  digitalWrite(READING_PIN, HIGH);
  Serial.print("Start reading ");
  Serial.println(identify_element(what));
}

/**
 * display mattering is ready
 * @param  {int} int what          What is processed (Pin Constant)
 * @return {void}
 */
void display_read_ready(int what){
  Serial.print("Finished reading ");
  Serial.println(identify_element(what));
  digitalWrite(READING_PIN, LOW);
}

/**
 * Identify what is in process
 * @param  {int} int what          Pin Constant
 * @return {String}     Name of Element
 */
String identify_element(int what){
  String readElement;
  switch (what){
    case TEMP_PIN_IN:
      readElement = "Temperature";
      break;
    case MOISTURE_PIN_IN:
      readElement = "Moisture";
      break;
    default:
      readElement = String(what);
      break;
  }
  return readElement;
}
