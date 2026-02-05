#include <TimerOne.h>
#define arrSize 32
#define noise 135
double sData = 0;
int val[arrSize];
int x=0;
int value, value1;
int value2, value3;
int smin=1023;
int smax=0;
int i=0;
float tmp;
int k=0;
float data[]{ };
int max[]{ };
int d;
int j;
float chast;

void sd(){
  val[x]=map(analogRead(A1), 0, 1023, 0, 255);
  Serial.write(val[x++]);
  if (x == arrSize) {
    // Если полностью заполнили массив
    // не выходим индексом i за размер массива
    x = 0;

    // Инициализируем максимальное и минимальное значение
    double maxV = val[0], minV = val[0];
  
    for (int m = 0; m < arrSize; m++) {
      if (val[m] > maxV)
        maxV = val[m];
      if (val[m] < minV)
        minV = val[m];
    }

    sData = maxV - minV;
  }
  if (sData < noise)
    digitalWrite(9,HIGH);
  else
    digitalWrite(9,LOW);
}


void setup() {
//pinMode(A0, INPUT);
Serial.begin(115200); 
pinMode(9, OUTPUT);
Timer1.initialize(3000);
Timer1.attachInterrupt(Getdata);
Timer1.attachInterrupt(sd);
for (int m=0; m<arrSize; m++){
  val[m]=1023;
}

}

int Getdata() {
  value=analogRead(A0);
  value1=map(value, 0, 1023, 0, 255);
  Serial.write(value1);
  Serial.write('A0');
  for (i=0; i<100; i++) 
  {data[i]=data[i+1];}
  data[100]=value; 



for (int j=0; j<15; j=j+1)
  max[j]=0; 

  k=0;
  for (int j=2; j<99; j=j+1)
 {
  if ((data[j]>data[j-1]) && (data[j]>data[j+1]))
   {
     max[k]=j; k=k+1;
   }
 }

}
void loop() {
int rawValue=analogRead(A1);
int ecgValue(rawValue, 0, 1023, 0, 255);
Serial.println(ecgValue);
i=0; 
chast =0;  
i = 0; 
 for (int j=1; j<10; j=j+1)   
  if (max[j]>0)
   {
    chast=chast+(max[j]-max[j-1]);      
    i=i+1;   
   }
 chast=int(chast/i);  
 if (( chast < 26 )&&(chast>13 )) {
  tone(9, 5000);
 }    
 
}


