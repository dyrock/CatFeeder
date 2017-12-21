// testing a stepper motor with a Pololu A4988 driver board or equivalent
// on an Uno the onboard led will flash with each step
// this version uses delay() to manage timing

byte directionPin = 9;
byte stepPin = 8;
int numberOfSteps = 100;
byte ledPin = 13;
int pulseWidthMicros = 20;  // microseconds

int minStepInterval = 8000;
int maxStepInterval = 12000;  // microseconds
int diff = (maxStepInterval-minStepInterval)/50; // Within 90 degree, accelerates to full speed

void setup() { 
  // Set pins
  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Set serial connection
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Starting StepperTest: Enter number to turn stepper motor (use sign to indicate direction)");
  digitalWrite(ledPin, LOW);
  
  delay(2000);
}

void loop() { 
  if (Serial.available())
  {
    int steps = Serial.parseInt();
    while (Serial.read() != '\n'){}
    if (steps > 0) {
      digitalWrite(directionPin, HIGH);
      Serial.println("\nDirection set to +");
    } else {
      digitalWrite(directionPin, LOW);
      Serial.print("\nDirection set to -");
      steps = -steps;
    }
    Serial.print(steps);

    for (int i = 0; i < steps; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(20);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(max(maxStepInterval - diff*(steps/2-abs(i-steps/2)), minStepInterval));
    }
  }
}
