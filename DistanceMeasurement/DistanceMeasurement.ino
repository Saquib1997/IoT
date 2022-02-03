#include "ThingSpeak.h"
#include "WiFi.h"

//-------Enter your WiFi Details------//
char ssid[] = "SaQuiB";       //SSID
char pass[] = "Saquib@1997";  //Password
//-----------------------------------//

WiFiClient client;

//-------------ThingSpeak Details-----------------//
unsigned long myChannelField = 1644754; //Channel ID
const int ChannelField3 = 3; //for Temperature
const char * myWriteAPIKey = "92QBGYQMC19UFF16"; //Your Write API Key
//-----------------------------------------------//

const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float Dist;

void setup() {

  Serial.begin(115200); // Starts the serial communication
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {

  //-----------------WiFi Setup-------------------//
  if(WiFi.status()!= WL_CONNECTED)
  {
    Serial.print("Attempting to Connect to SSID: ");
    Serial.println(ssid);
  }
  while(WiFi.status()!= WL_CONNECTED)
  {
    WiFi.begin(ssid,pass);
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nConnected.");
  //--------------------------------------------//

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  Dist = distanceCm; 
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

 //-------------Sending Data to ThingSpeak Cloud---------------//
  ThingSpeak.writeField(myChannelField,ChannelField3, Dist, myWriteAPIKey);
  
  delay(1000);

}

