#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 3 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!

#define IR_SENSOR 0
#define PIN_SERVO 10
#define PIN_LED   9


#define _DUTY_MIN 500  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1500 // servo neutral position (90 degree)
#define _DUTY_MAX 2500 // servo full counter-clockwise position (180 degree)
#define _DIST_MIN 100.0   // minimum distance to be measured (unit: mm)
#define _DIST_MAX 250.0
#define _EMA_ALPHA 0.3

#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)

float  dist_ema, dist_prev = _DIST_MAX;
Servo myservo;
unsigned long last_loop_time;   // unit: msec

void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  pinMode(PIN_LED, OUTPUT);
  pinMode(IR_SENSOR, INPUT);
  
  Serial.begin(57600);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;
  float dist;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  // Read IR Sensor value !!!
  a_value = analogRead(IR_SENSOR);
  // Convert IR sensor value into distance !!!
  dist = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;
  // we need distance range filter here !!!
  if (dist < _DIST_MIN) {
    dist = dist_prev;
    digitalWrite(PIN_LED, 1);           
  } else if (dist > _DIST_MAX) {
    dist = dist_prev;          
    digitalWrite(PIN_LED, 1); 
  } else {    
    dist_prev = dist;
    digitalWrite(PIN_LED, 0);
  }
  // we need EMA filter here !!!
  dist_ema = _EMA_ALPHA * dist + (1-_EMA_ALPHA) * dist_ema;
  if(dist_ema <= _DIST_MIN){
    duty = _DUTY_MIN;
    myservo.writeMicroseconds(duty); //500
    delay(50);
  }else if (dist_ema >= _DIST_MAX){
    duty = _DUTY_MAX;
    myservo.writeMicroseconds(duty); //2500
    delay(50);
  }else{
    duty = (int)((dist_ema - 100) * (40/3)) + 500;
    myservo.writeMicroseconds(duty); 
    delay(50);
    }



  // print IR sensor value, distnace, duty !!!
  Serial.print("MIN: "); Serial.print(_DIST_MIN);
  Serial.print(",IR:"); Serial.print(a_value);
  Serial.print(",dist:"); Serial.print(dist);
  Serial.print(",ema:"); Serial.print(dist_ema);
  Serial.print(",servo:"); Serial.print(duty);
  Serial.print(",Max:"); Serial.print(_DIST_MAX);
  Serial.println("");
}
