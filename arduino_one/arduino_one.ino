int switchA = 2; // input of controller switch A
int switchC = 3; // input of controller switch C
int switchD = 5; // input of controller switch D
// below outputs will be used as a 2-bit binary output
int outA = 7; // switch C output first bit
int outB = 8; // switch C output second bit
int outD = 9; // switch D output bit
int outRes = 10; // switch A output bit

int sigA; // pwm value of switchA 
int sigC; // pwm value of switchC 
int sigD; // pwm value of switchD 

void setup() {
  // put your setup code here, to run once:
  pinMode(switchC, INPUT);
  pinMode(switchD, INPUT);
  pinMode(switchA, INPUT);

  pinMode(outRes, OUTPUT);
  pinMode(outA, OUTPUT);
  pinMode(outB, OUTPUT);
  pinMode(outD, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  sigA = pulseIn(switchC, HIGH); // input pwm signal from receiver
  sigC = pulseIn(switchC, HIGH); // input pwm signal from receiver
  sigD = pulseIn(switchD, HIGH); // input pwm signal from receiver
  //Serial.println(sig);
  if (sigA > 1500) {
    digitalWrite(outRes, HIGH);
    digitalWrite(outD, LOW);
    Serial.println("BOOST");
  } else if (sigD > 1500) {
    digitalWrite(outD, HIGH);
    digitalWrite(outRes, LOW);
    Serial.println("BOOST");
  } else if (sigC > 1900) {
    digitalWrite(outA, HIGH);
    digitalWrite(outB, HIGH);
    digitalWrite(outD, LOW);
    digitalWrite(outRes, LOW);
    Serial.println("top");
  } else if (sigC < 1000 && sigC > 900) {
    digitalWrite(outA, LOW);
    digitalWrite(outB, LOW);
    digitalWrite(outD, LOW);
    digitalWrite(outRes, LOW);
    Serial.println("low");
  } else {
    digitalWrite(outA, HIGH);
    digitalWrite(outB, LOW);
    digitalWrite(outD, LOW);
    digitalWrite(outRes, LOW);
    Serial.println("mid");
  }
  delay(10);


}
