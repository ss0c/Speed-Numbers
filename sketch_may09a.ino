#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);



int a; // Numero random
int b; // Numero random
int c; // Resultado de los dos numeros random
int d;



void setup() {

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

}

void loop() {
 
  randomEasy();
  
  // Serial.println(a);
  // Serial.println(b);
  
  c = a + b;
  // Serial.println(c);
  
  Serial.print(d); 
  
  while(true){

    if(Serial.available()> 0){
      d = Serial.read();

      if(d == c){
        lcd.clear();
        lcd.print("Correcto");  
        delay(350);
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



void randomEasy(){
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


}
