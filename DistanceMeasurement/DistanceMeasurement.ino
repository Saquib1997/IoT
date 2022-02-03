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
const int ledpin = 19;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float Dist;
static int count = 0;

void setup() {

  Serial.begin(115200); // Starts the serial communication
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(ledpin, OUTPUT);
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
  
  if(distanceCm < 16){
    count++;
    Serial.print("The number of person present in room is: ");
    Serial.println(count);
    digitalWrite(ledpin, HIGH);
  }
  else{
    digitalWrite(ledpin, LOW);
  }
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  //-------------Sending Data to ThingSpeak Cloud---------------//
  //ThingSpeak.writeField(myChannelField,ChannelField3, Dist, myWriteAPIKey);
  //delay(500);

}

