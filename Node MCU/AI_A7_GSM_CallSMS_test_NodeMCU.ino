
char phone_no[]= "xxxx...";  //replace "xxxx..." with the target phone number

#include <SoftwareSerial.h>
SoftwareSerial A7Serial(14, 12, false, 256); // RX, TX 

void setup() {
  delay(1000);
  Serial.begin(115200);
  delay(500);
  Serial.println("StartED MCU serial...1");
  delay(500);
  Serial.println("StartED MCU serial...2");
  Serial.println("Starting AI A7 serial...");
  A7Serial.begin(115200);
  Serial.println("StartED AI A7 serial...");
  delay(1500);
  Serial.println("Initiating SMS...");
  sms();
  wait(2500);
  Serial.println("Message Sent??");
  wait(2000);
  Serial.println("Trying call function...");
  call();
  wait(1500);
  Serial.println("Called...???");
}

void loop() {
delay(2);
  A7SerialEvent();
delay(2);
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
      delay(2);   //to stabilize data communication
    }
  }
}
void A7SerialEvent(){
    delay(2);   //to stabilize data communication
    if(A7Serial.available() > 0){
//    while(A7Serial.available() > 0){
//      Serial.print((char)A7Serial.read());
//    }
      String A7AT = A7Serial.readString();
      Serial.println( "\n###A7(GSM module): \n"+A7AT+"\n................................" );
    }
    delay(2);   //to stabilize data communication
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
   
    wait(1000); // wait for the process to be done with
}

/*
 * Initiate a call
 */
void call(){
    A7Serial.println("AT");
        A7SerialEvent();
    wait(1000);
    A7Serial.print("ATD");
        A7SerialEvent();
    A7Serial.println(phone_no);
    //Serial.println(";");
        A7SerialEvent();
    wait(10000);
        A7SerialEvent();
    A7Serial.println("ATH");
        A7SerialEvent();

}

/*
 * This method works insted of delay 
 * to keep listening to the GSM whle waiting
 */
void wait(long del){
  unsigned long startTime = millis();
  long delayForDot=50;
  while(1){
    if ( (millis()-startTime) > delayForDot ){
      Serial.print(".");
      delayForDot+=50;
      if (delayForDot%2500==0) Serial.println("|");
    }
    if ( (millis()-startTime) > del ) {
          Serial.println("!");
          break;
    }
    
    A7SerialEvent();
    yield();
  }
}
