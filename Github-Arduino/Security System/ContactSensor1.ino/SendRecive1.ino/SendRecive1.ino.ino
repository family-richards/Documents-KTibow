
int InputContact = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, INPUT);
  Serial.begin(9600);
  Serial.print("Serial.begin Rund");
  Serial.println(" ");
  digitalWrite(13, HIGH); int conect = HIGH;
}

void loop() {
  // put your main code here, to run repeatedly:
  InputContact = digitalRead(12);
  if ((conect = HIGH && (InputContact = /*ON*/))) {
    Serial.print("Closed!")
    Serial.println(" ");
    
  } else {
    Serial.print("Alert! Alert! OPEN!");
    Serial.println(" ");
  }
}
