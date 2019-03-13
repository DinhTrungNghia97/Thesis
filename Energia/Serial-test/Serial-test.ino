/*
  Ví dụ về Serial Event
  Khi có dữ liệu tới thì thêm dữ liệu vào chuỗi và khi 
  nhận được dấu xuống dòng '\n' (newline) thì sẽ in ra chuỗi 
  và dừng quá trình nhận đồng thời xóa chuỗi.
  Chương trình này có thể được sử dụng để nhận tín hiệu GPS
  Created 9 May 2011
  by Tom Igoe
  Modified 24 April 2013
  by Sean Alvarado
-----------------------------------------
  Hardware Required:
  * TIVA LaunchPad
  Lưu ý:
  Chọn trong terminal hiển thị của Energia là newline
  
  This example code is in the public domain.
*/

String inputString2 = ""; // Khai báo chuỗi lưu các data nhận được
boolean stringComplete2 = false; // biến thông báo nhận chuỗi thành công

String inputString = ""; // Khai báo chuỗi lưu các data nhận được
boolean stringComplete = false; // biến thông báo nhận chuỗi thành công

void setup() {
  // Thiết lập cổng COM giao tiếp tốc độ baud 9600
  Serial.begin(19200);
  Serial2.begin(19200);
  // khai báo 200 byte cho inputString:
  inputString.reserve(200);
  Serial.print("Serial 0");
  Serial2.print("Serial 2");
}

void loop() {
  // In chuỗi khi có một dòng mới
  if (stringComplete2) {
    Serial.println(inputString2); 
    // Xóa chuỗi:
    inputString2 = "";
    stringComplete2 = false;
  }
   if (stringComplete) {
    Serial2.println(inputString); 
    // Xóa chuỗi:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent xảy ra khi có dữ liệu trên RX. Chương trình này
  chạy mỗi khi có loop(), do đó nếu sử dụng delay trong hàm loop
  sẽ tăng thời gian nhận phản hồi.
*/
void serialEvent2(){
    while (Serial2.available()) {
    // Nhận byte mới:
    char inChar2 = (char)Serial2.read(); 
    // thêm byte này vào inputString:
    inputString2 += inChar2;
    // Nếu có kí tự mới là newline, set cờ
    if (inChar2 == '\n') {
    stringComplete2 = true;
    } 
    }
}
void serialEvent(){
    while (Serial.available()) {
    // Nhận byte mới:
    char inChar = (char)Serial.read(); 
    // thêm byte này vào inputString:
    inputString += inChar;
    // Nếu có kí tự mới là newline, set cờ
    if (inChar == '\n') {
    stringComplete = true;
    } 
    }
}
