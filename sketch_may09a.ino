#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);


int a = 0;
int b = 0;
int c = 0;
int d = 0;
int p = 0;



void setup() {

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

}

void loop() {
  
  
  randomEasy(a,b);

  Serial.println(a);
  Serial.println(b);

  c = a + b;

  
  Serial.println(c);
  Serial.println(d);
  Serial.println(p);

  while(true){

    if(Serial.available()> 0){
      int d = Serial.read();

      if(d == c){
        lcd.clear();
        lcd.print("Correcto");  
        delay(350);
        p++;
        break;
      }
      else{
        lcd.clear();
        lcd.print("Incorrecto");
        delay(430);
        break;
      }
    }
  } // Llave del while
}// LLave del loop



int randomEasy(int a,int b){
  a = random(0,5);
  b = random(0,5);


  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print(a);
  lcd.setCursor(2,0);
  lcd.print("+");
  lcd.setCursor(4,0);
  lcd.print(b);
  lcd.setCursor(6,0);
  lcd.print("=");
  lcd.setCursor(0,1);
  lcd.blink();

  return a;
  return b;
}
