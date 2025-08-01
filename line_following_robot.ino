// Motor Pins
#define ENA 9
#define ENB 10
#define IN1 7
#define IN2 8
#define IN3 5
#define IN4 6

// Sensor Pins
#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A4

// Threshold for black/white detection
int threshold = 500; // You might need to calibrate this

void setup() {
  // Motor setup
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Sensor setup
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int s1 = analogRead(S1);
  int s2 = analogRead(S2);
  int s3 = analogRead(S3);
  int s4 = analogRead(S4);
  int s5 = analogRead(S5);

  // Convert to digital (black = LOW, white = HIGH)
  bool s1Black = s1 < threshold;
  bool s2Black = s2 < threshold;
  bool s3Black = s3 < threshold;
  bool s4Black = s4 < threshold;
  bool s5Black = s5 < threshold;

  // Debug
  Serial.print(s1Black); Serial.print(" ");
  Serial.print(s2Black); Serial.print(" ");
  Serial.print(s3Black); Serial.print(" ");
  Serial.print(s4Black); Serial.print(" ");
  Serial.println(s5Black);

  // Movement logic
  if (s3Black && !s1Black && !s2Black && !s4Black && !s5Black) {
    // Centered - go straight
    moveForward();
  }
  else if (s2Black || s1Black) {
    // Turn left
    turnLeft();
  }
  else if (s4Black || s5Black) {
    // Turn right
    turnRight();
  }
  else {
    // Lost - stop or search
    stopMotors();
  }

  delay(10);
}

// Movement functions
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); // Left motor backward
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);  // Right motor forward
  analogWrite(ENA, 120);
  analogWrite(ENB, 150);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);  // Left motor forward
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); // Right motor backward
  analogWrite(ENA, 150);
  analogWrite(ENB, 120);
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
