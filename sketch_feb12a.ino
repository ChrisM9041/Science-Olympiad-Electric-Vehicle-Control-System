
const int buttonPin = 4;   // LOW = pressed

const int motor1pin1 = 5;  
const int motor1pin2 = 6;  

#define encoder_ChA 2   
#define encoder_ChB 3   

volatile long encoderCount = 0;
volatile bool lastA = LOW;

const float wheelDiameter_cm = 6.5;      
const int encoderPPR = 185;               
const float targetDistance_cm = 720;   
const float stopCorrection_cm = -7.5;     
const float targetTime_s = 18.5;         

long targetCounts = 0;
bool runActive = false;
bool lastButtonState = LOW;
unsigned long startTime = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  pinMode(encoder_ChA, INPUT_PULLUP);
  pinMode(encoder_ChB, INPUT_PULLUP);

  Serial.begin(9600);

  lastA = digitalRead(encoder_ChA);

  float wheelCircumference_cm = wheelDiameter_cm * 3.14159;
  targetCounts = ((targetDistance_cm + stopCorrection_cm) / wheelCircumference_cm) * encoderPPR;

  attachInterrupt(digitalPinToInterrupt(encoder_ChA), encoderISR, CHANGE);
}

void loop() {
  // Button Detect
  bool buttonState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && buttonState == LOW) {
    // Button pressed: toggle run/reset
    encoderCount = 0;
    runActive = !runActive; 
    startTime = millis();   // start timing
    delay(200);             // debounce
  }

  lastButtonState = buttonState;

  // Run Control
  float wheelCircumference_cm = wheelDiameter_cm * 3.14159;
  float distance_cm = (encoderCount / (float)encoderPPR) * wheelCircumference_cm;

  if (runActive && encoderCount < targetCounts) {
    // Calculate elapsed time
    float elapsed_s = (millis() - startTime) / 1000.0;

    // Desired progress fraction (0.0 → 1.0)
    float targetFraction = elapsed_s / targetTime_s;

    // Current progress fraction (0.0 → 1.0)
    float currentFraction = (float)encoderCount / targetCounts;

    //Speed control
    float error = targetFraction - currentFraction;

    int motorPower = 0;
    if (error > 0) {
      motorPower = constrain((int)(error * 255), 255, 255);
    }

    analogWrite(motor1pin1, motorPower); // PWM speed control
    digitalWrite(motor1pin2, LOW);       // forward
  } 
  else {
    analogWrite(motor1pin1, 0);          // stop motor
    digitalWrite(motor1pin2, LOW);
  }

  // Serial Feedback
  Serial.print("Run: ");
  Serial.print(runActive ? "ACTIVE" : "IDLE");
  Serial.print(" | Count: ");
  Serial.print(encoderCount);
  Serial.print(" | Distance (cm): ");
  Serial.print(distance_cm);
  Serial.print(" | Time (s): ");
  Serial.println((millis() - startTime) / 1000.0);

  delay(20);
}

// ISR
void encoderISR() {
  bool A = digitalRead(encoder_ChA);
  bool B = digitalRead(encoder_ChB);

  if (!lastA && A) {   // count only rising edge
    if (B == LOW)
      encoderCount++;
    else
      encoderCount--;
  }

  lastA = A;
}
