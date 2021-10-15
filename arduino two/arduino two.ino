int bitA = 27; // ouput bit A from uno
int bitB = 28; // ouput bit B from uno
int bitD = 29; // ouput bit B from uno

int PUL = 7;
int readA; // read of bitA
int readB; // read of bitB
int readD; // read of bitB

float freq = 80;
float time;

void setup() {
  pinMode(bitA, INPUT);
  pinMode(bitB, INPUT);
  pinMode(bitD, INPUT);
  pinMode(PUL, OUTPUT);

  //Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (1) {
    readA = digitalRead(bitA);
    readB = digitalRead(bitB);
    readD = digitalRead(bitD);
    time = ftoms(freq);

    if (readD) {
      boost();
    } 

    if (freq > 19500 && readB) { // max controlled (current controlled max 19500)
      digitalWrite(PUL, HIGH);
      delayMicroseconds(time);
      digitalWrite(PUL, LOW);
      delayMicroseconds(time);
    } else if (readA && readB) {
      digitalWrite(PUL, HIGH);
      delayMicroseconds(time);
      digitalWrite(PUL, LOW);
      delayMicroseconds(time);
      freq = freq + 0.5;
    } else if (readA) {
      digitalWrite(PUL, HIGH);
      delayMicroseconds(time);
      digitalWrite(PUL, LOW);
      delayMicroseconds(time);
    } else {
      digitalWrite(PUL, HIGH);
      delayMicroseconds(time);
      digitalWrite(PUL, LOW);
      delayMicroseconds(time);
      freq = freq - 0.5;
    }
  }
}

void boost(void) {
  while (freq < 32000) { // max uncontrolled (current max 3200)
    digitalWrite(PUL, HIGH);
    delayMicroseconds(time);
    digitalWrite(PUL, LOW);
    delayMicroseconds(time);
    time = ftoms(freq);
    freq = freq + 0.5;
  }
  while (freq > 29000) { // super slow deceleration period ("high hold") 
    digitalWrite(PUL, HIGH);
    delayMicroseconds(time);
    digitalWrite(PUL, LOW);
    delayMicroseconds(time);
    time = ftoms(freq);
    freq = freq - 0.03;
  }
  while (freq > 19000) { // fast deceleration to controlled
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