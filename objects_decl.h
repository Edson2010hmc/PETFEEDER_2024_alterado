// OBJECTS DECLARATIONS -----------------------------------------------------------
WiFiManager wifiManager;
WiFiUDP udp;
NTPClient ntp(udp);
WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
//Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);
//--------------------------------------------------------------------------------
