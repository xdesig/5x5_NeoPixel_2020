/*
    Visualizador de espectro de audio de cinco bandas
    Usando a pantalla de 25 Neopixeles "https://github.com/xdesig/5x5_NeoPixel_2020"
    Transformada rapida de Fourier (FFT). Autor: Dimitrios P. Bouras, mantenida por Enrique Condes
    Pulsando SR aumentamos a amplificacion, Sl baixamos a amplificacion
    O Led vermello indica maxima amplificación o laranxa media e o verde minima. 
    XDeSIG 2021
*/

#include <Adafruit_NeoPixel.h>
#define PIN_NEO A4
#define NUM_LEDS 25
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN_NEO, NEO_GRB + NEO_KHZ800);


#include <fix_fft.h>          // biblioteca para implementar FFT
char re[128], im[128];        // Matrices de muestras / resultados de la FFT
byte i;                       // indice para almacenar as mostras
int dat;                      // variable da amplitude da frecuencia

int F[5] = {2, 3, 6, 9, 15}; // Frecuencias a mostrar en pantalla *73,8Hz

#define MIC A7
// Entrada de Audio (Microfono)

#define SR 2                  // Pulsador para subir a amplificacion
#define SL 3                  // Pulsador para bajar a amplificacion
#define Red 13                // Led vermello (Amplificación maxima)
#define Orn 12                // Led laranxa (Amplificación media)
#define Gre 11                // Led verde (Amplificación minima)

int amp = 25;                 // Valor inicial de amplificacion


int y;                        // Variable de resultados (eixo Y) mapeados para mostrar na pantalla
int x;                        // variable para recorer o eixo x
int A;                        // Amplitude en leds
int pix;                      // Variable de pixel a mostrar (pix = x + y*5)

int R;                        // Variable da cor vermella
int G;                        // Variable da cor verde
int B;                        // Variable da cor azul



void setup() {
  analogReference(INTERNAL);    // Axustamos a referencia do conversos analoxico/dixital a 1.1Volts
  pinMode(SR, INPUT);           // Definimos o rol de cada pin
  pinMode(SL, INPUT);
  pinMode (Red, OUTPUT);
  pinMode (Orn, OUTPUT);
  pinMode (Gre, OUTPUT);

  pixels.begin();              // Inicializamos os neoPixeles
}

void loop() {

  // *** Comprobamos si se pulsou SR para amplificar ou SR par atenuar
  while (digitalRead (SR)) {
    amp = amp + 1;
    if ( amp >= 50) {
      amp = 50;
      digitalWrite (Red, 1);
      digitalWrite (Orn, 0);
      digitalWrite (Gre, 0);
    }
    delay(100);
  }
  while (digitalRead (SL) ) {
    amp = amp - 1;
    if ( amp <= 1) {
      amp = 1;
      digitalWrite (Red, 0);
      digitalWrite (Orn, 0);
      digitalWrite (Gre, 1);
    }
    delay(100);
  }
  // *** Comprobamos si o valor de amplificacion e medio e acendemos o led laranxa
  if (amp > 20 and amp < 30) {
    digitalWrite (Red, 0);
    digitalWrite (Orn, 1);
    digitalWrite (Gre, 0);
  }



  //*** lectura de audio e conversion a amplitude por frecuencia.

  for (i = 0; i < 128; i++) {                     // Tomamos 128 mostras da entrada analoxica (micro)
    int sample = amp * (analogRead(MIC));
    re[i] = sample / 4 - 128;                     // Escalamos a variable para que se axuste a un caracter de -128 a 127
    im[i] = 0;                                    // Neste momento non temos valores imaxinarios e poñemos todos a cero
  }
  fix_fft(re, im, 7, 0);                          // Enviamos as mostras para a conversión FFT, devolvendo os resultados reais/imaxinarios nas mesmas matrices


  for (x = 0; x < 5; x++) {                       // Recorremos o eixo x da pantalla

    dat = sqrt(re[F[x]] * re[F[x]] + im[F[x]] * im[F[x]]);     // A magnitude da frecuencia é a raíz cadrada da suma dos cadrados das partes real e imaxinaria dos vectores
    // Solo recuperamos os valores das frecuencias elixidas F[x]

    A = map(dat, 0, 25, 4, 0);                                 // Mapeamos os valores de amplitude de cada frecunencia os pixeles verticais

    for (y = 5; y >= A  ; y--) {                               // Comprobamos cantos pixeles verticais acendemos

      pix = x + y * 5;                                         // Pasamos  as coordenadas X e Y a linea de pixeles

      if (y == 0) {                                            // Axustamos a cor a cada liña
        R = 32;
        G = 0;
        B = 0;
      }
      if (y == 1) {
        R = 16;
        G = 8;
        B = 4;
      }
      if (y == 2) {
        R = 16;
        G = 8;
        B = 16;
      }

      if (y == 3) {
        R = 4;
        G = 0;
        B = 16;
      }
      if (y == 4) {
        R = 0;
        G = 2;
        B = 2;
      }
      pixels.setPixelColor(pix, pixels.Color(R, G, B));           // Acendemos cada pixel ca sua cor
    }
    for (int y = 0; y < A  ; y++) {                               // Comprobamos que pixeles apagar
      pix = x + y * 5 ;
      pixels.setPixelColor(pix, pixels.Color(0, 0, 0));           // Apagamos cada pixel selecionado
    }
    pixels.show();                                                // Enviamos os datos a pantalla de NeoPixeles
  }
}
