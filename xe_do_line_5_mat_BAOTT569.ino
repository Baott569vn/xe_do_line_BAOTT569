/*Mô Tả Chương Trình - Điều Khiển Robot Di Động với Cảm Biến Đường Dẫn

Tên Chương Trình: xe_do_line_5_mat_BAOTT569.ino

Tác Giả: [BAOTT569]

Ngày Sửa Đổi Cuối Cùng: [19/12/2023]

Mô Tả:
Chương trình RobotControlPathSensor.ino là một đoạn mã Arduino được tạo ra để điều khiển một robot
di động dựa trên dữ liệu đọc từ các cảm biến đường dẫn.
Chương trình này cung cấp khả năng cho robot thực hiện các hành động như tiến thẳng, lùi, quẹo trái,
và quẹo phải tùy thuộc vào thông tin thu được từ môi trường xung quanh.*/

// Khai báo các chân cảm biến
const size_t SENSOR_PINS[] = {A0, A1, A2, A3, A4};
int sensorValues[] = {0, 0, 0, 0, 0};

unsigned long previousMillis = 0;
const long interval = 2;

size_t numSensors = sizeof(SENSOR_PINS) / sizeof(SENSOR_PINS[0]);
long int concatenatedNumber = 0;

byte xnxx;

// Cấu trúc để lưu trữ chân điều khiển động cơ
struct MotorPins
{
  byte en, in1, in2;
};

// Cấu trúc lưu trữ thông tin về động cơ
struct
{
  MotorPins motorA{8, 7, 6};
  MotorPins motorB{3, 5, 4};
  byte maxSpeed = 160;
  byte maxSpeedTurn = 160;
} motorData;

// Cấu trúc lưu trữ các điều kiện và hành động
struct DirectionMapping
{
  long int condition;
  void (*action)(byte, byte, byte);
  byte parameters[3];
};

void notLine(byte, byte, byte);
void straitsBack(byte, byte, byte);
void leftRight(byte, byte, byte);

// Mảng chứa các điều kiện và hành động tương ứng
DirectionMapping directionMappings[] = {
    {11111, notLine, {0, 0, 0}},

    {10001, straitsBack, {1, 0, 0}},
    {11011, straitsBack, {1, 0, 0}},
    {0, straitsBack, {1, 0, 0}},

    {11110, leftRight, {0, 1, 0}},
    {11100, leftRight, {0, 1, 0}},
    {11101, leftRight, {0, 1, 0}},
    {11000, leftRight, {0, 1, 0}},
    {10000, leftRight, {0, 1, 0}},
    // {11001, leftRight, {0, 1, 0}}, //??
    {11001, straitsBack, {1, 0, 0}}, //??

    {10011, straitsBack, {1, 0, 0}}, //??
    // {10011, leftRight, {0, 1, 0}}, //??
    {10111, leftRight, {1, 0, 0}},
    {1111, leftRight, {1, 0, 0}},
    {111, leftRight, {1, 0, 0}},
    {11, leftRight, {1, 0, 0}},
    {1, leftRight, {1, 0, 0}},
};
void setup()
{
  Serial.begin(115200);
  // Thiết lập chân điều khiển động cơ và cảm biến
  pinMode(motorData.motorA.en, OUTPUT);
  pinMode(motorData.motorA.in1, OUTPUT);
  pinMode(motorData.motorA.in2, OUTPUT);
  pinMode(motorData.motorB.en, OUTPUT);
  pinMode(motorData.motorB.in1, OUTPUT);
  pinMode(motorData.motorB.in2, OUTPUT);

  pinMode(A5, INPUT);

  for (size_t i{0}; i < numSensors; ++i)
  {
    pinMode(SENSOR_PINS[i], INPUT);
    digitalWrite(SENSOR_PINS[i], 0);
  }
  delay(2000);
}

void readSensors()
{
  // Đọc giá trị từ cảm biến và giới hạn chúng trong khoảng 0-1000
  for (size_t i{0}; i < numSensors; ++i)
  {
    sensorValues[i] = analogRead(SENSOR_PINS[i]);
    sensorValues[i] = constrain(sensorValues[i], 0, 1000);
  }
  // Serial.println();
}

void processSensorValues()
{
  // Chuyển đổi giá trị từ cảm biến thành số nhị phân
  for (size_t i{0}; i < numSensors; ++i)
  {
    int valueMap = map(sensorValues[i], 0, 1000, 0, 1);
    concatenatedNumber = (concatenatedNumber * 10) + valueMap;
    /*concatenatedNumber = 0 * 10 + 1 = 1
     concatenatedNumber = 1 * 10 + 0 = 10
     concatenatedNumber = 10 * 10 + 1 = 101
     concatenatedNumber = 101 * 10 + 0 = 1010
     concatenatedNumber = 1010 * 10 + 0 = 10100*/
  }
  Serial.println(concatenatedNumber);
}

// Hàm xử lý hướng di chuyển
void handleDirection()
{
  // Duyệt qua mảng và kiểm tra điều kiện
  for (const auto &mapping : directionMappings)
  {
    if (concatenatedNumber == mapping.condition)
    {
      mapping.action(mapping.parameters[0], mapping.parameters[1], mapping.parameters[2]);
      break; // Thoát khỏi vòng lặp khi đã tìm thấy điều kiện
    }
  }
}

void functionSituation()
{
  readSensors();
  processSensorValues();
  handleDirection();
}

void notLine(byte, byte, byte)
{
  leftRight(1, 0, 0);
  delay(200);
  straitsBack(0, 0, 1);
  delay(50);
}

void driveMotors(byte in1, byte in2, byte en, MotorPins motor)
{
  // Điều khiển động cơ bằng cách đặt các chân đúng giá trị
  digitalWrite(motor.in1, in1);
  digitalWrite(motor.in2, in2);
  analogWrite(motor.en, en);
}

void resetMotors()
{
  // Tắt động cơ bằng cách đặt tất cả các chân về giá trị 0
  digitalWrite(motorData.motorA.in1, 0);
  digitalWrite(motorData.motorA.in2, 0);
  analogWrite(motorData.motorA.en, 0);
  digitalWrite(motorData.motorB.in1, 0);
  digitalWrite(motorData.motorB.in2, 0);
  analogWrite(motorData.motorB.en, 0);
}

void straitsBack(byte forward, byte reverse, byte stop)
{
  // Điều khiển động cơ để di chuyển thẳng, lùi, hoặc dừng
  if (forward == 1 && reverse == 0 && stop == 0)
  {
    // Serial.println("thuan");

    driveMotors(0, 1, motorData.maxSpeed, motorData.motorA);
    driveMotors(0, 1, motorData.maxSpeed, motorData.motorB);
  }
  else if (forward == 0 && reverse == 1 && stop == 0)
  {
    // Serial.println("nghich");
    driveMotors(1, 0, motorData.maxSpeed, motorData.motorA);
    driveMotors(1, 0, motorData.maxSpeed, motorData.motorB);
  }
  else if (forward == 0 && reverse == 0 && stop == 1)
  {
    // Serial.println("stop");
    driveMotors(0, 0, motorData.maxSpeed, motorData.motorA);
    driveMotors(0, 0, motorData.maxSpeed, motorData.motorB);
  }
}

void leftRight(byte left, byte right, byte leftmode)
{
  // Điều khiển động cơ để rẽ trái hoặc phải
  if (left == 1 && right == 0)
  {
    // Serial.println("trai");
    driveMotors(0, 1, motorData.maxSpeed, motorData.motorA);
    driveMotors(1, 0, motorData.maxSpeedTurn, motorData.motorB);
  }
  else if (left == 0 && right == 1)
  {
    // Serial.println("phai");
    driveMotors(1, 0, motorData.maxSpeedTurn, motorData.motorA);
    driveMotors(0, 1, motorData.maxSpeed, motorData.motorB);
  }
  else if (leftmode)
  {
    driveMotors(0, 1, 255, motorData.motorA);
    driveMotors(1, 0, 255, motorData.motorB);
  }
  return;
}
void barrierA5()
{
  straitsBack(0, 0, 1);
  delay(500);
  leftRight(00, 0, 1);
  delay(800);
}

void resetVariable()
{
  // Đặt lại biến và tắt động cơ
  leftRight(0, 0, 0);
  straitsBack(0, 0, 0);
  concatenatedNumber = 0; // khong dc xoa
}

void loop()
{
  unsigned long currentMillis = millis();

  bool valueA5 = digitalRead(A5);

  if (currentMillis - previousMillis >= interval)
  {

    if (valueA5 == 1)
    {
      // Serial.println("BARRIER!!!!");
      barrierA5();
    }
    functionSituation();
    resetVariable();
    previousMillis = currentMillis;
  }
}
