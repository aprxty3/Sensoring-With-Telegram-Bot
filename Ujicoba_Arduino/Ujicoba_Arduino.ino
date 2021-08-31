#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3);
String data;
char c;
const int relay = 13;

int lm35 = A0;
int val;
float mv;
float temp;

void setup() {
  Serial.begin(115200);
  mySerial.begin(115200);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  delay(10);
}

void loop() {
  while(mySerial.available()>0){
    delay(10);
    c = mySerial.read();
    data += c;
  }  
  if (data.length()>0) {
    Serial.println(data);
    if (data == "RELAY ON") {
      digitalWrite(relay, LOW);
      Serial.println("RELAY ON");
    } 
    else if (data == "RELAY OFF") {
      digitalWrite(relay, HIGH);
      Serial.println("RELAY OFF");
    } 
    else if (data == "TEMPERATURE") {
      val = analogRead(lm35);
      mv = (val/1024.00)*5000;
      temp = mv/10;
      mySerial.print(temp);
      Serial.println(temp);
    }
    data = "";
  }
}
