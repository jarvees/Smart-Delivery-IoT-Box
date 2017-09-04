//  _ ___ _______     ___ ___ ___  ___ _   _ ___ _____ ___ 
// / |_  )__ /   \   / __|_ _| _ \/ __| | | |_ _|_   _/ __| 
// | |/ / |_ \ |) | | (__ | ||   / (__| |_| || |  | | \__ \ 
// |_/___|___/___/   \___|___|_|_\\___|\___/|___| |_| |___/ 
// 
// The Unnamed Circuit
// 
// Made by karthiknagaraj561 karthiknagaraj561
// License: CC-BY-SA 3.0
// Downloaded from: https://circuits.io/circuits/4845340-the-unnamed-circuit

#include <Servo.h>
#include <Keypad.h>
#include <SoftwareSerial.h>
 
//SIM800 TX is connected to Arduino D8
#define SIM800_TX_PIN 10
 
//SIM800 RX is connected to Arduino D7
#define SIM800_RX_PIN 13


//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);




Servo servo_Motor; 
char a[4];
int k=1;// HIGH MEANS NO OBSTACLE
int w=0;
int i=1;
int j=0;
int done=0;
int isObstaclePin = 12;  // This is our input pin
int isObstacle = HIGH;  // HIGH MEANS NO OBSTACLE
char password[4];
int position = 0;
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS] = { 8, 7, 6, 9 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



void setup()
{
   servo_Motor.attach(11);  // attaches the servo on pin 9 to the servo object
   pinMode(isObstaclePin, INPUT);
   Serial.begin(9600);
 }

void loop() {
  while(isObstacle == HIGH && done<= 3)
  {
    Serial.begin(9600);
     Serial.println("OBSTACLE!!, OBSTACLE!!");
    if(k==1)
      { 
      servo_Motor.write(90);
         sms();
         k++;
        
      }done++;
  }
 while(done == 4)
 { 
   char key = keypad.getKey();
   Serial.println(key);
   Serial.println(password[0]);
   while(key == password[0])
    { 
       char key = keypad.getKey(); 
       Serial.println(key);
       Serial.println(password[1]);
      while(key == password[1])
      {
        char key = keypad.getKey(); 
         Serial.println(key);
         Serial.println(password[2]);
        while(key == password[2])
        {
          char key = keypad.getKey(); 
           Serial.println(key);
           Serial.println(password[3]);
          while(key == password[3])
          {
             servo_Motor.write(0);
          }
        }
      }
   }
 }
}
 void sms(){
  char num[4];
  int temp1;
  int temp2;
  int sade;
  int i =0;
  int k=1;

  //Begin serial comunication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  while(!Serial);
   
  //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(9600);
  delay(1000);
 
  Serial.println("Setup Complete!");
  Serial.println("Sending SMS...");
  
   
  //Set SMS format to ASCII
  serialSIM800.write("AT+CMGF=1\r\n");
  delay(1000);
 
  //Send new SMS command and message number
  serialSIM800.write("AT+CMGS=\"09513489357\"\r\n");
  delay(1000);
   
  //Send SMS content
 sade=randum();
 Serial.println(sade);
 while (sade > 0) {
 int digit = sade % 10;
 num[i]=digit;
 sade=sade/10;
 Serial.println(num[i]);
 i++;
}
temp1=num[0];
num[0]=num[3];
num[3]=temp1;
temp2=num[1];
num[1]=num[2];
num[2]=temp2;


num[0]=num[0]+48;
num[1]=num[1]+48;
num[2]=num[2]+48;
num[3]=num[3]+48;
for(int j=0;j<=3;j++)
{
  Serial.println(num[j]);
  password[j]=num[j];
}
   // Push each char 1 by 1 on each loop pass
   serialSIM800.write("parcel is placed and the password is=");
  for(int j=0;j<=3;j++)
  {
  serialSIM800.write(num[j]);
  }
  delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
  serialSIM800.write((char)26);
  delay(1000);
     
  Serial.println("SMS Sent!");
 
 }
 

int randum(){
  long randNumber;
  int num[4];
  int temp1,temp2;
  Serial.begin(9600);
  randomSeed(analogRead(0));
   randNumber = random(1000, 9999);
  Serial.println(randNumber);
  return randNumber;

  }



void taken()
{

   Serial.begin(9600);
  while(!Serial);
   
  //Being serial communication witj Arduino and SIM800
  serialSIM800.begin(9600);
  delay(1000);
 
  Serial.println("Setup Complete!");
  Serial.println("Sending SMS...");
  
   
  //Set SMS format to ASCII
  serialSIM800.write("AT+CMGF=1\r\n");
  delay(1000);
 
  //Send new SMS command and message number
  serialSIM800.write("AT+CMGS=\"09513489357\"\r\n");
  delay(1000);
   
 
   // Push each char 1 by 1 on each loop pass
  
  serialSIM800.write("the parcel has been taken");
  
  delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
  serialSIM800.write((char)26);
  delay(1000);
     
  Serial.println("SMS Sent!");

 }
 
