#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

int led = 13;
int boton1 = 7;
int valor;


void draw1(void) {
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr( 5, 22, "Contar tuercas");
  u8g.drawStr( 5, 50, "Separar tuercas");
}

void setup() {         
  
  pinMode(boton1, INPUT);
  pinMode(led, OUTPUT);     
  
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}


void loop() {
  valor=digitalRead(boton1);
  if (valor==HIGH)
  {
  digitalWrite(led, LOW);  
  u8g.firstPage();  
  do {
    draw1();
  } while( u8g.nextPage() );
  delay(50);  }            // wait for a second
  
  else{digitalWrite(led, HIGH);    // turn the LED off by making the voltage LOW
  delay(50);  }             // wait for a second
}
