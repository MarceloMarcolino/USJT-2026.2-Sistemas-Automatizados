# Casos de teste — TP03

Registro gerado a partir da bateria automatizada do núcleo técnico. A
validação cobre cálculos, regras, estrutura do circuito e compilação
para Arduino Uno; a captura `circuito-wokwi.png` documenta a montagem
visual no simulador.

## Proveniência

- Fase: `nucleo-tecnico`
- Execução UTC: `2026-09-07T17:44:35.489276+00:00`
- `sketch.ino` SHA-256: `ac4b7aeb87e7aac2057f2fe70027b0e91ca2d8538d844e0815658d71c391b074`
- `classificacao.h` SHA-256: `4aae4070b2c0fc4cc02ba1b75cd798a5ed44ccc415dcf1ec3dd9a6fc66296801`
- `diagram.json` SHA-256: `ded8f8d91298e76843335b610de603ac654992dee153dd3a422b81cc3c9c0264`
- Resultado: **44/44 aprovados**

## A — Aquisição

| Caso | Entrada | Esperado | Obtido | Situação |
|---|---|---|---|---|
| A1 | `botao=0; bruto=0` | `0,0,0.00,0.00,NORMAL` | `0,0,0.00,0.00,NORMAL` | Aprovado |
| A2 | `botao=1; bruto=0` | `1,0,0.00,0.00,NORMAL` | `1,0,0.00,0.00,NORMAL` | Aprovado |
| A3 | `botao=0; bruto=512` | `0,512,50.05,50.05,NORMAL` | `0,512,50.05,50.05,NORMAL` | Aprovado |
| A4 | `botao=0; bruto=1023` | `0,1023,100.00,100.00,PERIGO` | `0,1023,100.00,100.00,PERIGO` | Aprovado |

## B — Fronteiras percentuais injetadas

| Caso | Entrada | Esperado | Obtido | Situação |
|---|---|---|---|---|
| B1 | `pct=-1.00` | `FALHA` | `FALHA` | Aprovado |
| B2 | `pct=0.00` | `NORMAL` | `NORMAL` | Aprovado |
| B3 | `pct=69.99` | `NORMAL` | `NORMAL` | Aprovado |
| B4 | `pct=70.00` | `ATENCAO` | `ATENCAO` | Aprovado |
| B5 | `pct=84.99` | `ATENCAO` | `ATENCAO` | Aprovado |
| B6 | `pct=85.00` | `PERIGO` | `PERIGO` | Aprovado |
| B7 | `pct=100.00` | `PERIGO` | `PERIGO` | Aprovado |
| B8 | `pct=100.01` | `FALHA` | `FALHA` | Aprovado |

## Q — Quantização do ADC

| Caso | Entrada | Esperado | Obtido | Situação |
|---|---|---|---|---|
| Q1 | `bruto=0` | `pct=0.0000;tempC=0.00;mA=4.0000;V=0.0000;estado=NORMAL;LED=0` | `pct=0.0000;tempC=0.00;mA=4.0000;V=0.0000;estado=NORMAL;LED=0` | Aprovado |
| Q2 | `bruto=256` | `pct=25.0244;tempC=25.02;mA=8.0039;V=2.5024;estado=NORMAL;LED=0` | `pct=25.0244;tempC=25.02;mA=8.0039;V=2.5024;estado=NORMAL;LED=0` | Aprovado |
| Q3 | `bruto=512` | `pct=50.0489;tempC=50.05;mA=12.0078;V=5.0049;estado=NORMAL;LED=0` | `pct=50.0489;tempC=50.05;mA=12.0078;V=5.0049;estado=NORMAL;LED=0` | Aprovado |
| Q4 | `bruto=716` | `pct=69.9902;tempC=69.99;mA=15.1984;V=6.9990;estado=NORMAL;LED=0` | `pct=69.9902;tempC=69.99;mA=15.1984;V=6.9990;estado=NORMAL;LED=0` | Aprovado |
| Q5 | `bruto=717` | `pct=70.0880;tempC=70.09;mA=15.2141;V=7.0088;estado=ATENCAO;LED=0` | `pct=70.0880;tempC=70.09;mA=15.2141;V=7.0088;estado=ATENCAO;LED=0` | Aprovado |
| Q6 | `bruto=768` | `pct=75.0733;tempC=75.07;mA=16.0117;V=7.5073;estado=ATENCAO;LED=0` | `pct=75.0733;tempC=75.07;mA=16.0117;V=7.5073;estado=ATENCAO;LED=0` | Aprovado |
| Q7 | `bruto=869` | `pct=84.9462;tempC=84.95;mA=17.5914;V=8.4946;estado=ATENCAO;LED=0` | `pct=84.9462;tempC=84.95;mA=17.5914;V=8.4946;estado=ATENCAO;LED=0` | Aprovado |
| Q8 | `bruto=870` | `pct=85.0440;tempC=85.04;mA=17.6070;V=8.5044;estado=PERIGO;LED=1` | `pct=85.0440;tempC=85.04;mA=17.6070;V=8.5044;estado=PERIGO;LED=1` | Aprovado |
| Q9 | `bruto=1023` | `pct=100.0000;tempC=100.00;mA=20.0000;V=10.0000;estado=PERIGO;LED=1` | `pct=100.0000;tempC=100.00;mA=20.0000;V=10.0000;estado=PERIGO;LED=1` | Aprovado |

## M — Média móvel de cinco amostras

| Caso | Entrada | Esperado | Obtido | Situação |
|---|---|---|---|---|
| M1 | `bruto=500` | `500.00` | `500.00` | Aprovado |
| M2 | `bruto=504` | `502.00` | `502.00` | Aprovado |
| M3 | `bruto=498` | `500.67` | `500.67` | Aprovado |
| M4 | `bruto=502` | `501.00` | `501.00` | Aprovado |
| M5 | `bruto=500` | `500.80` | `500.80` | Aprovado |
| M6 | `bruto=620` | `524.80` | `524.80` | Aprovado |
| M7 | `bruto=504` | `524.80` | `524.80` | Aprovado |
| M8 | `bruto=498` | `524.80` | `524.80` | Aprovado |
| M9 | `bruto=502` | `524.80` | `524.80` | Aprovado |
| M10 | `bruto=500` | `524.80` | `524.80` | Aprovado |
| M11 | `bruto=500` | `500.80` | `500.80` | Aprovado |

## I — Cálculo inverso

| Caso | Entrada | Esperado | Obtido | Situação |
|---|---|---|---|---|
| I1 | `tempC=0` | `mA=4.00;V=0.00;direta_mA=0.00;direta_V=0.00` | `mA=4.00;V=0.00;direta_mA=0.00;direta_V=0.00` | Aprovado |
| I2 | `tempC=25` | `mA=8.00;V=2.50;direta_mA=25.00;direta_V=25.00` | `mA=8.00;V=2.50;direta_mA=25.00;direta_V=25.00` | Aprovado |
| I3 | `tempC=50` | `mA=12.00;V=5.00;direta_mA=50.00;direta_V=50.00` | `mA=12.00;V=5.00;direta_mA=50.00;direta_V=50.00` | Aprovado |
| I4 | `tempC=75` | `mA=16.00;V=7.50;direta_mA=75.00;direta_V=75.00` | `mA=16.00;V=7.50;direta_mA=75.00;direta_V=75.00` | Aprovado |
| I5 | `tempC=100` | `mA=20.00;V=10.00;direta_mA=100.00;direta_V=100.00` | `mA=20.00;V=10.00;direta_mA=100.00;direta_V=100.00` | Aprovado |

## G — Diagnóstico elétrico 4–20 mA

| Caso | Entrada | Esperado | Obtido | Situação |
|---|---|---|---|---|
| G1 | `mA=3.20` | `pct=-5.00;estado=FALHA` | `pct=-5.00;estado=FALHA` | Aprovado |
| G2 | `mA=4.00` | `pct=0.00;estado=NORMAL` | `pct=0.00;estado=NORMAL` | Aprovado |
| G3 | `mA=12.00` | `pct=50.00;estado=NORMAL` | `pct=50.00;estado=NORMAL` | Aprovado |
| G4 | `mA=15.20` | `pct=70.00;estado=ATENCAO` | `pct=70.00;estado=ATENCAO` | Aprovado |
| G5 | `mA=17.60` | `pct=85.00;estado=PERIGO` | `pct=85.00;estado=PERIGO` | Aprovado |
| G6 | `mA=20.00` | `pct=100.00;estado=PERIGO` | `pct=100.00;estado=PERIGO` | Aprovado |
| G7 | `mA=20.80` | `pct=105.00;estado=FALHA` | `pct=105.00;estado=FALHA` | Aprovado |
