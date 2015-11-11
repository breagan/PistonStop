/*
    PWR 5 ---|  |---   Vcc
   ADC  3 ---|  |---   2 TGT
  Calib 4 ---|  |---   1 LOW pwm  
      gnd ---|  |---   0 High pwm 
 */

// the setup routine runs once when you press reset:
int highvalue =0;
int lowvalue = 1023;
int diff = 0;
int x = 1;
int PistonTarget = 0;
int adcaverage = 0;
String calibrate = "no";
int ledRdy = 4;
int ledLow = 1;
int ledTgt = 2;
int ledHigh = 0;
int ldrADC = 3;
int ADCrange = 4;   // tgt illums within this range.  2 * ADCrange = window +/-

void setup() {

  pinMode(ledHigh, OUTPUT); //0  pwm
  pinMode(ledLow, OUTPUT);  //1  pwm
  pinMode(ledTgt, OUTPUT);  //2
  pinMode(ledRdy, OUTPUT);  //4 
  pinMode(ldrADC,INPUT);      ///3  Analog input
  
    x = 255;
    while( x != 0)
  {
  analogWrite(ledHigh, x);
  analogWrite(ledLow, x);
  delay(5);
  x--;
  }
    digitalWrite(ledTgt, HIGH);
    
    delay(350);
    digitalWrite(ledTgt, LOW);
  
  while( x < 255)
  {
  analogWrite(ledHigh, x);
  analogWrite(ledLow, x);
  delay(5);
  x++;
  }
digitalWrite(ledLow, LOW);
digitalWrite(ledHigh,LOW);
delay(350);
digitalWrite(ledRdy, HIGH);
x=1;
}
  
// the loop routine runs over and over again forever:
void loop() {
 
  // read the input on analog pin 3:
  long voltage = analogRead(ldrADC);

  // 10K to ground on LDR
  //float sensorValue = voltage/4;   // ldr ranges from mv to 4.73v  
  float sensorValue = voltage;   // ldr ranges from mv to 4.73v 
  //float ADCraw = voltage * 216.279;  //  converts ADC to 0-1023  216.279 = voltage/1023
  
  adcaverage = adcaverage + sensorValue;
  
  if(x == 3)
    {
      sensorValue = adcaverage/3;
        if(sensorValue > highvalue)
          {
            highvalue = sensorValue;
          }
        if(sensorValue < lowvalue)
          {
            lowvalue = sensorValue;
          } 
          diff = highvalue - lowvalue;
        
        if(diff > 400)
           {
              calibrate = "yes";
              PistonTarget = highvalue * .70;
                
                int pwmHigh = map(sensorValue, PistonTarget, 1023, 0, 255);
                int pwmLow = map(sensorValue, 0, PistonTarget, 255, 0);
              
              
              digitalWrite(ledRdy, LOW);
      
              //        lights here
              if(sensorValue > PistonTarget - ADCrange && sensorValue < PistonTarget + ADCrange)
                    {
                      digitalWrite(ledTgt, HIGH);
                    }
              else 
                    {
                       digitalWrite(ledTgt, LOW);
                     }
              //  High light   
              if(sensorValue > PistonTarget + ADCrange)
                     {
                       analogWrite(ledHigh,pwmHigh);      ////////////////
                     }
               else 
                     {
                        digitalWrite(ledHigh, LOW);
                     }
                  // low light  
                if(sensorValue < PistonTarget - ADCrange)
                      {
                        analogWrite(ledLow,pwmLow);       /////////////////////
                      }
                 else {
                         digitalWrite(ledLow, LOW);
                       }

          }
        else
          {
            calibrate = "no";
          }
    delay(100);
    adcaverage = 0;
    x = 0;
   }
  x = x + 1;
}
