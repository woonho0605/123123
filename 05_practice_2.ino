#define PIN_LED 7
unsigned int count, toggle;

void setup(){
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial){;
  
  }
  Serial.println("Hello World!");
  count = toggle = 0;
  digitalWrite(PIN_LED, toggle);
  delay(1000);
  }



  void loop(){
      while(1) {
    Serial.println(++count);
    toggle = (++toggle);
    digitalWrite(PIN_LED, toggle) ;
    delay(100);
    toggle = (--toggle);
    digitalWrite(PIN_LED, toggle) ;
    delay(100);
    if (count == 6){
    break;
    }
      }
    while(1) {
      digitalWrite(PIN_LED, 1);
    }
  }
