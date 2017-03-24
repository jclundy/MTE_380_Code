#define TEST_PIN 3
#define LEFT_PIN 2
#define RIGHT_PIN 4
// left and right are 2 and 4
void setup() {
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
  pinMode(TEST_PIN, OUTPUT);
  digitalWrite(TEST_PIN, LOW);
}

void loop() {
  int val = digitalRead(LEFT_PIN);
  digitalWrite(TEST_PIN, val);
}
