#include <SoftwareSerial.h>

SoftwareSerial mySerial(7, 8); 
//byte RX = 8; // This is your RX-Pin on Arduino UNO,connect with A7 UTXD pin
//byte TX = 7; // This is your TX-Pin on Arduino UNO,connect with a7 URXD pin
//SoftwareSerial *A7board = new SoftwareSerial(RX, TX); 

int incomingByte = 0;   // for incoming serial data

typedef int bool;
#define true 1
#define false 0
int isSendMessage;
int posValue;

 
void setup()
{
  mySerial.begin(115200);   // Setting the baud rate of GSM Module 
  delay(2000);
  
  Serial.begin(115200);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(2000);
  
  mySerial.println("AT");
  delay(2000);

  isSendMessage = false;
  posValue = 0;
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(2000);
  //Clear mySerial buffer
  while(mySerial.available()){
      char t = mySerial.read();
      mySerial.flush();
  }
  
  Serial.println("Waiting for message !!!"); // printing in IDE 
  isSendMessage = false;

}

void loop()
{

  if (mySerial.available()>0){
    if(isSendMessage == false){
      Serial.println("Message received!! ");
      isSendMessage = true;
    }
    
    while(mySerial.available()){
      char t = mySerial.read();
      mySerial.flush();
    }
    Serial.println("Build sms message");
    SendMessage();
  }


}

void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(2000); 
 
  mySerial.println("AT+CMGS=\"+353*********\"\r"); // Number to send 
  delay(2000);
 
 //Locations ! Carlow -> Motorway -> Hide in small road 
 char *pos[30]; 
       pos[0] = "52.827297";
       pos[1] = "-6.937482";
       pos[2] = "52.825609";
       pos[3] = "-6.938776";
       pos[4] = "52.818474";
       pos[5] = "-6.945629";
       pos[6] = "52.803765";
       pos[7] = "-6.952410";
       pos[8] = "52.784172";
       pos[9] = "-6.949063";
       pos[10] = "52.771321";
       pos[11] = "-6.951252";
       pos[12] = "52.778018";
       pos[13] = "-6.942835";
       pos[14] = "52.786617";
       pos[15] = "-6.927158";
       pos[16] = "52.791424";
       pos[17] = "-6.896612";
       pos[18] = "52.802062";
       pos[19] = "-6.882235";
       pos[20] = "52.794717";
       pos[21] = "-6.871678";
       pos[22] = "52.794717";
       pos[23] = "-6.871678";
       pos[24] = "52.791169";
       pos[25] = "-6.860288";
       pos[26] = "52.790286";
       pos[27] = "-6.851962";
       pos[28] = "52.785665";
       pos[29] = "-6.851790";
  

  //Target String -> "http://serversite.info/iot/gpos.php?latitude=46.924093&longitude=29.984894"
  String baseUrl = ""; //Clear String object !!!
  baseUrl = "The vehicle position is :\n";
  baseUrl.concat("http://serversite.info/iot/gpos.php?latitude=");
  baseUrl.concat(pos[posValue]);
  posValue += 1;
  baseUrl.concat("&longitude=");
  baseUrl.concat(pos[posValue]);
  posValue += 1;
  delay(2000);
  mySerial.println(baseUrl);// The SMS text you want to send
  Serial.println(baseUrl); // printing in IDE 
  delay(8000);

  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(2000); 
  
  //Reset position to demo GPS locations
  if(posValue>=30){
      posValue = 0;
  }

   while(mySerial.available()){
      char t = mySerial.read();
      mySerial.flush();
    }
  //Delay 20 seconds
  delay(20000);
  
  //Set buffer to send new position
  mySerial.write(1);
}

//void RecieveMessage()
//{ 
//  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
//  Serial.println("Receive message");
//
//}

