void init_system(){
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3);
  //tft.fillScreen(0x0000);
  tft.fillRect(0, 0, 160, 128, bc);
  digitalWrite(4,HIGH);
  desenha_logo();
  delay(500);
}


void init_display(){
  //tft.fillScreen(az);
  //desenha_pet_logo();
  tft.fillRect(0, 26, 160, 102, az);
  desenha_dog();//desenha_pet_logo
  desenha_cat();
  tft.fillRect(40, 62, 80, 40 , 0xC6F3);
  

}

void init_menu(){
  //tft.fillScreen(az);
  //desenha_pet_logo();
  tft.fillRect(0, 26, 157, 93, az);
  wifi_icon_refresh(check_wifi_level());
}





void drawtext(String text, uint16_t color,uint16_t bgcolor, uint8_t col_txt, uint8_t lin_txt, uint8_t txtsz) {
  tft.setTextSize(txtsz);
  tft.setCursor(col_txt, lin_txt);
  tft.setTextColor(color,bgcolor);
  tft.setTextWrap(true);
  int str_leng = text.length()+1;
  char buffer[str_leng];
  text.toCharArray(buffer,str_leng);
  tft.print(buffer);
}


void color_cat_prog(int c1, int bc1, int c2,int bc2,int c3,int bc3, int c4,int bc4){
cat_color_1 = c1;
cat_color_bg1 = bc1;
cat_color_2 = c2;
cat_color_bg2 = bc2;
cat_color_3 = c3;
cat_color_bg3 = bc3;
cat_color_4 = c4;
cat_color_bg4 = bc4;
}

void color_dog_prog(int d1, int bd1, int d2,int bd2,int d3,int bd3, int d4,int bd4){

dog_color_1 = d1;
dog_color_bg1 = bd1;
dog_color_2 = d2;
dog_color_bg2 = bd2;
dog_color_3 = d3;
dog_color_bg3 = bd3;
dog_color_4 = d4;
dog_color_bg4 = bd4;
}

void nivel_res_refresh(){
  int lvdog = lv_dog_res().toInt();
  int lvcat = lv_cat_res().toInt();
  nivel_dog(lvdog);
  nivel_cat(lvcat);

}

void refresh_ihm(){
 if (flag_menu != 3){
  relogio();
  calendario();
  }
  color_dog_prog(az,cz,az,cz,az,cz,az,cz);
  color_cat_prog(az,cz,az,cz,az,cz,az,cz);
  pet_food();
}



void desenha_logo(){

int x = 30, y = 14;

  // Em ESP32, PROGMEM é lido direto, então pode passar o ponteiro.
  // Se as cores saírem trocadas, faça tft.setSwapBytes(true);
  tft.drawRGBBitmap(x, y, logo, 100, 100);

/*int posmem=0;
  for (int row=14; row<114; row++) { // For each scanline...
     for (int col=30; col<130; col++) {
     // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col, row, (logo[posmem]));
      posmem++;
    } // end pixel
  }*/
  drawtext("  SOLUCOES  TECNOLOGICAS  ", vm,bc,0,102,1);
}




void desenha_dog(){

int x = 40, y = 34;

  // Em ESP32, PROGMEM é lido direto, então pode passar o ponteiro.
  // Se as cores saírem trocadas, faça tft.setSwapBytes(true);
  tft.drawRGBBitmap(x, y, dog, 32, 28);

/* int posmem=0;
  for (int row=34; row<62; row++) { // For each scanline...
     for (int col=40; col<72; col++) {
     // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col, row, (dog[posmem]));
      posmem++;
    } // end pixel
  }*/
}

void desenha_cat(){

int x = 91, y = 34;

  // Em ESP32, PROGMEM é lido direto, então pode passar o ponteiro.
  // Se as cores saírem trocadas, faça tft.setSwapBytes(true);
  tft.drawRGBBitmap(x, y, cat, 32, 28);
  
 /* int posmem=0;
  for (int row=34; row<62; row++) { // For each scanline...
     for (int col=91; col<123; col++) {
     // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col, row, (cat[posmem]));
      posmem++;
    } // end pixel
  }*/
}



void desenha_pet_logo(){

int x = 0, y = 0;

 tft.drawRGBBitmap(x, y, petlogo, 140, 25);

/*int  buffidx=0;
  
  for (int row=0; row<25; row++) { // For each scanline...
     for (int col=0; col<140; col++) {
     // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col, row,(petlogo[buffidx]));
      buffidx++;
    } // end pixel
  }*/
}


void nivel_dog(int nivel){

if (nivel_dog_anterior == nivel){
  return;
}
else{
  nivel_dog_anterior = nivel;

}


//String tp_lv_dog = from_machine +"-resdog";
//publica(tp_lv_dog,String(nivel));
if (nivel<100 && nivel>0){

  if (nivel >=85) {
    color_dog=0x07E0;
  }

   if ((nivel >=65) && (nivel <85)){
    color_dog=0x07FF;
  }

   if ((nivel >=45) && (nivel <65)){
    color_dog=0xFFE0;
  }

     if ((nivel >=25) && (nivel <45)){
    color_dog=0xFC00;
  }

  if (nivel <25) {
    color_dog= 0xF800;
  }


map_niveldog= map(nivel,1,99,99,31); 
heigh_dog_yel= 100 ;
tft.fillRect(10,   30     , 25, 70 , ST77XX_BLACK);
tft.fillRect(10,   map_niveldog  , 25, heigh_dog_yel , color_dog);
tft.fillRect(10,   100  , 25, 128 , ST77XX_BLUE);
tft.drawRect(8, 28, 30, 74, ST77XX_WHITE);


}

else if (nivel<1){
  tft.fillRect(10, 30, 25, 70, ST77XX_BLACK); 
  tft.fillRect(10,   100  , 25, 128 , ST77XX_BLUE);
  tft.drawRect(8, 28, 30, 74, ST77XX_WHITE);
}
else{
 tft.fillRect(10, 30, 25, 70, ST77XX_GREEN);
 tft.fillRect(10,   100  , 25, 128 , ST77XX_BLUE);
 tft.drawRect(8, 28, 30, 74, ST77XX_WHITE);
 }

value_nivel = String(nivel)+"%";
int coluna_txt_dog=14;
if (value_nivel.length() > 3){
  coluna_txt_dog = 11;
}
drawtext(value_nivel, ST77XX_WHITE,ST77XX_BLUE,coluna_txt_dog,105,1);
}


void nivel_cat(int nivel){

if (nivel_cat_anterior == nivel){
  return;
}
else{
  nivel_cat_anterior = nivel;

}
String tp_lv_cat = from_machine +"-rescat";
//publica(tp_lv_cat,String(nivel));
//if (nivel<100 && nivel>0){

  if (nivel >=85) {
    color_cat=0x07E0;
  }

   if ((nivel >=65) && (nivel <85)){
    color_cat=0x07FF;
  }

   if ((nivel >=45) && (nivel <65)){
    color_cat=0xFFE0;
  }

     if ((nivel >=25) && (nivel <45)){
    color_cat=0xFC00;
  }

  if (nivel <25) {
    color_cat=0xF800;
  }

//tft.drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)

if (nivel<100 && nivel>0){
map_nivelcat= map(nivel,1,99,99,31); 
heigh_cat_yel= 100 ;
tft.fillRect(125,   30     , 25, 70 , ST77XX_BLACK);
tft.fillRect(125,   map_nivelcat  , 25, heigh_cat_yel , color_cat);
tft.fillRect(125,   100  , 25, 128 , ST77XX_BLUE);
tft.drawRect(122, 28, 30, 74, ST77XX_WHITE);
 }

else if (nivel<1){
  tft.fillRect(125, 30, 25, 70, ST77XX_BLACK);
  tft.fillRect(125,   100  , 25, 128 , ST77XX_BLUE); 
  tft.drawRect(122, 28, 30, 74, ST77XX_WHITE);
}

else{
 tft.fillRect(125, 30, 25, 70, ST77XX_GREEN);
 tft.fillRect(125,   100  , 25, 128 , ST77XX_BLUE);
 tft.drawRect(122, 28, 30, 74, ST77XX_WHITE); 
 }

value_nivel = String(nivel)+"%";
int coluna_txt_cat=129;
if (value_nivel.length() > 3){
  coluna_txt_cat = 126;
}

drawtext(value_nivel, ST77XX_WHITE,ST77XX_BLUE,coluna_txt_cat,105,1);

}





void pet_food(){

if (ajusteprog){
drawtext(progdata[5],cat_color_1,cat_color_bg1,89,64,1);
drawtext(progdata[6],cat_color_2,cat_color_bg2,89,74,1);
drawtext(progdata[7],cat_color_3,cat_color_bg3,89,84,1);
drawtext(progdata[8],cat_color_4,cat_color_bg4,89,94,1);

drawtext(progdata[1],dog_color_1,dog_color_bg1,41,64,1);
drawtext(progdata[2],dog_color_2,dog_color_bg2,41,74,1);
drawtext(progdata[3],dog_color_3,dog_color_bg3,41,84,1);
drawtext(progdata[4],dog_color_4,dog_color_bg4,41,94,1);
ajusteprog = false;
}
}

void fuso_menu(){

drawtext(nome_fuso[menufuso-2],cz,az,15,44,1);
drawtext(nome_fuso[menufuso-1],cz,az,15,54,1);
drawtext(nome_fuso[menufuso  ],vm,am,15,64,1);
drawtext(nome_fuso[menufuso+1],cz,az,15,74,1);
drawtext(nome_fuso[menufuso+2],cz,az,15,84,1);

drawtext("  Anterior <   > Proximo  ",am,az,0,110,1);
drawtext("SET Confirma   ESC Retorna",am,az,0,120,1);
}
