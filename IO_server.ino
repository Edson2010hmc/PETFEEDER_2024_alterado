//-----------------MQTT FUNCTIONS -----------------------------------------------------------------------------------
void mqtt_start(){
  
    mqttClient.setUsernamePassword(mqtt_user, mqtt_pass);
    if (!mqttClient.connect(broker, port)) {
      Serial.print("CÓDIGO DE ERRO No. "); 
      Serial.print(mqttClient.connectError());
      Serial.println (" ao tentar se conectar ao Broker MQTT");
      Serial.println ("CONEXÃO NÃO REALIZADA! Continuando sem MQTT...");
      
      // ✅ NÃO REINICIA - permite funcionamento offline
      return;
    }
    else{
       Serial.println ("CONECTADO AO BROKER MQTT");
    }
 
    mqttClient.subscribe(topico);
    
}

 //updt07:0011:0015:0019:0007:0011:0015:0019:00

void check_mqtt(){
  String subsc = subscreve();
  String comm_sub = subsc.substring(0,4);

  // update schedule
  if (comm_sub =="updt"){
    progdata[1] = subsc.substring(4,9);
    progdata[2] = subsc.substring(9,14);
    progdata[3] = subsc.substring(14,19);
    progdata[4] = subsc.substring(19,24);
    progdata[5] = subsc.substring(24,29);
    progdata[6] = subsc.substring(29,34);
    progdata[7] = subsc.substring(34,39);
    progdata[8] = subsc.substring(39,44);
    update_prog_data();
    ajusteprog = true;
    refresh_ihm();
    } 

  if (comm_sub =="catf"){feed_cat();}
  if (comm_sub =="dogf"){feed_dog();}
  if(comm_sub=="prog"){publish_schedule();}
  if(comm_sub=="lvsl"){pub_lvsl();}


  if(comm_sub=="disp"){
    int idx = 0;
    String val[4];
    String temp = "";
    String dados = subsc.substring(4);
    
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
    Serial.println("Dispenser_config atualizado via MQTT");
  }
} 



void pub_lvsl(){
String top_lev_dog=from_machine+"-resdog";
String top_lev_cat=from_machine+"-rescat";
publica(top_lev_dog,String(lv_dog_res()));
publica(top_lev_cat,String(lv_cat_res()));
}



void publica(String topic, String mensagem){
      // ✅ VERIFICAR SE MQTT ESTÁ CONECTADO
      if (mqttClient.connected()) {
        mqttClient.beginMessage(topic);
        mqttClient.print(mensagem);
        mqttClient.endMessage();
      } else {
        if (debug_set) {
          Serial.println("[MQTT] Não conectado - mensagem não enviada");
        }
      }
}

String subscreve(){
    String msgrec="";
    int messageSize = mqttClient.parseMessage();
    if (messageSize) {
    
   msgrec=(mqttClient.readString());
}
return msgrec;
}
