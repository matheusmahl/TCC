#include <SoftwareSerial.h>


// Target Access Point
#define ssid         "Mahl_202"
#define pass         "agoratemsenha"

// TCP Server IP and port
#define serverIP    "192.168.0.100"
#define serverPort  6789

SoftwareSerial WifiSerial(2, 5); // RX | TX

void setup() {
 Serial.begin(115200);

 WifiSerial.begin(115200);

}

void loop() {
 //WifiSerial.write("AT+RST");
 clearBuffer();
 Serial.println("AT: ");
 WifiSerial.write("AT\r\n");
 delay(2000);
 String data = readData();
 Serial.println("Retorno: " + data);
 delay(10000);
}

String readData() {
    String data = "";
    while(WifiSerial.available() > 0) {
        char r = WifiSerial.read();
        if (r == '\n') {
            return data;
        } else if(r == '\r') {
        } else {
            data += r;  
        }
    }
    return "";
}

void clearBuffer() {
  while(WifiSerial.available() > 0) {
    WifiSerial.read();
  }
}
