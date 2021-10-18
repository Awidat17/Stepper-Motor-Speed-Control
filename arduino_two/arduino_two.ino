int bitA = 27; // output bit A from uno
int bitB = 28; // output bit B from uno
int bitD = 29; // output bit B from uno
int bitRes = 33; // output bit from switch C

int PUL = 7;
int readA; // read of bitA
int readB; // read of bitB
int readD; // read of bitB
int readRes; // read of bitRes

float freq = 80;
float time;

void setup() {
  pinMode(bitA, INPUT);
  pinMode(bitB, INPUT);
  pinMode(bitD, INPUT);
  pinMode(bitRes, INPUT);
  pinMode(PUL, OUTPUT);

  //Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (1) {
    readA = digitalRead(bitA);
    readB = digitalRead(bitB);
    readD = digitalRead(bitD);
    readRes = digitalRead(bitRes);
    time = ftoms(freq);

    if (readRes) {
      freq = 1000;
    } else if (readD) {
      boost();
    } else if (freq > 19500 && readB) { // max controlled (current controlled max 19500)
      digitalWrite(PUL, HIGH);
      delayMicroseconds(time);
      digitalWrite(PUL, LOW);
      delayMicroseconds(time);
    } else if (readA && readB) {
      digitalWrite(PUL, HIGH);
      delayMicroseconds(time);
      digitalWrite(PUL, LOW);
      delayMicroseconds(time);
      freq = freq + rate(freq);
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
      freq = freq + rate(freq);
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

int rate(float frq) {
  if (frq > 5000) {
    return 0.5;
  } else if (frq > 4000) {
    return 1;
  } else if (frq > 3000) {
    return 2;
  } else if (frq > 2000) {
    return 3;
  } else if (frq > 1500) {
    return 5;
  }
}
