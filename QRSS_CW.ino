// Programa de transmision monobanda en QRSS  desarrollado por Juanpa EA5JTT el 9/12/2025
// Probado con Lilygo T-Beam + Si5351
// Parametros:
// - Indicativo: EA5JTT en Morse como cadena de simbolos, no vale la pena generarlo con tabla
// - Modulación modo FSK  con desplazamiento de frecuencia de +10 Hz
// - Velocidad Velocidad: QRSS3 (3 segundos por símbolo)
// - frecuencia  10.140,000 kHz 
// - salida de RF: CLK1
Parametros:
// - Indicativo: EA5JTT en Morse como cadena de simbolos, no vale la pena generarlo con tabla
// - Modulación modo FSK  con desplazamiento de frecuencia de +10 Hz
// - Velocidad Velocidad: QRSS3 (3 segundos por símbolo)
// - frecuencia  10.140,000 kHz 
// - salida de RF: CLK1
/*
Frecuencias de trabajo en QRSS

Band	QRSS Frequency (±100 Hz)    USB Dial(Hz)	Audio Frequency (Hz)
600m	476,100 kHz	                474,200	        1.900
160m	1.837,900 kHz	            1.836,600	        1.300
80m	3.569,900 kHz  popular	    3.568,600	        1.300
60m	5.288,550 kHz	            5.287,200	        1.350
40m	7.039,900 kHz popular	    7.038,600	        1.300
30m	10.140,000 kHz la mas popular    10.138,700	1.300
22m	13.555,400 kHz	            13.553,900	        1.300
20m	14.096,900 kHz popular	    14.095,600	        1.300
17m	18.105,900 kHz	            18.104,600	        1.300
15m	21.095,900 kHz	            21.094,600	        1.300
12m	24.925,900 kHz	            24.924,600	        1,300
10m	28.125,700 kHz	            28,124,600	        1.100
6m	50.294,300 kHz	            50.293,000	        1,.00
*/
/*
QRSS3 = 3000 ms el punto
Desde QRSS3, QRSS19, ... hasta QRSS120
*/

#include <Wire.h>


#include <Wire.h>
#include <si5351.h>

Si5351 si5351;

// OLED
#include <SPI.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SSD1306.h"
#include "Fixed8x16.h"
// OLED I2C pins Lilygo T-Beam / T3 
#define OLED_RST NOT_A_PIN
#define OLED_SDA 21
#define OLED_SCL 22
Adafruit_SSD1306 display(OLED_RST);


// Frecuencia base QRSS en centesima de Hz
//uint64_t base_freq = 14097100ULL * 100; // Hz * 100
//CALIBRACION
//Si 10140000 es en real 10141490 hay que restar 1490

uint64_t base_freq = (10140000ULL - 1490ULL) * 100; // Hz * 100// 
uint64_t shift = 10ULL * 100; // +10Hz (FSK)
uint64_t mark = base_freq + shift;
//no la usa, puntos y rayas van en la misma frecuencia
uint64_t space = base_freq;

// QRSS timing
// QRS3, QRSS10, QRSS30, QRSS60,  QRSS120
const int dit = 3000; // 3 segundos
const int dah = dit * 3; // 9 segundos
const int sym_pause = dit; // pausa entre símbolos
const int char_pause = dit*3; // pausa entre letras

// Mensaje en Morse (EA5JTT)
// debe codificar su indicativo, en este modo no se usa CQ
const char* message[] = {
  ".",".-",".....",".---","-","-",NULL
};

// conumtacion
// hard (la que e usa) , apaga la portadora
//soft : mantien la portadora

void sendSymbol(char s) {
  if (s == '.') {
    si5351.set_freq(mark, SI5351_CLK1);
    si5351.output_enable(SI5351_CLK1, 1);
    delay(dit);
  }
  if (s == '-') {
    si5351.set_freq(mark, SI5351_CLK1);
    si5351.output_enable(SI5351_CLK1, 1);
    delay(dah);
  }
  si5351.output_enable(SI5351_CLK1, 0);
  delay(sym_pause);
}

void sendChar(const char* morse) {
  for (int i = 0; morse[i] != 0; i++) {
    sendSymbol(morse[i]);
  }
  delay(char_pause);
}

void setup() {
  Wire.begin(21, 22);

  Serial.begin(115200);
  delay(1000);
  Serial.println("Inicio setup");
  // OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, true, OLED_SDA, OLED_SCL);
  display.clearDisplay();
  display.setFont(&Fixed8x16);
  display.setTextColor(WHITE);
  display.setCursor(0, 12);
  display.println("QRSS TX - EA5JTT");
  display.display();

   if (!si5351.init(SI5351_CRYSTAL_LOAD_8PF, 0, 0)) {
      Serial.println("ERROS Si5351.");
      display.setCursor(0, 26);
      display.println("IERROR SI5351");
    while (1);
  }

  si5351.set_freq(base_freq, SI5351_CLK1);
  si5351.drive_strength(SI5351_CLK1, SI5351_DRIVE_2MA);
  si5351.output_enable(SI5351_CLK1, 0);

  display.setCursor(0, 26);
  display.println("INIT SI5351");
  display.display();
  Serial.println("INIT SI5351");
  delay(5000UL);
}

void loop() {
  for (int i = 0; message[i] != NULL; i++) {
    sendChar(message[i]);
  }

  // Repetición cada minuto (ajustable)
  delay(60000);
}

