
// BEGIN NTP SYSTEM AFTER WIFI CONNECTION------------------------------------------
void ntp_start(){
  ntp.begin();
  ntp.forceUpdate();//Força o Update.
  relogio();
  if (debug_set){Serial.println(dia_semana+", "+datahora);}              
  }


//--- TIME SYSTEM------------------------------------------------------
// ✅ OTIMIZADO: Usa sprintf ao invés de concatenações String
void relogio(){
  if (WiFi.status() == WL_CONNECTED) {

  time_t epoch = ntp.getEpochTime();
  struct tm *ptm = gmtime ((time_t *)&epoch); 
  String hora_formatada = ntp.getFormattedTime();
  
  // ✅ Buffers temporários para sprintf (muito mais rápido)
  static char hora_buf[3];
  static char min_buf[3];
  static char seg_buf[3];
  static char dia_buf[3];
  static char mes_buf[3];
  static char ano_buf[5];
  static char data_buf[11];
  static char horario_buf[6];
  static char datahora_buf[25];
  
  // ✅ Formatar com sprintf (evita alocações dinâmicas)
  sprintf(hora_buf, "%02d", ntp.getHours());
  sprintf(min_buf, "%02d", ntp.getMinutes());
  sprintf(seg_buf, "%02d", ntp.getSeconds());
  sprintf(dia_buf, "%02d", ptm->tm_mday);
  sprintf(mes_buf, "%02d", ptm->tm_mon + 1);
  sprintf(ano_buf, "%04d", ptm->tm_year + 1900);
  sprintf(data_buf, "%02d/%02d/%04d", ptm->tm_mday, ptm->tm_mon + 1, ptm->tm_year + 1900);
  sprintf(horario_buf, "%02d:%02d", ntp.getHours(), ntp.getMinutes());
  sprintf(datahora_buf, "%02d/%02d/%04d  %02d:%02d", 
          ptm->tm_mday, ptm->tm_mon + 1, ptm->tm_year + 1900,
          ntp.getHours(), ntp.getMinutes());
  
  // ✅ Converter para String (compatível com código existente)
  hora = String(hora_buf);
  minuto = String(min_buf);
  segundo = String(seg_buf);
  dia_mes = String(dia_buf);
  mes = String(mes_buf);
  ano = String(ano_buf);
  currentDate = String(data_buf);
  horario = String(horario_buf);
  datahora = String(datahora_buf);
  
  dia_semana = weekDays[ntp.getDay()];
  nome_mes = months[ptm->tm_mon];
  hora_val = ntp.getHours();

}
}

// ✅ OTIMIZADO: Usa buffers fixos ao invés de VLA
void calendario(){

  // ✅ Buffers fixos (tamanho máximo conhecido)
  static char sem_ch[14];       // "QUARTA-FEIRA" + \0
  static char data_ch[11];      // "DD/MM/YYYY" + \0
  static char hora_ch[6];       // "HH:MM" + \0
  
  static char sem_ch_anterior[14] = {0};
  static char data_ch_anterior[11] = {0};
  static char hora_ch_anterior[6] = {0};
  
  // ✅ Copiar strings para buffers
  dia_semana.toCharArray(sem_ch, 14);
  
  if (strcmp(sem_ch, sem_ch_anterior) != 0) {
      tft.setTextSize(1);
      tft.setCursor(1, 120);
      tft.setTextColor(ST77XX_CYAN, ST77XX_BLUE);
      tft.print(sem_ch);
      strcpy(sem_ch_anterior, sem_ch);
  }

  currentDate.toCharArray(data_ch, 11);
  
  if (strcmp(data_ch, data_ch_anterior) != 0) {
    tft.setCursor(100, 120);
    tft.setTextColor(ST7735_CYAN, ST7735_BLUE);
    tft.print(data_ch);
    strcpy(data_ch_anterior, data_ch);
  }

  horario.toCharArray(hora_ch, 6);

  if (strcmp(hora_ch, hora_ch_anterior) != 0) {
      tft.setTextSize(2);
      tft.setCursor(52, 103);
      tft.setTextColor(ST7735_CYAN, ST7735_BLUE);
      tft.print(hora_ch);
      strcpy(hora_ch_anterior, hora_ch);
  }

}
