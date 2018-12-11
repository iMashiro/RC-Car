#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define FrontMotorSpeed 5 //RIGHT - D1
#define FrontMotorDir   0 //        D3
#define BackMotorSpeed  4 //LEFT    D2
#define BackMotorDir    2 //        D4

// Initializing variables for connection.
char auth[] = ""; // Auth token from Blynk app.
char ssid[] = ""; // Wifi id to connect.
char pass[] = ""; // Password.

// Setting a minimum parameter for starting a movement.
int minRange = 312;
int maxRange = 712;

// Setting the min and max speeds of the DC motors.
int minSpeed = 450;
int maxSpeed = 1020;
int noSpeed = 0;

// Function to convert the parameters of analogic from blynk in movement.
void moveControl(int x, int y)
{
  // Move foward
  if(y >= maxRange && x >= minRange && x <= maxRange)
  {
    digitalWrite(BackMotorDir,LOW);
    analogWrite(FrontMotorSpeed,noSpeed);
    analogWrite(BackMotorSpeed,maxSpeed);
  }
 
  // Move forward and right
  else if(x >= maxRange && y >= maxRange)
  {
    digitalWrite(BackMotorDir,LOW);
    digitalWrite(FrontMotorDir,HIGH);
    analogWrite(BackMotorSpeed,maxSpeed);
    analogWrite(FrontMotorSpeed,maxSpeed);
  }

  // Move forward and left
  else if(x <= minRange && y >= maxRange)
  {
    digitalWrite(FrontMotorDir,LOW);
    digitalWrite(BackMotorDir,LOW);
    analogWrite(FrontMotorSpeed,maxSpeed);
    analogWrite(BackMotorSpeed,maxSpeed);
  }

  // Neutral
  else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
    analogWrite(FrontMotorSpeed,noSpeed);
    analogWrite(BackMotorSpeed,noSpeed);
  }
  
  // Neutral and left
  else if(x <= minRange && y >= minRange && y <= maxRange)
  {
    digitalWrite(FrontMotorDir,LOW);
    analogWrite(FrontMotorSpeed,maxSpeed);
    analogWrite(BackMotorSpeed,noSpeed);
  }
  
  // Neutral and right
  else if(x >= maxRange && y >= minRange && y <= maxRange)
  {
    digitalWrite(FrontMotorDir,HIGH);
    analogWrite(FrontMotorSpeed,maxSpeed);
    analogWrite(BackMotorSpeed,noSpeed);
  }

  // Move back
  else if(y <= minRange && x >= minRange && x <= maxRange)
  {
    digitalWrite(BackMotorDir,HIGH);
    analogWrite(FrontMotorSpeed,noSpeed);
    analogWrite(BackMotorSpeed,maxSpeed);
  }
  
  // Move back and right
  else if(y <= minRange && x <= minRange)
  {
    digitalWrite(BackMotorDir,HIGH);
    digitalWrite(FrontMotorDir,LOW);
    analogWrite(BackMotorSpeed,maxSpeed);
    analogWrite(FrontMotorSpeed,maxSpeed); 
  }

  // Move back and left
  else if(y <= minRange && x >= maxRange)
  {
    digitalWrite(FrontMotorDir,HIGH);
    digitalWrite(BackMotorDir, HIGH);
    analogWrite(FrontMotorSpeed,maxSpeed);
    analogWrite(BackMotorSpeed,maxSpeed);
  }
}

void setup(){
  Blynk.begin(auth, ssid, pass);
  
  // Initial settings for motors off and direction forward
  
  pinMode(FrontMotorSpeed, OUTPUT);
  pinMode(BackMotorSpeed, OUTPUT);
  pinMode(FrontMotorDir, OUTPUT);
  pinMode(BackMotorDir, OUTPUT);
 
  digitalWrite(FrontMotorSpeed, LOW);
  digitalWrite(BackMotorSpeed, LOW);
  digitalWrite(FrontMotorDir, HIGH);
  digitalWrite(BackMotorDir,HIGH); 
}

void loop()
{ 
  Blynk.run();
}

// Receiving paramaters from analogical in Blynk app with virtual pin 2
BLYNK_WRITE(V2)
{
  int x = param[0].asInt();
  int y = param[1].asInt();
  moveControl(x,y);
} 
