#include <Servo.h>
Servo Leonardo;
Servo Donatello;
Servo Michelangelo;
Servo Raphael;
int pot[4];

void setup() 
{
  Leonardo.attach(13);                     
  Donatello.attach(12);                    
  Michelangelo.attach(11);           
  Raphael.attach(10);
  pinMode(9, INPUT);              //Botão automático/manual
  pinMode(8, OUTPUT);             //LED modo automático
  pinMode(7, OUTPUT);             //LED trocando de modo
  pinMode(6, OUTPUT);             //LED modo manual
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH); 
}

void loop() 
{
  int btn=0,i;
  if(digitalRead(9) == HIGH)
  {
    btn = 1;
    delay(500);
  }
  if(btn == 1)
  {
    digitalWrite(6, LOW);          //Desliga modo Manual
    digitalWrite(7, HIGH);         //Mudando de modo
    delay(2000);                   //Aguarde...
    digitalWrite(7, LOW);         
    digitalWrite(8, HIGH);         //Liga modo Automático
    Leonardo.write(85);            //Posição I
    Donatello.write(70);
    Michelangelo.write(180);
    Raphael.write(140);
    delay(tempo());
    Leonardo.write(0);             //Posição II
    delay(595);                             
    Donatello.write(140);          //Posição III
    delay(490);
    Michelangelo.write(155);       //Posição IV
    delay(280);             
    Raphael.write(180);            //Posição V
    delay(280);
    Michelangelo.write(180);       //Posição VI
    delay(280);
    Donatello.write(70);           //Posição VII
    delay(490);
    for(i=0;i<=180;i+=1)            //Posição VIII
    {
      Leonardo.write(i);
      delay(5);           
    }
    Raphael.write(100);            //Posição IX
    delay(1000);
    digitalWrite(8, LOW);          //Desliga modo Automático
    digitalWrite(7, HIGH);         //Mudando de modo
    delay(2000);                   //Aguarde...
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH);         //Liga modo Manual
  }
  else
  {
    pot[0] = analogRead(0); 
    pot[0] = map(pot[0], 0, 1023, 180, 0);
    Leonardo.write(pot[0]);        //Leonardo manual
    pot[1] = analogRead(1); 
    pot[1] = map(pot[1], 0, 1023, 180, 0);
    Donatello.write(pot[1]);       //Donatello manual
    pot[2] = analogRead(2); 
    pot[2] = map(pot[2], 0, 1023, 180, 0);
    Michelangelo.write(pot[2]);    //Michelangelo manual
    pot[3] = analogRead(3); 
    pot[3] = map(pot[3], 0, 1023, 180, 0);
    Raphael.write(pot[3]);         //Raphael manual
    delay(5);
  }
}

int tempo()
{
  int pos[4],time,maior,ctrl;      //Determina qual servo
  pos [0]= 45 - pot[0];            //irá gastar mais tempo
  pos [1]= 90 - pot[1];            //para chegar até a 1ª
  pos [2]= 135 - pot[2];           //posição automática
  pos [3]= 180 - pot[3];
  maior = pos[0];
  for(ctrl=1;ctrl<4;ctrl+=1)
  {
    if(pos[ctrl]>maior)
    maior = pos[ctrl];
  }
  time = 7*maior;
  return(time);
}
