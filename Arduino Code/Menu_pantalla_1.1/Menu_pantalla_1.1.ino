#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); 

#define tamano_menu 2
int posicion_menu = 0; //Variable de la posicion del marco en el menu principal
int numero = 0; //Variable del menu Separar1
int cuenta=0; //Variable del menu contar


#define encoder0PinA  2 //Variables del encoder (pin A, pin B y boton)
#define encoder0PinB  4
#define boton 3


volatile unsigned int encoder0Pos = 0;


void drawMenu(void) {

  char *menu[tamano_menu] = {
    "Contar tuercas", "Separar tuercas"  };
  int i=0;

  for (i=0; i<tamano_menu; i++) {  

    u8g.setFontPosTop();
    int ancho = u8g.getStrWidth(menu[i]);
    int margen_ancho = (128-ancho)/2;
    int altura = u8g.getFontAscent()-u8g.getFontDescent();
    int margen_alto = (48-(altura*tamano_menu))/tamano_menu+1;

    u8g.setFont(u8g_font_unifont);
    u8g.drawStr( margen_ancho, margen_alto*(i+1)+altura*i, menu[i]);

    if ( i == posicion_menu ) {
      u8g.drawFrame(margen_ancho-3, (margen_alto*(i+1)+altura*i)-1 , ancho+6, altura+4);
    }
  }

}



void drawContar (void) {
  int l=0, m=0;
  char *texto_contar[2] = {"Pulsa el encoder", "para salir"};
  
  u8g.setFontPosTop();
  u8g.setFont(u8g_font_unifont);
  
  for (l=0;l<2;l++){ 
  u8g.drawStr(0,44+16*l,texto_contar[l]);}
  
  u8g.setFontPosTop();
  u8g.setFont(u8g_font_ncenR18);
  int ancho_fuente2 = 10;
  int margen_ancho3 = (128-4*ancho_fuente2)/2;
  int altura3 = u8g.getFontAscent()-u8g.getFontDescent();
  int margen_alto3 = 24;
  
  if (cuenta<10) {m=3;}
   else if (cuenta>=10&&cuenta<100) {m=2;}
    else if (cuenta>=100&&cuenta<1000) {m=1;}
     else {m=0;}
     
  u8g.setPrintPos(margen_ancho3+ancho_fuente2*m, margen_alto3);
  u8g.print(cuenta);

}



void drawSeparar1(void) {

  int j=0, k=0;  
  char *texto_separar[3] = {"Seleccione el numero", "de tuercas que desea", "separar"  }; 

  u8g.setFontPosTop();
  u8g.setFont(u8g_font_6x13);
  for(k=0;k<3;k++){
    u8g.drawStr(3, 13*(k+1), texto_separar[k]);
  }

  u8g.setFontPosTop();
  u8g.setFont(u8g_font_gdr14);
  int ancho_fuente = 10;
  int margen_ancho2 = (128-4*ancho_fuente)/2;
  int altura2 = u8g.getFontAscent()-u8g.getFontDescent();
  int margen_alto2 = 60;

  if (numero<10) {j=3;}
   else if (numero>=10&&numero<100) {j=2;}
    else if (numero>=100&&numero<1000) {j=1;}
     else {j=0;}

  u8g.setPrintPos(margen_ancho2+ancho_fuente*j, margen_alto2);
  u8g.print(numero);

}



void doEncoder() {
  
  /* If pinA and pinB are both high or both low, it is spinning
   * forward. If they're different, it's going backward.
   */
   
  if (digitalRead(encoder0PinA) == digitalRead(encoder0PinB)) {
    numero++;
  } else {
    numero--;
  }
}



void setup(void) {

 pinMode(encoder0PinA, INPUT_PULLUP);
 pinMode(encoder0PinB, INPUT_PULLUP); 
   
 attachInterrupt(0, doEncoder, CHANGE);  // encoder pin on interrupt 0 - pin 2
 Serial.begin (9600); 
 
}



void loop(void) {
  // picture loop
 
  u8g.firstPage();  
  do {
    drawMenu();
  } 
  while( u8g.nextPage() );

}





  // rebuild the picture after some delay

//  cuenta=cuenta+1; //Para testear el cambio de numero en la funcion de contador


//  numero=numero+1; //Para testear el cambio de numero que haria con el encoder


  //  if (posicion_menu == 0) {posicion_menu=1;} //Para testear el cambio de marco en la pantalla
  //  else {posicion_menu=0;}



