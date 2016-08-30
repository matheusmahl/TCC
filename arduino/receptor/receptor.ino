#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 10); // RX, TX
String command = "";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
 // mySerial.println("Hello, world?");
}
void loop() {
 // Read device output if available.  
  if (mySerial.available()) 
  {  
     while(mySerial.available()) 
     { // While there is more to be read, keep reading.  
       command += (char)mySerial.read();  
     }  
   Serial.println(command);  
   command = ""; // No repeats  
  }  
  
  // Read user input if available.  
  if (Serial.available())
  {  
    delay(10); // The DELAY!  
    mySerial.write(Serial.read());  
  }  

}
