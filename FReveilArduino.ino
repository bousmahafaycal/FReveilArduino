int byte_read = 0; ///< The current byte
int recieved_integer = 0; ///< The current recieved integer
boolean recu = false;

int ledBouton = 5;
int  ledPresence = 7;
int ledLockAudio = 9;
int pinBouton=11;
boolean stateLedBouton = false;
int stateBouton = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ledBouton,OUTPUT);
  pinMode(ledPresence,OUTPUT);
  pinMode(ledLockAudio,OUTPUT);
  pinMode(pinBouton,INPUT_PULLUP);
}

boolean is_a_number(int n)
{
  return n >= 48 && n <= 57;
}

int ascii2int(int n, int byte_read)
{
  return n*10 + (byte_read - 48);
}

void loop() {
  recieved_integer = 0;
  recu = false;
  while ( Serial.available() ) {
    byte_read = Serial.read();
    if ( is_a_number(byte_read) ) {
          recieved_integer = ascii2int(recieved_integer, byte_read);
    }
  }
  
  if (recieved_integer == 0){
     recu = false;
  }
  else {
     recu = true;
     if ( recieved_integer == 1){
         digitalWrite(ledPresence, LOW);
     } 
     else if ( recieved_integer == 2){
         digitalWrite(ledPresence, HIGH);
     }
     else if ( recieved_integer == 3){
         digitalWrite(ledBouton, LOW);
         stateLedBouton = false;
     }
     else if ( recieved_integer == 4){
         digitalWrite(ledBouton, HIGH);
         stateLedBouton = true;
     }
     else if ( recieved_integer == 5){
         digitalWrite(ledLockAudio, LOW);
     }
     else if ( recieved_integer == 6){
         digitalWrite(ledLockAudio, HIGH);
     }
  }
  
  boolean etatBouton = ! digitalRead(pinBouton); // A cause du mode pullup le bouton est appuyé quand ça vaut false
  boolean reponse = false;
  
  if (etatBouton){
      //Serial.println("appui");
      
      if (stateBouton == 0){
        stateLedBouton = ! stateLedBouton;
        
        if (stateLedBouton){
            Serial.println("4");
            digitalWrite(ledBouton, HIGH);
            stateBouton = stateBouton + 1;
            reponse = true;
        }
        else{
            Serial.println("3");
            digitalWrite(ledBouton, LOW);
            stateBouton = stateBouton + 1;
            reponse = true;
        }
      }
      delay(50);
    
  }
  if (!(etatBouton || reponse) && recu){
      Serial.println("0");
  }
  else{
    delay(50);
  }
  
  
  if (stateBouton == 10){
    stateBouton = 0;      
  }
  else if  (stateBouton != 0){
    stateBouton = stateBouton + 1;
  }
  //delay(50);
}

