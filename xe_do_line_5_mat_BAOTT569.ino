const size_t sensorLine[] = {A0, A1, A2, A3, A4};
int valueTotalSen[] = {0, 0, 0, 0, 0};

unsigned long previousMillis = 0; // Biến để lưu giữ thời gian lần cuối cùng
const long interval = 20;         // Thời gian chờ là 20 milliseconds (đã sửa đổi từ 1 giây)

size_t arraySize = sizeof(sensorLine) / sizeof(sensorLine[0]);
long int convertNumber = 0;

void setup()
{
  Serial.begin(9600);

  // Khởi tạo chân đầu vào và tắt tất cả các cảm biến
  for (size_t a{0}; a < arraySize; ++a)
  {
    pinMode(sensorLine[a], INPUT);
    digitalWrite(sensorLine[a], 0);
  }
}

void funciton_Read_Sensor()
{
  // Đọc giá trị từ các cảm biến và giới hạn chúng trong khoảng 0-1000
  for (size_t i{0}; i < arraySize; ++i)
  {
    valueTotalSen[i] = analogRead(sensorLine[i]);
    valueTotalSen[i] = constrain(valueTotalSen[i], 0, 1000);
  }
  Serial.println();
}

void Funciton_sitution()
{
  for (size_t b{0}; b < arraySize; ++b)
  {
    // Ánh xạ giá trị cảm biến vào khoảng 0-1
    int valueMap = map(valueTotalSen[b], 0, 1000, 0, 1);
    convertNumber = (convertNumber * 10) + valueMap;
  }
  Serial.println(convertNumber);

  // Xử lý các tình huống dựa trên giá trị convertNumber
  if (convertNumber == 0)
  {
    not_line();
  }
  else if (convertNumber != 0 && convertNumber != 11111)
  {
    if (convertNumber == 11000 || convertNumber == 11100) // queo trái
    {
      left_right(1, 0);
    }
    else if (convertNumber == 00011 || convertNumber == 00111) // queo phải
    {
      left_right(0, 1);
    }
    else if (convertNumber == 01110) // đi thẳng
    {
      straits_back(1, 0);
    }
  }
}

void not_line()
{
  int wait_check = 1000;
  if (convertNumber == 00000)
  {
    left_right(1, 0);
    delay(wait_check);
    straits_back(1, 0);
    delay(wait_check);
    left_right(0, 1);
    delay(wait_check);
    straits_back(0, 1);
    delay(wait_check);
  }
}

// Hàm điều khiển khi đi thẳng hoặc lùi
void straits_back(bool forward, bool reveres)
{
  if (!forward && reveres)
  {
    Serial.println("thuan");
    // Thực hiện hành động khi lùi
    // analogWrite(3, 255);
    // analogWrite(4, 255);
  }
  else if (forward && !reveres)
  {
    Serial.println("nghich");
    // Thực hiện hành động khi đi thẳng
    // analogWrite(3, -255);
    // analogWrite(4, -255);
  }
}

// Hàm điều khiển khi rẽ trái hoặc phải
void left_right(bool left, bool right)
{
  if (!left && right)
  {
    Serial.println("trai");
    // Thực hiện hành động khi rẽ trái
    // analogWrite(3, -255);
    // analogWrite(4, 255);
  }
  else if (left && !right)
  {
    Serial.println("phai");
    // Thực hiện hành động khi rẽ phải
    // analogWrite(3, 255);
    // analogWrite(4, -255);
  }
}

// Hàm đặt lại biến cờ convertNumber
void resetVariable()
{
  convertNumber = 0;
}

void loop()
{
  unsigned long currentMillis = millis(); // Lấy thời gian hiện tại

  if (currentMillis - previousMillis >= interval)
  {
    funciton_Read_Sensor();
    Funciton_sitution();
    // Cập nhật thời gian lần cuối cùng
    previousMillis = currentMillis;
  }
  resetVariable();
}
