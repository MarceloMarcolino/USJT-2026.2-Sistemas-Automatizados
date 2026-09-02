# Casos de teste — Estação de monitoramento (TP02)

Registro preenchido durante a execução no Wokwi, caso a caso. Cada linha traz a
entrada aplicada, a saída esperada, a saída obtida e a situação.

Projeto: `TP02 - Estacao de monitoramento` (Wokwi).
Circuito: `BTN=D2` (`INPUT_PULLUP`), `LED=D8` com resistor de 220 Ω, `POT=A0`,
`DHT22=D4`. Monitor Serial a 9600 baud.

## Digitais — D1 a D4

Executados na etapa 2, quando ainda não existem serial nem classificação. O
critério de aceite é apenas a resposta do LED.

| Caso | Entrada aplicada | Saída esperada | Saída obtida | Situação |
|---|---|---|---|---|
| D1 | Botão liberado (HIGH) | LED apagado | LED apagado | Aprovado |
| D2 | Botão pressionado (LOW) | LED aceso | LED aceso | Aprovado |
| D3 | Cinco acionamentos sucessivos | Cinco respostas correspondentes | Cinco respostas correspondentes | Aprovado |
| D4 | Botão mantido pressionado | LED permanece aceso | LED permaneceu aceso | Aprovado |

**Significado lógico de LOW e HIGH nesta montagem.** O pino do botão é
configurado com `INPUT_PULLUP`, o que liga o resistor interno do
microcontrolador entre o pino e a alimentação. Com o botão solto, o circuito
fica aberto e o resistor mantém o pino em **HIGH**. Ao pressionar, o botão
fecha o caminho até o GND e o pino é puxado para **LOW**. A leitura é, portanto,
invertida em relação à intuição: pressionado corresponde a LOW, e é por isso que
o programa compara `digitalRead(BTN) == LOW` para decidir se o botão está
acionado.

## Integrados — T1 a T7

*(a executar na etapa 6)*

| Caso | Pot. | Temp. | Botão | Esperado | Obtido | Situação |
|---|---|---|---|---|---|---|
| T1 | 200 | 25 °C | livre | NORMAL; LED apagado | | |
| T2 | 500 | 25 °C | livre | ATENÇÃO; LED apagado | | |
| T3 | 800 | 25 °C | livre | ALARME; LED apagado | | |
| T4 | 200 | 35 °C | livre | ATENÇÃO; LED apagado | | |
| T5 | 200 | 45 °C | livre | ALARME; LED apagado | | |
| T6 | 200 | 25 °C | pressionado | NORMAL; LED aceso | | |
| T7 | 200 | inválida | livre | FALHA DE SENSOR; LED apagado | | |

## Fronteiras — F1 a F8

*(a executar nas etapas 4 e 6)*

Nos casos de potenciômetro a temperatura fica em 25 °C; nos de temperatura o
potenciômetro fica em 200. Botão livre e LED apagado em todos.

| Caso | Entrada aplicada | Esperado | Obtido | Situação |
|---|---|---|---|---|
| F1 | pot 399 | NORMAL | 399 → NORMAL | Aprovado |
| F2 | pot 400 | ATENÇÃO | 400 → ATENCAO | Aprovado |
| F3 | pot 749 | ATENÇÃO | 749 → ATENCAO | Aprovado |
| F4 | pot 750 | ALARME | 750 → ALARME | Aprovado |
| F5 | temp 29,9 °C | NORMAL | | |
| F6 | temp 30 °C | ATENÇÃO | | |
| F7 | temp 39,9 °C | ATENÇÃO | | |
| F8 | temp 40 °C | ALARME | | |

As quatro fronteiras do potenciômetro foram atingidas nos valores exatos, com a
transição de estado observada em cada limite: 399/400 e 749/750.

**Verificação suplementar** (valores imediatamente acima dos limites), ambas
confirmadas: 401 → ATENCAO e 751 → ALARME.

F1 a F4 foram executados na etapa 4, quando a classificação considerava apenas o
potenciômetro. Serão reconfirmados na etapa 6, já com a decisão integrada e a
temperatura fixada em 25 °C.

## Ensaio da etapa 5 — DHT22

Executado antes da decisão integrada, quando o programa ainda imprime os campos
em linhas separadas. **Não constitui o caso T7**, cujo critério de aceite exige o
formato serial fixo introduzido na etapa 6.

Biblioteca: **DHT sensor library** (Adafruit), instalada pelo gerenciador do
próprio projeto no Wokwi. O programa usa `DHT.h` diretamente, e não `DHT_U.h`;
por isso a Adafruit Unified Sensor não é exigida e não foi instalada — não há
dependência transitiva a registrar.

| Ensaio | Entrada aplicada | Esperado | Obtido | Situação |
|---|---|---|---|---|
| E5.1 | DHT22 em 24,0 °C | leitura válida | `24.00` | Aprovado |
| E5.2 | DHT22 alterado para 46,9 °C em execução | a leitura acompanha | `46.90` | Aprovado |
| E5.3 | fio de DATA desconectado de D4 | falha identificada | `FALHA DE SENSOR` | Aprovado |
| E5.4 | fio de DATA reconectado | leitura válida de volta | `24.00` | Aprovado |

E5.3 e E5.4 seguiram o protocolo de seis passos da especificação, com a simulação
parada nas trocas de fio. A desconexão foi feita removendo a conexão
`[ "dht1:SDA", "uno:4", "green", [ "v0" ] ]` do `diagram.json` e restaurando-a em
seguida — equivalente a desligar o fio no editor visual, porém reversível de
forma exata. O `diagram.json` final é idêntico ao anterior ao ensaio.

**Observação levada para a etapa 6.** Com o fio desconectado, a saída trouxe
`FALHA DE SENSOR` e `NORMAL` no mesmo ciclo: a classificação do potenciômetro e a
verificação da temperatura ainda são impressas de forma independente. É
exatamente isso que a decisão integrada corrige, ao aplicar a prioridade
falha > alarme > atenção > normal numa única linha.
