void hard_reset(){
  tft.fillRect(0, 26, 160, 102, az);
  drawtext("  RESETING STORAGED DATA   ",bc,pt,0,60,1);
  reset_all_files();
  wifi_reset();
  ESP.restart();
                 }

void wifi_reset(){
  tft.fillRect(0, 26, 160, 102, az);
  drawtext("RESETING WIFI CREDENTIALS ",bc,pt,0,60,1);
  wifiManager.resetSettings();
  delay(1000);
  //ESP.restart(); 
                 }

void check_reset(){
  if (digitalRead(WIFI_RST)==0){wifi_reset();}
  if (digitalRead(HARD_RST)==0){hard_reset();}
                  }


bool bt_up(){
    if(digitalRead(bt4)){t_bt4 = 0x01;}
      if(!digitalRead(bt4) && t_bt4){t_bt4 = 0x00; 
         Serial.println("UP");       return true;}
    return false; 
}

bool bt_down(){
    if(digitalRead(bt3)){
        t_bt3 = 0x01; 
    }
    
     if(!digitalRead(bt3) && t_bt3){                                           
         t_bt3 = 0x00;
         Serial.println("DOWN");                            
         return true;
     }
    return false; 
}

bool bt_set(){
    if(digitalRead(bt2)){
        t_bt2 = 0x01; 
    }
    
     if(!digitalRead(bt2) && t_bt2){                                           
         t_bt2 = 0x00;
         Serial.println("SET");                            
         return true;
     }
    return false; 
}

bool bt_ok(){
    if(digitalRead(bt1)){
        t_bt1 = 0x01; 
    }
    
     if(!digitalRead(bt1) && t_bt1){                                           
         t_bt1 = 0x00;
         Serial.println("OK");                            
         return true;
     }    
    return false; 
}
