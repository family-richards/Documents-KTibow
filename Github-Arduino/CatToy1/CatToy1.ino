
int CounterPin = 1;


    

void setup() {
  // put your setup code here, to run once:
pinMode(1, OUTPUT);
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  void WriteHighAll(NumberOfPins) {
  for(int NumDid = 0; NumDid != NumberOfPins; NumDid++;) {
    digitalWrite(CounterPin, HIGH);
    CounterPin++;
  }
  }
  WriteHighAll(13);
  

}


