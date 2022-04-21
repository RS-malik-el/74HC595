/*
	DATE 	: 20/04/2022
	AUTHEUR : RACHEL SYSTEME 
	YOUTUBE : https://youtu.be/VaY-VGB0h5g

	Ce programme permet d'allumer un ensemble de 8 leds via un
	registre à décalage 74HC595 de la gauche vers la droite puis
	de la droite vers la gauche.
*/

#define PIN_DATA  		8
#define REGISTER_CLOCK  9
#define SERIAL_CLOCK  	10

// Tableau contenu les bits de sortie
bool data[8] = {};
 
// Prototypes des fonctions créées
void clear(void); 
void writeRegister(void);


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
	
	// Allumage des leds 1 à 1 de la gauche vers la droite
	for (int i = 0; i < 7; ++i){
		clear();
		data[i] = 1 ; // mise à jour du tableau
		writeRegister();
		delay(250);
	}

	// Allumage des leds 1 à 1 de la droite vers la gauche
	for (int i = 7; i >= 1; --i){
		clear();
		data[i] = 1 ; // mise à jour du tableau
		writeRegister();
		delay(250);
	}
}


// Cette fonction permet de mettre toutes les sorties  
// du registre à l'état bas (0)
void clear(){
	// Mise à jour du tableau
	for (int i = 0; i < 8; ++i){
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
	for (int i = 7; i >= 0; --i){
		digitalWrite(SERIAL_CLOCK,LOW);
		digitalWrite(PIN_DATA,data[i]); // donnée à envoyer
		digitalWrite(SERIAL_CLOCK,HIGH);
	}

	// Mise à jour des sorties du registre
	digitalWrite(REGISTER_CLOCK,HIGH);
}
