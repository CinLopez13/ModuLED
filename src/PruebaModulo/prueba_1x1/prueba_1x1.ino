#include <LedControl.h>

// Définition des broches de raccordement Arduino Nano → Matrice LED pilotée par MAX7219
#define brocheDeSelection               10        // Sortie D10 de l'Arduino (/SS)  vers la broche CS  de la matrice LED
#define brochePourLesDonnees            11        // Sortie D11 de l'Arduino (MOSI) vers la broche DIN de la matrice LED
#define brochePourLhorloge              13        // Sortie D13 de l'Arduino (SCK)  vers la broche CLK de la matrice LED

// Définition des autres "constantes"
#define nombreDeMatricesLedRaccordees   1         // Nombre pouvant aller de 1 à 8 (nombre maxi de matrice led pilotable ici)
#define adresseDeLaMatrice              0         // Pour les 8 matrices max évoquées ci-dessus, leurs index respectifs (adresses) vont de 0 à 7
#define delaiAllumageLed                100       // Temps de maintien d'allumage LED, exprimé en millisecondes

// Instanciation de celle-ci
LedControl matriceLed = LedControl(brochePourLesDonnees, brochePourLhorloge, brocheDeSelection, nombreDeMatricesLedRaccordees);


// ========================
// Initialisation programme
// ========================
void setup() {

  // Initialisation de la matrice LED
  matriceLed.shutdown(adresseDeLaMatrice, false);       // shutdown     : "true" active le mode "sommeil", tandis que "false" active le mode "normal"
  matriceLed.setIntensity(adresseDeLaMatrice, 5);       // setIntensity : valeur pouvant aller de 0 à 15 (pour 16 niveaux de luminosité, donc)
  matriceLed.clearDisplay(adresseDeLaMatrice);          // clearDisplay : éteint toutes les LEDs de la matrice
  
}

// =================
// Boucle principale
// =================
void loop() {

  // *********************
  // Chenillard
  // *********************

  for(int ligne = 0; ligne < 8; ligne++) {                              // Parcours des 8 lignes de la matrice LED
    for(int colonne = 0; colonne < 8; colonne++) {                          // Parcours des 8 colonnes de la matrice LED
      matriceLed.setLed(adresseDeLaMatrice, ligne, colonne, true);              // Allumage de la LED située à la position ligne/colonne
      delay(delaiAllumageLed);                                                  // Maintien de cette LED allumée, un certain temps
      matriceLed.setLed(adresseDeLaMatrice, ligne, colonne, false);             // Et extinction de cette LED, avant passage à la led suivante
    }
  }
  
}