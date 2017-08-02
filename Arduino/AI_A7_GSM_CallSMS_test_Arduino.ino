
char phone_no[]="01759848889";

#include <SoftwareSerial.h>
SoftwareSerial A7Serial(10, 11); // RX, TX 
void setup() {
  // put your setup code here, to run once:
  A7Serial.begin(115200);
  Serial.begin(9600);
  delay(500);
//  sms();
//  Serial.println("Message Sent??");
//  delay(500);
//  delay(500);
  Serial.println("Trying call...");
  call();
  Serial.println("Called...???");
}

void loop() {

  A7SerialEvent();
  SerialEvent();

}
void SerialEvent(){
    if(Serial.available() > 0){
    while(Serial.available() > 0){
      //A7Serial.print((char)Serial.read());
      char x = Serial.read();
      if (x == '*'){
        A7Serial.print((char)26); //the ASCII code of the ctrl+z is 26
      }
      else{
        A7Serial.print(x);
      }
      
    }
  }
}
void A7SerialEvent(){
    if(A7Serial.available() > 0){
//    while(A7Serial.available() > 0){
//      Serial.print((char)A7Serial.read());
//    }
      String A7AT = A7Serial.readString();
      A7AT.trim();
      Serial.println( A7AT );
    }
}

void sms(){
    A7Serial.println("AT+CMGF=1");
      A7SerialEvent();    
    delay(2000);
    A7Serial.print("AT+CMGS=\"");
      A7SerialEvent();
    A7Serial.print(phone_no);
      A7SerialEvent(); 
    A7Serial.write(0x22);
      A7SerialEvent();
    A7Serial.write(0x0D);  // hex equivalent of Carraige return    
      A7SerialEvent();
    A7Serial.write(0x0A);  // hex equivalent of newline
      A7SerialEvent();
    delay(2000);
    A7Serial.print("GSM A7 test message!");
      A7SerialEvent();
    delay(500);
    A7Serial.println (char(26));//the ASCII code of the ctrl+z is 26 to "send SMS"
      A7SerialEvent();  
//      delay(500);
//      A7Serial.flush();

}

void call(){
    A7Serial.println("AT");
        A7SerialEvent();
    delay(1000);
    A7Serial.print("ATD");
        A7SerialEvent();
    A7Serial.println(phone_no);
    //Serial.println(";");
        A7SerialEvent();
    delay(10000);
        A7SerialEvent();
    A7Serial.println("ATH");
        A7SerialEvent();

        //delay(500);
        //A7Serial.flush();
}
