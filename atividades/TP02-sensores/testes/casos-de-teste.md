# Casos de teste — Estação de monitoramento (TP02)

Registro completo da validação, preenchido durante a execução, caso a caso.
Este arquivo parte do registro da etapa obrigatória e o **completa** com os
exercícios adicionais — prioridade (P1–P5), histerese (H1–H8 e ensaio
complementar) — e com a regressão de T1–T7 e F1–F8 sobre o firmware final.

Projeto on-line da etapa obrigatória:
[`TP02 - Estacao de monitoramento`](https://wokwi.com/projects/473835836746646529)
(Wokwi). O firmware final dos adicionais é o `sketch.ino` desta entrega.
Circuito: `BTN=D2` (`INPUT_PULLUP`), `LED=D8` com resistor de 220 Ω, `POT=A0`,
`DHT22=D4`. Monitor Serial a 9600 baud.
Bibliotecas instaladas: **DHT sensor library 1.4.7** (Adafruit) e sua
dependência declarada **Adafruit Unified Sensor 1.1.15**. O programa inclui
`DHT.h` diretamente e não usa a interface `DHT_U.h`.

## Método de execução

Três turnos, todos no simulador Wokwi:

1. **26/08/2026 — editor do Wokwi (manual)**: D1–D4 na etapa 2; F1–F4 na
   etapa 4; ensaio do DHT22 na etapa 5.
2. **02/09/2026 — wokwi-cli v0.26.1 (headless, cenários de automação),
   firmware obrigatório**: bateria da etapa 6 — D1–D4 reconfirmados com
   verificação elétrica do pino D8 (`expect-pin`), T1–T7, F1–F8 (F1–F4
   reconfirmados no formato serial final) e suplementares S1–S2.
   **21/21 aprovados.** Registro congelado no checkpoint.
3. **02/09/2026 — wokwi-cli, firmware final (com função de classificação e
   histerese)**: regressão de T1–T7, F1–F8 e S1–S2 com o latch inicialmente
   desligado; P1–P5; H1–H8 e ensaio complementar em execução contínua.
   **36/36 aprovados.**

Critério de aceite dos casos T/F/S/P/H/E: a **linha serial completa** esperada,
no formato fixo, com o potenciômetro calibrado até o valor bruto exato quando
aplicável e o LED no estado esperado (`expect-pin` em D8). O firmware foi
compilado com arduino-cli (`arduino:avr:uno`) e executado no simulador oficial.
Os mosaicos em `evidencias/` têm um quadro rotulado por caso e foram gerados do
registro de cada execução. Nos casos digitais, o critério principal é apenas o
estado elétrico do LED; D1 e D2 também confirmam o botão na saída serial.

## Digitais — D1 a D4

Critério de aceite: apenas a resposta do LED.

| Caso | Entrada aplicada | Saída esperada | Saída obtida | Situação |
|---|---|---|---|---|
| D1 | Botão liberado (HIGH) | LED apagado | LED apagado (26/08); pino D8 = 0 confirmado por expect-pin (02/09) | Aprovado |
| D2 | Botão pressionado (LOW) | LED aceso | LED aceso (26/08); pino D8 = 1 confirmado por expect-pin (02/09) | Aprovado |
| D3 | Cinco acionamentos sucessivos | Cinco respostas correspondentes | Cinco respostas correspondentes (26/08); os 10 estados do pino D8 conferidos por expect-pin (02/09) | Aprovado |
| D4 | Botão mantido pressionado | LED permanece aceso | LED permaneceu aceso (26/08); pino D8 = 1 mantido após 6 s (02/09) | Aprovado |

**Significado lógico de LOW e HIGH nesta montagem.** O pino do botão é
configurado com `INPUT_PULLUP`, o que liga o resistor interno do
microcontrolador entre o pino e a alimentação. Com o botão solto, o circuito
fica aberto e o resistor mantém o pino em **HIGH**. Ao pressionar, o botão
fecha o caminho até o GND e o pino é puxado para **LOW**. A leitura é, portanto,
invertida em relação à intuição: pressionado corresponde a LOW, e é por isso que
o programa compara `digitalRead(BTN) == LOW` para decidir se o botão está
acionado.

## Integrados — T1 a T7

Executados na etapa 6 (firmware obrigatório) e repetidos como **regressão**
sobre o firmware final, com o latch inicialmente desligado — mesmas linhas
seriais nos dois turnos. Botão livre e LED apagado em todos, exceto T6. T7
executado com o fio DATA do DHT22 desconectado, pelo protocolo de seis passos
(variante controlada do diagrama, restaurada em seguida).

| Caso | Pot. | Temp. | Botão | Esperado | Obtido (linha serial, nos dois turnos) | Situação |
|---|---|---|---|---|---|---|
| T1 | 200 | 25 °C | livre | NORMAL; LED apagado | `BTN=LIBERADO \| POT=200 \| TEMP=25.0 C \| ESTADO=NORMAL` | Aprovado |
| T2 | 500 | 25 °C | livre | ATENÇÃO; LED apagado | `BTN=LIBERADO \| POT=500 \| TEMP=25.0 C \| ESTADO=ATENCAO` | Aprovado |
| T3 | 800 | 25 °C | livre | ALARME; LED apagado | `BTN=LIBERADO \| POT=800 \| TEMP=25.0 C \| ESTADO=ALARME` | Aprovado |
| T4 | 200 | 35 °C | livre | ATENÇÃO; LED apagado | `BTN=LIBERADO \| POT=200 \| TEMP=35.0 C \| ESTADO=ATENCAO` | Aprovado |
| T5 | 200 | 45 °C | livre | ALARME; LED apagado | `BTN=LIBERADO \| POT=200 \| TEMP=45.0 C \| ESTADO=ALARME` | Aprovado |
| T6 | 200 | 25 °C | pressionado | NORMAL; LED aceso | `BTN=PRESSIONADO \| POT=200 \| TEMP=25.0 C \| ESTADO=NORMAL` | Aprovado |
| T7 | 200 | inválida | livre | FALHA DE SENSOR; LED apagado | `BTN=LIBERADO \| POT=200 \| TEMP=INVALIDA \| ESTADO=FALHA DE SENSOR` | Aprovado |

T3 e T5 confirmam o operador **OU** na regra de alarme. T6 confirma que o botão
não participa da classificação. T7 confirma a prioridade da falha numa única
linha — corrigindo a observação levada da etapa 5.

## Fronteiras — F1 a F8

Nos casos de potenciômetro a temperatura fica em 25 °C; nos de temperatura o
potenciômetro fica em 200. Botão livre e LED apagado em todos. Executados na
etapa 6 e repetidos como regressão sobre o firmware final, com as mesmas
linhas seriais.

| Caso | Entrada aplicada | Esperado | Obtido (linha serial, nos dois turnos) | Situação |
|---|---|---|---|---|
| F1 | pot 399 | NORMAL | `BTN=LIBERADO \| POT=399 \| TEMP=25.0 C \| ESTADO=NORMAL` | Aprovado |
| F2 | pot 400 | ATENÇÃO | `BTN=LIBERADO \| POT=400 \| TEMP=25.0 C \| ESTADO=ATENCAO` | Aprovado |
| F3 | pot 749 | ATENÇÃO | `BTN=LIBERADO \| POT=749 \| TEMP=25.0 C \| ESTADO=ATENCAO` | Aprovado |
| F4 | pot 750 | ALARME | `BTN=LIBERADO \| POT=750 \| TEMP=25.0 C \| ESTADO=ALARME` | Aprovado |
| F5 | temp 29,9 °C | NORMAL | `BTN=LIBERADO \| POT=200 \| TEMP=29.9 C \| ESTADO=NORMAL` | Aprovado |
| F6 | temp 30 °C | ATENÇÃO | `BTN=LIBERADO \| POT=200 \| TEMP=30.0 C \| ESTADO=ATENCAO` | Aprovado |
| F7 | temp 39,9 °C | ATENÇÃO | `BTN=LIBERADO \| POT=200 \| TEMP=39.9 C \| ESTADO=ATENCAO` | Aprovado |
| F8 | temp 40 °C | ALARME | `BTN=LIBERADO \| POT=200 \| TEMP=40.0 C \| ESTADO=ALARME` | Aprovado |

F1–F4 haviam sido aprovados na etapa 4 (26/08) e foram **reconfirmados com a
decisão integrada e o formato serial final** nos dois turnos de 02/09. As oito
fronteiras foram atingidas nos valores exatos.

**Verificação suplementar** (valores imediatamente acima dos limites), ambas
confirmadas nos dois turnos: `POT=401 → ATENCAO` (S1) e `POT=751 → ALARME` (S2).

## Ensaio da etapa 5 — DHT22 (26/08/2026)

Executado antes da decisão integrada, quando o programa ainda imprimia os
campos em linhas separadas. Não constitui o caso T7.

| Ensaio | Entrada aplicada | Esperado | Obtido | Situação |
|---|---|---|---|---|
| E5.1 | DHT22 em 24,0 °C | leitura válida | `24.00` | Aprovado |
| E5.2 | DHT22 alterado para 46,9 °C em execução | a leitura acompanha | `46.90` | Aprovado |
| E5.3 | fio de DATA desconectado de D4 | falha identificada | `FALHA DE SENSOR` | Aprovado |
| E5.4 | fio de DATA reconectado | leitura válida de volta | `24.00` | Aprovado |

E5.3 e E5.4 seguiram o protocolo de seis passos da especificação, com a
simulação parada nas trocas de fio; o `diagram.json` final é idêntico ao
anterior ao ensaio.

## Prioridade — P1 a P5 (adicional 1, firmware final, 02/09/2026)

A classificação foi isolada na função `classificar(bruto, t, temperaturaValida)`,
que recebe as medidas e devolve o estado. Botão livre e LED apagado em todos.
P5 executado com a variante do diagrama sem o fio DATA (mesmo protocolo do T7).

| Caso | Pot. | Temp. | Esperado | Obtido (linha serial) | Situação |
|---|---|---|---|---|---|
| P1 | 900 | 45 °C | ALARME | `BTN=LIBERADO \| POT=900 \| TEMP=45.0 C \| ESTADO=ALARME` | Aprovado |
| P2 | 500 | 45 °C | ALARME | `BTN=LIBERADO \| POT=500 \| TEMP=45.0 C \| ESTADO=ALARME` | Aprovado |
| P3 | 900 | 35 °C | ALARME | `BTN=LIBERADO \| POT=900 \| TEMP=35.0 C \| ESTADO=ALARME` | Aprovado |
| P4 | 500 | 35 °C | ATENÇÃO | `BTN=LIBERADO \| POT=500 \| TEMP=35.0 C \| ESTADO=ATENCAO` | Aprovado |
| P5 | 900 | inválida | FALHA DE SENSOR | `BTN=LIBERADO \| POT=900 \| TEMP=INVALIDA \| ESTADO=FALHA DE SENSOR` | Aprovado |

**P5, o caso decisivo, aprovou**: mesmo com o potenciômetro em faixa de alarme,
a leitura inválida produziu FALHA DE SENSOR — a falha é avaliada antes do
alarme, e o sistema não confia em medição inválida.

## Histerese — H1 a H8 e ensaio complementar (adicional 2, 02/09/2026)

Sequências percorridas **em execução contínua**, sem reiniciar a simulação
entre as amostras (a histerese depende do estado anterior). Potenciômetro fixo
em 200; latch térmico inicialmente desligado; LED conferido apagado em cada
amostra. Regra: liga em 40 °C, mantém acima de 37 °C e desliga em 37 °C ou
menos. As duas invariantes de integração também estão explícitas na função
`classificar`: somente uma temperatura válida atualiza o latch, e o
potenciômetro é consultado depois, sem modificá-lo.

| Caso | Temp. | Alarme anterior | Esperado | Obtido (linha serial) | Situação |
|---|---|---|---|---|---|
| H1 | 36 °C | desligado | ATENÇÃO | `... TEMP=36.0 C \| ESTADO=ATENCAO` | Aprovado |
| H2 | 39 °C | desligado | ATENÇÃO | `... TEMP=39.0 C \| ESTADO=ATENCAO` | Aprovado |
| H3 | 40 °C | desligado | ALARME (liga) | `... TEMP=40.0 C \| ESTADO=ALARME` | Aprovado |
| H4 | 39 °C | ligado | ALARME (mantém) | `... TEMP=39.0 C \| ESTADO=ALARME` | Aprovado |
| H5 | 38 °C | ligado | ALARME (mantém) | `... TEMP=38.0 C \| ESTADO=ALARME` | Aprovado |
| H6 | 37 °C | ligado | ATENÇÃO (desliga) | `... TEMP=37.0 C \| ESTADO=ATENCAO` | Aprovado |
| H7 | 36 °C | desligado | ATENÇÃO | `... TEMP=36.0 C \| ESTADO=ATENCAO` | Aprovado |
| H8 | 29 °C | desligado | NORMAL | `... TEMP=29.0 C \| ESTADO=NORMAL` | Aprovado |

H6 deu ATENÇÃO e não NORMAL, como previsto: a histerese desliga o alarme em
37 °C, mas a regra de atenção continua válida a partir de 30 °C.

**Ensaio complementar** (execução contínua própria, latch inicialmente
desligado): 39,8 → 40,0 → 39,9 → 39,7 → 37,1 → 37,0.

| Amostra | Temp. | Esperado | Obtido | Situação |
|---|---|---|---|---|
| 1 | 39,8 °C | ATENÇÃO (ainda desligado) | ATENCAO | Aprovado |
| 2 | 40,0 °C | ALARME (liga) | ALARME | Aprovado |
| 3 | 39,9 °C | ALARME (mantém) | ALARME | Aprovado |
| 4 | 39,7 °C | ALARME (mantém) | ALARME | Aprovado |
| 5 | 37,1 °C | ALARME (mantém) | ALARME | Aprovado |
| 6 | 37,0 °C | ATENÇÃO (desliga) | ATENCAO | Aprovado |

Ligou em 40,0, permaneceu ligado até 37,1 e desligou somente em 37,0 —
exatamente o comportamento especificado.

## Resumo geral

| Turno | Firmware | Execuções | Resultado |
|---|---|---|---|
| Etapa 6 (02/09) | obrigatório | D1–D4, T1–T7, F1–F8, S1–S2 | **21/21 aprovados** (checkpoint congelado) |
| Final (02/09) | com função de classificação e histerese | regressão T1–T7 + F1–F8 + S1–S2, P1–P5, H1–H8, ensaio | **36/36 aprovados** |

A regressão confirmou que a integração da histerese **não alterou o
comportamento obrigatório** com o latch inicialmente desligado.

No total automatizado foram **57/57 execuções aprovadas**, cobrindo **40 casos
distintos**; 17 casos T/F/S foram repetidos na regressão do firmware final.
