/*
  DATE  : 21/04/2022
  AUTHEUR : RACHEL SYSTEME 
  YOUTUBE : https://youtu.be/VaY-VGB0h5g
  
  Ce programme permet d'allumer un ensemble de 16 leds via deux
  registres à décalage 74HC595 connecté en série.
  les leds s'allument de la gauche vers la droite puis
  de la droite vers la gauche: 1 à 1 puis 2 à 2.
*/

#define PIN_DATA        8
#define REGISTER_CLOCK  9
#define SERIAL_CLOCK    10

// Tableau contenu les bits de sortie
bool data[16] = {};
 
// Prototypes des fonctions créées
void clear(void); 
void writeRegister(void);
void allumage_1(int attente);
void allumage_2(int attente);


// Programme initial
void setup(){
  // Définition des pins comme sortie
  for (int i = 8; i <= 10 ; ++i){
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
}

// programme principal
void loop(){
  allumage_1(200);
  allumage_2(200);
}


// Cette fonction permet de mettre toutes les sorties  
// du registre à l'état bas (0)
void clear(){
  // Mise à jour du tableau
  for (int i = 0; i < 16; ++i){
    data[i] = 0;
  }
  writeRegister();
}


// Cette fonction permet d'écrire dans le registre :
// Ecrit dans le registre le contenu du tableau "data"
// puis ensuite mets à jour les sorties
void writeRegister(){
  // Préparation du registre à recevoir les données
  digitalWrite(REGISTER_CLOCK,LOW);

  // Ecriture des données
  for (int i = 15; i >= 0; --i){
    digitalWrite(SERIAL_CLOCK,LOW);
    digitalWrite(PIN_DATA,data[i]); // donnée à envoyer
    digitalWrite(SERIAL_CLOCK,HIGH);
  }

  // Mise à jour des sorties du registre
  digitalWrite(REGISTER_CLOCK,HIGH);
}


void allumage_1(int attente){
  // Allumage des leds 1 à 1 de la gauche vers la droite
  for (int i = 0; i < 15; ++i){
    clear();
    data[i] = 1 ; // mise à jour du tableau
    writeRegister();
    delay(attente);
  }

  // Allumage des leds 1 à 1 de la droite vers la gauche
  for (int i = 15; i >= 1; --i){
    clear();
    data[i] = 1 ; // mise à jour du tableau
    writeRegister();
    delay(attente);
  }
}


void allumage_2(int attente){
  // Allumage des leds 2 à 2 de la gauche vers la droite
  for (int i = 0; i < 14; i+=2){
    clear();
    // mise à jour du tableau
    data[i]   = 1 ; 
    data[i+1] = 1 ;
    writeRegister();
    delay(attente);
  }

  // Allumage des leds 2 à 2 de la droite vers la gauche
  for (int i = 15; i >= 1; i-=2){
    clear();
    // mise à jour du tableau
    data[i]   = 1 ; 
    data[i-1] = 1 ;
    writeRegister();
    delay(attente);
  }
}