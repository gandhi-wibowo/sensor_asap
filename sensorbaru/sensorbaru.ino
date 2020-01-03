#include <SoftwareSerial.h>
#include <espduino.h>
#include <rest.h>
SoftwareSerial espPort(10, 11);
ESP esp(&espPort, &Serial, 9);
REST rest(&esp);
boolean wifiConnected = false;
const int relay1 =  8;
char response[266];
char buff_get[64];
char buff_post[64];


void wifiCb(void* response){
  uint32_t status;
  RESPONSE res(response);
  if(res.getArgc() == 1) {
    res.popArgs((uint8_t*)&status, 4);
    if(status == STATION_GOT_IP) {
      Serial.println("TERHUBUNG KE WIFI");
      wifiConnected = true;
    } else {
      wifiConnected = false;
    }
  }
}

void setup() {
  pinMode(relay1, OUTPUT); 
  digitalWrite(relay1,HIGH);  
  Serial.begin(9600);
  espPort.begin(19200);  
  esp.enable();
  delay(500);
  esp.reset();
  delay(500);
  while(!esp.ready());
  Serial.println("ARDUINO: Setup client");
  if(!rest.begin("192.168.0.100")) {
    Serial.println("ARDUINO: Gagal Setup client");
    while(1);
  }
  Serial.println("ARDUINO: Menghubungkan dengan Wifi");
  esp.wifiCb.attach(&wifiCb);
  esp.wifiConnect("MR3020","jangandonlot");
  Serial.println("ARDUINO: System sudah siap!");
}

void loop() {   
  esp.process();  
  if(wifiConnected) { 

    int val = analogRead(A0);
    sprintf(buff_post, "/alamsyah/Data/insert/%i",val); // insert data gas
    Serial.println(buff_post);
    rest.get((const char*)buff_post);
      
    sprintf(buff_get, "/alamsyah/Saklar/status/1"); // get status saklar 1
    Serial.println(buff_get);
    rest.get((const char*)buff_get);
    if(rest.getResponse(response, 266) == HTTP_STATUS_OK){ 
      String data = response;
      if(data == "0"){
        digitalWrite(relay1,HIGH);
        // matikan
      }
      else{
        digitalWrite(relay1,LOW);
        // hidupkan
      }
    }

    sprintf(buff_get, "/alamsyah/Saklar/status/2"); // get status saklar 1
    Serial.println(buff_get);
    rest.get((const char*)buff_get);
    if(rest.getResponse(response, 266) == HTTP_STATUS_OK){ 
      String data = response;
      if(data == "0"){
        digitalWrite(relay1,HIGH);
        // matikan
      }
      else{
        digitalWrite(relay1,LOW);
        // hidupkan
      }
    }        
  }    
}
