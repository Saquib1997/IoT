// Smart Garbage Bin interfaced to BLYNK 
#include "DHT.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define DHTPIN 16     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

#define BLYNK_PRINT Serial

const int LED1=12; // red
const int LED2=13; // blue
const int LED3=14; // green
const int LED4 =27; //red

// You should get Auth Token in the Blynk App.
char auth[] = "cb88b0a487e947108aee25f384d773ba";

// WiFi credentials.
char ssid[] = "SaQuiB";
char pass[] = "Saquib@1997";

//int volt=512;
//int curent=1024;
const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float distanceCm;
float h ;
float t ;
String comment;

void setup() {
  dht.begin();
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {

  digitalWrite(trigPin, LOW);  // Clears the trigPin
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  
  distanceCm = duration * SOUND_SPEED/2;// Calculate the distance
  
  Serial.print("Distance (cm): "); // Prints the distance in the Serial Monitor
  Serial.println(distanceCm);
  
  Blynk.run();

  // Reading temperature
  t = dht.readTemperature();
  Serial.print("Temperature(deg C): ");
  Serial.println(t);

  if(t <= 20 && t >= 50)
  {
    Serial.println("Temperature Threshold Reached");
    digitalWrite(LED4, HIGH);
    delay(1000);
    digitalWrite(LED4, LOW);
    delay(1000);
  }

 if(distanceCm<10){
    comment="Bin full. Please remove garbage";
    Serial.println("Bin Full. Please remove garbage");
    digitalWrite(LED1,HIGH);
    digitalWrite(LED2,LOW);
    digitalWrite(LED3,LOW);
    Blynk.email("sdppawar78@gmail.com", "Garbage alert", "BIN IS FULL,PLEASE REMOVE GARBAGE");
   }
   if(distanceCm<18 && distanceCm>10){
    comment="Bin partially filled";
    Serial.println("Bin partially filled");
    digitalWrite(LED2,HIGH);
    digitalWrite(LED1,LOW);
    digitalWrite(LED3,LOW);
   }

   if( distanceCm>18){
    comment="Bin empty";
   Serial.println("Bin Empty.");
   digitalWrite(LED3,HIGH);
   digitalWrite(LED2,LOW);
   digitalWrite(LED1,LOW);
   }
 display();
  delay(1000);
}

// Sending Data to cloud
void display(){
  Blynk.virtualWrite(V1,t);
  Blynk.virtualWrite(V4,distanceCm);
  Blynk.virtualWrite(V5,comment);
}