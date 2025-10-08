#include <LedControl.h> // Librería para controlar el MAX7219

// Definición de los pines entre el Arduino y el módulo MAX7219
#define PIN_CLK  7   // Pin D13 del Arduino (SCK) → pin CLK del módulo
#define PIN_CS   6   // Pin D10 del Arduino (CS o LOAD) → pin CS del módulo
#define PIN_DIN  5   // Pin D11 del Arduino (MOSI) → pin DIN del módulo


// Configuración del módulo
#define NUM_MODULOS   1   // Número de matrices (puede ir de 1 a 8)
#define DIRECCION     0   // Dirección del módulo (si hay varios en cascada)
#define TIEMPO_LED   100  // Tiempo que cada LED se mantiene encendido (ms)

// Creación del objeto que controla el módulo (parámetros: DIN, CLK, CS, número de módulos)
LedControl matrizLed = LedControl(PIN_DIN, PIN_CLK, PIN_CS, NUM_MODULOS);

// =========================
// Función de inicialización
// =========================
void setup() {
  // Activamos el módulo (false = modo normal, true = modo ahorro)
  matrizLed.shutdown(DIRECCION, false);

  // Brillo de la matriz (0 a 15)
  matrizLed.setIntensity(DIRECCION, 5);

  // Apaga todos los LEDs antes de empezar
  matrizLed.clearDisplay(DIRECCION);
}

// =================
// Bucle principal
// =================
void loop() {

  // ***************
  // Efecto barrido
  // ***************
  // Recorre todas las filas y columnas encendiendo un LED a la vez
  for (int fila = 0; fila < 8; fila++) {        // Recorre las 8 filas
    for (int columna = 0; columna < 7; columna++) {  // Recorre las 8 columnas
      matrizLed.setLed(DIRECCION, fila, columna, true);   // Enciende el LED (fila, columna)
      delay(TIEMPO_LED);                                  // Espera un momento
      matrizLed.setLed(DIRECCION, fila, columna, false);  // Apaga ese LED antes de pasar al siguiente
    }
  }
}
