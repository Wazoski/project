#define Ultrasonic_Trig_PIN 3
#define Ultrasonic_Echo_PIN 2
#define POT_PIN A0
#define pir 7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Ultrasonic_Trig_PIN, OUTPUT); // Trig를 센서 입장에서 입력 받도록 아두이노가 출력해준다.
  pinMode(Ultrasonic_Echo_PIN, INPUT);  // Echo를 센서입장에서 출력하도록 아두이노가 입력받는다.
  pinMode(pir,INPUT);
}

void loop() {
  int ultra_val = 0;
  int light_val = 0;
  int pir_val = 0;
  int i;
  int tmp;
  String ultra_string = "";
  
  // ultrasonic
  digitalWrite(Ultrasonic_Trig_PIN,HIGH); // Trig를 발생한다.
  delayMicroseconds(10); // 10마이크로초를 HIGH 유지
  digitalWrite(Ultrasonic_Trig_PIN,LOW); // Trig를 멈춘다.
  ultra_val = (int)(((float)pulseIn(Ultrasonic_Echo_PIN,HIGH)/1000000) * 340 * 100 / 2); 
  // 이때 Echo가 HIGH하는 순간 시간을 읽어낸다.
  // 거리 = 시간*속력

  // light
  light_val = analogRead(POT_PIN);

  // pir
  if(digitalRead(pir)==HIGH){
    pir_val = 1;
  }else{
    pir_val = 0;
  }

  for(i=0;i<16;i++){
    tmp = ultra_val % 2;
    if(tmp == 1){
      ultra_string = "1" + ultra_string;
    }else{
      ultra_string = "0" + ultra_string;
    }
    ultra_val = ultra_val >> 1;
  }
  for(i=0;i<16;i++){
    tmp = light_val % 2;
    if(tmp == 1){
      ultra_string = "1" + ultra_string;
    }else{
      ultra_string = "0" + ultra_string;
    }
    light_val = light_val >> 1;
  }
  
  tmp = pir_val % 2;
  if(tmp == 1){
    ultra_string = "1" + ultra_string;
  }else{
    ultra_string = "0" + ultra_string;
  }
  
  Serial.println(ultra_string);
  
  delay(200);
}
