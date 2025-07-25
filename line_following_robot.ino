// Line Sensor Pins
#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A4

// Motor Driver Pins
#define ENA 9
#define IN1 8
#define IN2 7

#define ENB 10
#define IN3 6
#define IN4 5

int baseSpeed = 150;    // Adjust this for your motor torque
float Kp = 30;           // Proportional constant
float Kd = 20;           // Derivative constant
int lastError = 0;

void setup() {
  // Sensor Inputs
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  // Motor Outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  // Read sensors as analog
  int s[5];
  s[0] = analogRead(S1);
  s[1] = analogRead(S2);
  s[2] = analogRead(S3);
  s[3] = analogRead(S4);
  s[4] = analogRead(S5);

  // Threshold the sensors (black = 0, white = 1)
  for (int i = 0; i < 5; i++) {
    if (s[i] > 500) s[i] = 1;  // white surface
    else s[i] = 0;             // black line
  }

  // Calculate error based on position
  int error = 0;

  if (s[0] == 0) error = -4;
  else if (s[1] == 0) error = -2;
  else if (s[2] == 0) error = 0;
  else if (s[3] == 0) error = 2;
  else if (s[4] == 0) error = 4;
  else error = lastError;  // if all white, use last known error

  int correction = Kp * error + Kd * (error - lastError);
  lastError = error;

  // Compute motor speeds
  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // Move motors with PWM
  moveMotors(leftSpeed, rightSpeed);
}

void moveMotors(int leftPWM, int rightPWM) {
  // Left motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, leftPWM);

  // Right motor forward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, rightPWM);
}
