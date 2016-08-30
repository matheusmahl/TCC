//Carrega a biblioteca Wire
#include<Wire.h>

//Biblioteca para comunicação com SDCard
#include <SPI.h>
#include <SD.h>

//Biblioteca para controle do relógio real.
#include <virtuabotixRTC.h> 

//Biblioteca para controle da porta serial do módulo Blutooth
#include <SoftwareSerial.h>

/*
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 * 
 * Clock pins
 ** CLK - 6
 ** DAT - 7
 ** RST - 8
*/

//Endereco I2C do MPU6050
const int MPU=0x68;

//CS - ChipSelect
const int chipSelect = 4; 

// Determina os pinos ligados ao modulo
// myRTC(clock, data, rst)
virtuabotixRTC myRTC(6, 7, 8);

//http://www.embarcados.com.br/modulos-bluetooth-hc-05-e-hc-06/
SoftwareSerial BTSerial(9, 10); // RX | TX

int numeroArquivo = 0;
String dataSemFormato = "01012000"; // DD/MM/AAAA
String horaSemFormato = "000000"; // 00:00:00

void setup()
{
  Serial.begin(9600);
  BTSerial.begin(38400);

  // Informacoes iniciais de data e hora
  // Apos setar as informacoes, comente a linha abaixo
  // (segundos, minutos, hora, dia da semana, dia do mes, mes, ano)
  //myRTC.setDS1302Time(00, 4, 22, 2, 29, 8, 2016);

  pinMode(13, OUTPUT);
  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    ErrorLoop(1);
  }

  numeroArquivo = VerificarArquivoDiaAtual();
 
}

void loop()
{
  if (BTSerial.available()) {
    CopiarArquivos();
  }
  //Variaveis para armazenar valores dos sensores
  int AcX,AcY,AcZ,GyX,GyY,GyZ;
  double Temp;

 // Le as informacoes do CI
  myRTC.updateTime(); 
 // myRTC.dayofmonth
 // myRTC.month
 // myRTC.year
 // myRTC.hours
 // myRTC.minutes
 // myRTC.seconds

  Serial.print(", ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
   Serial.print("Hora : ");
  // Adiciona um 0 caso o valor da hora seja <10
  if (myRTC.hours < 10)
  {
    Serial.print("0");
  }
  Serial.print(myRTC.hours);
  Serial.print(":");
  // Adiciona um 0 caso o valor dos minutos seja <10
  if (myRTC.minutes < 10)
  {
    Serial.print("0");
  }
  Serial.print(myRTC.minutes);
  Serial.print(":");
  // Adiciona um 0 caso o valor dos segundos seja <10
  if (myRTC.seconds < 10)
  {
    Serial.print("0");
  }
  Serial.println(myRTC.seconds);

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);

  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);

  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Temp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //Converte a temperatura para Graus Celsius
  Temp = (Temp/340.00) + 36.53;

  String leitura = "";

  leitura.concat("AcX=");
  leitura.concat(AcX);
  leitura.concat("|AcY=");
  leitura.concat(AcY);
  leitura.concat("|AcZ=");
  leitura.concat(AcZ);
  leitura.concat("|GyX=");
  leitura.concat(GyX);
  leitura.concat("|GyY=");
  leitura.concat(GyY);
  leitura.concat("|GyZ=");
  leitura.concat(GyZ);
  leitura.concat("|Temp=");
  leitura.concat(Temp);

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("LEITURA.TXT", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(leitura);
    dataFile.close();
    // print to the serial port too:
    Serial.println(leitura);
  }

  

  //Aguarda 2000 ms e reinicia o processo
  delay(2000);
}


void ErrorLoop(int tipoErro){
  int Delay1 = 1000;
  int Delay2 = 1000;
  
  if (tipoErro = 1){
    Delay1 = 1000;
    Delay2 = 500; 
  }
  
  while (true){
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(Delay1);              // wait for a second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    delay(Delay2);              // wait for a second 
  }
}

void CopiarArquivos(){

  
}

int VerificarArquivoDiaAtual(){
   //Verificar se existe arquivo do dia atual. Se tiver, buscar o último numero e gravar em numeroArquivo.
   File root;
   //Abre diretorio raiz
   root = SD.open("/");
   root.rewindDirectory();
   File arquivo = root.openNextFile();
   String nome = arquivo.name();
  
}


