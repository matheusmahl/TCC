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

//Endereco I2C do MPU6050
const int MPU=0x68;

int ledPinErro = 3;

//CS - ChipSelect do CardReader
const int chipSelect = 4; 

// Determina os pinos ligados ao modulo
// myRTC(clock, data, rst)
virtuabotixRTC myRTC(6, 7, 8);

//http://www.embarcados.com.br/modulos-bluetooth-hc-05-e-hc-06/
//SoftwareSerial BTSerial(9, 10); // RX | TX

//wifi serial
SoftwareSerial WifiSerial(2, 5); // RX | TX

String dataSemFormato = "01012000"; // DD/MM/AAAA
String horaSemFormato = "000000"; // 00:00:00

const int delayLeitura = 2000;
#define ARRAYSIZE 10

#define DEBUG true

void setup()
{
  Serial.begin(9600);
//  BTSerial.begin(38400);
 // WifiSerial.begin(115200);

  //ConectarWifi();
  // Informacoes iniciais de data e hora
  // Apos setar as informacoes, comente a linha abaixo
  // (segundos, minutos, hora, dia da semana, dia do mes, mes, ano)
  //myRTC.setDS1302Time(00, 32, 13, 7, 13, 05, 2017);

  pinMode(ledPinErro, OUTPUT);
  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Erro no cartao");
    ErrorLoop(1);
  }
  Serial.println("Cartao aberto");

 // VerificarArquivoDiaAtual(); //Atualiza o valor de numeroArquivo; 
}

void loop()
{
  Serial.println("loop");
  
  //Variaveis para armazenar valores dos sensores
  int AcX,AcY,AcZ;//GyX,GyY,GyZ;
 // double Temp;


 // Le as informacoes do CI
  myRTC.updateTime();
   
  dataSemFormato = "";
  dataSemFormato.concat(CompletarComZerosEsquerda(myRTC.dayofmonth, 2));
  dataSemFormato.concat(CompletarComZerosEsquerda(myRTC.month, 2));
  dataSemFormato.concat(CompletarComZerosEsquerda(myRTC.year, 4));
 
  horaSemFormato = "";
  horaSemFormato.concat(CompletarComZerosEsquerda(myRTC.hours, 2));
  horaSemFormato.concat(CompletarComZerosEsquerda(myRTC.minutes, 2));
  horaSemFormato.concat(CompletarComZerosEsquerda(myRTC.seconds, 2));

  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);

  //Solicita os dados do sensor
  Wire.requestFrom(MPU, 14, true);

  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX = Wire.read() << 8 | Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY = Wire.read() << 8 | Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
//  Temp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //Converte a temperatura para Graus Celsius
//  Temp = (Temp/340.00) + 36.53;

  String leitura = "";

  leitura.concat(dataSemFormato);
  leitura.concat("|");
  leitura.concat(horaSemFormato);
  leitura.concat("|");
  leitura.concat(AcX);
  leitura.concat("|");
  leitura.concat(AcY);
  leitura.concat("|");
  leitura.concat(AcZ);
  //leitura.concat("|");
 // leitura.concat(GyX);
 // leitura.concat(GyY);
 // leitura.concat(GyZ);
 // leitura.concat(Temp);

 leitura.concat("N"); //Indica o final da linha

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  // Nome do arquivo não deve conter mais de 8 caracteres.(Ex: MEUTEXTO.TXT).
  String arquivo = dataSemFormato + ".TXT";
  Serial.println(arquivo);
  File dataFile = SD.open(arquivo, FILE_WRITE);


  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(leitura);
    dataFile.close();
    // print to the serial port too:
    Serial.println(leitura);
  }

 // CopiarArquivos();

 enviarDados(leitura);
  
  //Aguarda e reinicia o processo
  delay(delayLeitura);
}


void ErrorLoop(int tipoErro){
  int Delay1 = 10000;
  int Delay2 = 100;
  
  if (tipoErro = 1){
    Delay1 = 1000;
    Delay2 = 500; 
  } else if (tipoErro = 2){
    Delay1 = 500;
    Delay2 = 2000;
  }
  
  while (true){
    digitalWrite(ledPinErro, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(Delay1);              // wait for a second
    digitalWrite(ledPinErro, LOW);    // turn the LED off by making the voltage LOW
    delay(Delay2);              // wait for a second 
  }
}

void ConectarWifi() {
  sendData("AT+RST\r\n", 2000, DEBUG); // rst
  // Conecta a rede wireless
  sendData("AT+CWJAP=\"Mahl_202\",\"mudeiasenha\"\r\n", 2000, DEBUG);
  delay(3000);
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
  // Mostra o endereco IP
  sendData("AT+CIFSR\r\n", 1000, DEBUG);
  // Configura para multiplas conexoes
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);
  // Inicia o web server na porta 80
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
}

void CopiarArquivos(){
/* Serial.println("INICIO");
  char flag = 'L';
  if (BTSerial.available() > 0){
    flag = BTSerial.read();
  }
  if (flag != 'L'){
    exit;
    //enviar blocos e verificar flag...
  }
  else
  {
  File dir = SD.open("/");
  dir.rewindDirectory();
  while (true){
    File entry =  dir.openNextFile();
    if (!entry) {
      break;
    }

    String arquivo = entry.name();
    Serial.println(arquivo.substring(0,8));
    if (!(arquivo.substring(0,8) == dataSemFormato)){
      while (entry.available()){
        String linha = "";
        char inputChar = 0;
        while (inputChar != 'N'){
          inputChar = entry.read(); // Gets one byte from serial buffer
                   
          if (CaractereValido(inputChar)){
             linha.concat(String(inputChar)); // Store it          
          } else {
              inputChar = 'N';           
          }         
        }      
       // linha = entry.read();
      
        if (linha != ""){
          Serial.println("linha: " + linha);
          
          BTSerial.print(linha);
          delay(2000);
        }
      }
      entry.close();
      break;
    }
    entry.close();
  }
  dir.close();


//char myString[] = "EH NOIX QUE VOA BRUXAO";

// for (int i = 0; i < sizeof(myString) - 1; i++){
  delay(10); // The DELAY!  
  BTSerial.print("FINAL"); 
 //}
  }*/
}

boolean CaractereValido(char element) {

char lista[13] = {'1','2','3','4','5','6','7','8','9','0','-','|','N'};
  
for (int i = 0; i < 13; i++) {
  if (lista[i] == element) {
    return true;
  }
}
return false;
}

String CompletarComZerosEsquerda(int valor, int quantidadeZeros){
  String texto = String(valor);
  
  if (texto.length() >= quantidadeZeros){
    return texto;
  } else {
    int quantidadeFaltante = quantidadeZeros - texto.length();
    String auxiliar = "";

    for (int i = 0; i < quantidadeFaltante; ++i)
     auxiliar.concat("0");
    
    auxiliar.concat(texto);
    return auxiliar;
  }
}

void VerificarArquivoDiaAtual(){
/*  myRTC.updateTime();
   
  String dataAtual = "";
  dataAtual.concat(CompletarComZerosEsquerda(myRTC.dayofmonth, 2));
  dataAtual.concat(CompletarComZerosEsquerda(myRTC.month, 2));
  dataAtual.concat(CompletarComZerosEsquerda(myRTC.year, 4));

  //Verificar se existe arquivo do dia atual. Se tiver, buscar o último numero e gravar em numeroArquivo.
  File root;
  //Abre diretorio raiz
  root = SD.open("/");
  root.rewindDirectory();

  String indiceArquivo = "0";
  File arquivo = root.openNextFile();
  while (arquivo){
    if (!arquivo){
      return;
    } else {
      String nome = arquivo.name();
      Serial.println(nome.substring(0,8));
      if (nome.substring(0,7) == dataAtual){
        indiceArquivo = nome.substring(9,11);    
      }
      arquivo = root.openNextFile();  
    }
   }
  Serial.println(numeroArquivo);*/
}

void enviarDados(String linha) {
  // Verifica se o ESP8266 esta enviando dados
 // Serial.print("enviardados 1");

  if (WifiSerial.available())
  {
    Serial.print("enviardados 2");
    if (WifiSerial.find("+IPD,"))
    {
      Serial.print("enviardados 3");
       delay(300);
      int connectionId = WifiSerial.read() - 48;
 
      String webpage = "<head><meta http-equiv=""refresh"" content=""3"">";
      webpage += "</head><h1><u>ESP8266 - Web Server</u></h1><h2>Porta";
      webpage += "Linha";
     // int a = digitalRead(8);
      webpage += linha;
 
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";
 
      sendData(cipSend, 1000, DEBUG);
      sendData(webpage, 1000, DEBUG);
 
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";
 
      sendData(closeCommand, 3000, DEBUG);
    }
  }
}

String sendData(String command, const int timeout, boolean debug)
{
  // Envio dos comandos AT para o modulo
  String response = "";
  WifiSerial.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (WifiSerial.available())
    {
      // The esp has data so display its output to the serial window
      char c = WifiSerial.read(); // read the next character.
      response += c;
    }
  }
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}


