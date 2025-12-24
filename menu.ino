void check_flag_menu(){

//---MAIN SCREEN CHECK FLAG-------------
if (flag_menu==0){
  init_display();
  nivel_dog_anterior = 0;
  nivel_cat_anterior = 0;
  ajusteprog=true;
  flag_menu=1;
}
if (flag_menu==1){
nivel_res_refresh();  
wifi_led_status();
wifi_icon_refresh(check_wifi_level());   
refresh_ihm();
}

if (flag_menu==2){
  init_menu();
  flag_menu=3;
}//--------------------------------------------



// MENU SCREEN CHECK FLAG ----------------------

if (flag_menu==3){
 menu_system();
}

if (flag_menu==4){
 menu_system();
}//-----------------------------------------------------




//---PROG MENU  CHECK FLAG ------------------------------

if (flag_menu==5){

 select_menu_prog();
}

if (flag_menu==15){
select_menu_fuso();
}

if (flag_menu==25){

drawtext(" RESTAURAR CONFIG. FABRICA",bc,vm,0,50,1);
drawtext("SET Confirma   ESC Retorna",am,az,0,120,1);
flag_menu=26;
}


if (flag_menu==35){

drawtext(" LIMPAR CREDENCIAIS WIFI  ",bc,vm,0,50,1);
drawtext("SET Confirma   ESC Retorna",am,az,0,120,1);
flag_menu=36;
}

if (flag_menu==45){
String num_ser_scr="";
num_ser_scr = "N/S: "  + num_ser +"        ";
const char* num_ser_char = num_ser_scr.c_str();
drawtext("  PETFEEDER MOD.DPF2002   ",bc,vm,0,40,1);
drawtext("--------------------------",bc,az,0,49,1);
drawtext(num_ser_char,bc,az,0,60,1);
drawtext("ESC Retorna",am,az,0,120,1);
}



if (flag_menu==8){
  set_prog();
}
if (flag_menu==7){
  prog_selected();
}//------------------------------------------------------

}




void check_buttons(){

 // ----UP BUTTON PRESSED ------------------------------------------------
if (bt_up()){
    if (debug_set){
    Serial.println("UP pressed");
    Serial.print("flag_menu:->");
    Serial.println(flag_menu);
    Serial.print("MnOPT:->");
    Serial.println(mnopt);
    }
    
    if (flag_menu==3){
       //one_beep();
        mnopt++;
    }

    // PROG MENU --------------------------------------------
    if (flag_menu==5){
      //one_beep();
      ajusteprog=true;
      menuprog--;
    }

       if (flag_menu==15){
        //one_beep();
        menufuso--;
      }
      if (flag_menu==8){
      //one_beep();  
      ajusteprog=true;
      set_prog_op--;
      if (debug_set){
      Serial.print("set_prog_op:");
      Serial.println(set_prog_op);
      }
    } //BUTTON UP MENU PROG END -------------------------------

}// IF BUTTON UP END -------------------------------------------




// ------DOWN BUTTON PRESSED -----------------------------------------------
if (bt_down()){
  if (debug_set){
    Serial.println("DOWN pressed");
    Serial.print("flag_menu:");
    Serial.println(flag_menu);
  }
    if (flag_menu==3){
        //one_beep();
        mnopt--;
    }

  // ----MENU PROG--------------------------------------
       if (flag_menu==5){
      //one_beep();   
      ajusteprog=true;
      menuprog++;
    }

      if (flag_menu==15){
        //one_beep();
        menufuso++;
      }



       if (flag_menu==8){
      //one_beep();  
      ajusteprog=true;
      set_prog_op++;
      if (debug_set){
      Serial.print("set_prog_op:");
      Serial.println(set_prog_op);
      }
    }//BUTTON DOWN MENU PROG END ------------------------------

    } //IF BUTTON DONW END--------------------------------------------









// ----SET BUTTON PRESSED ------------------------------------------------------
if (bt_set()){
    //one_beep();
    if (debug_set){
    Serial.println("SET pressed");
    Serial.print("flag_menu:");
    Serial.println(flag_menu);
    }
    if (flag_menu==1){
    flag_menu = 2;
    }
   
 if (flag_menu==3){
    flag_menu=4;
    }

    if (flag_menu==4){
      
      if (mnopt==1){
      flag_menu = 5;  // ✅ CORRIGIDO: atribuição ao invés de comparação
      }
   
    }

  
  // MENU PROG-------------------------------------------------
    if (flag_menu==5 && mnopt==1){
      if (debug_set){
       Serial.println("Acesso ao Menu de Programação");
       Serial.print("Variavel flag_menu:"); 
       Serial.println(flag_menu);
      }

       flag_menu=6;
    }

    if (flag_menu ==6){
      ajusteprog=true;
      flag_menu = 7;

    }
    if (flag_menu==8){

    save_selected_file();
    drawtext("    PROGRAMACAO SALVA     ", bc, pt,0, 120, 1);
    delay(300);  // ✅ REDUZIDO de 1000ms para 300ms
    drawtext("SET Seleciona  ESC Retorna",am,az,0,120,1);
    ajusteprog=true;
    select_menu_prog();
    flag_menu=5;
    }//BUTTON SET MENU PROG END---------------------------------------------
  
  //----FUSO MENU ------------------------
    if (flag_menu==15){
      save_fuso_prog();
      flag_menu=3;
    }//BUTTON SET MENU fuso END---------------------------------------------

    
    
    if (flag_menu==26){
      hard_reset();
      flag_menu=3;
    }

   if (flag_menu==36){
      wifi_reset();
      flag_menu=3;
  
}//IF BUTTON SET END--------------------------------------------

}
//----OK BUTTON PRESSED ------------------------------------------------------------
if (bt_ok()){
  if (debug_set){
    Serial.println("OK pressed");
    Serial.print("flag_menu:");
    Serial.println(flag_menu);
  }
    if (flag_menu==3){
      //one_beep();
      ajusteprog=true;
      flag_menu=0;
    }
    if (flag_menu==4){
      //one_beep();
      flag_menu=3;
    }
    // MENU PROG------------------------------------------
    if (flag_menu==5){
      //one_beep();
      tft.fillRect(0, 35, 157, 93, az);
      flag_menu=3;
    }
    if (flag_menu==15){
      //one_beep();
      tft.fillRect(0, 35, 157, 93, az);
      flag_menu=3;
    }

     if (flag_menu==25){
      //one_beep();
      tft.fillRect(0, 35, 157, 93, az);
      flag_menu=3;
    }

    if (flag_menu==26){
      //one_beep();
      tft.fillRect(0, 35, 157, 93, az);
      flag_menu=3;
    }

    if (flag_menu==35){
      //one_beep();
      tft.fillRect(0, 35, 157, 93, az);
      flag_menu=3;
    }

    if (flag_menu==36){
      //one_beep();
      tft.fillRect(0, 35, 157, 93, az);
      flag_menu=3;
    }

    if(flag_menu==45){
      //one_beep();
      tft.fillRect(0, 35, 157, 93, az);
      flag_menu=3;
    }


    if (flag_menu==6){
      //one_beep();
        ajusteprog=true;
        select_menu_prog();
        flag_menu=5;
    }
     if (flag_menu==7){
      //one_beep();
      ajusteprog=true;
      select_menu_prog();
      flag_menu=5;
    }
     if (flag_menu==8){
      //one_beep();
      ajusteprog=true;
      select_menu_prog();
      flag_menu=5;
    }//BUTTON OK MENU PROG END------------------------------

   
    } //IF BUTTON OK END--------------------------------------------

}





void menu_system(){

    if (mnopt < 1) {
      mnopt=5;
    }
    if (mnopt>5){
      mnopt=1;
    }

   if (flag_menu==3){
   
   drawtext(menuop[mnopt], am, pt,3, 26, 1);
   drawtext(menu_desc_ptbr[0][mnopt],cy,az,0,55,1);
   drawtext(menu_desc_ptbr[1][mnopt],cy,az,0,65,1);
   drawtext("  Anterior <   > Proximo  ",am,az,0,110,1);
   if (mnopt==5){
                drawtext("ESC Retorna               ",am,az,0,120,1);
                }
   else{
        drawtext("SET Seleciona  ESC Retorna",am,az,0,120,1);
       }
     
   }



   if (flag_menu==4){
   drawtext(menuop[mnopt], am, vm,3, 26, 1);
   ajusteprog=true;
   
   if (mnopt==1){
      tft.fillRect(0, 35, 157, 93, az);
      tft.fillRect(40, 62, 80, 40 , 0xC6F3);
      refeicoes_dog_ant=0;
      refeicoes_cat_ant=0;
      desenha_dog();
      desenha_cat();
      pet_food();
      flag_menu=5;
      }

  if (mnopt==2){
      tft.fillRect(0, 35, 157, 93, az);
      menufuso = fuso_index_saved; 
      flag_menu=15;
      fuso_menu();
      }

 if (mnopt==3){
      tft.fillRect(0, 35, 157, 93, az);
      flag_menu=25;
      }


 if (mnopt==4){
      tft.fillRect(0, 35, 157, 93, az);
      flag_menu=35;
   }


if (mnopt==5){
  tft.fillRect(0, 35, 157, 93, az);
  flag_menu=45;
}


   }

}

void prog_selected(){

drawtext("  Anterior <   > Proximo  ",am,az,0,110,1);
drawtext("SET Confirma   ESC Retorna",am,az,0,120,1);

  if (menuprog==1){
color_dog_prog(vm,vd,az,cz,az,cz,az,cz);
color_cat_prog(az,cz,az,cz,az,cz,az,cz);
pet_food();
}

if (menuprog==2){
color_dog_prog(az,cz,vm,vd,az,cz,az,cz);
color_cat_prog(az,cz,az,cz,az,cz,az,cz);
pet_food();
}

if (menuprog==3){
color_dog_prog(az,cz,az,cz,vm,vd,az,cz);
color_cat_prog(az,cz,az,cz,az,cz,az,cz);
pet_food();
}


if (menuprog==4){
color_dog_prog(az,cz,az,cz,az,cz,vm,vd);
color_cat_prog(az,cz,az,cz,az,cz,az,cz);
pet_food();
}

if (menuprog==5){
color_dog_prog(az,cz,az,cz,az,cz,az,cz);
color_cat_prog(vm,vd,az,cz,az,cz,az,cz);
pet_food();
}

if (menuprog==6){
color_dog_prog(az,cz,az,cz,az,cz,az,cz);
color_cat_prog(az,cz,vm,vd,az,cz,az,cz);
pet_food();
}

if (menuprog==7){
color_dog_prog(az,cz,az,cz,az,cz,az,cz);
color_cat_prog(az,cz,az,cz,vm,vd,az,cz);
pet_food();
}

if (menuprog==8){
color_dog_prog(az,cz,az,cz,az,cz,az,cz);
color_cat_prog(az,cz,az,cz,az,cz,vm,vd);
pet_food();
}
set_prog_op =  (prog_index_from_file[menuprog].toInt());
if (debug_set){
Serial.print("Variavel Set_prog_op:");
Serial.println(set_prog_op);
}
flag_menu = 8;
}



void set_prog(){

  if (set_prog_op < 1){
    set_prog_op=98;
    }
if (set_prog_op>98){
    set_prog_op=1;
    }

    
    progdata[menuprog] = prog[set_prog_op];
    pet_food();

}


void select_menu_fuso(){

  if (menufuso < 1){
    menufuso=24;
    }
if (menufuso>24){
    menufuso=1;
    }

 
 fuso_menu();

}


void select_menu_prog(){

if (menuprog < 1){
    menuprog=8;
    }
if (menuprog>8){
    menuprog=1;
    }

if (menuprog==1){
color_dog_prog(vm,am,az,cz,az,cz,az,cz);
color_cat_prog(az,cz,az,cz,az,cz,az,cz);
pet_food();
}

if (menuprog==2){
color_dog_prog(az,cz,vm,am,az,cz,az,cz);
color_cat_prog(az,cz,az,cz,az,cz,az,cz);
pet_food();
}

if (menuprog==3){
color_dog_prog(az,cz,az,cz,vm,am,az,cz);
color_cat_prog(az,cz,az,cz,az,cz,az,cz);
pet_food();
}


if (menuprog==4){
color_dog_prog(az,cz,az,cz,az,cz,vm,am);
color_cat_prog(az,cz,az,cz,az,cz,az,cz);
pet_food();
}

if (menuprog==5){
color_dog_prog(az,cz,az,cz,az,cz,az,cz);
color_cat_prog(vm,am,az,cz,az,cz,az,cz);
pet_food();
}

if (menuprog==6){
color_dog_prog(az,cz,az,cz,az,cz,az,cz);
color_cat_prog(az,cz,vm,am,az,cz,az,cz);
pet_food();
}

if (menuprog==7){
color_dog_prog(az,cz,az,cz,az,cz,az,cz);
color_cat_prog(az,cz,az,cz,vm,am,az,cz);
pet_food();
}

if (menuprog==8){
color_dog_prog(az,cz,az,cz,az,cz,az,cz);
color_cat_prog(az,cz,az,cz,az,cz,vm,am);
pet_food();
}
drawtext("  Anterior <   > Proximo  ",am,az,0,110,1);
drawtext("SET Seleciona  ESC Retorna",am,az,0,120,1);
if (mnprg_ant != menuprog){
if (debug_set){
Serial.print("Variavel flag_menu:");
Serial.println(flag_menu);
Serial.print("Variavel mnopt:");
Serial.println(mnopt);
Serial.print("Variavel menuprog:");
Serial.println(menuprog);
}
mnprg_ant = menuprog;
}

}
