#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int randNumb; // Numero random
int randNumb2; // Numero random
int resultNumb = 0; // Resultado de los dos numeros random
int userData; // Numero que introduce el usuario
unsigned long time1;
unsigned long time2;
unsigned long time3;
bool newData;
int score = 0;
bool exceso = false;
int difficulty = 0;



const byte lol = 32;
char keyS[lol];
int rdm;

//Variables que se usan para el keypad

const byte rows = 4; //Numero de filas
const byte cols = 3; //Numero de columnas
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'#','0','*'}
};
byte rowPins[rows] = {8, 2, 3, 4}; //connect to the row pinouts of the keypad
byte colPins[cols] = {5, 6, 7}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols );



void setup() {

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

}

void loop() {

  time1 = 0;
  lcd.clear();
  lcd.home();

  lcd.setCursor(3,0);
  lcd.print("Elija la");
  
  lcd.setCursor(2,1);
  lcd.print("Dificultad"); 

  delay(2000);

  
  lcd.clear();
  lcd.print("1)Facil");
  lcd.setCursor(8,0);
  lcd.print("2)Media");
  lcd.setCursor(3,1);
  lcd.print("3)Dificil");

  delay(2000);

  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Ingrese la");
  lcd.setCursor(3,1);
  lcd.print("Dificultad");
  delay(350);

  userData = 999;
  while(userData == 999){
    userData = 999;
    rKey();
  }

  Serial.println(userData);
  
  
  switch(userData){
    case 1:
     while(time1 < 30000){
          time1 =  millis();
          easyP();
          Serial.println(time1);
      }
      break;
      
    case 2:
      while(time1 < 30000){
          time1 =  millis();
          mediumP();
          Serial.println(time1);
      }
      break;
      
    case 3:
      while(time1 < 30000){
          time1 =  millis();
          hardP();
          Serial.println(time1);
      }
      break;





  }
      lcd.clear();
      lcd.print("Termino el Juego");
      delay(3000);
  
    
                
 
}

void randomEasy(){
  String sRmd;

  lcd.clear();
  randNumb = random(1,5);
  randNumb2 = random(1,5);
  while(randNumb < randNumb2){
      randNumb = random(1,5);
  }
  rdm = random(0,500);
  if(rdm < 250){
     sRmd = "-";
     resultNumb = randNumb - randNumb2;
  }
  
  else{
    sRmd = "+";
     resultNumb = randNumb + randNumb2;
  }
  
  lcd.setCursor(0,0);
  lcd.print(randNumb);
  lcd.setCursor(2,0);
  lcd.print(sRmd);
  lcd.setCursor(4,0);
  lcd.print(randNumb2);
  lcd.setCursor(6,0);
  lcd.print("=");
  lcd.setCursor(0,1);
  lcd.blink();
}


void randomMedium(){
  String sRmd;

  lcd.clear();
  
  randNumb = random(1,10);
  randNumb2 = random(1,10);
  
  
  while(randNumb < randNumb2){
      randNumb = random(1,10);
  }
  
  rdm = random(0,500);
  if(rdm < 124 and rdm > 0){
     sRmd = "-";
     resultNumb = randNumb - randNumb2;
  }
  
  else if(rdm > 125 and rdm < 249){
    sRmd = "+";
     resultNumb = randNumb + randNumb2;
  }


  else if(rdm > 250 and rdm < 500){
    sRmd = "X";
     resultNumb = randNumb * randNumb2;
  }

  
  
  lcd.setCursor(0,0);
  lcd.print(randNumb);
  lcd.setCursor(2,0);
  lcd.print(sRmd);
  lcd.setCursor(4,0);
  lcd.print(randNumb2);
  lcd.setCursor(6,0);
  lcd.print("=");
  lcd.setCursor(0,1);
  lcd.blink();
}




void randomHard(){
  String sRmd;

  lcd.clear();
  randNumb = random(1,20);
  randNumb2 = random(1,20);
  while(randNumb < randNumb2){
      randNumb = random(1,5);
  }
  rdm = random(0,500);
  if(rdm < 124 and rdm > 0){
     sRmd = "-";
     resultNumb = randNumb - randNumb2;
  }
  
  else if(rdm > 125 and  rdm < 249){
    sRmd = "+";
     resultNumb = randNumb + randNumb2;
  }


  else if(rdm > 250 and rdm < 374){
    sRmd = "X";
     resultNumb = randNumb * randNumb2;
  }

  else if(rdm > 375 and rdm < 500){
    sRmd = "/";
     resultNumb = randNumb / randNumb2;
  }

  
  
  lcd.setCursor(0,0);
  lcd.print(randNumb);
  lcd.setCursor(3,0);
  lcd.print(sRmd);
  lcd.setCursor(5,0);
  lcd.print(randNumb2);
  lcd.setCursor(7,0);
  lcd.print("=");
  lcd.setCursor(0,1);
  lcd.blink();
}













void rKey(){
  int rc;
  static uint8_t ndx = 0;
  int endMark = 42; 
  

  rc = keypad.getKey();
  
  if(rc != NO_KEY){
    
    if(rc != endMark){ //Si llega un valor del teclado lo imprime en pantalla y lo convierte de ascii a un numero

      
      lcd.print(rc-48); // Problema de las 3 lineas en el display
      Serial.println(keyS[ndx]);
      keyS[ndx] = rc-48;
      ndx++;
    }
    
    else{  //Si el valor que llega es el numeral lo que hace es pasar los valores que se introdujeron a la variable userData
      
      if(resultNumb > 9){  //Si el resultado es mayor de 9, se acomodan los numeros de tal forma que el primer numero ingresado sea una decena y el segundo sea una unidad
        
        userData = (keyS[0]*10) + keyS[1];
        Serial.println(userData);
        newData = true;
        ndx = 0; 
         
      }
      
      else if(resultNumb <= 9){
        userData = keyS[0];
        Serial.println(userData);
        newData = true;
        ndx = 0;
      }

      else if(resultNumb >= 100){
        
      userData = (keyS[0]*100) + (keyS[1]*10) + keyS[2];
      Serial.println(userData);
      newData = true;
      ndx = 0; 
      
      }
    }
  }
}

void easyP(){
   randomEasy();
   
                // Se entra a un ciclo infinito que lo que hace es evaluar
        while(true){
      
          userData = 999;
          rKey();

          Serial.println(time1);
          if(time1 > 30000){
            exceso = true;
            break;
          }  
      
          if(userData != 999){
        
            if(userData == resultNumb){
              lcd.clear();
              lcd.home();
              lcd.print("Correcto");  
              delay(500);
              score++;
              break;
            }
          
            else{        
              lcd.clear();
              lcd.home();
              delay(200);
              lcd.print("Incorrecto");
              delay(500);
              score--;
              break;
            }
          }
       }
}


void mediumP(){
   randomMedium();
   
                // Se entra a un ciclo infinito que lo que hace es evaluar
        while(true){
      
          userData = 999;
          rKey();

          Serial.println(time1);
          if(time1 > 30000){
            exceso = true;
            break;
          }  
      
          if(userData != 999){
        
            if(userData == resultNumb){
              lcd.clear();
              lcd.home();
              lcd.print("Correcto");  
              delay(500);
              score++;
              break;
            }
          
            else{        
              lcd.clear();
              lcd.home();
              delay(200);
              lcd.print("Incorrecto");
              delay(500);
              score--;
              break;
            }
          }
       }
}

void hardP(){
   randomHard();
   
                // Se entra a un ciclo infinito que lo que hace es evaluar
        while(true){
      
          userData = 999;
          rKey();

          Serial.println(time1);
          if(time1 > 30000){
            exceso = true;
            break;
          }  
      
          if(userData != 999){
        
            if(userData == resultNumb){
              lcd.clear();
              lcd.home();
              lcd.print("Correcto");  
              delay(500);
              score++;
              break;
            }
          
            else{        
              lcd.clear();
              lcd.home();
              delay(200);
              lcd.print("Incorrecto");
              delay(500);
              score--;
              break;
            }
          }
       }
}
