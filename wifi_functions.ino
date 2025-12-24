// ============================================================================
// TASK DE CONEXÃO - CORE 1
// ============================================================================
void connect_Wifi {
  
  Serial.println("Iniciando rotina WiFi");
  
  // ✅ CONFIGURAR TIMEOUTS NO WIFIMANAGER
  wifiManager.setConfigPortalTimeout(120);   // 2 minutos máximo no portal
  wifiManager.setConnectTimeout(30);         // 30 segundos por tentativa
  wifiManager.setConnectRetries(3);          // 3 tentativas de conexão
  wifiManager.setDebugOutput(debug_set);     // Debug conforme configuração
  wifiManager.setMinimumSignalQuality(20);   // Sinal mínimo aceitável
  
  unsigned long ultimaTentativaWiFi = 0;
  const unsigned long intervaloTentativa = 60000; // Tentar a cada 1 minuto
  
  for (;;) {
    // ✅ VERIFICAR SE PRECISA TENTAR CONECTAR
    if (WiFi.status() != WL_CONNECTED) {
      // Evita tentativas muito frequentes
      if (millis() - ultimaTentativaWiFi > intervaloTentativa) {
        ultimaTentativaWiFi = millis();
        
        wifiManager.setBreakAfterConfig(true);
        Serial.println("[WIFI] Tentando conectar...");
        
        // ✅ TRATAMENTO DE TIMEOUT
        if (!wifiManager.autoConnect("PETFEEDER", "password")) {
          Serial.println("[WIFI] Timeout - continuando sem WiFi");
          Serial.println("[WIFI] Próxima tentativa em 1 minuto");
          // ✅ NÃO REINICIA O ESP - continua funcionando
        } else {
          Serial.println("[WIFI] Conectado com sucesso!");
          Serial.print("[WIFI] IP: ");
          Serial.println(WiFi.localIP());
          Serial.print("[WIFI] MAC: ");
          Serial.println(WiFi.macAddress());
          Serial.print("[WIFI] RSSI: ");
          Serial.print(WiFi.RSSI());
          Serial.println(" dB");
        }
      }
    }
    
    // ✅ MQTT - Conectar se WiFi estiver ok
    if (WiFi.status() == WL_CONNECTED && !mqttClient.connected()) {
      Serial.println("[MQTT] Tentando conectar...");
      mqtt_start();
      
      if (mqttClient.connected()) {
        Serial.println("[MQTT] Conectado!");
      } else {
        Serial.println("[MQTT] Falha na conexão");
      }
    }
    
    // ✅ NTP - Sincronizar relógio
    if (WiFi.status() == WL_CONNECTED) {
      if (ntp_flag == false) {
        Serial.println("[NTP] Sincronizando relógio...");
        ntp_start();
        ntp_flag = true;  // ✅ ATRIBUIÇÃO CORRIGIDA
        Serial.println("[NTP] Sincronizado!");
      }
    } else {
      ntp_flag = false;
    }
    
    // ✅ ALIMENTAR WATCHDOG E LIBERAR CPU
    vTaskDelay(pdMS_TO_TICKS(2000)); // Espera 2 segundos
  }
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
      iconData = wifi50;
      break;
    case 3:
      iconData = wifi75;
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
  const unsigned long intervalo = 30000;  // 30 segundos
  
  if (millis() - ultimaVerificacao > intervalo) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("[WIFI] Desconectado - tentando reconectar...");
      WiFi.reconnect();
    }
    ultimaVerificacao = millis();
  }
}
