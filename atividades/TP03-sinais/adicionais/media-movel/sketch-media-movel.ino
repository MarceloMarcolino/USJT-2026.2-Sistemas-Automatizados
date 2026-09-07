#include <string.h>

#include "classificacao.h"
#include "media_movel5.h"

const int BTN = 2;
const int POT = A0;
const int LED_ALARME = 8;

unsigned long amostra = 0;
MediaMovel5 filtro;

void setup() {
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED_ALARME, OUTPUT);
  digitalWrite(LED_ALARME, LOW);
  Serial.begin(9600);
  Serial.println("amostra,botao,bruto,filtrado,pct,tempC,estado");
}

void loop() {
  const bool botao = digitalRead(BTN) == LOW;
  const int bruto = analogRead(POT);
  const float filtrado = filtro.adicionar(bruto);
  const float pct = 100.0f * filtrado / 1023.0f;
  const float tempC = pct;
  const char* estado = classificar(pct);

  digitalWrite(LED_ALARME,
               strcmp(estado, "PERIGO") == 0 ? HIGH : LOW);

  Serial.print(amostra++);
  Serial.print(',');
  Serial.print(botao);
  Serial.print(',');
  Serial.print(bruto);
  Serial.print(',');
  Serial.print(filtrado, 2);
  Serial.print(',');
  Serial.print(pct, 2);
  Serial.print(',');
  Serial.print(tempC, 2);
  Serial.print(',');
  Serial.println(estado);
  delay(500);
}
