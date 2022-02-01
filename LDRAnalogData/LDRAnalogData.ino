const int ldr=22;
const int led=21;
int val;

void setup() {

  // put your setup code here, to run once:

  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(115200);
}

void loop() {

  // put your main code here, to run repeatedly:
  
  val = analogRead(ldr);
  Serial.println(val);
  if(val >= 1500){
    digitalWrite(led, 1);
  }
  else{
    digitalWrite(led, 0);
    delay(1000);
  }
}
