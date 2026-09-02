#include <DHT.h>

const int BTN = 2;
const int LED = 8;
const int POT = A0;
#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Latch do alarme térmico (histerese): liga quando t >= 40,0 °C e só desliga
// quando t <= 37,0 °C. Sobrevive às repetições do loop(). O potenciômetro não
// arma nem mantém o latch; durante leitura inválida o latch não é atualizado.
bool alarmeTermico = false;

// Etapa 8: a classificação recebe as medidas e devolve o estado.
// Prioridade: falha > alarme (pot >= 750 OU latch térmico) >
// atenção (t >= 30 OU pot >= 400) > normal.
const char* classificar(int bruto, float t, bool temperaturaValida) {
  if (!temperaturaValida) {
    return "FALHA DE SENSOR";  // latch conserva o valor que tinha
  }
  if (t >= 40.0) {
    alarmeTermico = true;
  } else if (t <= 37.0) {
    alarmeTermico = false;
  }
  if (alarmeTermico || bruto >= 750) {
    return "ALARME";
  }
  if (t >= 30.0 || bruto >= 400) {
    return "ATENCAO";
  }
  return "NORMAL";
}

void setup() {
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  bool detectado = digitalRead(BTN) == LOW;
  digitalWrite(LED, detectado ? HIGH : LOW);

  int bruto = analogRead(POT);
  float t = dht.readTemperature();
  bool temperaturaValida = !isnan(t);

  Serial.print("BTN=");
  Serial.print(detectado ? "PRESSIONADO" : "LIBERADO");
  Serial.print(" | POT=");
  Serial.print(bruto);
  Serial.print(" | TEMP=");

  if (temperaturaValida) {
    Serial.print(t, 1);
    Serial.print(" C");
  } else {
    Serial.print("INVALIDA");
  }

  Serial.print(" | ESTADO=");
  Serial.println(classificar(bruto, t, temperaturaValida));

  delay(1000);
}
