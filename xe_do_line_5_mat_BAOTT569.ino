const size_t sensorLine[] = {A0, A1, A2, A3, A4};
int valueTotalSen[] = {0, 0, 0, 0, 0};

unsigned long previousMillis = 0; // Biến để lưu giữ thời gian lần cuối cùng
const long interval = 20;         // Thời gian chờ là 1 giây (2 milliseconds)

size_t arraySize = sizeof(sensorLine) / sizeof(sensorLine[0]);
long int convertNumber = 0;

void setup()
{
  Serial.begin(9600);
  for (size_t a{0}; a < arraySize; ++a)
  {
    pinMode(sensorLine[a], INPUT);
    digitalWrite(sensorLine[a], 0);
  }
}

void funciton_Read_Sensor()
{
  for (size_t i{0}; i < arraySize; ++i)
  {
    valueTotalSen[i] = analogRead(sensorLine[i]);

    // Kiểm tra giá trị cảm biến và giới hạn nó trong khoảng 0-1000
    valueTotalSen[i] = constrain(valueTotalSen[i], 0, 1000);
    // Serial.print(String("Sensor ") + i + String(":\t") + valueTotalSen[i] + String(":\t"));
  }
  Serial.println();
}

void Funciton_sitution()
{
  for (size_t b{0}; b < arraySize; ++b)
  {
    int valueMap = map(valueTotalSen[b], 0, 1000, 0, 1);
    convertNumber = (convertNumber * 10) + valueMap;
    /*concatenatedNumber = 0 * 10 + 1 = 1
      concatenatedNumber = 1 * 10 + 0 = 10
      concatenatedNumber = 10 * 10 + 1 = 101
      concatenatedNumber = 101 * 10 + 0 = 1010
      concatenatedNumber = 1010 * 10 + 0 = 10100*/
  }
  Serial.println(convertNumber);
  if (convertNumber == 0)
  {
    not_line();
  }
  else if (convertNumber != 0 && convertNumber != 11111)
  {
    if (convertNumber == 11000 || convertNumber == 11100) // queo trai
    {
      left_right(1, 0);
    }
    else if (convertNumber == 00011 || convertNumber == 00111) // queo phai
    {
      left_right(0, 1);
    }
    else if (convertNumber == 01110) // di thang
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

void straits_back(bool forward, bool reveres)
{
  if (!forward && reveres)
  {
    Serial.println("thuan");
    // analogWrite(3, 255);
    // analogWrite(4, 255);
  }
  else if (forward && !reveres)
  {
    Serial.println("nghich");
    // analogWrite(3, -255);
    // analogWrite(4, -255);
  }
}

void left_right(bool left, bool right)
{
  if (!left && right)
  {
    Serial.println("trai");
    // analogWrite(3, -255);
    // analogWrite(4, 255);
  }
  else if (left && !right)
  {
    Serial.println("phai");
    // analogWrite(3, 255);
    // analogWrite(4, -255);
  }
}

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