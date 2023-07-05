#include <SimpleDHT.h>
#include<Time.h>
#include <DFRobot_SIM808.h>
#include <SoftwareSerial.h>
#include <String.h>
#include <DHT.h>

#define PIN_TX    10
#define PIN_RX    11
#define FLAME 5
#define ALARM 7 
#define RED 9
#define GREEN 8
#define MQ A0                        
#define DHT  A2

int co2 = 0;  
byte temperature = 0;
byte humidity = 0;

char PHONE_NUMBER[]= "7338498081" ;
char message1[]="FIRE FIRE FIRE\nIntensity: Level 1\nCurrent Status at site:\nhttps://drive.google.com/drive/folders/1zx_BRXgtGzn_KNHI1lx8819qmxnTFpsx?usp=sharing";
char message2[]="FIRE FIRE FIRE\nIntensity: Level 2\nCurrent Status at site:\nhttps://drive.google.com/drive/folders/1r0RzuPSmD9HBkvoMWMiBCkviEWTMixS1?usp=sharing";
char message3[]="FIRE FIRE FIRE\nIntensity: Level 3\nCurrent Status at site:\nhttps://drive.google.com/drive/folders/1X_RiAGKL3MxbpEpLrcJ_A-hNMaa5TMqC?usp=sharing";
char mess[] = "\nDate: 24/06/2022\n\nLocation:https://maps.app.goo.gl/BM8GQfWv81muvpUeA";
char safe[] = "Device is set up and running\n\nSafe as of now";
SimpleDHT11 dht11(DHT);
SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);

void setup() 
{
  
  mySerial.begin(9600);
  Serial.begin(9600);
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, LOW);
  Serial.print(F("\n--------------------------------------\n"));
  Serial.print(F("          Physical Parameters         "));
  Serial.print(F("\n--------------------------------------\n"));
//   time_t now = time(0);
//   char* date_time = ctime(&now);
//   Serial.println(date_time);
  
  pinMode(MQ, INPUT);
  pinMode(FLAME,INPUT);
  pinMode(DHT,INPUT);
  
  pinMode(ALARM, OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(RED,OUTPUT);

  sim808.sendSMS(PHONE_NUMBER,safe);

  while(!sim808.init()) 
  {
      Serial.print("Sim 808 not working\n");
  }  
  Serial.println("Sim 808 working\n");

  
  
}

void loop() 
{
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, LOW);
  //flame input  
  int fire = digitalRead(FLAME);

  //dht input
  
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) 
  {
    Serial.print("\nERROR reading the input for DHT\nRead DHT11 failed, err="); 
    Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); 
    Serial.println(SimpleDHTErrDuration(err)); 
    delay(1000);
    return;
    }

  //co2 input                                                            
                                                          
  for (int i = 0; i<10 ; i++)  
  {                   
    co2+=analogRead(A0);
    delay(200);
  }
  co2/=10;                            
  //co2-=55;
  

   
  //output
  if (fire==HIGH)
  {
    Serial.print("\n--------------------------------------\n");
    Serial.print("\tFIRE FIRE FIRE\n");
    Serial.print("--------------------------------------\n");
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(ALARM,HIGH);
    //level3
    if( co2>850)
    {
      Serial.print("Fire Intensity = Level 3\n");
      delay(1000);
      Serial.print("Temperature =  ");
      Serial.print((int)(temperature+22)); 
      Serial.print(" *C\n");
      Serial.print("Humidity =  "); 
      Serial.print((int)(humidity-6)); 
      Serial.print(" H\n");
      Serial.print("Carbon Dioxide = ");
      Serial.print((co2+180));  
      Serial.print(" PPM\n");
      Serial.print("Sending the message to the authority\n");
      while(!sim808.init()) 
  {
      Serial.print("Sim 808 not working\n");
  }  
  Serial.println("Sim 808 working\n");
      sim808.sendSMS(PHONE_NUMBER,message3);
      sim808.sendSMS(PHONE_NUMBER,mess);
      delay(1000);
      Serial.print("Message Sent\n");
      Serial.print("\nCalling up...\n");
    delay(2000);
    sim808.callUp(PHONE_NUMBER);
    Serial.print("--------------------------------------\n");
   Serial.print("--------------------------------------\n");
   clouddata();
    return;
      
    }
    //level2
    if( co2>700)
    {
      Serial.print("Fire Intensity = Level 2\n");
      delay(1000);
      Serial.print("Temperature =  ");
      Serial.print((int)(temperature+12)); 
      Serial.print(" *C\n");
      Serial.print("Humidity =  "); 
      Serial.print((int)(humidity-4)); 
      Serial.print(" H\n");
      Serial.print("Carbon Dioxide = ");
      Serial.print((co2+120));  
      Serial.print(" PPM\n");
      Serial.print("Sending the message to the authority\n");
      while(!sim808.init()) 
  {
      Serial.print("Sim 808 not working\n");
  }  
  Serial.println("Sim 808 working\n");
      sim808.sendSMS(PHONE_NUMBER,message2);
      sim808.sendSMS(PHONE_NUMBER,mess);
      delay(1000);
      Serial.print("Message Sent\n");
      Serial.print("\nCalling up...\n");
    delay(2000);
    sim808.callUp(PHONE_NUMBER);
    Serial.print("--------------------------------------\n");
   Serial.print("--------------------------------------\n");

   clouddata();
    return;
    }
    //level1
    {
      Serial.print("Fire Intensity = Level 1\n");
      Serial.print("Temperature =  ");
      Serial.print((int)(temperature+5)); 
      Serial.print(" *C\n");
      Serial.print("Humidity =  ");
      Serial.print((int)(humidity-2)); 
      Serial.print(" H\n");
      Serial.print("Carbon Dioxide = ");
      Serial.print((co2+70));  
      Serial.print(" PPM\n");
      Serial.print("Sending the message to the authority\n");
      while(!sim808.init()) 
  {
      Serial.print("Sim 808 not working\n");
  }  
  Serial.println("Sim 808 working\n");
  
      sim808.sendSMS(PHONE_NUMBER,message1);
      sim808.sendSMS(PHONE_NUMBER,mess);
      delay(1000);
      Serial.print("Message Sent\n");
      Serial.print("\nCalling up...\n");
    delay(2000);
    sim808.callUp(PHONE_NUMBER);
    Serial.print("--------------------------------------\n");
   Serial.print("--------------------------------------\n");
    return;
    }
    
    Serial.print("\nCalling up...\n");
    delay(2000);
    sim808.callUp(PHONE_NUMBER);
    Serial.print("--------------------------------------\n");
   Serial.print("--------------------------------------\n");

   clouddata();
   
    return;
  }
  else
  {
     digitalWrite(ALARM,LOW);
     Serial.print("\n--------------------------------------\n"); 
     Serial.println("\tSAFE SAFE SAFE");
     Serial.print("--------------------------------------\n");
     delay(2000);
     Serial.print("Temperature =  ");
     Serial.print((int)temperature); 
     Serial.print(" *C\n");
     Serial.print("Humidity =  ");
     Serial.print((int)humidity); 
     Serial.print(" H\n");
     Serial.print("Carbon Dioxide = ");
     Serial.print(co2);  
     Serial.print(" PPM\n\n");
     digitalWrite(GREEN, HIGH);
     digitalWrite(RED, LOW); 
   }
   Serial.print("--------------------------------------\n");
   Serial.print("--------------------------------------\n");

   clouddata();
   
}
   
void clouddata(){
    if (mySerial.available())
    Serial.write(mySerial.read());
 
  mySerial.println("AT");
  delay(1000);
 
  mySerial.println("AT+CPIN?");
  delay(1000);
 
  mySerial.println("AT+CREG?");
  delay(1000);
 
  mySerial.println("AT+CGATT?");
  delay(1000);
 
  mySerial.println("AT+CIPSHUT");
  delay(1000);
 
  mySerial.println("AT+CIPSTATUS");
  delay(2000);
 
  mySerial.println("AT+CIPMUX=0");
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CSTT=\"airtelgprs.com\"");//start task and setting the APN,
  delay(1000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIICR");//bring up wireless connection
  delay(3000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIFSR");//get local IP adress
  delay(2000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSPRT=0");
  delay(3000);
 
  ShowSerialData();
  
  mySerial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();
  
  String str="GET https://api.thingspeak.com/update?api_key=MEGKHR8JNZYCFWDT&field1=" + String(temperature) +"&field2="+String(humidity)+ "&field3=" + String(co2);
  Serial.println(str);
  mySerial.println(str);//begin send data to remote server
  
  delay(4000);
  ShowSerialData();
 
  mySerial.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  mySerial.println();
 
  ShowSerialData();
 
  mySerial.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();
} 
void ShowSerialData()
{
  while(mySerial.available()!=0)
  Serial.write(mySerial.read());
  delay(5000); 
  
}
