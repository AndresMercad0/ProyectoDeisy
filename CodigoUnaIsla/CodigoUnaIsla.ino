/*************
 * LIBRARIES *
 *************/
// -------- LEDS --------
#include <FastLED.h>


/********************
 * GLOBAL CONSTANTS *
 ********************/
// -------- LEDS --------
#define NUM_LEDS 20
#define DATA_LED_A0 2
#define DATA_LED_A1 3
// #define DATA_LED_A2 4
// -------- Sensores de toque --------
#define SENSOR_A0 A0
#define SENSOR_A1 A1
#define SENSOR_A2 A2
int valor_referencia_A0 = 0;
int valor_referencia_A1 = 0;
int valor_referencia_A2 = 0;
bool toque_A0 = false;
bool toque_A1 = false;
bool toque_A2 = false;
#define rango 100


/******************
 * GLOBAL OBJECTS *
 ******************/
// -------- LEDS --------
CRGB leds_A0[NUM_LEDS]; // Define the array of leds
CRGB leds_A1[NUM_LEDS]; // Define the array of leds
//CRGB leds_A2[NUM_LEDS]; // Define the array of leds



/*******************************************
 * CODE THAT EXECUTES ONLY ONCE AT STARTUP *
 *******************************************/
void setup() {
    /***********************
     * INIT COMMUNICATIONS *
     ***********************/
    // --- Serial ---------------------------------------------------------------------------------------
    Serial.begin(9600); // initialize serial communication at 9600 bits per second
    while (!Serial);
    // --- LEDS ---------------------------------------------------------------------------------------
    FastLED.addLeds<NEOPIXEL, DATA_LED_A0>(leds_A0, NUM_LEDS);  // GRB ordering is assumed
    FastLED.addLeds<NEOPIXEL, DATA_LED_A1>(leds_A1, NUM_LEDS);  // GRB ordering is assumed
    // FastLED.addLeds<NEOPIXEL, DATA_LED_A2>(leds_A2, NUM_LEDS);  // GRB ordering is assumed

    /*************************
     *  Calibración inicial  *
     *************************/
    for(int i=0; i<NUM_LEDS; i++) { // Enciende todos los leds en verde
        leds_A0[i] = CRGB(0, 255, 0);
        leds_A1[i] = CRGB(0, 255, 0);
        //leds_A2[i] = CRGB(0, 255, 0);
        FastLED.show();
    }
    delay(5000); // Espera 5 segundos
    // Lee el valor actual de cada sensor y lo guarda en una variable global
    valor_referencia_A0 = analogRead(A0);
    valor_referencia_A1 = analogRead(A1);
    valor_referencia_A2 = analogRead(A2);
    for(int i=0; i<NUM_LEDS; i++) { // Apaga todos los leds
        leds_A0[i] = CRGB(0, 0, 0);
        leds_A1[i] = CRGB(0, 0, 0);
        //leds_A2[i] = CRGB(0, 0, 0);
    }
}



/*************************************
 *  CODE RUNNING IN AN ENDLESS LOOP  *
 *************************************/
void loop() {
    // Lee sí alguien toca alguno de los sensores
    if(analogRead(A0)>(valor_referencia_A0+rango) || analogRead(A0)<(valor_referencia_A0-rango))
    {toque_A0 = true;}
    if(analogRead(A1)>(valor_referencia_A1+rango) || analogRead(A1)<(valor_referencia_A1-rango))
    {toque_A1 = true;}
    if(analogRead(A2)>(valor_referencia_A2+rango) || analogRead(A2)<(valor_referencia_A2-rango))
    {toque_A2 = true;}

    if (toque_A0 == true || toque_A1 == true || toque_A2 == true) {

        for(int i=0; i<NUM_LEDS; i++){
            leds_A0[i] = CRGB(0, 0, 0);
            leds_A1[i] = CRGB(0, 0, 0);
            //leds_A2[i] = CRGB(0, 0, 0);
        }
        delay(10000);
        toque_A0 = false;
        toque_A1 = false;
        toque_A2 = false;

    }


    // Hacer el blink (De todos)
    for(int i=0; i<NUM_LEDS; i++){
        leds_A0[i] = CRGB(255, 50, 100);
        leds_A1[i] = CRGB(255, 50, 100);
        //leds_A2[i] = CRGB(255, 50, 100);
        FastLED.show();
        delay(20);
        leds_A0[i] = CRGB(0, 0, 0);
        leds_A1[i] = CRGB(0, 0, 0);
        //leds_A2[i] = CRGB(0, 0, 0);
    }
}