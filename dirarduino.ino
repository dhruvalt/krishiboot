const int pwmpin = 2;
const int pwmpin2 = 4;
const int pwmpinout = 9;
const int  dir1=6;
const int  dir2=7;
const int dir3= 11;
const int dir4=12;
int dutyPercent = 40; //max is 63
float dutyCycle;
void setup() {
  pinMode(pwmpinout,OUTPUT);
  pinMode(dir1,OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(dir3,OUTPUT);
  pinMode(dir4,OUTPUT);
  pinMode(pwmpin, INPUT);
  pinMode(pwmpin2, INPUT);
  Serial.begin(9600);
   TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  TCCR1A |= (1 << COM1A1) | (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10);
  ICR1 = 1000; // 16MHz /1000= 16kHz
  updatePWM();
    digitalWrite(dir1,HIGH);
    digitalWrite(dir2,HIGH);
    digitalWrite(dir3,HIGH);
    digitalWrite(dir4,HIGH);
}
void loop() {
    //   digitalWrite(dir1,HIGH);
    //  digitalWrite(dir2,HIGH);
    //  digitalWrite(dir3,HIGH);
    //  digitalWrite(dir4,HIGH);
    float duty1 = readpwm(pwmpin);
    Serial.println("duty1");
    Serial.println(duty1);
    control(duty1,dir1, dir2);
    float duty2 = readpwm(pwmpin2);
    control(duty2, dir3,dir4);
    Serial.println("duty2");
    Serial.println(duty2);
  delay(100);
}

float readpwm(int pin){
    unsigned long hightime, lowtime, period;
    hightime=pulseIn(pin, HIGH);
    lowtime=pulseIn(pin, LOW);
    period=hightime+lowtime;
    if(period == 0) return 0;
    float duty= (hightime*100)/period;
    return duty;
}

float control(float duty, int pina, int pinb){
    if (duty<7.5){
        digitalWrite(pina, HIGH);
        digitalWrite(pinb, LOW);
  } else if (duty > 8.5) {
      digitalWrite(pina, HIGH);
      digitalWrite(pinb, LOW);
  } else {
      digitalWrite(pina, HIGH);
      digitalWrite(pinb, HIGH);
}
}
void updatePWM() {
  OCR1A = (ICR1 * dutyPercent) / 100;
}
