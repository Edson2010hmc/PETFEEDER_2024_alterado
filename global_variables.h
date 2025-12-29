// CONSTANT DATA--------------------------------------------------------------------------------------------
const char* topico = "PF022400132S3-remote"; // topico software e broker para maquina
// Servo Ajuste
bool ntp_flag=false;
//-----------------------------------------------------
// ✅ FLAG DE SINCRONIZAÇÃO - Task WiFi aguarda setup terminar
bool setup_completo = false;
//-----------------------------------------------------
// ✅ DEBUG DESLIGADO EM PRODUÇÃO (mude para true se precisar debugar)
bool debug_set = true;
int tempo=140;
String num_ser = "PF022400132S3";
String mqtt_user = num_ser;
String mqtt_pass = "petfeeder"; 
String from_machine = num_ser; // +"-schedule"; // topico maquina para broker e software
String resdog = num_ser+"-resdog"; // topico programacao
String rescat = num_ser+"-rescat"; // topico programacao
String weekDays[7]= PROGMEM {"DOMINGO      ", "SEGUNDA-FEIRA", "TERCA-FEIRA  ", "QUARTA-FEIRA ", "QUINTA-FEIRA ", "SEXTA-FEIRA  ", "SABADO       "};
String months[12]= PROGMEM {"jan", "fev", "mar", "abr", "mai", "jun", "jul", "ago", "set", "out", "nov", "dez"};
String prog_index_from_file[9] = {"x","","","","","","","",""};
String data_pub="";
String menuop[6] PROGMEM ={
  "NONE                      ",
  "PROGRAMACAO               ",
  "FUSO HORARIO              ",
  "RESET CONFIGURACOES       ",
  "RESET DADOS WIFI          ",
  "SOBRE                     "
  };

String menu_desc_ptbr[2][6] PROGMEM = {
   {"X","   AJUSTA HORARIOS PARA   ","  DEFINE FUSO HORARIO DO  ","  REDEFINE CONFIGURACOES  "," REDEFINE CREDENCIAIS DA  ","  INFORMACOES DO SISTEMA  "},
   {"X","      SERVIR A RACAO      ","         SISTEMA          "," PARA O PADRAO DE FABRICA ","       CONEXAO WIFI       "," DADOS DA CONEXAO DE REDE "}
};

String prog[99] PROGMEM ={"NONE",
         "06:00", "06:30", "07:00", "07:30", "07:40", "07:50",
         "08:00", "08:10", "08:20", "08:30", "08:40", "08:50",
         "09:00", "09:10", "09:20", "09:30", "09:40", "09:50",
         "10:00", "10:10", "10:20", "10:30", "10:40", "10:50",
         "11:00", "11:10", "11:20", "11:30", "11:40", "11:50",
         "12:00", "12:10", "12:20", "12:30", "12:40", "12:50",
         "13:00", "13:10", "13:20", "13:30", "13:40", "13:50",
         "14:00", "14:10", "14:20", "14:30", "14:40", "14:50",
         "15:00", "15:10", "15:20", "15:30", "15:40", "15:50",
         "16:00", "16:10", "16:20", "16:30", "16:40", "16:50",
         "17:00", "17:10", "17:20", "17:30", "17:40", "17:50",
         "18:00", "18:10", "18:20", "18:30", "18:40", "18:50",
         "19:00", "19:10", "19:20", "19:30", "19:40", "19:50",
         "20:00", "20:10", "20:20", "20:30", "20:40", "20:50",
         "21:00", "21:10", "21:20", "21:30", "21:40", "21:50",
         "22:00","XX:XX"};
String progdata[9] = PROGMEM {"XX:XX","","","","","","","",""};
String fusos_mundiais[25] = PROGMEM {"x","12","-11","-10","-9","-8","-7","-6","-5","-4","-3","-2","-1","0","1","2","3","4","5","6","7","8","9","10","11"};
String nome_fuso[26]= PROGMEM {
  "x",
  "GMT 12 Fiji       ",
  "GMT-11 Samoa      ",
  "GMT-10 Havai      ",
  "GMT-9 Alasca      ",
  "GMT-8 S Francisco ",
  "GMT-7 Denver      ",
  "GMT-6 Chicago     ",
  "GMT-5 New York    ",
  "GMT-4 Santiago    ",
  "GMT-3 Brasilia    ",
  "GMT-2 Fern Noronha",
  "GMT-1 Acores      ",
  "GMT 0 Greenwich   ",
  "GMT+1 Berlim      ",
  "GMT+2 Istambul    ",
  "GMT+3 Moscou      ",
  "GMT+4 Dubai       ",
  "GMT+5 Islamabad   ",
  "GMT+6 Dhaka       ",
  "GMT+7 Bangkok     ",
  "GMT+8 Hong Kong   ",
  "GMT+9 Tokio       ",
  "GMT+10 Sydney     ",
  "GMT+11 N Caledonia",
};  

const char broker[] ="45.140.192.166";
int port = 1883;
// CLOCK AND NTP VARIABLES
char sem_ch_anterior[13]="";
char data_ch_anterior[10]="";
char hora_ch_anterior[5]="";
String datahora;
String hora;
String minuto;
String horario;
String segundo;
String dia_semana;
String dia_mes;
String mes;
String nome_mes;
String ano ;
String currentDate;
int hora_val =0;
String lv_dog;
String lv_cat;
//FIREBASE VARIABLES---------------------------------
String bd_ip = "/REDE/IP";
String bd_dh = "/REDE/Ultima Conexao";
String bd_mi = "/HARDWARE/Memoria Interna";
String bd_prog = "/PROGRAMACAO/Programa";
String comm_ser="\0";
String trata_comm="\0"; 
String value_nivel="";

// GAUGE FOR LEVEL FOOD METER -------------------------------
int map_nivelcat=0;
int map_niveldog=0;
int nivel_dog_anterior = 0;
int nivel_cat_anterior = 0;
int level_dog =95;
int level_cat = 78;
int heigh_cat_yel=0;
int heigh_dog_yel=0;
int color_cat;
int color_dog;
int wf_lv=0;
int posmem_wifi=0;
int lv_cat_res_ant=0;
int lv_dog_res_ant=0;
int str_compr = 0;

// BUTTONS IHM FLAGS ---------------------------------------------
int t_bt1=0;
int t_bt2=0;
int t_bt3=0;
int t_bt4=0;
String horario_ant="";
String data_hoje_ant="";
String dia_semana_ant="";
String saved_fuso="";
uint8_t flag_menu=0;
int refeicoes_cat_ant=0;
int refeicoes_dog_ant=0;
uint8_t mnopt=1;
uint8_t mnopt_ant=-1;

// MENU PROG ------------------------------------------------
int cat_color_1 = 0;
int cat_color_bg1 = 0;
int cat_color_2 = 0;
int cat_color_bg2 = 0;
int cat_color_3 = 0;
int cat_color_bg3 = 0;
int cat_color_4 = 0;
int cat_color_bg4 = 0;
int dog_color_1 = 0;
int dog_color_bg1 = 0;
int dog_color_2 = 0;
int dog_color_bg2 = 0;
int dog_color_3 = 0;
int dog_color_bg3 = 0;
int dog_color_4 = 0;
int dog_color_bg4 = 0;
int menuprog=1;
int menufuso=1;
int mnprg_ant=0;
bool ajusteprog=false;
int set_prog_op = 0;
bool flag_dispenser = false;
int fuso_set= 0;
int fuso_index_saved=0;
bool flag_file=false;
uint16_t dispenser_dog_speed = 30;  //entre 92 e 0
uint16_t dispenser_cat_speed = 30;
uint16_t dispenser_dog_time = 1300; // 1 volta  = 1300
uint16_t dispenser_cat_time = 1300;
uint16_t dispenser_time = 1000;
String dispenser_time_str = "";
 
//--------------------------------------------------
int melody[] = {
  // Pink Panther theme
  // Score available at https://musescore.com/benedictsong/the-pink-panther
  // Theme by Masato Nakamura, arranged by Teddy Mason
  REST,2, REST,4, REST,8, NOTE_DS4,8, 
  NOTE_E4,-4, REST,8, NOTE_FS4,8, NOTE_G4,-4, REST,8, NOTE_DS4,8,
  NOTE_E4,-8, NOTE_FS4,8,  NOTE_G4,-8, NOTE_C5,8, NOTE_B4,-8, NOTE_E4,8, NOTE_G4,-8, NOTE_B4,8,   
  NOTE_AS4,2, NOTE_A4,-16, NOTE_G4,-16, NOTE_E4,-16, NOTE_D4,-16, 
  NOTE_E4,2, REST,4, REST,8};
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;
