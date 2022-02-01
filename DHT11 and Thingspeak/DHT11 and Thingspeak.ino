#include <WiFi.h>       //include library for wifi
#include "DHT.h"        //include library for DHT sensor
#include "ThingSpeak.h"  //include library for wifi

  //Provide your wifi details ----------------------------
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;
 //-------------------------------------------------------
#define DHTPIN 22 // DHT11 Data pin connected to esp32 pin no.

float temperature;   // Variable to store temperature
float humidity;      // Variable to store Humidity
DHT dht(DHTPIN, DHT11);
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;       //channal id from thingspeak
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;   // write api kay from thingspeak
const int ChannelField1 =1;   //channel field 1 for temp
const int ChannelField2 =2;   //channel field 1 for humidity   

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  dht.begin();
  ThingSpeak.begin(client);  // Initialize ThingSpeak  
  WiFi.mode(WIFI_STA);

}

void loop() {
  // put your main code here, to run repeatedly:

  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(1000);     
    } 
    Serial.println("\nConnected.");
  }  
  temperature=dht.readTemperature();    //read temperature
  humidity=dht.readHumidity();          //read Humidity


  if (isnan(temperature) || isnan(humidity)
   {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

Serial.print(F("%  Temperature: "));
Serial.print(temperature);

Serial.print(F(" Humidity: "));
Serial.print(humidity);

  
delay(10000);

ThingSpeask.writeField( myChannelNumber,ChannelField1,temperature,myWriteAPIKey);
ThingSpeask.writeField( myChannelNumber,ChannelField2,humidity,myWriteAPIKey);

delay(1000);
}
