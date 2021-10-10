int PUL = 9;
byte PWM_PIN = 3;

int min = 80;
int max = 32000; // cureent max max is 40000
float freq = 100;
int pwm_value;
float diff;
 
void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(PWM_PIN, INPUT);
  //Serial.begin(115200);
}
 
void loop() {
  pwm_value = pulseIn(PWM_PIN, HIGH);
  diff = map(pwm_value, 994, 1990, -10, 10);
  //Serial.println(diff);
  if (diff > 5) { // when remotes input is pushed up run  motor
    run();
  } 
}

void run(void) {
  float time = ftoms(freq);

  while (freq < 32000) {
    digitalWrite(PUL, HIGH);
    delayMicroseconds(time);
    digitalWrite(PUL, LOW);
    delayMicroseconds(time);
    time = ftoms(freq);
    freq = freq + 0.5;
    //Serial.println(freq);
  }
  while (freq > 0) {
    digitalWrite(PUL, HIGH);
    delayMicroseconds(time);
    digitalWrite(PUL, LOW);
    delayMicroseconds(time);
    time = ftoms(freq);
    freq = freq - 0.5;
  }
}

float ftoms(float freq) {
  return (1/freq)*1000000.0;
}