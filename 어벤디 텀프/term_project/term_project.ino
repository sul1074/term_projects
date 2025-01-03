// 궤도 DC모터 핀 설정
const int leftMotorPWM = 9;   // 왼쪽 모터 속도 제어 (PWM 핀)
const int leftMotorDIR1 = 34;    // 왼쪽 모터 방향 제어 핀 1
const int leftMotorDIR2 = 36;   // 왼쪽 모터 방향 제어 핀 2

const int rightMotorPWM = 10;   // 오른쪽 모터 속도 제어 (PWM 핀)
const int rightMotorDIR1 = 38;   // 오른쪽 모터 방향 제어 핀 1
const int rightMotorDIR2 = 40;    // 오른쪽 모터 방향 제어 핀 2

// 물 펌프 DC모터 핀 설정. L39DN 모터드라이버로 제어
const int waterPumpPWM = 8; // 물 펌프 DC모터 속도 제어 (PMW)
const int waterEn = 32; // 물 펌프 DC모터 Enable
const int waterPumpDIR = 33; // 물 펌프 DC모터 방향 제어(DIR)
// 물 펌프 토글 불리언
bool isWaterPumpToggled = false;

// RGB LED 핀 설정
const int RGB_LED[] = {5, 6, 7};
bool isRGBToggled = false;

void setup() {
  // 궤도 DC모터 초기화
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(leftMotorDIR1, OUTPUT);
  pinMode(leftMotorDIR2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(rightMotorDIR1, OUTPUT);
  pinMode(rightMotorDIR2, OUTPUT);

  // 물 펌프 DC모터 핀 초기화
  pinMode(waterPumpPWM, OUTPUT);
  pinMode(waterPumpDIR, OUTPUT);
  pinMode(waterEn, OUTPUT);

  // RGB LED 핀 초기화
  for (int i = 0; i < 3; i++) {
    pinMode(RGB_LED[i], OUTPUT);
  }

  stopMotors();
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  if (Serial1.available() > 0) {
    char command = Serial1.read();
    handleCommand(command);
  }
}

// 앞으로 이동
void moveForward(int speed) {
  digitalWrite(leftMotorDIR1, HIGH);
  digitalWrite(leftMotorDIR2, LOW);
  analogWrite(leftMotorPWM, speed);

  digitalWrite(rightMotorDIR1, LOW);
  digitalWrite(rightMotorDIR2, HIGH);
  analogWrite(rightMotorPWM, speed);

  Serial.println("Moving forward");
}

// 뒤로 이동
void moveBackward(int speed) {
  digitalWrite(leftMotorDIR1, LOW);
  digitalWrite(leftMotorDIR2, HIGH);
  analogWrite(leftMotorPWM, speed);

  digitalWrite(rightMotorDIR1, HIGH);
  digitalWrite(rightMotorDIR2, LOW);
  analogWrite(rightMotorPWM, speed);

  Serial.println("Moving backward");
}

// 왼쪽 회전
void turnLeft(int leftSpeed, int rightSpeed) {
  digitalWrite(leftMotorDIR1, HIGH);
  digitalWrite(leftMotorDIR2, LOW);
  analogWrite(leftMotorPWM, leftSpeed);

  digitalWrite(rightMotorDIR1, LOW);
  digitalWrite(rightMotorDIR2, HIGH);
  analogWrite(rightMotorPWM, rightSpeed);

  Serial.println("Turning left");
}

// 오른쪽 회전
void turnRight(int leftSpeed, int rightSpeed) {
  digitalWrite(leftMotorDIR1, HIGH);
  digitalWrite(leftMotorDIR2, LOW);
  analogWrite(leftMotorPWM, leftSpeed);

  digitalWrite(rightMotorDIR1, LOW);
  digitalWrite(rightMotorDIR2, HIGH);
  analogWrite(rightMotorPWM, rightSpeed);

  Serial.println("Turning right");
}

// 정지
void stopMotors() {
  digitalWrite(leftMotorDIR1, LOW);
  digitalWrite(leftMotorDIR2, LOW);
  analogWrite(leftMotorPWM, 0);

  digitalWrite(rightMotorDIR1, LOW);
  digitalWrite(rightMotorDIR2, LOW);
  analogWrite(rightMotorPWM, 0);

  Serial.println("Motors stopped");
}

void toggleWaterPump() {
  isWaterPumpToggled = !isWaterPumpToggled;

  if (isWaterPumpToggled) {
    digitalWrite(waterEn, HIGH);
    digitalWrite(waterPumpDIR, HIGH);
    digitalWrite(waterPumpPWM, LOW);
    Serial.println("Water Pump On (Forward)");
  } 
  else {
    digitalWrite(waterPumpPWM, HIGH);
    digitalWrite(waterEn, LOW);
    Serial.println("Water Pump Off");
  }
}

void toggleRGBLED() {
  isRGBToggled = !isRGBToggled;

  if (isRGBToggled) {
    analogWrite(RGB_LED[0], 0); // Red
    analogWrite(RGB_LED[1], 0); // Green
    analogWrite(RGB_LED[2], 0); // Blue
    Serial.println("RGB LED On (White)");
  } 
  else {
    analogWrite(RGB_LED[0], 255); // Red
    analogWrite(RGB_LED[1], 255); // Green
    analogWrite(RGB_LED[2], 255); // Blue
    Serial.println("RGB LED Off");
  }
}

// 명령에 따른 동작 제어
void handleCommand(char command) {
  switch (command) {
    case 'w': moveForward(255); break;
    case 's': moveBackward(255); break;
    case 'a': turnLeft(200, 255); break;
    case 'd': turnRight(255, 200); break;
    case 'h': stopMotors(); break;

    case 't': toggleWaterPump(); break;
    case 'x': toggleRGBLED(); break;
    default: Serial.println("Invalid command"); break;
  }
}