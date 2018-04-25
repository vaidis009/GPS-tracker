// 0 pin is your RX-Pin on Arduino UNO,connect with A7 UTXD pin
// 1 pin is your TX-Pin on Arduino UNO,connect with a7 URXD pin
char phone_no[]="+353873162262";

void setup() {
Serial.begin(115200);
delay(300); 

Serial.println("AT+CMGF=1");    
delay(2000);
Serial.print("AT+CMGS=\"");
Serial.print(phone_no); 
Serial.write(0x22);
Serial.write(0x0D);  // hex equivalent of Carraige return    
Serial.write(0x0A);  // hex equivalent of newline
delay(2000);
Serial.print("GSM A7 test message!");
delay(500);
Serial.println (char(26));//the ASCII code of the ctrl+z is 26

}

void loop()
{

}



