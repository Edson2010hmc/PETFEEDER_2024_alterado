// ============================================================================
// TASK DE CONEXÃO - CORE 1
// =============================================================================
void connect_Wifi() {
  Serial.println("Iniciando rotina WiFi");
  
  wifiManager.setConfigPortalTimeout(0);     // 0 = AGUARDA PARA SEMPRE
  wifiManager.setConnectTimeout(10);
  wifiManager.setConnectRetries(5);
  wifiManager.setDebugOutput(true);
  wifiManager.setBreakAfterConfig(true);
  
  Serial.println("[WIFI] Aguardando conexão...");
  
  wifiManager.autoConnect("PETFEEDER", "password");
  
  Serial.println("[WIFI] Conectado!");
  Serial.print("[WIFI] IP: ");
  Serial.println(WiFi.localIP());
  wifi_icon_refresh(check_wifi_level());
  mqtt_start();
  ntp_start();
  ntp_flag = true;
}
// ============================================================================
// FUNÇÃO WIFI START (BLOQUEANTE - USO OPCIONAL)
// ============================================================================
void wifi_start() {
  // WIFI Start
  wifiManager.setBreakAfterConfig(true);
  
  // ✅ CONFIGURAR TIMEOUTS
  wifiManager.setConfigPortalTimeout(120);
  wifiManager.setConnectTimeout(30);
  
  Serial.println("[WIFI] Iniciando conexão...");
  
  ledvm();
  
  if (!wifiManager.autoConnect("PETFEEDER", "password")) {
    Serial.println("[WIFI] Falha na conexão");
    Serial.println("[WIFI] Iniciando Access Point");
    
    drawtext("                          ", az, bc, 0, 110, 1);
    drawtext("  INICIANDO ACCESS POINT  ", az, bc, 0, 110, 1);
    wifi_led_status();
    
    delay(2000);
    
    // ✅ RETORNA ao invés de reiniciar
    return;
  }
  
  drawtext("                          ", az, bc, 0, 110, 1);
  drawtext("    CONECTADO AO WIFI     ", az, bc, 0, 110, 1);
  wifi_led_status();
  
  // Debug Wifi Connection to Serial Monitor
  Serial.print("[WIFI] Status Code: ");
  Serial.print(WiFi.status());
  Serial.println(" - Conectado!");
  Serial.print("[WIFI] IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("[WIFI] MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.print("[WIFI] RSSI: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dB");
}

// ============================================================================
// WIFI SIGNAL LEVEL CHECK
// ============================================================================
int check_wifi_level() {
  if (WiFi.status() == WL_CONNECTED) {
    wf_lv = 0;
    
    int rssi = WiFi.RSSI();
    //Serial.print("[RSSI]");
    //Serial.println(rssi);
    if (rssi > -50) {
      wf_lv = 4;
    } else if (rssi > -57) {
      wf_lv = 3;
    } else if (rssi > -63) {
      wf_lv = 2;
    } else if (rssi > -70) {
      wf_lv = 1;
    } else {
      wf_lv = 0;
    }
    
    return wf_lv;
  }
  
  return 0;  // Desconectado
}

// ============================================================================
// WIFI ICON UI REFRESH
// ============================================================================
void wifi_icon_refresh(int level_code) {
  posmem_wifi = 0;
  //Serial.print("[Wifi Level Scale]");
  //Serial.println(level_code);
  const uint16_t* iconData;
  
  // Selecionar ícone baseado no nível
  switch (level_code) {
    case 0:
      iconData = wifi00;
      break;
    case 1:
      iconData = wifi25;
      break;
    case 2:
      iconData = wifi55;
      break;
    case 3:
      iconData = wifi70;
      break;
    case 4:
      iconData = wifi100;
      break;
    default:
      iconData = wifi00;
      break;
  }
  
  // Desenhar ícone
  for (int row = 3; row < 20; row++) {
    for (int col = 141; col < 159; col++) {
      tft.drawPixel(col, row, iconData[posmem_wifi]);
      posmem_wifi++;
    }
  }
}

// ============================================================================
// FUNÇÕES AUXILIARES
// ============================================================================

// Verificar se deve resetar credenciais WiFi
void check_wifi_reset_button() {
  static unsigned long lastCheck = 0;
  
  if (millis() - lastCheck > 500) {  // Debounce 500ms
    if (digitalRead(WIFI_RST) == LOW) {
      Serial.println("[WIFI] Botão de reset pressionado");
      Serial.println("[WIFI] Aguarde 3 segundos para confirmar...");
      
      unsigned long pressStart = millis();
      while (digitalRead(WIFI_RST) == LOW && millis() - pressStart < 3000) {
        delay(100);
      }
      
      if (millis() - pressStart >= 3000) {
        Serial.println("[WIFI] Resetando credenciais...");
        
        // Mensagem no display
        tft.fillScreen(az);
        drawtext("  RESETANDO WIFI...  ", az, bc, 0, 60, 2);
        delay(1000);
        drawtext("                     ", az, bc, 0, 60, 2);
        // Reset
        wifiManager.resetSettings();
        
        delay(1000);
        Serial.println("[WIFI] Reiniciando...");
        ESP.restart();
      } else {
        Serial.println("[WIFI] Reset cancelado");
      }
    }
    
    lastCheck = millis();
  }
}

// Reconectar WiFi se desconectado
void wifi_reconnect_if_needed() {
  static unsigned long ultimaVerificacao = 0;
  
  if (millis() - ultimaVerificacao > 30000) {
    if (WiFi.status() != WL_CONNECTED) {
      wifi_icon_refresh(check_wifi_level());
      Serial.println("[WIFI] Desconectado - reconectando...");
      
      if (wifiManager.autoConnect("PETFEEDER", "password")) {
        Serial.println("[WIFI] Reconectado!");
        wifi_icon_refresh(check_wifi_level());
        mqtt_start();
        ntp_start();
        ntp_flag = true;
      }
    }
    ultimaVerificacao = millis();
  }
}