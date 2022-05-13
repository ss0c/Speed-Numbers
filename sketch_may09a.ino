#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);



int randNumb; // Numero random
int randNumb2; // Numero random
int resultNumb; // Resultado de los dos numeros random
int userNumber; // Numero que introduce el usuario

// Variables que se usan para la funcion de Leer y mostrar los datos que entrar por el monitor serial
const byte numChars  = 32;
char inChars[numChars] ;
bool newData = true;

void setup() {

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

}

void loop() {
              // Se randomizan dos numero y se imprimen  en el LCD por medio de una funcion
  randomEasy();
 
  resultNumb = randNumb + randNumb2;
  
              // Se entra a un ciclo infinito que lo que hace es evaluar 
  while(true){

   userNumber = 0;
   
   recvWithEndMark();
   showData();
   Serial.println(userNumber);
    if(userNumber != 0){
   
   
   
    if(userNumber == resultNumb){
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
    }// Llave del while
  } 
}


void randomEasy(){
  randNumb = random(1,5);
  randNumb2 = random(1,5);


  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print(randNumb);
  lcd.setCursor(2,0);
  lcd.print("+");
  lcd.setCursor(4,0);
  lcd.print(randNumb2);
  lcd.setCursor(6,0);
  lcd.print("=");
  lcd.setCursor(0,1);
  lcd.blink();
}


void recvWithEndMark(){
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  if(Serial.available() > 0){
    rc = Serial.read();

    if(rc != endMarker){
      inChars[ndx] = rc;
      ndx++;
      
      if(ndx >= numChars){
        ndx = numChars - 1;
      } 
    }
    
    else{
      inChars[ndx] = "\0";
      ndx = 0;
      newData = true;
    }
  }
}


void showData(){
  if(newData == true){
    userNumber = atoi(inChars);
    newData = false;
  }
}
