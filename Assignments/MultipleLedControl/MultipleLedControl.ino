const int LED1=12;
const int LED2=13;
const int LED3=22;

void setup() {

  // put your setup code here, to run once:

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  Serial.begin(115200);
}

void loop() {

  // put your main code here, to run repeatedly:
  
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);  
  Serial.print("LED1 is ON and LED2 and LED3 is OFF\n");
  delay(1000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  Serial.print("LED2 is ON and LED1 and LED3 is OFF\n");
  delay(1000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  Serial.print("LED3 is ON and LED1 and LED2 is OFF\n");
  delay(1000);   
}
