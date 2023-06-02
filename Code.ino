#include <SoftwareSerial.h>
SoftwareSerial SIM900(7,8); //rx,tx
String Textforsms;
int Buzzerpin = 5;
int Flamepin = 4;

boolean Flame_Sensor_Value = HIGH;

void setup()
{
randomSeed(analogRead(0));
Serial.begin(9600);
SIM900.begin(9600); // original 19200. while enter 9600 for sim900A
Serial.println(" logging time completed!");
pinMode (Buzzerpin, OUTPUT);
pinMode (Flamepin, INPUT);
Serial.begin(9600);
 
}

void loop()
{
  Flame_Sensor_Value = digitalRead (Flamepin);
  
  if (Flame_Sensor_Value == LOW)
  {
    Textforsms = "\n Fire Detected";
    digitalWrite(Buzzerpin, HIGH);
    sendSMS (Textforsms);
    //Serial.println("AT+CMGF=1");
    delay(1000);
    //Serial.println("AT+CMGS=\"+919404086387\"");
    Serial.println("Fire IN THE HOUSE");
    //Serial.println((char)26);
    delay(500);
  }
  else
  {
    digitalWrite(Buzzerpin,LOW);
  }
}
void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(1000);
 SIM900.println("AT + CMGS = \"+919404086387\"");  // recipient's mobile number, in international format
 
  delay(1000);
  SIM900.println(message);                         // message to send
  delay(1000);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(1000); 
  SIM900.println();
  delay(100);                                     // give module time to send SMS
 
}
