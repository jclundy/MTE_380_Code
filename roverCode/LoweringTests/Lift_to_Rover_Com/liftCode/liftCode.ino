#define SERIAL_BAUD_RATE 9600
#define OUTPUT_PIN 4

int outputValue = HIGH;

void setup() {
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, outputValue);
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.println("Enter a key to drive the ouput high");
}

void loop() {
  if(Serial.available() > 0)
  {
    char ch = Serial.read();
    outputValue = !outputValue;
    Serial.print("Signal Value: ");
    Serial.print(outputValue);
    Serial.print("\n");
    digitalWrite(OUTPUT_PIN, outputValue);
  }
  
  delay(100);
}
