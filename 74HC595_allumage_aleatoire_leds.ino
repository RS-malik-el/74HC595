/*
	DATE 	: 20/04/2022
	AUTHEUR : RACHEL SYSTEME 

	Ce programme permet d'allumer un ensemble de 8 leds via un
	registre à décalage 74HC595 de façon aléatoire.
*/

#define PIN_DATA  		8
#define REGISTER_CLOCK  9
#define SERIAL_CLOCK  	10
 
// Prototypes des fonctions créées
void clear(void); 
void writeRegister(int choix);


// Programme initial
void setup(){

	// Initialisation du tirage aléatoire
	randomSeed(analogRead(A0));

	// Définition des pins comme sortie
	for (int i = 8; i <= 10 ; ++i){
		pinMode(i,OUTPUT);
		digitalWrite(i,LOW);
	}
}

// programme principal
void loop(){

	// Tirage aléatoire de la combinaison des leds à allumer
	int choix = random(0,256);

	writeRegister(choix);
	delay(250);
	clear();
	delay(250);
}


// Cette fonction permet de mettre toutes les sorties  
// du registre à l'état bas (0)
void clear(){ 
	writeRegister(0); 
}


/*
	Cette fonction permet d'écrire dans le registre :
	Ecrit dans le registre le contenu du tableau "data"
	puis ensuite mets à jour les sorties.

	Parametre :
		int choix : ensemble de bits à envoyer
		ex : choix = 255 = B11111111 
*/
void writeRegister(int choix){

	// Tableau des bits à envoyer
	bool data[8] = {};
	// Position du premier bit lu
	int pos = 7 ; 

	// lecture des bits et stockage dans le tableau
	for (int i = 0; i < 8; ++i){
		bool state = bitRead(choix,i);
		data[pos] = state;
		--pos;

		if (pos < 0)
			pos = 0;
	}

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