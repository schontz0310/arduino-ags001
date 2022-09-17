////////////////////////////////////////////////////////////////////////////////////
//                                                                            //////
// Controle de bomba de abastecimento de Diesel com Bloco Medidor Analogico   //////
// Hardware - Arduino Mega                                                    //////
// Criado por Eliverto Schontz Moraes                                         //////
// 06/01/2020 - V2.0                                                          //////
// 06/08/2020 - V2.1 incluido telas de espera                                 //////
// 02/11/2020 - V3.1 Refatoração completa do cogido                           //////
// 10/12/2020 - V4.0 Refatoração completa usando plataformIO/VScode/GitHub    //////
// 25/07/2021 - V5.0 Finalizado refatoração e validado codigo com placa nova  //////
//  @Commit xxxxxxxxx                                                         //////
//  [v] -> Correção da conectividade Gprs/Mqtt com problema de timeout        //////
//  [ ] -> Apresentar codigo de erro com opção de continuar                   //////
//  [ ] -> Incluir liberação de funções com apresentação de cartão MASTER     //////
//  [ ] -> Ocultar caracteres de senha ao digitar                             //////
//  [v] -> Criado lista de codigos de erro                                    //////
//                                                                            //////
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
//                              CODIGOS DE ERROS                              //////
//  ------------------------------------------------------------------------  //////
// 1  - SD                                                                    //////
// 3  - RTC                                                                   //////
// 4  - SD E RTC                                                              //////
// 5  - RFID                                                                  //////
// 6  - SD E RFID                                                             //////
// 8  - RTC E RFID                                                            //////
// 9  - SD, RTC, RFID                                                         //////
// 11 - MODEM GPRS                                                            //////
// 12 - SD E MODEM GPRS                                                       //////
// 14 - RTC E MODEM GPRS                                                      //////
// 15 - SD, RTC E MODEM GPRS                                                  //////
// 16 - RFID E MODEM GPRS                                                     //////
// 17 - SD, RFID E MODEM GPRS                                                 //////
// 19 - RTC, RFID E MODEM GPRS                                                //////
// 20 - CONEXÃO MQTT                                                          //////
// 21 - SD E CONEXAO MQTT                                                     //////
// 23 - RTC E CONEXAO MQTT                                                    //////
// 24 - SD, RTC E CONEXAO MQTT                                                //////
// 25 - RFID E CONEXAO MQTT                                                   //////
// 26 - SD, RFID E CONEXAO MQTT                                               //////
// 28 - RTC, RFID E CONEXAO MQTT                                              //////
// 31 - MODEM GPRS E CONEXAO MQTT                                             //////
// 32 - SD, MODEM GPRS E CONEXAO MQTT                                         //////
// 34 - RTC, MODEM GPRS E CONEXAO MQTT                                        //////
// 36 - RFID, MODEM GPRS E CONEXAO MQTT                                       //////
//                                                                            //////
////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
//                            CODIGOS DE FUNCOES                              //////
//  ------------------------------------------------------------------------  //////
// 001  - CADASTRO DE OPERADOR                                                //////
// 002  - CADASTRO DE VEICULO                                                 //////
// 003  - CADASTRO DE PERMISSOES                                              //////
// 099  - CADASTRO DE ABASTECIMENTO                                           //////
////////////////////////////////////////////////////////////////////////////////////

//----------------------------Declaração de Bibliotecas-----------------------------

#include <SPI.h>                  // Biblioteca de comunicação SPI
#include <Keypad.h>               // Biblioteca para controle do teclado matricial 4x4  
#include <ArduinoUniqueID.h>      // Biblioteca de abstraao para captura de id unico do arduino mega
#include <MFRC522.h>              // Biblioteca de abstracao para uso do RFID
#include <U8glib.h>               // Biblioteca de abstracao para o LCD ST920
#include <Wire.h>                 // Biblioteca de comunicação I2C
#include <TimeLib.h>              // Biclioteca de configuração de data e hota 
#include <DS1307RTC.h>            // Biblioteca de integração com o modulo RTC
#include <SD.h>                   // SD Card Biblioteca
#define TINY_GSM_MODEM_SIM800     // Tipo de modem que estamos usando (emboora usemos o modem sim800l os parametros do sim808 apresentaram maior estabilidade).
#include <TinyGsmClient.h>        // Biblioteca de comunicação com o Modem
#include <PubSubClient.h>

//----------------------------Definição de Pinos padrões-----------------------------

String SENHA_AGS                =       "380130";

const uint8_t PIN_SS_DATA_LOG   =       46;                                     // Configuravel - Pino Slave Select/Chip Select modulo DATALOGGER
const uint8_t SOM               =       27;                                     // Pino de ligação do buzzer
const uint8_t LED_VERMELHO      =       29;                                     // Pino de ligação do led vermelho
const uint8_t LED_VERDE         =       31;                                     // Pino de ligação do led verde
const uint8_t CS_PIN            =       10;                                     // Chip Select (Slave Select do protocolo SPI) do modulo Lora
const uint8_t RST_PIN           =       10;                                     // Configuravel - Pino Reset modulo RFID
const uint8_t SS_SDA_PIN        =       4;                                      // Configuravel - Pino Slave Select (SDA) modulo RFID
const uint8_t RELE_02           =       A13;                                    // Pino Rele_02
const uint8_t RELE_01           =       A0;                                     // Pino Rele_01
const uint8_t BOTAO             =       8;                                      // Botao de uso geral

volatile unsigned long counter;
const byte lines = 4;                                                           //NUMERO DE LINHAS DO TECLADO
const byte columns = 4;                                                         //NUMERO DE COLUNAS DO TECLADO
byte linesPines[lines] = {41, 39, 37, 35};                                      //PINOS CONECTADOS AS LINHAS DO TECLADO
byte columnsPines[columns] = {49, 47, 45, 43};                                  //PINOS CONECTADOS AS COLUNAS DO TECLADO
//MATRIZ DO TECLADO DEFINA PELAS LINHAS E COLUNAS 
char matriz[lines][columns] =
{
  { '1', '2', '3', 'A'},
  { '4', '5', '6', 'B'},
  { '7', '8', '9', 'C'},
  { '*', '0', '#', 'D'},
};
//----------------------------Declaração de Instancias ------------------------------

U8GLIB_ST7920_128X64_1X display(11, 12, 13);
MFRC522 rfid(SS_SDA_PIN, RST_PIN);
TinyGsm modemGSM(Serial2);  
TinyGsmClient gsmClient(modemGSM);
PubSubClient client(gsmClient);
File fileName;
Keypad keyboard = Keypad( makeKeymap(matriz), linesPines, columnsPines, lines, columns);

//----------------------------Declaração de Variaveis Globais------------------------

enum MetodeAccesses{
  CARD,
  PASSWORD,
};

enum VehicleFuel{
  DIESEL_S10,
  DIESEL_S500,
};

enum ScreenName
{
  // GENERAL
  SCREEN_PROGRESS,
  SCREEN_ERROR,
  SCREEN_SUCCESS,
  // SETUP
  SCREEN_DRAW_LOGO,
  SCREEN_INIT,
  SCREEN_VERIFY_DATA_LOGGER_SD,
  SCREEN_VERIFY_DATA_LOGGER_RTC,
  SCREEN_VERIFY_RFID,
  SCREEN_VERIFY_MODEM,
  SCREEN_VERIFY_MQTT,
  // OPERATOR
  SCREEN_OPERATOR_READ,
  SCREEN_OPERATOR_SEARCH,
  SCREEN_OPERATOR_FOUND,
  SCREEN_OPERATOR_NOT_FOUND,
  // VEHICLE
  SCREEN_VEHICLE_READ,
  SCREEN_VEHICLE_SEARCH,
  SCREEN_VEHICLE_FOUND,
  SCREEN_VEHICLE_NOT_FOUND,
  // MENUS
  SCREEN_MENU_PRINCIPAL,
  SCREEN_MENU_CADASTRO,  
  SCREEN_MENU_CADASTRO_OPERADOR_CHOICE,
  SCREEN_MENU_CADASTRO_OPERADOR_READ_CARD,
  SCREEN_MENU_CADASTRO_OPERADOR_READ_NAME,
  SCREEN_MENU_CADASTRO_OPERADOR_READ_LEVEL,
  SCREEN_MENU_CADASTRO_VEHICLE_CHOICE,
  SCREEN_MENU_CADASTRO_VEHICLE_READ_CARD,
  SCREEN_MENU_CADASTRO_VEHICLE_READ_NAME,
  SCREEN_MENU_CADASTRO_VEHICLE_READ_LEVEL,
  SCREEN_MENU_CADASTRO_PERMISSION_CHOICE,
  SCREEN_MENU_CONFIGURACAO,
  SCREEN_CONFIGURACAO_REGISTRO_CHOICE,
  SCREEN_PUMP_CHARGE_FUEL,

  // SCREEN CONFIGURACAO
  SCREEN_CONFIGURACAO_REGISTRO,

  // ACCESSES SCREEN
  SCREEN_ACCCESSES,
  SCREEN_ACCCESSES_CHOICE,
  SCREEN_ACCCESSES_CARD,
  SCREEN_ACCCESSES_PASSWORD,
};

const String TOPIC_REGISTER     =       "registers/";                           // TOPICO MQTT para publicação
IPAddress MQTT_SERVER(3, 143, 105, 105);
const int MQTT_PORT             =       1883;                                   // Porta para comunicação com Broker MQTT
const char USER[]               =       "admin";                                // "USUARIO"
const char PASS[]               =       "ags001#2020";                          // "SENHA"
uint8_t statusCheck             =       0;
bool stateCheck[8]              =       {0,0,0,0,0,0,0,0};                      // 0=SD, 1=RTC, 2=RFID, 3=MODEN           
const uint8_t errorCode[6]      =       {1,3,5,11,20,0};                       
const bool GET_SYSTEM_TIMESTAMP =       false;                                   // Variavel para setar quando o programa deve pegar a hora do sistema
String COMPANY;
String OPERADOR_REGISTER;
String OPERADOR_NAME;
String OPERADOR_PERMISSION;
String VEHICLE_REGISTER;
String VEHICLE_NAME;
String VEHICLE_FUEL;                                                            // 0->S500 ->S10 
String PERMISSION_TAG;
float FUEL_QUANITY;
char _buffer[24];
tmElements_t tm;
String timestamp;
const char *monthNameDatalogger[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const int retryNumber = 1;
int retryCount;
int _position;
char _keyPressed;

bool successRead;
byte status;

String _vehicleName;
String _vehicleFuel;
String _vehicleUuid;
String  _operatorName;
String _operatorUuid;
String _operatorLevel;

String tagUuid;
String _uuidToCheck;
String _uuidRead;
String _UUIDPermission;

String fileRegisterLine;
String companyNumber;
String jsonPayload; 
String rfidReaderIDValue;
char tecla_presionada;
float fuelQuantity;


ScreenName _screen;
ScreenName _nextScreen;


void setup() {
  pinMode(PIN_SS_DATA_LOG, OUTPUT);
  pinMode(SOM, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  // Initialize Serial 
  Serial.begin(9600);
  // Initialize SPI protocol
  SPI.begin();
  // initialize visor setup
  visorBegin();
  // show first screen with logo 
  visorDrawSetup(SCREEN_DRAW_LOGO, 2000, 0);
  // show screen with UID
  visorDrawSetup(SCREEN_INIT, 3000, 0);
  dataloggerBegin();
  visorDrawSetup(SCREEN_VERIFY_DATA_LOGGER_SD, 2000, statusCheck);
  dataloggerSetTimestamp();
  visorDrawSetup(SCREEN_VERIFY_DATA_LOGGER_RTC, 2000, statusCheck);
  rfidReaderBegin();
  visorDrawSetup(SCREEN_VERIFY_RFID, 2000, statusCheck);
  gprsBegin();
  visorDrawSetup(SCREEN_VERIFY_MODEM, 2000, statusCheck);
  mqttBegin();
  visorDrawSetup(SCREEN_VERIFY_MQTT, 2000, statusCheck);
  validateSetup();
  COMPANY = dataloggerGetCompany();
  Serial.print("Company = ");
  Serial.println(COMPANY);
   while (COMPANY == "NO_COMPANY") {
      menuAssignDeviceRegister();
   }
}

void loop() {
  OPERADOR_REGISTER = "";
  OPERADOR_NAME = "";
  OPERADOR_PERMISSION = "";
  VEHICLE_REGISTER = "";
  VEHICLE_NAME = "";
  VEHICLE_FUEL = "";
  Serial.println(F("==============================================================="));
  Serial.println(F("====================== INICIO DO SISTEMA ======================"));
  Serial.println(F("==============================================================="));
  OPERADOR_REGISTER = operatorRead();
  OPERADOR_NAME = OPERADOR_REGISTER.substring(OPERADOR_REGISTER.indexOf("#") + 1, OPERADOR_REGISTER.lastIndexOf("#"));
  OPERADOR_PERMISSION = OPERADOR_REGISTER.substring(OPERADOR_REGISTER.lastIndexOf("#") + 1);
  OPERADOR_REGISTER = OPERADOR_REGISTER.substring(0, OPERADOR_REGISTER.indexOf("#"));
  Serial.println(F("==============================================================="));
  Serial.println(OPERADOR_NAME);
  Serial.println(OPERADOR_PERMISSION);
  Serial.println(OPERADOR_REGISTER);
  Serial.println(F("==============================================================="));
  VEHICLE_REGISTER = vehicleRead();
  VEHICLE_NAME = VEHICLE_REGISTER.substring(VEHICLE_REGISTER.indexOf("#") + 1, VEHICLE_REGISTER.lastIndexOf("#"));
  VEHICLE_FUEL = VEHICLE_REGISTER.substring(VEHICLE_REGISTER.lastIndexOf("#") + 1);
  VEHICLE_REGISTER = VEHICLE_REGISTER.substring(0, VEHICLE_REGISTER.indexOf("#"));
  Serial.println(F("==============================================================="));
  Serial.println(VEHICLE_NAME);
  Serial.println(VEHICLE_FUEL);
  Serial.println(VEHICLE_REGISTER);
  Serial.println(VEHICLE_REGISTER);
  Serial.println(F("==============================================================="));
    // final da funcao de captura do veiulo
  if (OPERADOR_PERMISSION == "3"){
    PERMISSION_TAG = OPERADOR_REGISTER + VEHICLE_REGISTER;
    Serial.println(PERMISSION_TAG);
    if (dataloggerCheckPermissionExist(PERMISSION_TAG) == false){
      visorDrawMenu(SCREEN_ERROR);
      somErrado();
      delay(1500);
      loop();
    } 
  }
  //permissáo checada
  VehicleFuel fuel;
  if (VEHICLE_FUEL == "1") {
    fuel = DIESEL_S10;
  }else{
    fuel = DIESEL_S500;
  }
  FUEL_QUANITY = fuelLoad(fuel);
  registerFueLCharger();
  loop(); 
}
