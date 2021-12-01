#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

#define red1 D0
#define green1 D1
#define TRIG D8
//#define servo D7
#define led_cancela D7
#define ECHO1 D2
#define ECHO2 D6
#define ECHO3 D5
#define red2 D3
#define green2 D4

String user = "grupo2-bancadaA1";
String passwd = "L@Bdygy2A1";

const char* ssid = "Zenfone Shot Plus";
const char* password = "lucas123";
const char* mqtt_server = "3.141.193.238";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];

Servo servoMotor;
int numVagas = 2;
int value = 0; //sinal de heartbeat
int vagas_livres[2];

uint32_t prev_millis;
uint32_t ms_cnt = 0;

const char* zero_cstr = "0";
const char* one_cstr = "1";

int valor, counter;

void setup_wifi() {

  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  counter = 0;
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Led buit-in mapeado no topico "user/ledhome"
  if (strcmp(topic,(user+"/ledhome").c_str())==0) {
    if ((char)payload[0] == '1') {
      // Turn the LED on by making the voltage LOW
      //digitalWrite(D7, HIGH);
    } else {
      // Turn the LED off by making the voltage HIGH
      //digitalWrite(D7, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    
    Serial.print("Attempting MQTT connection...");
    
    // Create a random client ID
    String clientId = user;
    clientId += String(random(0xffff), HEX);
    
    // Attempt to connect
    if (client.connect(clientId.c_str(), user.c_str(), passwd.c_str())) {
      
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish((user+"/homehello").c_str(), "hello world");
      client.subscribe((user+"/ledhome").c_str());
      
    } else {
      
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
      // Wait 5 seconds before retrying
      delay(5000);
      
    }
  }
}

int medirDistancia(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  return pulseIn(echo, HIGH) / 58;
}

void setup() {
  //pinMode(BUILTIN_LED, OUTPUT);
  //pinMode(D7, OUTPUT);
  pinMode(TRIG, OUTPUT);
  //pinMode(TRIG2, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(ECHO2, INPUT);
  pinMode(ECHO3, INPUT);
  pinMode(red1, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(led_cancela, OUTPUT);
  digitalWrite(red1, LOW);
  digitalWrite(green1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(green2, LOW);

  //servoMotor.attach(servo);
  
  Serial.begin(115200);
  vagas_livres[0] = 1;
  vagas_livres[1] = 1;
  
  //setup_wifi();
  
  //client.setServer(mqtt_server, 80);
  //client.setCallback(callback);
}

void loop() {
/*
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if(prev_millis!=millis()){
    prev_millis=millis();
    if(ms_cnt%100==0){
      // ====================================================
    }
    ms_cnt++;
  }

  unsigned long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    counter += 1;
    Serial.println(counter);
    //user+"topico".c_str() -> segundo argumento é valor
    client.publish((user+"/homehello").c_str(), String(counter).c_str());
  }*/

  int d1 = medirDistancia(TRIG, ECHO1);
  
//  Serial.println(d1);
  if (d1 < 18) {
    digitalWrite(red1, HIGH);
    digitalWrite(green1, LOW);
    vagas_livres[0] = 0;
  }
  else {
    digitalWrite(red1, LOW);
    digitalWrite(green1, HIGH);  
    vagas_livres[0] = 1;
  }

  delay(50);
  
  int d2 = medirDistancia(TRIG, ECHO2);

//  Serial.print("D2 = ");
//  Serial.println(d2);
  if (d2 < 18) {
    digitalWrite(red2, HIGH);
    digitalWrite(green2, LOW);
    vagas_livres[1] = 0;
  }
  else {
    digitalWrite(red2, LOW);
    digitalWrite(green2, HIGH);
    vagas_livres[1] = 1;
  }

  delay(50);
  numVagas = vagas_livres[0] + vagas_livres[1];

  
  int d3 = medirDistancia(TRIG, ECHO3);
  Serial.print("Vagas = ");
  Serial.println(numVagas);

  if (d3 > 20 && numVagas == 0)
      //servoMotor.write(100);
      digitalWrite(led_cancela, HIGH);
  else
      digitalWrite(led_cancela, LOW);
      //servoMotor.write(100);
 
  
}
