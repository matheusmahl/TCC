
/*
Pin 0 - Nada
Pin 1 - Nada
Pin 2 - Wifi RX
Pin 3 - Nada / LedErro
Pin 4 - CS CardReader
Pin 5 - Wifi TX
Pin 6 - Clk RTC Module
Pin 7 - Dat RTC Module
Pin 8 - Rst RTC Module
Pin 9 - Nada
Pin 10 - Nada
Pin 11 - MOSI CardReader
Pin 12 - MISO CardReader
Pin 13 - CLK CardReader

Analog 4 - SDA Acelerômetro
Analog 5 - SCL Acelerômetro
*/
/*
 *
 *  Client side for Simple Connection (Always Connected) 
 *
 */

#include <ESP8266_TCP.h>
#include <SoftwareSerial.h>

// ESP8266 Class
ESP8266_TCP wifi;

// Target Access Point
#define ssid         "Mahl_202"
#define pass         "agoratemsenha"

// TCP Server IP and port
#define serverIP    "192.168.0.100"
#define serverPort  6789

// Connect this pin to CH_PD pin on ESP8266
#define PIN_RESET    9

// Pin that connected to button to send any message
#define PIN_SEND     10

SoftwareSerial WifiSerial(2, 5); // RX | TX

void setup()
{
  delay(3000);
  
  // Set pin for send command to input mode
  pinMode(PIN_SEND, INPUT);
  
  // We use Serial1 to interface with ESP8266 
  // and use Serial to debugging
  Serial.begin(115200);
  WifiSerial.begin(115200);
  wifi.begin(&WifiSerial, &Serial, PIN_RESET);
  
  /* If your board has only 1 serial port
   * or you didn't need to debugging, try this.
   *
   * Serial.begin(115200);
   * wifi.begin(&Serial, PIN_RESET);
   *
   */
  Serial.println("wifi.Test");
  // Check that ESP8266 is available
  while(!wifi.test()) 
  {
  // Open TCP Server on port 2000 and 30 seconds for timeout
    Serial.println("Check module connection and restart to try again..."); 
   // while(true);
  }


  Serial.println("Conectando no AP");
// Connect to target Access Point
  String ip = connectAP();
  Serial.println(ip);
}

void loop()
{
  // Check for any data has coming to ESP8266
  int dataState = wifi.isNewDataComing(WIFI_CLIENT);
  
  if(dataState != WIFI_NEW_NONE) {
    if(dataState == WIFI_NEW_CONNECTED) {
    // Connected with TCP Server Side
      Serial.println("Connected");
    } else if(dataState == WIFI_NEW_DISCONNECTED) {
    // Disconnected from TCP Server Side
      Serial.println("Disconnected");
    } else if(dataState == WIFI_NEW_MESSAGE) {
    // Got a message from TCP Server Side
      Serial.println("Message : " + wifi.getMessage());
    } else if(dataState == WIFI_NEW_SEND_OK) {
    // Message transfer has successful
      Serial.println("SENT!!!!");
    } 
    else
    Serial.println("Data State1: " + dataState); 
  } 
  else
  Serial.println("Data State2: " + dataState);
  
  // When button for send message was pressed
  
    // Send a message
    Serial.println("Enviou mensagem para o servidor...");
    wifi.send("12345678");
    delay(10000);
    
  // Auto connect to TCP Server Side when connection timeout
  if(wifi.getRunningState() == WIFI_STATE_UNAVAILABLE) {
    // Connect to TCP Server Side
    Serial.println("ReConnect!!");
    delay(500);
    wifi.connectTCP(serverIP, serverPort);
    delay(500);
  }
  
  delay(50);
}

// Access Point Connection Function that you can loop connect to Access Point until successful
String connectAP() 
{
  String ip = "0.0.0.0";
  while(ip.equals("0.0.0.0")) 
  {
    ip = wifi.connectAccessPoint(ssid, pass);
    if(!ip.equals("0.0.0.0")) 
    {
      break;
    } 
  }
  return ip;
}
