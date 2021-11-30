#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 0, 177 };
byte server[] = { 54,228,42,199 }; 
char serverName[] = "cn-project-api.herokuapp.com";
EthernetClient client;

const int analogInPin = A0;

void sendReq(int value){
    if (client.connect(serverName, 80 )==1) {
    client.print(F("GET /sensorvalue?value="));
    client.print(value);
    client.println(F(" HTTP/1.0"));
    client.println(F("Host: cn-project-api.herokuapp.com"));
    client.println();
  } else {
    Serial.println("connection failed");
  }

  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) 
  { //connected or data available
    char c = client.read();
  }
  Serial.println();
  client.stop();
  
}

void setup() {
  // put your setup code here, to run once:
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  
  delay(1000);


}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(analogInPin);
  Serial.println(sensorValue);
  sendReq(sensorValue);

  delay(30);
}
