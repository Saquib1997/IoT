int ledPin = 13; // choose the pin for the LED
int PIR = 4; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status


void setup() {

pinMode(ledPin, OUTPUT); // declare LED as output
pinMode(PIR, INPUT); // declare sensor as input
Serial.begin(115200);

}


void loop(){

val = digitalRead(PIR); // read input value

Serial.println(val);
delay(4000);

if (val == HIGH) { // check if the input is HIGH
digitalWrite(ledPin, HIGH); // turn LED ON
if (pirState == LOW) {
// we have just turned on
Serial.println("Motion detected!");
// We only want to print on the output change, not state
pirState = HIGH;
}
} 
else {
digitalWrite(ledPin, LOW); // turn LED OFF
if (pirState == HIGH){
// we have just turned of
Serial.println("Motion ended!");
// We only want to print on the output change, not state
pirState = LOW;
}
}

}
