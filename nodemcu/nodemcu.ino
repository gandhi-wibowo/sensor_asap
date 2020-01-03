#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "Sensor";
const char* password = "selamatdatang21";

const char* host     = "192.168.43.242";
String saklar        = "/alamsyah/Saklar/all";
String data          = "/alamsyah/Data/insert/";
const int d0   = 16;
const int d1   = 5;
const int d2   = 4;

void setup() {
  pinMode(d0, OUTPUT);
  pinMode(d0, HIGH);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d1, HIGH);
  Serial.begin(115200);
  delay(10);
  WiFi.begin(ssid, password);

}

void loop() {

  WiFiClient Data,Saklar;
  const int httpPort = 80;
  int val = analogRead(A0);
  if(val > 200){
    digitalWrite(d2, HIGH);
  }
  else{
    digitalWrite(d2, LOW);
  }  
  if (Saklar.connect(host, httpPort) && Data.connect(host, httpPort)) {

        Data.print(String("GET ") + data + val + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: keep-alive\r\n\r\n");

        delay(1000);

        Saklar.print(String("GET ") + saklar + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: keep-alive\r\n\r\n");
        delay(1000);

        while(Saklar.available()){
          String sak = Saklar.readStringUntil('\r');
          DynamicJsonBuffer jsonBuffer;
          JsonArray& root = jsonBuffer.parseArray(sak);
          String id1 = root[0]["id_saklar"];
          String id2 = root[1]["id_saklar"];
          String stts1 = root[0]["status"];
          String stts2 = root[1]["status"];
          if(id1 == "1"){
            if(stts1 == "0"){
              digitalWrite(d0, HIGH);
            }
            else{
              digitalWrite(d0, LOW);
            }
          }
          if(id2 == "2"){
            if(stts2 == "0"){
              digitalWrite(d1, HIGH);
            }
            else{
              digitalWrite(d1, LOW);
            }
          }
        }
  }

}
