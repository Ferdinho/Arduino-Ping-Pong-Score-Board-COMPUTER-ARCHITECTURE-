#include <LiquidCrystal.h>

//Declaring pins for all buttons
const int buttonBlue = 2;
const int buttonGreen = 3;
const int buttonRed = 6;
const int buttonBlack = 5;

//Declaring pin for blue LED
const int blueLED = 13;
const int redLED = 12;


int playerAScore = 0;
int playerASet = 0;
int playerBScore = 0;
int playerBSet = 0;
int diff = abs(playerAScore- playerBScore);
//int ledServe = 0; //Variable to store how many serves there have been and then everytime it reaches 2, switch lights.
boolean blueOn = true;
int count = 0;
int previous =0;
//LCD screen pins
LiquidCrystal lcd(4,11,10,9,8,7);

void resetGame(){
   lcd.clear();
   playerAScore = 0;
   playerBScore = 0;
   playerASet = 0;
   playerBSet = 0;
//   ledStart();
  
  }
void printResults(){
  lcd.setCursor(0,1);
  lcd.print(playerASet);
  lcd.setCursor(14,0);
  lcd.print(playerAScore);
        
  lcd.setCursor(14,1);
  lcd.print(playerBSet);
  lcd.setCursor(0,0);
  lcd.print(playerBScore);
  lcd.setCursor(7,0);
  lcd.print("-");
  lcd.setCursor(7,1);
  lcd.print("-");
}

//Method to blink the LED of the winning player
 void blinkLED(int LED){
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
 }

//Trying to get the LED to switch every time two points are scored

//Randomly selects which player starts serving at the beginning of each set
// void ledStart(){
//  int ledServeStart = random(0, 2);  
//  digitalWrite((12+ledServeStart), HIGH);
// }

void switchSide(){
    int temp = playerASet;
    playerASet = playerBSet;
    playerBSet = temp;
 }

  
void setup()
{
  //Declaring Input and Output for LED and buttons
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buttonBlue, INPUT);
  pinMode(buttonGreen, INPUT);
  pinMode(buttonRed, INPUT);
  pinMode(buttonBlack, INPUT);

//  ledStart();
digitalWrite(blueLED, HIGH);

  lcd.begin(16, 2);
  lcd.clear();

}

void toggleLight(){
  if(blueOn){
        digitalWrite(blueLED, LOW);
        digitalWrite(redLED, HIGH);  
        blueOn = false;
      }
      else{
         digitalWrite(redLED, LOW);  
         digitalWrite(blueLED, HIGH);
         blueOn = true;
        }
  }
  void serviceLight(){
     if((playerAScore<10)&& (playerBScore<10)){ 
  
 if(count % 2 == 0){
    if(count != previous)
    {
      previous = count;
      toggleLight();
    }
  }
 }
   if((playerAScore>=10) && (playerBScore>=10)){
    
  // if(count % 2 == 1){
    if(count != previous)
    {
      previous = count;
      toggleLight();
    }
 // } 
   
   }
 }

 void checkScore(){
  diff = abs(playerAScore- playerBScore);
    
      
      if ((playerAScore>10 || playerBScore>10) && diff>=2 ){
          if (playerAScore > playerBScore){
            playerASet++;
            }else{
               playerBSet++;
            }
            switchSide();
          playerAScore = 0;
          playerBScore = 0;
          printResults();
          }
  
  }

  void endGame(){
    lcd.clear();
    lcd.setCursor(0,0);
     String message = playerASet>playerBSet ? "Player B won!!!" : "Player A Won!!!";
     if(playerASet > playerBSet){
        lcd.print(message);
        blinkLED(blueLED); //Need to find a way to put this in a loop. Everytime I tried a for, or while loop, it failed to blink the light.
        blinkLED(blueLED);
        blinkLED(blueLED);
        blinkLED(blueLED);
        delay(1000);
        resetGame();
     }else{
        lcd.print(message);
        blinkLED(redLED);
        blinkLED(redLED);
        blinkLED(redLED);
        blinkLED(redLED);
        delay(1000);
        resetGame();
     } 
    
    
    }
void loop()
{
  printResults();
  serviceLight();

    
  if((playerASet + playerBSet) != 5) {
    //Sets the cursor to the top right corner of the LCD screen
    
    lcd.setCursor(14,0);
    
    int blueButtonState;
    blueButtonState = digitalRead(buttonBlue);
    
    if(blueButtonState == LOW){
      playerBScore++;
      count += 1;

    }

    int greenButtonState = digitalRead(buttonGreen);
    
    if(greenButtonState == LOW){
      if(playerBScore > 0){
        playerBScore--;
        if(count%2 == 0){
        //  blueOn = true ? false : true;
          toggleLight();
          
           previous-=2;
          }
         else{
            blueOn = true ? false : true;
          }
         count --;
          
      }
    }
    
    if(digitalRead(buttonGreen)){
      lcd.print(playerBScore);  
      if(playerBScore < 10){
        lcd.setCursor(15,0);
        lcd.print(" ");
       }
    }
    
    //Sets the cursor to the top left corner of the LCD screen
    lcd.setCursor(0,0);
    
    int redButtonState;
    redButtonState = digitalRead(buttonRed);
    
    if(redButtonState == LOW){
     playerAScore++;
      count +=1 ;
    }

    
    lcd.setCursor(0,0);
    
    int blackButtonState;
    blackButtonState = digitalRead(buttonBlack);
    
    if(blackButtonState == LOW){
      if(playerAScore > 0){
        playerAScore--;
        if(count%2 == 0){
        //  blueOn = true ? false : true;
          toggleLight();
          
           previous-=2;
          }
         else{
            blueOn = true ? false : true;
          }
         count --;
          
      }
    }
    
    if(digitalRead(buttonBlack)){
      if(playerAScore >= 0)
        lcd.print(playerAScore);  
        if(playerAScore < 10){
          lcd.setCursor(1,0);
          lcd.print(" ");
          }
    }
    
    delay(100);
      checkScore();
      }
   
      else{
      endGame();   
 }

diff = 0;
delay(100);
}


