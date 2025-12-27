#include <Arduino.h>
#include "esp_task_wdt.h"
#include "driver/ledc.h"
#include <Adafruit_ST7735.h>
#include <FS.h>
#include <credentials.sample.h>
#include <WiFi.h>        
#include <DNSServer.h>
#include <WebServer.h>
#include <WiFiManager.h> 
#include <NTPClient.h>
#include <WiFiUDP.h>
#include <time.h>
#include <Adafruit_NeoPixel.h>
#include <cstddef>
#include "SD.h"
#include <ArduinoMqttClient.h>
#include "SPI.h"
#include "logo_dsl.h"
#include <base64.h>
#include "time.h"
#include <pgmspace.h>
#include "definitions.h"
#include "prototypes_functions.h"
#include "objects_decl.h"
#include "global_variables.h"

//-----------------------------------------------------------------------------------------------------
//    VOID SETUP 
//----------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(100);
  
  Serial.println("\n");
  Serial.println("=====================================");
  Serial.println("    PETFEEDER ESP32-S3               ");
  Serial.println("    Versão Otimizada                 ");
  Serial.println("=====================================");
  
  
  
  // Pins Config 
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  pinMode(bt3, INPUT);
  pinMode(bt4, INPUT);
  pinMode(WIFI_RST, INPUT_PULLUP);  // WIFI CREDENTIALS RESET
  pinMode(HARD_RST, INPUT_PULLUP);  // CONFIG FILES RESET
  pinMode(TYPE_FILE, INPUT_PULLUP); // READ FROM PROG MENU POSITIONS INDEX
  pinMode(TFT_LED, OUTPUT);         // LCD BACKGROUND LED
  
  Serial.println("[OK] Pinos configurados");
  
  // Servo Config
  disableJTAG();
  attach_servo((gpio_num_t)SERVO1_PIN, SERVO1_CHANNEL);
  attach_servo((gpio_num_t)SERVO2_PIN, SERVO2_CHANNEL);  
  
  Serial.println("[OK] Servos configurados");
  
  // SYSTEM SCREEN DISPLAY START - LCD_functions.ino
  Serial.println("[INFO] Inicializando display...");

  init_system();

  Serial.println("[OK] Display inicializado");
  
  // SD CARD START - SD_Card_Functions.ino
  Serial.println("[INFO] Inicializando cartão SD...");

  init_sd_card();

  for(int i=0; i<10; i++){yield(); delay(100);}
  Serial.println("[OK] Cartão SD inicializado");
  
  // READ CONFIG FILES SAVED ON SD CARD - SD_Card_Functions.ino
  Serial.println("[INFO] Carregando configurações...");

  get_config();


  Serial.println("[OK] Configurações carregadas");
  
  // Rendering main Screen

  tft.fillScreen(az);
  desenha_pet_logo();

  
  Serial.println("=====================================");
  Serial.println("    SETUP CONCLUÍDO!");
  Serial.println("=====================================\n");
  
  // Relatório de memória
  Serial.print("[MEM] Heap livre: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bytes");
  
  // ✅ SINALIZAR QUE SETUP TERMINOU
connect_Wifi(); 
}

//----------------------------------------------------------------------------------------------------
//    VOID LOOP
//----------------------------------------------------------------------------------------------------
void loop() {
  // Alimentar watchdog
  yield();
    // check external interrupts buttons - interrupts_ext.ino
  check_reset();
    // check commands from Serial port - Serial_Commands.ino
  check_serial();
    // check ihm buttons - menu.ino
  check_buttons();
  check_flag_menu();

  
  // ✅ SEMPRE EXECUTAR (crítico para dispenser)
  if (WiFi.status() == WL_CONNECTED) {
    relogio();
  }

  if (WiFi.status() != WL_CONNECTED) {
    wifi_reconnect_if_needed();
  }
  
  // check programmed times to dispenser food - dispenser.ino
  check_program();
  
  // check mqtt subscription messages - IOserver.ino
  check_mqtt();
  
  // Pequeno delay para não sobrecarregar
  delay(1);
}
