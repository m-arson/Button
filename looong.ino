int waitTime = 400;
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
  pinMode(13, OUTPUT);
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
        int f = 0;
        while (true) {
          if (!digitalRead(A1)) {
            ++f;
            if (f > 2000) {
              digitalWrite(13, HIGH);
            }
            delay(1);
          }
          else {
            digitalWrite(13, LOW);
            break;
          }
        }
      }
      else {
        if (count == 2) {
          blinks(3);
        }
        else if (count == 1) {
          blinks(1);
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
void blinks(int times) {
  for(int i = 0; i < times; ++i) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
  }
}
