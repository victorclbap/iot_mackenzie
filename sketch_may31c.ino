#include <DHT.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

// Definições de pinos e tipos
#define DHTPIN D5 
#define DHTTYPE DHT11
#define LED_PIN D2 

// Credenciais da rede Wi-Fi
const char* ssid = "Teixeira01";
const char* password = "camillo01";

// Configurações do ThingSpeak
unsigned long myChannelNumber = 2554611;
const char * myWriteAPIKey = "BD723DZ7QPOOKZJ4";

// Instâncias de objetos
DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

float temperaturaAnterior = NAN; // Inicializa com NAN para garantir a primeira comparação
float umidadeAnterior = NAN; // Inicializa com NAN para garantir a primeira comparação

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(LED_PIN, OUTPUT); // Define o pino do LED como saída
  digitalWrite(LED_PIN, LOW); // Assegura que o LED esteja apagado inicialmente
  delay(2000); // Pequeno atraso para estabilização do sensor

  // Conexão WiFi
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Inicializa o ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  float umidadeAtual = dht.readHumidity();
  float temperaturaAtual = dht.readTemperature(false);

  // Verifica se houve falha na leitura e tenta novamente
  if (isnan(umidadeAtual) || isnan(temperaturaAtual)) {
    Serial.println("Falha na leitura do sensor DHT!");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperaturaAtual);
    Serial.print("°C   Umidade: ");
    Serial.println(umidadeAtual);

    // Pisca o LED a cada nova leitura
    digitalWrite(LED_PIN, HIGH); // Acende o LED
    delay(500); // Mantém o LED aceso por 0.5 segundo
    digitalWrite(LED_PIN, LOW); // Apaga o LED

    // Envia os dados para o ThingSpeak com tentativas de repetição
    ThingSpeak.setField(1, temperaturaAtual);
    ThingSpeak.setField(2, umidadeAtual);

    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200) {
      Serial.println("Atualização bem-sucedida no ThingSpeak");
    } else {
      Serial.print("Erro ao atualizar o ThingSpeak. Código de erro: ");
      Serial.println(x);
      // Tentativas de repetição
      for (int i = 0; i < 3 && x != 200; i++) {
        delay(1000);
        x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
        if (x == 200) {
          Serial.println("Atualização bem-sucedida no ThingSpeak após tentativa de repetição");
        } else {
          Serial.print("Nova tentativa falhou. Código de erro: ");
          Serial.println(x);
        }
      }
    }
    
    // Atualiza os valores anteriores
    temperaturaAnterior = temperaturaAtual;
    umidadeAnterior = umidadeAtual;
  }

  // Verifica o estado da conexão Wi-Fi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado! Tentando reconectar...");
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, password);
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi reconectado");
  }

  delay(15000); // Intervalo de 15 segundos entre leituras para respeitar os limites do ThingSpeak
}