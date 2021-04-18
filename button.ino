int waitTime = 250;
int pressDelay = 50;
unsigned long waitTime_buff = 0;
unsigned long state_time = 0;
int count = 0;
bool s = false, t = false;
bool state = HIGH;
bool read;

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT_PULLUP);
}
void loop() {
  read = digitalRead(A1);
  if (read == LOW && state == HIGH && s == false) {
    s = true;
    waitTime_buff = millis();
  }
  if (read == LOW && state == HIGH) {
    t = true;
    state_time = millis();
  }
  if (s == true) {
    if ((unsigned long)(millis() - waitTime_buff) > waitTime) {
      if (!digitalRead(A1)) {
        Serial.println("Long Press");
      }
      else {
        if (count == 2) {
          Serial.println("Double Clicks");
        }
        else if (count == 1) {
          Serial.println("Just Clicks");
        }
      }
      count = 0;
      s = false;
    }
  }
  if (t == true) {
    if ((unsigned long)(millis() - state_time) > pressDelay) {
      count++;
      t = false;
    }
  }
  state = read;
}
