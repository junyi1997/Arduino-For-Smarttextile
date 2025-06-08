//tone(pin, frequency) 讓接在pin的蜂鳴器發出frequency頻率的聲音
//noTone(pin)          讓接在pin的蜂鳴器不發生聲音。
#define Do  523
#define Re  587
#define Mi  659
#define Fa  698
#define So  784
#define La  880
#define Si  988
#define Do1  1046
#define Re1  1175
#define Mi1  1318
#define Fa1  1397
#define So1  1568
#define La1  1760
#define Si1  1976
//2=二分音符；4=四分音符；8=八分音符；16=十六分音符；以四分音符為1秒
int melody_num[] = {15,13,14,15,13,14,15,5,6,7,11,12,13,14,13,11,12,13,3,4,5,6,5,4,5,3,4,5,4,6,5,4,3,2,3,2,1,2,3,4,5,6,4,6,5,6,7,11,5,6,7,11,12,13,14,15,13,11,12,13,12,11,12,7,11,12,13,12,11,7,11,6,7,11,1,2,3,4,3,2,3,11,7,11,6,11,7,6,5,4,5,4,3,4,5,6,7,1,6,11,7,11,7,6,7,11,12,11,7,11,6,7};
int metempo_num[] = {8,16,16,8,16,16,16,16,16,16,16,16,16,16,8,16,16,8,16,16,16,16,16,16,16,16,16,16,8,16,16,8,16,16,16,16,16,16,16,16,16,16,8,16,16,8,16,16,16,16,16,16,16,16,16,16,8,16,16,8,16,16,16,16,16,16,16,16,16,16,8,16,16,8,16,16,16,16,16,16,16,16,16,16,8,16,16,8,16,16,16,16,16,16,16,16,16,16,8,16,16,8,16,16,16,16,16,16,16,16,16,16};
//int melody[7] = {Do, Re, Mi, Fa, So, La, Si};
const int buzzer = 9;
void setup(){
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}
void loop() {  
  for (int i = 0;i < sizeof(melody_num); i++) {
    if(melody_num[i]==1){tone(buzzer, Do);}
    if(melody_num[i]==2){tone(buzzer, Re);}
    if(melody_num[i]==3){tone(buzzer, Mi);}
    if(melody_num[i]==4){tone(buzzer, Fa);}
    if(melody_num[i]==5){tone(buzzer, So);}
    if(melody_num[i]==6){tone(buzzer, La);}
    if(melody_num[i]==7){tone(buzzer, Si);}
    if(melody_num[i]==11){tone(buzzer, Do1);}
    if(melody_num[i]==12){tone(buzzer, Re1);}
    if(melody_num[i]==13){tone(buzzer, Mi1);}
    if(melody_num[i]==14){tone(buzzer, Fa1);}
    if(melody_num[i]==15){tone(buzzer, So1);}
    if(melody_num[i]==16){tone(buzzer, La1);}
    if(melody_num[i]==17){tone(buzzer, Si1);}
    //tone(buzzer, melody[i]);
    delay(2000/metempo_num[i]); 
    Serial.println(i);
  }
  noTone(buzzer);//不發出聲音
  delay(2000);
}
