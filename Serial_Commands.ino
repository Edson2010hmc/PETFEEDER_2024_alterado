
// CHECK IF THERE ARE COMMANDS FROM SERIAL----------------------------
void check_serial(){
  if (Serial.available()){
  comm_ser = Serial.readString();
  Serial.println(comm_ser);
  Serial_check(comm_ser);
  comm_ser="\0";}
}



// READ SERIAL COMMANDS ----------------------------------------

void Serial_check(String Com_S){

  if (Com_S=="catf"){
    Serial.println("O comando "+Com_S+ " foi processado.");
    feed_cat();
  }

  if (Com_S=="dogf"){
    Serial.println("O comando "+Com_S+ " foi processado.");
    feed_dog();
  }




  if (Com_S=="comm_1"){
    Serial.println("O comando "+Com_S+ " foi processado.");
    ledvm();
  }
  
   if (Com_S=="comm_2"){
    Serial.println("O comando "+Com_S+ " foi processado.");
    ledvd();
  }

     if (Com_S=="comm_3"){
    Serial.println("O comando "+Com_S+ " foi processado.");
    ledam();
  }

     if (Com_S=="comm_4"){
    Serial.println("O comando "+Com_S+ " foi processado.");
    ledaz();
  }

     if (Com_S=="comm_5"){
    Serial.println("O comando "+Com_S+ " foi processado.");
    
   }

 if (Com_S=="cat_10"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(10);
   }

   if (Com_S=="cat_20"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(20);
   }

   if (Com_S=="cat_30"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(30);
   }

   if (Com_S=="cat_40"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(40);
   }

 if (Com_S=="cat_50"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(50);
   }

if (Com_S=="cat_60"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(60);
   }
   if (Com_S=="cat_70"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(70);
   }
   if (Com_S=="cat_80"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(80);
   }
   if (Com_S=="cat_90"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(90);
   }
 if (Com_S=="cat_100"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(100);
   }

   if (Com_S=="cat_0"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(0);
   }

   if (Com_S=="dog_0"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_cat(0);
   }
















  if (Com_S=="dog_10"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_dog(10);
   }

   if (Com_S=="dog_20"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_dog(20);
   }

   if (Com_S=="dog_30"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_dog(30);
   }

   if (Com_S=="dog_40"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_dog(40);
   }

   if (Com_S=="dog_50"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_dog(50);
   }

   if (Com_S=="dog_60"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_dog(60);
   }

   if (Com_S=="dog_70"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_dog(70);
   }

   if (Com_S=="dog_80"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_dog(80);
   }

   if (Com_S=="dog_90"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_dog(90);
   }

   if (Com_S=="dog_100"){
    Serial.println("O comando "+Com_S+ " foi processado.");
        nivel_dog(100);
   }  

     if(Com_S.substring(0,4)=="disp"){
    int idx = 0;
    String val[4];
    String temp = "";
    String dados = Com_S.substring(4);
    
    for(int i = 0; i < dados.length(); i++){
      if(dados[i] == ','){
        val[idx++] = temp;
        temp = "";
      } else {
        temp += dados[i];
      }
    }
    val[idx] = temp;
    
    dispenser_dog_speed = val[0].toInt();
    dispenser_cat_speed = val[1].toInt();
    dispenser_dog_time = val[2].toInt();
    dispenser_cat_time = val[3].toInt();
    
    save_dispenser_config();
    Serial.println("Dispenser_config atualizado via Serial");
  }
}




   
