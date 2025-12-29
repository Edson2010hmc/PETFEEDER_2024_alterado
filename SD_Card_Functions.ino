  // SS    10
  // MOSI  11
  // SCK   12
  // MISO  13
// SD CARD SET UP---------------------------------------------
void init_sd_card(){
   //drawtext("                         ", az,bc,0,110,1);
   //drawtext("    INICIANDO SD CARD    ", az,bc,0,110,1);
     //     "  SOLUCOES  TECNOLOGICAS  "
   if(!SD.begin(CS)){
    //drawtext("                         ", az,bc,0,110,1);
    //drawtext("ERRO>SD CARD NÃO INICIADO ", az,bc,0,110,1);
          //     "  SOLUCOES  TECNOLOGICAS  "
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  //drawtext("                         ", az,bc,0,110,1);
  //drawtext("       SD CARD -  OK      ", az,bc,0,110,1);
        //     "  SOLUCOES  TECNOLOGICAS  "
}


// LIST FILES IN SD CARD FOLDER ------------------------------------------
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if(!root){
    Serial.println("Failed to open directory");
    return;
  }
  if(!root.isDirectory()){
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while(file){
    if(file.isDirectory()){
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if(levels){
        listDir(fs, file.name(), levels -1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}


// CREATE FOLDER IN SD CARD-------------------------------------------------
void createDir(fs::FS &fs, const char * path){
  Serial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)){
    Serial.println("Dir created");
  } else {
    Serial.println("mkdir failed");
  }
}

void removeDir(fs::FS &fs, const char * path){
  Serial.printf("Removing Dir: %s\n", path);
  if(fs.rmdir(path)){
    Serial.println("Dir removed");
  } else {
    Serial.println("rmdir failed");
  }
}

String read_saved(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);
  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    return "\0";
  }
  char string_temp[6];
  unsigned int index = 0;
  while(file.available()){
  string_temp[index] = file.read(); 
  index++;
  }
  file.close();
  String data_return;
  data_return = String(string_temp);
  Serial.print("Data from file: ");
  Serial.println(data_return);
  return data_return;
}

void read_prog_file(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);
  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    }
  unsigned int indx = 1;
  String linex = "";
        while (file.available()) {
            char w = file.read();
            if (debug_set){
            Serial.print(w);
            }
            if (w == ',') { // Separador 
                progdata[indx] = linex;
                indx++;
                if (debug_set){
                Serial.println("");
                Serial.println(linex);
                }
                linex = ""; // Limpa a linha para o próximo horário
            } else {
                linex += w;
            }
        }
  lv_dog = lv_dog_res();
  lv_cat = lv_cat_res();     
  data_pub=progdata[1] + "," + progdata[2] + "," + progdata[3]+ "," + progdata[4]+ "," + progdata[5]+ "," + progdata[6]+ "," + progdata[7]+ "," + progdata[8]/*+ "," + lv_dog + "," + lv_cat*/;
  // publish_schedule();  // ✅ REMOVIDO - será chamado após MQTT conectar
  
}

void read_dispenser_config(){
  String config_str = read_saved(SD, "/dispenser_config.ptf");
  
  if(config_str == "\0"){
    Serial.println("Arquivo dispenser_config não existe - criando...");
    writeFile(SD, "/dispenser_config.ptf", "30,30,1300,1300");
    return;
  }
  
  int idx = 0;
  String valores[4];
  String temp = "";
  
  for(int i = 0; i < config_str.length(); i++){
    if(config_str[i] == ','){
      valores[idx++] = temp;
      temp = "";
    } else {
      temp += config_str[i];
    }
  }
  valores[idx] = temp;
  
  dispenser_dog_speed = valores[0].toInt();
  dispenser_cat_speed = valores[1].toInt();
  dispenser_dog_time = valores[2].toInt();
  dispenser_cat_time = valores[3].toInt();
  
  if(debug_set){
    Serial.println("Servo config carregada:");
    Serial.print("Dog speed: "); Serial.println(dispenser_dog_speed);
    Serial.print("Cat speed: "); Serial.println(dispenser_cat_speed);
    Serial.print("Dog time: "); Serial.println(dispenser_dog_time);
    Serial.print("Cat time: "); Serial.println(dispenser_cat_time);
  }
}

void save_dispenser_config(){
  String config = String(dispenser_dog_speed) + "," + 
                  String(dispenser_cat_speed) + "," + 
                  String(dispenser_dog_time) + "," + 
                  String(dispenser_cat_time);
  
  writeFile(SD, "/dispenser_config.ptf", config.c_str());
  
  if(debug_set){
    Serial.println("Servo config salva: " + config);
  }
}





void publish_schedule(){
  String topico_pub = from_machine + "-schedule";
  publica(topico_pub,data_pub);
}




// READ FILE AND PUT INTO VARIABLE THE PROGRAMMED TIMES INDEX DATA -----------------------------------
void read_prog_index(fs::FS &fs, const char * path){
  if (debug_set){
  Serial.printf("Reading file: %s\n", path);
  }
  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    }
  unsigned int ind = 1;
  String line = "";
        while (file.available()) {
            char c = file.read();
            if (debug_set){
            Serial.print(c);
            }
            if (c == ',') { // Separador de horários
                prog_index_from_file[ind] = line;
                ind++;
                if (debug_set){
                Serial.println("");
                Serial.println(line);
                }
                line = ""; // Limpa a linha para o próximo horário
            } else {
                line += c;
            }
        }
}

//---- SAVE FILE FUSO-------------------------------------------------------------------------------------------
void save_fuso_prog(){

String save_index_fuso_str="";
save_index_fuso_str= String(menufuso);
const char* save_index_fuso_char = save_index_fuso_str.c_str();
if (debug_set){
Serial.print("variavel menufuso:");
Serial.println(menufuso);
Serial.print("variavel save_index_fuso_char:");
Serial.println(save_index_fuso_char);
Serial.print("variavel save_index_fuso_str:");
Serial.println(save_index_fuso_str);
}
writeFile(SD, "/fuso_index.ptf",save_index_fuso_char);
const char* fuso_to_save;
fuso_to_save = fusos_mundiais[menufuso].c_str();
writeFile(SD, "/fuso.ptf",fuso_to_save);
fuso_set = fusos_mundiais[menufuso].substring(1).toInt();
fuso_set *= 3600;
  if (fusos_mundiais[menufuso]== "-"){
     fuso_set = fuso_set * -1;
     }
      drawtext("    FUSO HORARIO SALVO    ", bc, pt,0, 120, 1);
      delay(1000);
      drawtext("SET Seleciona  ESC Retorna", am, az,0, 120, 1);
      tft.fillRect(0, 35, 157, 93, az);
      drawtext("RESETING TO SET LOCAL TIME",am,pt,0,60,1);
delay(500);
// ✅ NÃO REINICIA - NTP atualiza diretamente via setTimeOffset (linha 443)

}


//----SAVE FILE PROGRAM TIME MODIFIED  BY IHM ---------------------------------------------------------------------

void save_selected_file(){
   const char* progdata_char = progdata[menuprog].c_str();
      
   if (menuprog==1){
    //writeFile(SD, "/first_dog.ptf",progdata_char);
    if (debug_set){
    Serial.println(prog_index_from_file[1]);
    Serial.println(set_prog_op);
    }
    prog_index_from_file[1] = String(set_prog_op);
    if (debug_set){
    Serial.println(prog_index_from_file[1]);
    }
    
   }
    if (menuprog==2){
    //writeFile(SD, "/second_dog.ptf",progdata_char);
    if (debug_set){
    Serial.println(prog_index_from_file[2]);
    Serial.println(set_prog_op);
    }
     prog_index_from_file[2] = String(set_prog_op);
     if (debug_set){
     Serial.println(prog_index_from_file[2]);
     }
   }  
    if (menuprog==3){
    //writeFile(SD, "/third_dog.ptf",progdata_char);
    if (debug_set){
    Serial.println(prog_index_from_file[3]);
    Serial.println(set_prog_op);
    }
    prog_index_from_file[3] = String(set_prog_op);
    if (debug_set){
    Serial.println(prog_index_from_file[3]);
    }
   } 
    if (menuprog==4){
    //writeFile(SD, "/fourth_dog.ptf",progdata_char);
    if (debug_set){
    Serial.println(prog_index_from_file[4]);
    Serial.println(set_prog_op);
    }
    prog_index_from_file[4] = String(set_prog_op);
    if (debug_set){
    Serial.println(prog_index_from_file[4]);
    }
   }   
    if (menuprog==5){
    //writeFile(SD, "/first_cat.ptf",progdata_char);
    if (debug_set){
    Serial.println(prog_index_from_file[5]);
    Serial.println(set_prog_op);
    }
     prog_index_from_file[5] = String(set_prog_op);
     if (debug_set){
     Serial.println(prog_index_from_file[5]);
     }
   }   
     if (menuprog==6){
    //writeFile(SD, "/second_cat.ptf",progdata_char);
    if (debug_set){
    Serial.println(prog_index_from_file[6]);
    Serial.println(set_prog_op);
    }
     prog_index_from_file[6] = String(set_prog_op);
     if (debug_set){
     Serial.println(prog_index_from_file[6]);
     }
   }   
     
   if (menuprog==7){
    if (debug_set){Serial.println(prog_index_from_file[7]);
                   Serial.println(set_prog_op);}

    prog_index_from_file[7] = String(set_prog_op);

    if (debug_set){Serial.println(prog_index_from_file[7]);}
                   } 

   if (menuprog==8){
    if (debug_set){Serial.println(prog_index_from_file[8]);
                   Serial.println(set_prog_op);}
    
    prog_index_from_file[8] = String(set_prog_op);
    
    if (debug_set){Serial.println(prog_index_from_file[8]);}
   }

   update_prog_data();
   update_prog_index();       
}

// UPDATE AND SAVE PROGRAMMED TIMES INDEX DATA IN SD FILE-------------------------------
void update_prog_index(){

String save_index_str = "";
save_index_str = prog_index_from_file[1] + "," + prog_index_from_file[2] + "," + prog_index_from_file[3]+ "," + prog_index_from_file[4]+ "," + prog_index_from_file[5]+ "," + prog_index_from_file[6]+ "," + prog_index_from_file[7]+ "," + prog_index_from_file[8]+ ",";
if (debug_set){
Serial.print("variavel save_index_str:");
Serial.println(save_index_str);
}
const char* save_index_char = save_index_str.c_str();
if (debug_set){
Serial.print("variavel save_index_char:");
Serial.println(save_index_char);
}
writeFile(SD, "/prog_index.ptf",save_index_char);
if (debug_set){
Serial.println("Index prog data file:");
for (int x = 1; x<9; x++){
Serial.println(prog_index_from_file[x]);
}
}

}


void update_prog_data(){
String string_to_pub = "";
String save_data_str = "";
lv_dog = lv_dog_res();
lv_cat = lv_cat_res(); 
string_to_pub = progdata[1] + "," + progdata[2] + "," + progdata[3]+ "," + progdata[4]+ "," + progdata[5]+ "," + progdata[6]+ "," + progdata[7]+ "," + progdata[8]+ ","+lv_dog+","+lv_cat;
save_data_str = progdata[1] + "," + progdata[2] + "," + progdata[3]+ "," + progdata[4]+ "," + progdata[5]+ "," + progdata[6]+ "," + progdata[7]+ "," + progdata[8]+ ",";
String top_pub = from_machine+"-schedule";
publica(top_pub,string_to_pub);
if (debug_set){
Serial.print("variavel save_data_str:");
Serial.println(save_data_str);
}
const char* save_data_char = save_data_str.c_str();
if (debug_set){
Serial.print("variavel save_data_char:");
Serial.println(save_data_char);
}
writeFile(SD, "/prog_data.ptf",save_data_char);
if (debug_set){
Serial.println("Prog data file:");
}
//three_beep();
if (debug_set){
for (int x = 1; x<9; x++){
Serial.println(progdata[x]);
}
}
// delay(500);  // ✅ REMOVIDO - desnecessário
// get_config();  // ✅ REMOVIDO - dados já estão em memória, não precisa reler



}//-----------------------------------------------------------------------------------------------------------




// RESET AL CONFIG FILES TO DEFAULT VALUES ---------------------------------------------

void reset_all_files(){
  deleteFile(SD, "/fuso.ptf");
  deleteFile(SD, "/progs.ptf");
  deleteFile(SD,"/prog_index.ptf");
  deleteFile(SD,"/dispenser_config.ptf");
  deleteFile(SD,"/fuso_index.ptf");
  deleteFile(SD,"/time_disp.ptf");
  deleteFile(SD,"//prog_data.ptf");
  delay(500); 
  writeFile(SD, "/prog_data.ptf","07:00,11:00,15:00,19:00,07:00,11:00,15:00,19:00,");
  String tp_pub= from_machine+"-schedule";
  publica(tp_pub,"07:00,11:00,15:00,19:00,07:00,11:00,15:00,19:00,");
  writeFile(SD, "/fuso.ptf","-3");
  writeFile(SD,"/prog_index.ptf","7,31,55,79,7,31,55,79,");
  writeFile(SD,"/fuso_index.ptf","10");
  writeFile(SD,"/time_disp.ptf","3000");
  writeFile(SD, "/dispenser_config.ptf","30,30,1300,1300");
  delay(500);
  const int inicioHora = 6;   
  const int fimHora = 22;     
  const int intervalo = 10;
  String format_data = "";
  for (int hora = inicioHora; hora <= fimHora; hora++) {
    for (int minuto = 0; minuto < 60; minuto += intervalo) {
        String horaStr = hora < 10 ? "0" + String(hora) : String(hora);
        String minutoStr = minuto < 10 ? "0" + String(minuto) : String(minuto);
        format_data = (horaStr + ":" + minutoStr + ",");
        const char*  format_data_char = format_data.c_str();
        appendFile_creating(SD,"/progs.ptf",format_data_char);
    }
  }
}





// GET VALUES FROM CONFIG FILES AND PUT INTO VARIABLES ---------------------------------------
void get_config(){
     String fuso_index_saved_str="";
     read_prog_file(SD,"/prog_data.ptf");
     read_dispenser_config();
     fuso_index_saved_str=(read_saved(SD,"/fuso_index.ptf"));
     saved_fuso =         (read_saved_times(SD, "/fuso.ptf"));
     dispenser_time_str = (read_saved(SD,"/time_disp.ptf"));
     read_prog_index(SD,"/prog_index.ptf");
     if (debug_set){
     Serial.print("Variavel dispenser_time_str");
     Serial.println(dispenser_time_str);
     Serial.print("Variavel saved_fuso:");  
     Serial.println(saved_fuso); 
     }
     fuso_set = saved_fuso.substring(1).toInt();
     fuso_index_saved = fuso_index_saved_str.toInt();
     fuso_set *= 3600;
     if (saved_fuso[0]== '-'){
     fuso_set = fuso_set * -1;
     }
     dispenser_time = dispenser_time_str.toInt();
     if (debug_set){
     Serial.print("Variavel dispenser_time");
     Serial.println(dispenser_time);
     Serial.print("Variavel fuso_set:");  
     Serial.println(fuso_set);
     }
     ntp.setTimeOffset(fuso_set); // SET TIME OFFSET BEFORE READ FILE CONFIG
 }//---------------------------------------------------------------

// READ FILE WHIT TIMES TIME TO DISPENSER FOOD ------------------------------------
String read_saved_times(fs::FS &fs, const char * path){
  if (debug_set){
  Serial.printf("Reading file: %s\n", path);
  }
  File file = fs.open(path);
  if(!file){
    if (debug_set){
    Serial.println("Failed to open file for reading");
    }
    return "\0";
  }
  char string_temp_times[2];
  unsigned int index = 0;
  while(file.available()){
  string_temp_times[index] = file.read(); 
  index++;
  }
  file.close();
  String data_return;
  data_return = String(string_temp_times);
  if (debug_set){
  Serial.print("Data from file: ");
  Serial.println(data_return);
  }
  return data_return;
}//----------------------------------------------------


/*void readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  char string[100];
  unsigned int index = 0;
  while(file.available()){
  fourth_cat[index] = file.read(); 
  index++;
  }
  Serial.println(fourth_cat);
  file.close();
}*/


// CREATE AND PUT DATA IN CONFIG FILES IN SD CARD -------------------------------
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.print("Dados sendo salvos:");
    Serial.println(message);
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

/*void appendFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
    Serial.println("Failed to open file for appending or file not found.");
    return;
  }
  if(file.print(message)){
      Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}*/



// IF MULTIPLE LINES FILE CONFIG NOT EXIST, CREATE AND PUT DATA------------------------------------
void appendFile_creating(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  
  if(!file){
    flag_file = true;
    Serial.println("Failed to open file for appending or file not found. Creating File");
    File file = fs.open(path, FILE_WRITE);
    delay(200);
    if(!file){
      Serial.println("Failed to create file");
      return;
    }
  }
  else{
    flag_file = false;
  }
  if (flag_file == true){
    File file = fs.open(path, FILE_APPEND);
    flag_file = false;
    }
  if(file.print(message)){
      Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}



// RENAME FILE IN SD CARD ----------------------------------------------
void renameFile(fs::FS &fs, const char * path1, const char * path2){
  Serial.printf("Renaming file %s to %s\n", path1, path2);
  if (fs.rename(path1, path2)) {
    Serial.println("File renamed");
  } else {
    Serial.println("Rename failed");
  }
}


// DELETE FILE IN SD CARD -----------------------------------------
void deleteFile(fs::FS &fs, const char * path){
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)){
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}
