// LED RGB ---------------------------------------------------
void ledvm(){
  //pixels.clear(); 
  //pixels.setPixelColor(0, pixels.Color(150, 0, 0));
  //pixels.show();
  }

void ledvd(){
  //pixels.clear(); 
  //pixels.setPixelColor(0, pixels.Color(0, 150, 0));
  //pixels.show();
  }

void ledaz(){
  //pixels.clear(); 
  //pixels.setPixelColor(0, pixels.Color(0, 0, 150));
  //pixels.show();
  }

void ledam(){
  //pixels.clear(); 
  //pixels.setPixelColor(0, pixels.Color(150, 150, 0));
  //pixels.show();
  }

// WIFI STATUS LED -----------------------------------------
void wifi_led_status(){
 if (WiFi.status() ==6){
  ledvm();
}
 if (WiFi.status() ==3){
  ledaz();
}
 if (WiFi.status() ==4){
  ledam();
}
}
