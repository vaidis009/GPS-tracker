#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); 

//byte RX = 8; // This is your RX-Pin on Arduino UNO,connect with A7 UTXD pin
//byte TX = 7; // This is your TX-Pin on Arduino UNO,connect with a7 URXD pin
//SoftwareSerial *A7board = new SoftwareSerial(RX, TX); 

void setup()
{
  mySerial.begin(115200);   // Setting the baud rate of GSM Module 
  Serial.begin(115200);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);

  mySerial.begin(115200);
  delay(200); 

  mySerial.println("AT");
  delay(25000);

  mySerial.println("AT+GPS=1");  
  delay(10000);  
 
  mySerial.println("AT+GPSRD=1");  
  delay(10000);

}

void loop()
{
 if (Serial.available()>0){
  //SendMessage();
 //  Serial.write("Hello from Serial");
 }   
 if (mySerial.available()>0){    
    Serial.write("Hello from myserial");
    SendMessage();    
 } 
}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000); 
 
  mySerial.println("AT+CMGS=\"+353873162###\"\r"); // Number to send
  delay(1000);

  String st = mySerial.readString();

  mySerial.println(st);// The SMS text you want to send
  Serial.println(st); // printing in IDE 
  delay(100);

  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000); 
}

 void RecieveMessage()
{ 
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
}




