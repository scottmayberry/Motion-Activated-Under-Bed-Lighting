String state = "";
String LIGHT = "LIGHT";
String DARK = "DARK";
String onOff = "";
String ON = "ON";
String OFF = "OFF";
String MOVEMENT = "MOVEMENT";
String TIMERDELAY = "TIMERDELAY";
int delayNum = 100;
int timerDelay = 20; //seconds
int checker = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  state = LIGHT;
  digitalWrite(2, HIGH);
  delay(100);
  pinMode(2, OUTPUT);
  delay(100);
  digitalWrite(2, HIGH);
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(state == LIGHT || state == DARK)
  {
    int an = analogRead(A0);
    Serial.println(an);
    if(an > 1008 || onOff == ON)
      state = DARK;
    else
      state = LIGHT;
  }
  if(state == DARK)
  {
    int ir_a = analogRead(A1);
    int ir_b = analogRead(A2);
    int ir_c = analogRead(A3);
    int ir = ir_a + ir_b + ir_c;
    Serial.println(ir_c);
    if(ir > 600)
    {
      state = MOVEMENT;
    }
  }else
  if(state == MOVEMENT)
  {
    digitalWrite(2, LOW);
    checker = timerDelay*1000;
    state = TIMERDELAY;
  }else
  if(state == TIMERDELAY)
  {
    onOff = ON;
    checker = timerDelay*1000;
    state = LIGHT;
  }
  Serial.println(state);
  delay(delayNum);
  if(onOff == ON)
  {
    checker = checker - delayNum;
    Serial.println(checker);
    if(checker <= 0)
    {
      onOff = OFF;
      digitalWrite(2,HIGH);
      delay(500);
    }
  }
}
