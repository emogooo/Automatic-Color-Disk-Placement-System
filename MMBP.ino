#include <Servo.h>
#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define EN  6

#define BUTON1 10
#define BUTON2 12
#define BUTON3 13
#define RESET 8

Servo servo;
int x, poz=0, servoKontrol=0, tutucu=2, alici2, sayac1=0, sayac2=0, sayac3=0;
char alici;

void setup() {  
  servo.attach(9);
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);

  pinMode(BUTON1, INPUT);
  pinMode(BUTON2, INPUT);
  pinMode(BUTON3, INPUT);
  pinMode(RESET, INPUT);
  
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
  
  for (poz = 90; poz <= 180; poz++) {
     servo.write(poz);              
     delay(6);
   }
  
}

void loop() {
  
  if(digitalRead(BUTON1) == HIGH || digitalRead(BUTON2) == HIGH || digitalRead(BUTON3) == HIGH || digitalRead(RESET) == HIGH ){  

    if(digitalRead(RESET) == HIGH){
     alici2=2;
     sayac1=0;
     sayac2=0;
     sayac3=0;
    }
    
    else if( digitalRead(BUTON1) == HIGH){ 
     if(sayac1 < 3){
      alici2=1;
      sayac1++; 
     }
     else{
      alici2=-3;
     }
    }
    else if( digitalRead(BUTON2) == HIGH){
     if(sayac2 < 3){
      alici2=2;
      sayac2++;  
     }else{
      alici2=-2;
     }    
    }
    else if( digitalRead(BUTON3) == HIGH){
     if(sayac3 < 3){
      alici2=3;
      sayac3++;
     }else{
      alici2=-1;
     }
    } 

   if((tutucu < 0 && alici2 > 0) || (tutucu > 0 && alici2 < 0)){
    servoDon();
    delay(500);
   }

   if(fabs(alici2) - fabs(tutucu) == 0){
    tutucu =alici2;
    delay(500);
   }
   else if(fabs(alici2) - fabs(tutucu) == 1){
    geriGit(1);
    tutucu=alici2;
   }
   else if(fabs(alici2) - fabs(tutucu) == 2){
    geriGit(2);
    tutucu=alici2;
   }
   else if(fabs(alici2) - fabs(tutucu) == -1){
    ileriGit(1);
    tutucu=alici2;
   }
   else if(fabs(alici2) - fabs(tutucu) == -2){
    ileriGit(2);
    tutucu=alici2;
   }

  }  
}

void servoDon()
{
  servoKontrol = (servoKontrol+1)%2;
  if(servoKontrol==0)
  {
   for (poz = 0; poz <= 180; poz += 1) {
     servo.write(poz);              
     delay(6);                      
   }
  }
  else
  {
   for (poz = 180; poz >=0; poz -= 1) 
   { 
     servo.write(poz);              
     delay(6);
   }
 }                       
}

void ileriGit(int a)
{
  digitalWrite(dir, HIGH);
  digitalWrite(EN,LOW);
  for(x= 0; x<1090*a; x++) 
  {
    digitalWrite(stp,HIGH);
    delay(1);
    digitalWrite(stp,LOW); 
    delay(1);
  }
  digitalWrite(EN,HIGH);
  delay(500);
}

void geriGit(int a)
{
  digitalWrite(dir, LOW);
  digitalWrite(EN,LOW);
  for(x= 0; x<1090*a; x++)
  {
    digitalWrite(stp,HIGH);
    delay(1);
    digitalWrite(stp,LOW);
    delay(1);
  }
  digitalWrite(EN,HIGH);
  delay(500);
}
