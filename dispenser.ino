void disableJTAG() {
  gpio_reset_pin((gpio_num_t)SERVO1_PIN);
}

// Inicializa servo em um canal LEDC
void attach_servo(gpio_num_t pin, ledc_channel_t channel) {
  static bool timerConfigured = false;

  if (!timerConfigured) {
    ledc_timer_config_t timer_conf = {
      .speed_mode       = LEDC_LOW_SPEED_MODE,
      .duty_resolution  = LEDC_TIMER_14_BIT,
      .timer_num        = LEDC_TIMER_0,
      .freq_hz          = SERVO_FREQ_HZ,
      .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_conf);
    timerConfigured = true;
  }

  pinMode(pin, OUTPUT);

  ledc_channel_config_t ledc_conf = {
    .gpio_num       = pin,
    .speed_mode     = LEDC_LOW_SPEED_MODE,
    .channel        = channel,
    .intr_type      = LEDC_INTR_DISABLE,
    .timer_sel      = LEDC_TIMER_0,
    .duty           = 0,
    .hpoint         = 0
  };
  ledc_channel_config(&ledc_conf);
}

void start_servo(uint8_t pin, int angle) {
  int pulseWidth = map(angle, 0, 180, SERVO_MIN_US, SERVO_MAX_US);
  uint32_t duty = (pulseWidth * ((1 << 14) - 1)) / (1000000UL / SERVO_FREQ_HZ);

  if (pin == SERVO1_PIN) {
    ledc_set_duty(LEDC_LOW_SPEED_MODE, SERVO1_CHANNEL, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, SERVO1_CHANNEL);
  }
  else if (pin == SERVO2_PIN) {
    ledc_set_duty(LEDC_LOW_SPEED_MODE, SERVO2_CHANNEL, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, SERVO2_CHANNEL);
  }
}


void check_program(){

if (segundo=="00"){
//Serial.println(horario);
//Serial.println(segundo);
  if (debug_set){
//Serial.println("Verificando horários programados a cada minuto - Segundos = 0");
  }
check_prog_clock_dog();
check_prog_clock_cat();
}
}



// pino 17 gato
// pino 18 cachorro
void check_prog_clock_dog(){


if (progdata[1]==horario) {
  if (debug_set){
Serial.print("Horario prog dog match:");
Serial.println(horario);
  }
feed_dog();
}

if (progdata[2]==horario) {
  if (debug_set){
Serial.print("Horario prog dog match:");
Serial.println(horario);
  }
feed_dog();
}

if (progdata[3]==horario) {
  if (debug_set){
Serial.print("Horario prog dog match:");
Serial.println(horario);
  }
feed_dog();
}

if (progdata[4]==horario){
  if (debug_set){
Serial.print("Horario prog dog match:");
Serial.println(horario);
  }
feed_dog();
}

}

void check_prog_clock_cat(){


if (progdata[5]==horario){
  if (debug_set){
Serial.print("Horario prog cat match:");
Serial.println(horario);
  }
feed_cat();

}

if (progdata[6]==horario){
  if (debug_set){
Serial.print("Horario prog cat match:");
Serial.println(horario);
  }
feed_cat();
}

if (progdata[7]==horario){
  if (debug_set){
Serial.print("Horario prog cat match:");
Serial.println(horario);
  }
feed_cat();
}

if (progdata[8]==horario){
  if (debug_set){
Serial.print("Horario prog cat match:");
Serial.println(horario);
  }
feed_cat();
}


}

void feed_cat(){
//start_servo(SERVO1_PIN, 135);
//delay(700);
start_servo(SERVO1_PIN, dispenser_cat_speed);
Serial.println("Dispenser CAT");
delay(dispenser_cat_time);
start_servo(SERVO1_PIN, 92);
// ✅ VERIFICAR SE MQTT ESTÁ CONECTADO antes de publicar
if (mqttClient.connected()) {
  publica(from_machine+"-status","Last food cat:"+horario);
} else {
  if (debug_set) {
    Serial.println("[MQTT] Não conectado - log cat não enviado");
  }
}
}

void feed_dog(){
//start_servo(SERVO2_PIN, 135);
//delay(700);
start_servo(SERVO2_PIN, dispenser_dog_speed);
Serial.println("Dispenser DOG");
delay(dispenser_dog_time);
start_servo(SERVO2_PIN, 92);
// ✅ VERIFICAR SE MQTT ESTÁ CONECTADO antes de publicar
if (mqttClient.connected()) {
  publica(from_machine+"-status","Last food dog:"+horario);
} else {
  if (debug_set) {
    Serial.println("[MQTT] Não conectado - log dog não enviado");
  }
}
}



void stop_disp(){
  delay(dispenser_time);
}
