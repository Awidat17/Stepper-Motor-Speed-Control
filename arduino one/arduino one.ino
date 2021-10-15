int switchC = 3; // input of controller switch C
int switchD = 5; // input of controller switch D
// below outputs will be used as a 2-bit binary ouput
int outA = 7; // switch C output first bit
int outB = 8; // switch C output second bit
int outD = 9; // switch D output bit

int sigC; // pwm value of switchC 
int sigD; // pwm value of switchD 

void setup() {
  // put your setup code here, to run once:
  pinMode(switchC, INPUT);
  pinMode(switchD, INPUT);

  pinMode(outA, OUTPUT);
  pinMode(outB, OUTPUT);
  pinMode(outD, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  sigC = pulseIn(switchC, HIGH); // input pwm signal from receiver
  sigD = pulseIn(switchD, HIGH); // input pwm signal from receiver
  //Serial.println(sig);
  if (sigD > 1500) {
    digitalWrite(outD, HIGH);
    Serial.println("BOOST");
  } else if (sigC > 1900) {
    digitalWrite(outA, HIGH);
    digitalWrite(outB, HIGH);
    digitalWrite(outD, LOW);
    Serial.println("top");
  } else if (sigC < 1000 && sigC > 900) {
    digitalWrite(outA, LOW);
    digitalWrite(outB, LOW);
    digitalWrite(outD, LOW);
    Serial.println("low");
  } else {
    digitalWrite(outA, HIGH);
    digitalWrite(outB, LOW);
    digitalWrite(outD, LOW);
    Serial.println("mid");
  }
  delay(50);


}
