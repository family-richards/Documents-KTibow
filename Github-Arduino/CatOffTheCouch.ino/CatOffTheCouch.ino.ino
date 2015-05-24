
int OnOffRead = LOW;

const int MOTIONPIN = 1;

const int PIEZO = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(PIEZO, OUTPUT);
pinMode(MOTIONPIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadSend(MOTIONPIN, PIEZO);
}
void ReadSend(InputPin, OutputPin) {
  OnOffRead = digitalRead(InputPin);
  if (OnOffRead == HIGH) {

