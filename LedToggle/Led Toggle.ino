const int LED=22;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(LED, HIGH);
  Serial.print("LED is ON\n");
  delay(2000);
  
  digitalWrite(LED, LOW);
  Serial.print("LED is OFF\n");
  delay(2000);
}

