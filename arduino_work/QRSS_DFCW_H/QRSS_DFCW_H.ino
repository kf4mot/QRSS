// Programa de transmision monobanda en QRSS  desarrollado por Juanpa EA5JTT el 9/12/2025
// Probado con Lilygo T-Beam + Si5351
// Parametros:
// - Indicativo: EA5JTT en Morse como cadena de simbolos, no vale la pena generarlo con tabla
// - Modulación modo FSK  con desplazamiento de frecuencia de +10 Hz
// - Velocidad Velocidad: QRSS3 (3 segundos por símbolo)
// - frecuencia  10.140,000 kHz 
// - salida de RF: CLK1

/*
Frecuencias de trabajo en QRSS

Band	QRSS Frequency (±100 Hz)      USB Dial(Hz)	Audio Frequency (Hz)
600m	476,100 kHz	                      474,200	        1.900
160m	1.837,900 kHz	                  1.836,600	        1.300
80m	3.569,900 kHz  popular	          3.568,600	        1.300
60m	5.288,550 kHz	                    5.287,200	        1.350
40m	7.039,900 kHz popular	            7.038,600	        1.300
30m	10.140,000 kHz la mas popular    10.138,700	        1.300
22m	13.555,400 kHz	                 13.553,900	        1.300
20m	14.096,900 kHz popular	         14.095,600	        1.300
17m	18.105,900 kHz	                 18.104,600	        1.300
15m	21.095,900 kHz	                 21.094,600	        1.300
12m	24.925,900 kHz	                 24.924,600	        1,300
10m	28.125,700 kHz	                 28,124,600	        1.100
6m	50.294,300 kHz	                 50.293,000	        1.100
*/
/*
QRSS3 = 3000 ms el punto
Desde QRSS3, QRSS19, ... hasta QRSS120
*/

#include <Wire.h>
#include <si5351.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306.h"
#include "Fixed8x16.h"

// -------------------- OLED --------------------
//#define OLED_RST NOT_A_PIN
#define OLED_SDA 6
#define OLED_SCL 7
//Adafruit_SSD1306 display(OLED_RST);
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// -------------------- SI5351 --------------------
Si5351 si5351;

// -------------------- FRECUENCIAS DFCW --------------------
// Corrección de tu SI5351
int32_t manual_offset_hz = -145;  //freq. calibration

// Base QRSS
uint64_t base = (10140000ULL + manual_offset_hz) * 100ULL;

// SHIFT típico DFCW = 10 Hz
uint64_t shift = 10ULL * 100ULL;

uint64_t MARK  = base + shift;   // Frecuencia 1
uint64_t SPACE = base;           // Frecuencia 2

// -------------------- TIEMPOS QRSS --------------------
const int dit  = 3000;        // 3 s
const int dah  = dit * 3;     // 9 s
const int sym_pause = dit;    // silencio entre símbolos
const int char_pause = dit*3; // silencio entre letras

// -------------------- MENSAJE MORSE --------------------
//const char* message[] = {".", ".-", ".....", ".---", "-", "-", NULL};
const char* message[] = {"-.-", "..-.", "....-", "--", "---", "-", NULL}; //kf4mot

// -------------------- DFCW HARD --------------------
void sendSymbol_DFCW(char s) {
  if (s == '.') {
    // PUNTO = tono MARK
    si5351.set_freq(MARK, SI5351_CLK1);
    si5351.output_enable(SI5351_CLK1, 1);
    delay(dit);
  }
  else if (s == '-') {
    // RAYA = tono SPACE
    si5351.set_freq(SPACE, SI5351_CLK1);
    si5351.output_enable(SI5351_CLK1, 1);
    delay(dah);
  }
  // SILENCIO entre símbolos
  si5351.output_enable(SI5351_CLK1, 0);
  delay(sym_pause);
}

void sendChar_DFCW(const char* morse) {
  for (int i = 0; morse[i] != 0; i++) {
    sendSymbol_DFCW(morse[i]);
  }
  delay(char_pause); // silencio entre letras
}

// -------------------- SETUP --------------------
void setup() {
  Wire.begin(OLED_SDA, OLED_SCL);
  Serial.begin(115200);
  delay(1000);
  Serial.println("INICIO");
  // OLED
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, true, OLED_SDA, OLED_SCL); for old library
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setFont(&Fixed8x16);
  display.setTextColor(WHITE);
  display.setCursor(0, 12);
  display.println("DFCW HARD EA5JTT");
  display.display();

  // SI5351
  if (!si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0)) {
    Serial.println("ERROR SI5351!");
    while(1);
  }

  si5351.set_freq(SPACE, SI5351_CLK1);
  si5351.drive_strength(SI5351_CLK1, SI5351_DRIVE_6MA);
  si5351.output_enable(SI5351_CLK1, 0);

  display.setCursor(0, 26);
  display.println("INIT OK");
  display.display();
  delay(2000);
}

// -------------------- LOOP --------------------
void loop() {
  display.fillRect(0, 12, 128, 60, BLACK);
  display.display();
  display.setCursor(0,45 );
  display.println("     ON AIR");
  display.display();
  // Enviar indicativo completo
  for (int i = 0; message[i] != NULL; i++) {
    sendChar_DFCW(message[i]);
  }
  //
  display.fillRect(0, 12, 128, 60, BLACK);
  display.display();
  display.setCursor(0,45 );
  display.println("      WAIT");
  display.display();
  // Repetición cada minuto
  delay(60000);
}
