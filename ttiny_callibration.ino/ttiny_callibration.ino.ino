/*
  ReadAnalogVoltage
  Reads an analog input on pin 0, converts it to voltage, and prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

 This example code is in the public domain.
 */

// the setup routine runs once when you press reset:
int highvalue =0;
int lowvalue = 10000;
int diff = 0;
int x = 1;
int PistonTarget = 0;
int adcaverage = 0;
String calibrate = "no";
//int ledPwr = 5;         // Reset pin
int ledRdy = 4;
int ledLow = 1;
int ledTgt = 2;
int ledHigh = 0;
int ldrADC = 3; 
int pwmvalue = 0;

//   rst 5 ---|  |---   Vcc
//   A3  3 ---|  |---   2 A1
//   A2  4 ---|  |---   1 pwm  
//     gnd ---|  |---   0 pwm 


void setup() {
  pinMode(ledRdy, OUTPUT);  
  pinMode(ledLow, OUTPUT);  
  pinMode(ledTgt, OUTPUT);  
  pinMode(ledHigh, OUTPUT);  
  pinMode(ldrADC,INPUT);   
    x = 255;
    while( x != 0)
  {
  analogWrite(ledHigh, x);
  analogWrite(ledLow, x);
  delay(10);
  x--;
  }
    digitalWrite(ledTgt, HIGH);
    
    delay(350);
    digitalWrite(ledTgt, LOW);
  
  while( x < 255)
  {
  analogWrite(ledHigh, x);
  analogWrite(ledLow, x);
  delay(10);
  x++;
  }
digitalWrite(ledLow, LOW);
digitalWrite(ledHigh,LOW);
delay(350);
digitalWrite(ledRdy, HIGH);
  
  
}
  
  
// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 3:
  long sensorValue = analogRead(ldrADC);
  // 10K to ground on LDR
  float voltage = sensorValue/4;   // ldr ranges from mv to 4.73v  
  //float ADCraw = voltage * 216.279;  //  converts ADC to 0-1023  216.279 = voltage/1023
  int pwmHigh = map(sensorValue, 0, 1023, 150, 0);
   int pwmLow = map(sensorValue, 0, 1023, 0, 150); 
 // analogWrite(ledHigh, pwmHigh);        // digitalWrite(ledTgt, HIGH);
 // analogWrite(ledLow, pwmLow);
  delay(100);
 // digitalWrite(ledTgt, LOW);
 // delay(500);
}
