# Casos de teste — TP03

Registro gerado a partir da verificação nativa do código entregue e da
planilha recalculada no Microsoft Excel. O campo **esperado** vem das
tabelas literais da especificação; o campo **obtido** vem das fontes
identificadas em cada linha.

**Limite declarado:** o harness executa o fonte Arduino no computador
com uma camada mínima da API Arduino. Isso não equivale à execução do
binário AVR nem à simulação elétrica do Wokwi. Os três sketches também
foram compilados separadamente para `arduino:avr:uno`.

<!-- inicio:observacoes-wokwi -->
**Execução no simulador.** Em 8 de setembro de 2026 o firmware obrigatório
foi executado no Wokwi. Foram preservados 29 registros selecionados, cobrindo
os nove códigos do grupo Q com os mesmos valores de CSV desta tabela. O LED
foi observado apagado em 716, 717 e 869; aceso em 870 e 1023, inclusive com
o botão pressionado em 870. O registro está em
[`../evidencias/monitor-serial-wokwi.txt`](../evidencias/monitor-serial-wokwi.txt).
Essa execução é independente do harness — mesma especificação como
esperado, mas o obtido vem do binário AVR simulado.
O caso A2 (`botao=1; bruto=0`) e as observações do LED em Q1, Q2, Q3 e Q6
continuam sem registro nesta evidência on-line; a aprovação local permanece
identificada por sua fonte nas tabelas abaixo.
<!-- fim:observacoes-wokwi -->

## Método

| Grupos | Fonte do valor obtido |
|---|---|
| A | `setup()` e `loop()` do `sketch.ino` entregue, executados no harness nativo |
| B | `classificar()` do `classificacao.h` entregue, executada no harness e conferida por fórmula na planilha |
| Q | `sketch.ino` executado no harness para ADC/CSV/estado/LED e planilha para escalas precisas e sinais equivalentes |
| M | `setup()` e `loop()` do sketch adicional, usando o `media_movel5.h` publicado |
| I, G | fórmulas presentes no XLSX e valores recalculados e salvos pelo Excel |

## Proveniência

- Execução UTC: `2026-09-08T23:15:27.893930+00:00`
- `sketch.ino` SHA-256: `ac4b7aeb87e7aac2057f2fe70027b0e91ca2d8538d844e0815658d71c391b074`
- `classificacao.h` SHA-256: `4aae4070b2c0fc4cc02ba1b75cd798a5ed44ccc415dcf1ec3dd9a6fc66296801`
- `media_movel5.h` SHA-256: `16482c624a26139f7bbd97404a441fe3a345e30a1c046d4ce6913eb00ffcb3ee`
- `sketch-media-movel.ino` SHA-256: `71988634919de73171940821c5a23e2fb0c7da7857eafddb8860399c0a771dd9`
- `diagram.json` SHA-256: `ded8f8d91298e76843335b610de603ac654992dee153dd3a422b81cc3c9c0264`
- `planilha-tp03.xlsx` SHA-256: `92bdcaae22cf6755ddd9ee89423455291cf623bcacedfa3114703ce4f321f5d6`
- `harness_tp03.cpp` SHA-256: `bd86772b6b292cae8f208f0a962f38088a461fa3233d3b042e6bda846a303329`
- `harness_tp03.exe` SHA-256: `06972609f4465d84301fc7f584e6d3029a10f54e627012af21f8bd67b952660c`
- Resultado: **44/44 aprovados**
- Conferência cruzada: **B 8/8** e **Q 9/9**

## A — Aquisição

| Caso | Entrada | Esperado | Obtido | Fonte | Situação |
|---|---|---|---|---|---|
| A1 | `botao=0; bruto=0` | `0,0,0.00,0.00,NORMAL` | `0,0,0.00,0.00,NORMAL` | sketch.ino via harness nativo | Aprovado |
| A2 | `botao=1; bruto=0` | `1,0,0.00,0.00,NORMAL` | `1,0,0.00,0.00,NORMAL` | sketch.ino via harness nativo | Aprovado |
| A3 | `botao=0; bruto=512` | `0,512,50.05,50.05,NORMAL` | `0,512,50.05,50.05,NORMAL` | sketch.ino via harness nativo | Aprovado |
| A4 | `botao=0; bruto=1023` | `0,1023,100.00,100.00,PERIGO` | `0,1023,100.00,100.00,PERIGO` | sketch.ino via harness nativo | Aprovado |

## B — Fronteiras percentuais injetadas

| Caso | Entrada | Esperado | Obtido | Fonte | Situação |
|---|---|---|---|---|---|
| B1 | `pct=-1.00` | `FALHA` | `FALHA` | classificacao.h via harness nativo + planilha Excel | Aprovado |
| B2 | `pct=0.00` | `NORMAL` | `NORMAL` | classificacao.h via harness nativo + planilha Excel | Aprovado |
| B3 | `pct=69.99` | `NORMAL` | `NORMAL` | classificacao.h via harness nativo + planilha Excel | Aprovado |
| B4 | `pct=70.00` | `ATENCAO` | `ATENCAO` | classificacao.h via harness nativo + planilha Excel | Aprovado |
| B5 | `pct=84.99` | `ATENCAO` | `ATENCAO` | classificacao.h via harness nativo + planilha Excel | Aprovado |
| B6 | `pct=85.00` | `PERIGO` | `PERIGO` | classificacao.h via harness nativo + planilha Excel | Aprovado |
| B7 | `pct=100.00` | `PERIGO` | `PERIGO` | classificacao.h via harness nativo + planilha Excel | Aprovado |
| B8 | `pct=100.01` | `FALHA` | `FALHA` | classificacao.h via harness nativo + planilha Excel | Aprovado |

## Q — Quantização do ADC

| Caso | Entrada | Esperado | Obtido | Fonte | Situação |
|---|---|---|---|---|---|
| Q1 | `bruto=0` | `pct=0.0000;tempC=0.00;mA=4.0000;V=0.0000;estado=NORMAL;LED=0` | `pct=0.0000;tempC=0.00;mA=4.0000;V=0.0000;estado=NORMAL;LED=0` | sketch.ino via harness nativo + planilha Excel | Aprovado |
| Q2 | `bruto=256` | `pct=25.0244;tempC=25.02;mA=8.0039;V=2.5024;estado=NORMAL;LED=0` | `pct=25.0244;tempC=25.02;mA=8.0039;V=2.5024;estado=NORMAL;LED=0` | sketch.ino via harness nativo + planilha Excel | Aprovado |
| Q3 | `bruto=512` | `pct=50.0489;tempC=50.05;mA=12.0078;V=5.0049;estado=NORMAL;LED=0` | `pct=50.0489;tempC=50.05;mA=12.0078;V=5.0049;estado=NORMAL;LED=0` | sketch.ino via harness nativo + planilha Excel | Aprovado |
| Q4 | `bruto=716` | `pct=69.9902;tempC=69.99;mA=15.1984;V=6.9990;estado=NORMAL;LED=0` | `pct=69.9902;tempC=69.99;mA=15.1984;V=6.9990;estado=NORMAL;LED=0` | sketch.ino via harness nativo + planilha Excel | Aprovado |
| Q5 | `bruto=717` | `pct=70.0880;tempC=70.09;mA=15.2141;V=7.0088;estado=ATENCAO;LED=0` | `pct=70.0880;tempC=70.09;mA=15.2141;V=7.0088;estado=ATENCAO;LED=0` | sketch.ino via harness nativo + planilha Excel | Aprovado |
| Q6 | `bruto=768` | `pct=75.0733;tempC=75.07;mA=16.0117;V=7.5073;estado=ATENCAO;LED=0` | `pct=75.0733;tempC=75.07;mA=16.0117;V=7.5073;estado=ATENCAO;LED=0` | sketch.ino via harness nativo + planilha Excel | Aprovado |
| Q7 | `bruto=869` | `pct=84.9462;tempC=84.95;mA=17.5914;V=8.4946;estado=ATENCAO;LED=0` | `pct=84.9462;tempC=84.95;mA=17.5914;V=8.4946;estado=ATENCAO;LED=0` | sketch.ino via harness nativo + planilha Excel | Aprovado |
| Q8 | `bruto=870` | `pct=85.0440;tempC=85.04;mA=17.6070;V=8.5044;estado=PERIGO;LED=1` | `pct=85.0440;tempC=85.04;mA=17.6070;V=8.5044;estado=PERIGO;LED=1` | sketch.ino via harness nativo + planilha Excel | Aprovado |
| Q9 | `bruto=1023` | `pct=100.0000;tempC=100.00;mA=20.0000;V=10.0000;estado=PERIGO;LED=1` | `pct=100.0000;tempC=100.00;mA=20.0000;V=10.0000;estado=PERIGO;LED=1` | sketch.ino via harness nativo + planilha Excel | Aprovado |

## M — Média móvel de cinco amostras

| Caso | Entrada | Esperado | Obtido | Fonte | Situação |
|---|---|---|---|---|---|
| M1 | `bruto=500` | `500.00` | `500.00` | sketch adicional + media_movel5.h via harness nativo | Aprovado |
| M2 | `bruto=504` | `502.00` | `502.00` | sketch adicional + media_movel5.h via harness nativo | Aprovado |
| M3 | `bruto=498` | `500.67` | `500.67` | sketch adicional + media_movel5.h via harness nativo | Aprovado |
| M4 | `bruto=502` | `501.00` | `501.00` | sketch adicional + media_movel5.h via harness nativo | Aprovado |
| M5 | `bruto=500` | `500.80` | `500.80` | sketch adicional + media_movel5.h via harness nativo | Aprovado |
| M6 | `bruto=620` | `524.80` | `524.80` | sketch adicional + media_movel5.h via harness nativo | Aprovado |
| M7 | `bruto=504` | `524.80` | `524.80` | sketch adicional + media_movel5.h via harness nativo | Aprovado |
| M8 | `bruto=498` | `524.80` | `524.80` | sketch adicional + media_movel5.h via harness nativo | Aprovado |
| M9 | `bruto=502` | `524.80` | `524.80` | sketch adicional + media_movel5.h via harness nativo | Aprovado |
| M10 | `bruto=500` | `524.80` | `524.80` | sketch adicional + media_movel5.h via harness nativo | Aprovado |
| M11 | `bruto=500` | `500.80` | `500.80` | sketch adicional + media_movel5.h via harness nativo | Aprovado |

## I — Cálculo inverso

| Caso | Entrada | Esperado | Obtido | Fonte | Situação |
|---|---|---|---|---|---|
| I1 | `tempC=0.0` | `mA=4.00;V=0.00;volta=0.00` | `mA=4.00;V=0.00;volta=0.00` | planilha Excel (formula e cache recalculado) | Aprovado |
| I2 | `tempC=25.0` | `mA=8.00;V=2.50;volta=25.00` | `mA=8.00;V=2.50;volta=25.00` | planilha Excel (formula e cache recalculado) | Aprovado |
| I3 | `tempC=50.0` | `mA=12.00;V=5.00;volta=50.00` | `mA=12.00;V=5.00;volta=50.00` | planilha Excel (formula e cache recalculado) | Aprovado |
| I4 | `tempC=75.0` | `mA=16.00;V=7.50;volta=75.00` | `mA=16.00;V=7.50;volta=75.00` | planilha Excel (formula e cache recalculado) | Aprovado |
| I5 | `tempC=100.0` | `mA=20.00;V=10.00;volta=100.00` | `mA=20.00;V=10.00;volta=100.00` | planilha Excel (formula e cache recalculado) | Aprovado |

## G — Diagnóstico elétrico 4–20 mA

| Caso | Entrada | Esperado | Obtido | Fonte | Situação |
|---|---|---|---|---|---|
| G1 | `mA=3.2` | `pct=-5.00;estado=FALHA` | `pct=-5.00;estado=FALHA` | planilha Excel (formula e cache recalculado) | Aprovado |
| G2 | `mA=4.0` | `pct=0.00;estado=NORMAL` | `pct=0.00;estado=NORMAL` | planilha Excel (formula e cache recalculado) | Aprovado |
| G3 | `mA=12.0` | `pct=50.00;estado=NORMAL` | `pct=50.00;estado=NORMAL` | planilha Excel (formula e cache recalculado) | Aprovado |
| G4 | `mA=15.2` | `pct=70.00;estado=ATENCAO` | `pct=70.00;estado=ATENCAO` | planilha Excel (formula e cache recalculado) | Aprovado |
| G5 | `mA=17.6` | `pct=85.00;estado=PERIGO` | `pct=85.00;estado=PERIGO` | planilha Excel (formula e cache recalculado) | Aprovado |
| G6 | `mA=20.0` | `pct=100.00;estado=PERIGO` | `pct=100.00;estado=PERIGO` | planilha Excel (formula e cache recalculado) | Aprovado |
| G7 | `mA=20.8` | `pct=105.00;estado=FALHA` | `pct=105.00;estado=FALHA` | planilha Excel (formula e cache recalculado) | Aprovado |
