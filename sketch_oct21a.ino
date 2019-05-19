#include <SPI.h>
#include <RFID.h>
int buzzerPin = 2;
int buzzerPin2 = 4;
RFID lrt720(10,9);
const int switchPin=3;
int switchstate=1;
int flag=0;
int x=0;
int y=0;
int kapandi=0;
 
void setup()
{
  Serial.begin(9600);
  SPI.begin();  
  lrt720.init();
  pinMode(buzzerPin, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
  pinMode(switchPin,INPUT);
}
void loop()
{
switchstate = digitalRead(switchPin);




if(switchstate == HIGH && flag==0)
{
  if(y==1)
  {
                if(x>10)
                {
                  tone(buzzerPin2, 2000);
                }
                else
                {
                  tone(buzzerPin, 1150);
                  delay(800);
                  noTone(buzzerPin);
                  delay(200);
                  x=x+1;                                   
                }  
  }
 else
 {
    kapandi=0;
    x=0;
    noTone(buzzerPin);    // kapı kapalıyken ve kart okutulmamışken => ses yok 
 }
  

             
}





if(switchstate == LOW && flag==0)   // kapı açık ve kart okutulmamış
{ 
          if(kapandi==0)
          {        
            y=1;
          }
          if (lrt720.isCard())
          {
              lrt720.readCardSerial();
                if((lrt720.serNum[0]== 234) && (lrt720.serNum[1]== 248)&& (lrt720.serNum[2]== 31)&& (lrt720.serNum[3]== 43)&& (lrt720.serNum[4]== 38))
                  {
                    kapandi=0;
                    x=0;
                    y=0;
                    flag =1;
                    noTone(buzzerPin);
                    Serial.println("Giriş işlemi başarılı.");
                    delay(3000);
                    return;                    
                  }
                  else
                  {
                    Serial.println("Hatalı Kart girişi. Giriş onaylanmadı.");
                    noTone(buzzerPin);
                    tone(buzzerPin2, 750);
                    delay(200);
                    noTone(buzzerPin2);
                    delay(200);
                    tone(buzzerPin2, 750);
                    delay(200);
                    noTone(buzzerPin2);
                    delay(200);
                    tone(buzzerPin2, 750);
                    delay(200);
                    noTone(buzzerPin2);
                    delay(200);
                  }
         } 
         else
         {      
                if(x>10)
                {
                  tone(buzzerPin, 2000);
                }
                else
                {
                  tone(buzzerPin, 1150);
                  delay(800);
                  noTone(buzzerPin);
                  delay(200);
                  x=x+1;
                                   
                }                              
         }          
}

if(switchstate == HIGH && flag==1) // kapı kapalı ve kart okutulmuş
{
  x=0;
  y=0;
  noTone(buzzerPin);
  kapandi=0;
}


if(switchstate == LOW && flag==1)
{        
          if (lrt720.isCard())
          {
              lrt720.readCardSerial();
                if((lrt720.serNum[0]== 234) && (lrt720.serNum[1]== 248)&& (lrt720.serNum[2]== 31)&& (lrt720.serNum[3]== 43)&& (lrt720.serNum[4]== 38))
                  { y=0;                  
                    x=0;
                    flag =0;
                    kapandi=1;
                    Serial.println("Kilit işlemi başarılı. Kapınızı kapatınız.");
                    delay(1000);                 
                  }
                  else
                  {
                    Serial.println("Hatalı Kart girişi. Çıkış onaylanmadı.");
                    noTone(buzzerPin);
                    tone(buzzerPin2, 750);
                    delay(200);
                    noTone(buzzerPin2);
                    delay(200);
                    tone(buzzerPin2, 750);
                    delay(200);
                    noTone(buzzerPin2);
                    delay(200);
                    tone(buzzerPin2, 750);
                    delay(200);
                    noTone(buzzerPin2);
                    delay(200);
                  }
         }            
}
}
