#define WALL_DIRECTION_PIN A1
#define SPOOL_UP_BUTTON_PIN A2
#define GO_AHEAD_PIN A3

int wall_direction_value = 0;
int spool_up_button_value = 0;
int go_ahead_value = 0;

int new_wall_direction_value = 0;
int new_spool_up_button_value = 0;
int new_go_ahead_value = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(WALL_DIRECTION_PIN, INPUT);
  pinMode(SPOOL_UP_BUTTON_PIN, INPUT);
  pinMode(GO_AHEAD_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(new_wall_direction_value == wall_direction_value && new_spool_up_button_value == spool_up_button_value  && new_go_ahead_value == go_ahead_value) {
    new_wall_direction_value = digitalRead(WALL_DIRECTION_PIN);
    new_spool_up_button_value = digitalRead(SPOOL_UP_BUTTON_PIN);
    new_go_ahead_value = digitalRead(GO_AHEAD_PIN);
  }
  
  wall_direction_value = new_wall_direction_value;
  spool_up_button_value = new_spool_up_button_value;
  go_ahead_value = new_go_ahead_value;
  
  Serial.print("WALL_DIRECTION: ");
  Serial.print(wall_direction_value);
  Serial.print("\n");

  Serial.print("SPOOL_UP_BUTTON_PIN: ");
  Serial.print(spool_up_button_value);
  Serial.print("\n");
  
  Serial.print("GO_AHEAD_PIN: ");
  Serial.print(go_ahead_value);
  Serial.print("\n");
  
  delay(100);
}
