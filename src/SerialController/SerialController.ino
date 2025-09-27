#include <LedControl.h>

#define PIN_DIN 11
#define PIN_CLK 13 
#define PIN_CS 10

#define adress 0

LedControl matrixLed = LedControl(PIN_DIN, PIN_CLK, PIN_CS, 1);

uint8_t data[8][8] = {0};

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  matrixLed.shutdown(adress, false);       // shutdown     : "true" active le mode "sommeil", tandis que "false" active le mode "normal"
  matrixLed.setIntensity(adress, 5);       // setIntensity : valeur pouvant aller de 0 à 15 (pour 16 niveaux de luminosité, donc)
  matrixLed.clearDisplay(adress);
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Leer hasta nueva línea
    input.trim(); // Eliminar espacios iniciales y finales

    int spaceIndex = input.indexOf(' ');
    if (spaceIndex > 0) {
      String param1Str = input.substring(0, spaceIndex);
      String param2Str = input.substring(spaceIndex + 1);

      int param1 = param1Str.toInt();
      int param2 = param2Str.toInt();

      // Verificación básica
      if (param1Str.length() > 0 && param2Str.length() > 0) {
        data[param1][param2] = !data[param1][param2];
        matrixLed.setLed(adress, param1, param2, data[param1][param2]);
      } else {
        Serial.println("Error: entradas invalidas.");
      }
    } else {
      Serial.println("Error: se requieren dos numeros separados por un espacio.");
    }
  }
}
