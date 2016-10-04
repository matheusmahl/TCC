#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // RX, TX
String command = "";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(38400);
 // mySerial.println("Hello, world?");
}
void loop() {
 // Read device output if available.  
  if (mySerial.available()) 
  {  
    Serial.println("MySerial.available = true");
     while(mySerial.available() > 0) 
     { 
      // While there is more to be read, keep reading. 
       
       command += (char)mySerial.read();       
       delay(20); 
     }  
     Serial.println(command);
   
   command = ""; // No repeats  
  }  
  else
  {
    Serial.println("MySerial.available = false");
  }
  delay(1000);
}
