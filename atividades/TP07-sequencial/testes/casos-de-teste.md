# TP07 — relatório de testes

Gerado por `simulacao/verifica_tp07.py` em 2026-10-11T01:45:15Z a partir da execução no motor nativo do PLC Simulator Online (`index-52YZHsrG.js`, 2026-10-11T01:44:49.966Z). O esperado de cada caso foi fixado antes da execução, a partir das regras do motor e da política de cada parte (README, seção Validação). Tempo do simulador: 66 ms por varredura.

## Resumo

| Item | Resultado |
|---|---|
| Programa A — temporização e contagem | 120/120 casos, 846 varreduras |
| Programa B — GRAFCET de enchimento | 184/184 casos, 2055 varreduras |
| Caracterização do TOF (não é programa entregue) | 8/8 passos, 62 varreduras |
| Nativo × interpretador independente | 19160/19160 leituras idênticas (todas as tags observadas, programas e mutantes) |
| Invariantes | 13/13 sem violação (845 + 2044 varreduras) |
| Mutantes | 12/12 reprovados onde devem |
| Capturas | 11/11 conferidas (2026-10-11T01:45:15.192Z) |

## Programa A — temporização e contagem

### SEQ-A-OBR — Atraso de partida: T01, T02, T04, T05

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| T01 | START=1 | 31 | fim: T1.ET=2046, T1.Q=0, MOTOR_DELAY=0; em todas as 31 varreduras: T1.Q=0, MOTOR_DELAY=0 | fim: T1.ET=2046, T1.Q=0, MOTOR_DELAY=0; em todas as 31 varreduras: confere | PASSA |
| T01b | START=0 | 1 | fim: T1.ET=0, T1.Q=0, MOTOR_DELAY=0 | fim: T1.ET=0, T1.Q=0, MOTOR_DELAY=0 | PASSA |
| T02a | START=1 | 45 | fim: T1.ET=2970, T1.Q=0, MOTOR_DELAY=0; em todas as 45 varreduras: T1.Q=0, MOTOR_DELAY=0 | fim: T1.ET=2970, T1.Q=0, MOTOR_DELAY=0; em todas as 45 varreduras: confere | PASSA |
| T02 | — | 1 | fim: T1.ET=3000, T1.Q=1, MOTOR_DELAY=1 | fim: T1.ET=3000, T1.Q=1, MOTOR_DELAY=1 | PASSA |
| T02c | — | 20 | fim: T1.ET=3000, T1.Q=1, MOTOR_DELAY=1; em todas as 20 varreduras: T1.ET=3000, MOTOR_DELAY=1 | fim: T1.ET=3000, T1.Q=1, MOTOR_DELAY=1; em todas as 20 varreduras: confere | PASSA |
| T04 | EMG_OK=0 | 1 | fim: MOTOR_DELAY=0, T1.Q=0, T1.ET=0 | fim: MOTOR_DELAY=0, T1.Q=0, T1.ET=0 | PASSA |
| T04b | START=0 | 1 | fim: MOTOR_DELAY=0, T1.Q=0, T1.ET=0 | fim: MOTOR_DELAY=0, T1.Q=0, T1.ET=0 | PASSA |
| T05 | EMG_OK=1 | 60 | fim: MOTOR_DELAY=0, T1.ET=0, T1.Q=0; em todas as 60 varreduras: MOTOR_DELAY=0, T1.ET=0 | fim: MOTOR_DELAY=0, T1.ET=0, T1.Q=0; em todas as 60 varreduras: confere | PASSA |

### SEQ-A-T03 — Atraso de partida: T03 (STOP durante a temporização)

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| T03a | START=1 | 20 | fim: T1.ET=1320, T1.Q=0, MOTOR_DELAY=0 | fim: T1.ET=1320, T1.Q=0, MOTOR_DELAY=0 | PASSA |
| T03 | STOP_OK=0 | 1 | fim: T1.ET=0, T1.Q=0, MOTOR_DELAY=0 | fim: T1.ET=0, T1.Q=0, MOTOR_DELAY=0 | PASSA |
| T03b | — | 30 | fim: T1.ET=0; em todas as 30 varreduras: T1.ET=0, MOTOR_DELAY=0 | fim: T1.ET=0; em todas as 30 varreduras: confere | PASSA |
| T03c | STOP_OK=1 | 1 | fim: T1.ET=66, T1.Q=0, MOTOR_DELAY=0 | fim: T1.ET=66, T1.Q=0, MOTOR_DELAY=0 | PASSA |
| T03d | — | 45 | fim: T1.ET=3000, T1.Q=1, MOTOR_DELAY=1 | fim: T1.ET=3000, T1.Q=1, MOTOR_DELAY=1 | PASSA |

### SEQ-A-EMG — Atraso de partida: emergência liberada com START mantido

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| T05c | START=1, EMG_OK=0 | 10 | fim: T1.ET=0, MOTOR_DELAY=0; em todas as 10 varreduras: T1.ET=0, T1.Q=0, MOTOR_DELAY=0 | fim: T1.ET=0, MOTOR_DELAY=0; em todas as 10 varreduras: confere | PASSA |
| T05d | EMG_OK=1 | 45 | fim: T1.ET=2970, T1.Q=0, MOTOR_DELAY=0; em todas as 45 varreduras: MOTOR_DELAY=0 | fim: T1.ET=2970, T1.Q=0, MOTOR_DELAY=0; em todas as 45 varreduras: confere | PASSA |
| T05e | — | 1 | fim: T1.ET=3000, T1.Q=1, MOTOR_DELAY=1 | fim: T1.ET=3000, T1.Q=1, MOTOR_DELAY=1 | PASSA |

### SEQ-A-INT — Atraso de partida: interrupções antes e depois de PT

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| I01a | START=1 | 40 | fim: T1.ET=2640, T1.Q=0 | fim: T1.ET=2640, T1.Q=0 | PASSA |
| I01b | START=0 | 1 | fim: T1.ET=0, T1.Q=0 | fim: T1.ET=0, T1.Q=0 | PASSA |
| I01c | START=1 | 40 | fim: T1.ET=2640, T1.Q=0, MOTOR_DELAY=0; em todas as 40 varreduras: MOTOR_DELAY=0 | fim: T1.ET=2640, T1.Q=0, MOTOR_DELAY=0; em todas as 40 varreduras: confere | PASSA |
| I02a | — | 6 | fim: T1.ET=3000, T1.Q=1, MOTOR_DELAY=1 | fim: T1.ET=3000, T1.Q=1, MOTOR_DELAY=1 | PASSA |
| I02 | START=0 | 1 | fim: T1.ET=0, T1.Q=0, MOTOR_DELAY=0 | fim: T1.ET=0, T1.Q=0, MOTOR_DELAY=0 | PASSA |
| I03a | START=1 | 46 | fim: T1.ET=3000, MOTOR_DELAY=1 | fim: T1.ET=3000, MOTOR_DELAY=1 | PASSA |
| I03 | STOP_OK=0 | 1 | fim: T1.ET=0, T1.Q=0, MOTOR_DELAY=0 | fim: T1.ET=0, T1.Q=0, MOTOR_DELAY=0 | PASSA |
| I03b | STOP_OK=1, START=0 | 10 | fim: T1.ET=0, MOTOR_DELAY=0; em todas as 10 varreduras: MOTOR_DELAY=0 | fim: T1.ET=0, MOTOR_DELAY=0; em todas as 10 varreduras: confere | PASSA |

### SEQ-A-PISCA — Sinal intermitente: 6 s de execução

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| P01 | HAB_PISCA=1 | 91 | fim: PISCA=1, LAMPADA=1, T_LIG.ET=726, T_LIG.Q=0, T_DESL.ET=0, T_DESL.Q=0; varredura a varredura (91 leituras de PISCA, LAMPADA, T_DESL.ET, T_DESL.Q, T_LIG.ET, T_LIG.Q) pela fórmula da especificação | fim: PISCA=1, LAMPADA=1, T_LIG.ET=726, T_LIG.Q=0, T_DESL.ET=0, T_DESL.Q=0; 91/91 leituras conferem | PASSA |
| P02 | HAB_PISCA=0 | 1 | fim: PISCA=0, LAMPADA=0, T_DESL.ET=0, T_LIG.ET=0, T_DESL.Q=0, T_LIG.Q=0 | fim: PISCA=0, LAMPADA=0, T_DESL.ET=0, T_LIG.ET=0, T_DESL.Q=0, T_LIG.Q=0 | PASSA |
| P03 | HAB_PISCA=1 | 16 | fim: PISCA=1, LAMPADA=1, T_DESL.ET=1000, T_DESL.Q=1, T_LIG.ET=0, T_LIG.Q=0; varredura a varredura (16 leituras de PISCA, LAMPADA, T_DESL.ET, T_DESL.Q, T_LIG.ET, T_LIG.Q) pela fórmula da especificação | fim: PISCA=1, LAMPADA=1, T_DESL.ET=1000, T_DESL.Q=1, T_LIG.ET=0, T_LIG.Q=0; 16/16 leituras conferem | PASSA |

### SEQ-A-LOTE — Lote de 5: uma contagem por peça, sensor mantido

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| L1a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| L1b | — | 2 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| L1c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| L2a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=2, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=2, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| L2b | — | 2 | fim: C_LOTE.CV=2, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=2 | fim: C_LOTE.CV=2, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| L2c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=2; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |
| L3a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=3, LOTE_OK=0 | fim: P_PECA=1, C_LOTE.CV=3, LOTE_OK=0 | PASSA |
| L3b | — | 100 | fim: C_LOTE.CV=3; em todas as 100 varreduras: P_PECA=0, C_LOTE.CV=3 | fim: C_LOTE.CV=3; em todas as 100 varreduras: confere | PASSA |
| L3c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=3 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=3 | PASSA |
| L4a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=4, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=4, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| L4b | — | 2 | fim: C_LOTE.CV=4, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=4 | fim: C_LOTE.CV=4, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| L4c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=4; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=4 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=4; em todas as 2 varreduras: confere | PASSA |
| L5a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=5, LOTE_OK=1, C_LOTE.QU=1 | fim: P_PECA=1, C_LOTE.CV=5, LOTE_OK=1, C_LOTE.QU=1 | PASSA |
| L5b | — | 2 | fim: C_LOTE.CV=5, LOTE_OK=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=5 | fim: C_LOTE.CV=5, LOTE_OK=1; em todas as 2 varreduras: confere | PASSA |
| L5c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=5; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=5 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=5; em todas as 2 varreduras: confere | PASSA |
| L6a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=6, LOTE_OK=1, C_LOTE.QU=1 | fim: P_PECA=1, C_LOTE.CV=6, LOTE_OK=1, C_LOTE.QU=1 | PASSA |
| L6b | — | 2 | fim: C_LOTE.CV=6, LOTE_OK=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=6 | fim: C_LOTE.CV=6, LOTE_OK=1; em todas as 2 varreduras: confere | PASSA |
| L6c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=6; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=6 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=6; em todas as 2 varreduras: confere | PASSA |

### SEQ-A-RST1 — Zeragem com CV=0, CV=3 e CV=5

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| R01 | RESET_LOTE=1 | 1 | fim: C_LOTE.CV=0, LOTE_OK=0, C_LOTE.QU=0 | fim: C_LOTE.CV=0, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R01b | RESET_LOTE=0 | 1 | fim: C_LOTE.CV=0 | fim: C_LOTE.CV=0 | PASSA |
| R1-1a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R1-1b | — | 2 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R1-1c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| R1-2a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=2, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=2, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R1-2b | — | 2 | fim: C_LOTE.CV=2, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=2 | fim: C_LOTE.CV=2, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R1-2c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=2; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |
| R1-3a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=3, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=3, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R1-3b | — | 2 | fim: C_LOTE.CV=3, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=3 | fim: C_LOTE.CV=3, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R1-3c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=3; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=3 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=3; em todas as 2 varreduras: confere | PASSA |
| R02 | RESET_LOTE=1 | 1 | fim: C_LOTE.CV=0, LOTE_OK=0 | fim: C_LOTE.CV=0, LOTE_OK=0 | PASSA |
| R02b | RESET_LOTE=0 | 1 | fim: C_LOTE.CV=0 | fim: C_LOTE.CV=0 | PASSA |
| R2-1a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R2-1b | — | 2 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R2-1c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| R2-2a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=2, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=2, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R2-2b | — | 2 | fim: C_LOTE.CV=2, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=2 | fim: C_LOTE.CV=2, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R2-2c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=2; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |
| R2-3a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=3, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=3, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R2-3b | — | 2 | fim: C_LOTE.CV=3, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=3 | fim: C_LOTE.CV=3, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R2-3c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=3; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=3 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=3; em todas as 2 varreduras: confere | PASSA |
| R2-4a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=4, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=4, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R2-4b | — | 2 | fim: C_LOTE.CV=4, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=4 | fim: C_LOTE.CV=4, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R2-4c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=4; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=4 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=4; em todas as 2 varreduras: confere | PASSA |
| R2-5a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=5, LOTE_OK=1, C_LOTE.QU=1 | fim: P_PECA=1, C_LOTE.CV=5, LOTE_OK=1, C_LOTE.QU=1 | PASSA |
| R2-5b | — | 2 | fim: C_LOTE.CV=5, LOTE_OK=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=5 | fim: C_LOTE.CV=5, LOTE_OK=1; em todas as 2 varreduras: confere | PASSA |
| R2-5c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=5; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=5 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=5; em todas as 2 varreduras: confere | PASSA |
| R03 | RESET_LOTE=1 | 1 | fim: C_LOTE.CV=0, LOTE_OK=0, C_LOTE.QU=0 | fim: C_LOTE.CV=0, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R03b | RESET_LOTE=0 | 1 | fim: C_LOTE.CV=0, LOTE_OK=0 | fim: C_LOTE.CV=0, LOTE_OK=0 | PASSA |
| R06-a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R06-b | — | 2 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R06-c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |

### SEQ-A-RST2 — Zeragem simultânea à contagem e reset mantido

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| R3-1a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R3-1b | — | 2 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R3-1c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| R3-2a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=2, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=2, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R3-2b | — | 2 | fim: C_LOTE.CV=2, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=2 | fim: C_LOTE.CV=2, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R3-2c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=2; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |
| R3-3a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=3, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=3, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R3-3b | — | 2 | fim: C_LOTE.CV=3, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=3 | fim: C_LOTE.CV=3, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R3-3c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=3; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=3 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=3; em todas as 2 varreduras: confere | PASSA |
| R3-4a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=4, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=4, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R3-4b | — | 2 | fim: C_LOTE.CV=4, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=4 | fim: C_LOTE.CV=4, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R3-4c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=4; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=4 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=4; em todas as 2 varreduras: confere | PASSA |
| R04 | S_PECA=1, RESET_LOTE=1 | 1 | fim: P_PECA=1, C_LOTE.CV=0, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=0, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R04b | RESET_LOTE=0 | 2 | fim: C_LOTE.CV=0, P_PECA=0; em todas as 2 varreduras: C_LOTE.CV=0, P_PECA=0 | fim: C_LOTE.CV=0, P_PECA=0; em todas as 2 varreduras: confere | PASSA |
| R04c | S_PECA=0 | 2 | fim: C_LOTE.CV=0 | fim: C_LOTE.CV=0 | PASSA |
| R04d-a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R04d-b | — | 2 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R04d-c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| R05a | RESET_LOTE=1 | 1 | fim: C_LOTE.CV=0 | fim: C_LOTE.CV=0 | PASSA |
| R05b | S_PECA=1 | 3 | fim: C_LOTE.CV=0; em todas as 3 varreduras: C_LOTE.CV=0 | fim: C_LOTE.CV=0; em todas as 3 varreduras: confere | PASSA |
| R05c | S_PECA=0 | 2 | fim: C_LOTE.CV=0; em todas as 2 varreduras: C_LOTE.CV=0 | fim: C_LOTE.CV=0; em todas as 2 varreduras: confere | PASSA |
| R05d | S_PECA=1 | 3 | fim: C_LOTE.CV=0; em todas as 3 varreduras: C_LOTE.CV=0 | fim: C_LOTE.CV=0; em todas as 3 varreduras: confere | PASSA |
| R05 | S_PECA=0, RESET_LOTE=0 | 2 | fim: C_LOTE.CV=0, LOTE_OK=0; em todas as 2 varreduras: C_LOTE.CV=0 | fim: C_LOTE.CV=0, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R05e-a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| R05e-b | — | 2 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| R05e-c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |

### SEQ-A-PARADA — Parada e retomada da simulação

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| PA-1a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=1, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| PA-1b | — | 2 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| PA-1c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=1 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| PA-2a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=2, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=2, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| PA-2b | — | 2 | fim: C_LOTE.CV=2, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=2 | fim: C_LOTE.CV=2, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| PA-2c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=2; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |
| PA-3a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=3, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=3, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| PA-3b | — | 2 | fim: C_LOTE.CV=3, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=3 | fim: C_LOTE.CV=3, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| PA-3c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=3; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=3 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=3; em todas as 2 varreduras: confere | PASSA |
| PA-4a | S_PECA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=4, LOTE_OK=0, C_LOTE.QU=0 | fim: P_PECA=1, C_LOTE.CV=4, LOTE_OK=0, C_LOTE.QU=0 | PASSA |
| PA-4b | — | 2 | fim: C_LOTE.CV=4, LOTE_OK=0; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=4 | fim: C_LOTE.CV=4, LOTE_OK=0; em todas as 2 varreduras: confere | PASSA |
| PA-4c | S_PECA=0 | 2 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=4; em todas as 2 varreduras: P_PECA=0, C_LOTE.CV=4 | fim: P_PECA=0, S_PECA_ANT=0, C_LOTE.CV=4; em todas as 2 varreduras: confere | PASSA |
| PA0a | S_PECA=1, START=1, HAB_PISCA=1 | 1 | fim: P_PECA=1, C_LOTE.CV=5, LOTE_OK=1, T1.ET=66, T_DESL.ET=66, PISCA=0 | fim: P_PECA=1, C_LOTE.CV=5, LOTE_OK=1, T1.ET=66, T_DESL.ET=66, PISCA=0 | PASSA |
| PA0b | — | 19 | fim: T1.ET=1320, PISCA=1, LAMPADA=1, T_LIG.ET=264, C_LOTE.CV=5, P_PECA=0 | fim: T1.ET=1320, PISCA=1, LAMPADA=1, T_LIG.ET=264, C_LOTE.CV=5, P_PECA=0 | PASSA |
| PA1 | parar a simulação | 1 | fim: MOTOR_DELAY=0, T1.ET=0, T1.Q=0, PISCA=0, LAMPADA=0, T_DESL.ET=0, T_LIG.ET=0, P_PECA=0, LOTE_OK=0, C_LOTE.CV=5, S_PECA_ANT=1, C_LOTE.QU=1, C_LOTE.R=0 | fim: MOTOR_DELAY=0, T1.ET=0, T1.Q=0, PISCA=0, LAMPADA=0, T_DESL.ET=0, T_LIG.ET=0, P_PECA=0, LOTE_OK=0, C_LOTE.CV=5, S_PECA_ANT=1, C_LOTE.QU=1, C_LOTE.R=0 | PASSA |
| PA2 | — | 1 | fim: C_LOTE.CV=5, P_PECA=0, LOTE_OK=1, T1.ET=66, PISCA=0, T_DESL.ET=66, T_LIG.ET=0 | fim: C_LOTE.CV=5, P_PECA=0, LOTE_OK=1, T1.ET=66, PISCA=0, T_DESL.ET=66, T_LIG.ET=0 | PASSA |

## Programa B — GRAFCET de enchimento

### SEQ-B-NORMAL — Ciclo normal: transportar, encher, liberar

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| G00 | — | 1 | fim: INIT=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=0, Y_VALV=0, C_LOTE.CV=0, LOTE_OK=0, TR01=0, TR12=0, TR20=0 | fim: INIT=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=0, Y_VALV=0, C_LOTE.CV=0, LOTE_OK=0, TR01=0, TR12=0, TR20=0 | PASSA |
| G01 | — | 3 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1; em todas as 3 varreduras: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, Y_VALV=0 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1; em todas as 3 varreduras: confere | PASSA |
| G02 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, M_EST=0, Y_VALV=1, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, M_EST=0, Y_VALV=1, T_ENCH.ET=66 | PASSA |
| G03 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| G04 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| G05 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0 | PASSA |
| G06 | — | 2 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, C_LOTE.CV=0; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, C_LOTE.CV=0, TR20=0 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, C_LOTE.CV=0; em todas as 2 varreduras: confere | PASSA |
| G07 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, M_EST=1, LOTE_OK=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, M_EST=1, LOTE_OK=0 | PASSA |
| G08 | — | 1 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=1 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=1 | PASSA |
| G09.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| G09.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| G09.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| G09.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| G09.5 | — | 2 | fim: C_LOTE.CV=1; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| G09.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| G09.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |

### SEQ-B-LOTE — Lote de 6: bloqueio e zeragem

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| GL1.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GL1.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GL1.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GL1.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GL1.5 | — | 2 | fim: C_LOTE.CV=0; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=0 | fim: C_LOTE.CV=0; em todas as 2 varreduras: confere | PASSA |
| GL1.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GL1.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=1 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| GL2.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GL2.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GL2.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GL2.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GL2.5 | — | 2 | fim: C_LOTE.CV=1; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| GL2.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GL2.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |
| GL3.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GL3.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GL3.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GL3.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GL3.5 | — | 2 | fim: C_LOTE.CV=2; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=2 | fim: C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |
| GL3.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=3, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=3, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GL3.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=3; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=3 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=3; em todas as 2 varreduras: confere | PASSA |
| GL4.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GL4.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GL4.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GL4.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GL4.5 | — | 2 | fim: C_LOTE.CV=3; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=3 | fim: C_LOTE.CV=3; em todas as 2 varreduras: confere | PASSA |
| GL4.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=4, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=4, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GL4.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=4; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=4 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=4; em todas as 2 varreduras: confere | PASSA |
| GL5.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GL5.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GL5.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GL5.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GL5.5 | — | 2 | fim: C_LOTE.CV=4; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=4 | fim: C_LOTE.CV=4; em todas as 2 varreduras: confere | PASSA |
| GL5.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=5, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=5, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GL5.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=5; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=5 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=5; em todas as 2 varreduras: confere | PASSA |
| GL6.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GL6.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GL6.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GL6.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GL6.5 | — | 2 | fim: C_LOTE.CV=5; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=5 | fim: C_LOTE.CV=5; em todas as 2 varreduras: confere | PASSA |
| GL6.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=6, LOTE_OK=1, M_EST=0, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=6, LOTE_OK=1, M_EST=0, Y_VALV=0 | PASSA |
| GL6.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=6; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=0, C_LOTE.CV=6 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=6; em todas as 2 varreduras: confere | PASSA |
| G10 | S_PECA=1 | 70 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=6; em todas as 70 varreduras: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, TR01=0, Y_VALV=0, M_EST=0, C_LOTE.CV=6, LOTE_OK=1 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=6; em todas as 70 varreduras: confere | PASSA |
| G11 | RESET_LOTE=1 | 1 | fim: C_LOTE.CV=0, LOTE_OK=0, TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, M_EST=0, Y_VALV=1, T_ENCH.ET=66 | fim: C_LOTE.CV=0, LOTE_OK=0, TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, M_EST=0, Y_VALV=1, T_ENCH.ET=66 | PASSA |
| G12a | RESET_LOTE=0 | 59 | fim: T_ENCH.ET=3960, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | fim: T_ENCH.ET=3960, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | PASSA |
| G12b | — | 1 | fim: T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | fim: T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | PASSA |
| G12c | — | 1 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1 | PASSA |
| G12 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, LOTE_OK=0, M_EST=1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, LOTE_OK=0, M_EST=1 | PASSA |

### SEQ-B-EMG — Emergência em E0, E1 e E2

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| G20 | EMG_OK=0 | 3 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=0; em todas as 3 varreduras: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=0 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=0; em todas as 3 varreduras: confere | PASSA |
| G21 | S_PECA=1 | 3 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, TR01=0; em todas as 3 varreduras: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, TR01=0, M_EST=0, Y_VALV=0 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, TR01=0; em todas as 3 varreduras: confere | PASSA |
| G22 | EMG_OK=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| G22b | — | 29 | fim: T_ENCH.ET=1980, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=1980, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| G23 | EMG_OK=0 | 1 | fim: Y_VALV=0, M_EST=0, T_ENCH.ET=0, T_ENCH.Q=0, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | fim: Y_VALV=0, M_EST=0, T_ENCH.ET=0, T_ENCH.Q=0, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | PASSA |
| G23b | — | 50 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, T_ENCH.ET=0; em todas as 50 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, T_ENCH.ET=0, Y_VALV=0, M_EST=0 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, T_ENCH.ET=0; em todas as 50 varreduras: confere | PASSA |
| G24 | EMG_OK=1 | 1 | fim: Y_VALV=1, T_ENCH.ET=66, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | fim: Y_VALV=1, T_ENCH.ET=66, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | PASSA |
| G24b | — | 60 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | PASSA |
| G24c | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, Y_VALV=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, Y_VALV=0 | PASSA |
| G25 | EMG_OK=0 | 1 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=0 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=0 | PASSA |
| G26 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, M_EST=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, M_EST=0 | PASSA |
| G27 | EMG_OK=1 | 1 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1 | PASSA |

### SEQ-B-PARTIDA — Partida com recipiente já no sensor

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| GI0 | S_PECA=1 | 1 | fim: INIT=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, TR01=0, M_EST=0, Y_VALV=0 | fim: INIT=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, TR01=0, M_EST=0, Y_VALV=0 | PASSA |
| GI1 | — | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |

### SEQ-B-EMG2 — Emergência na varredura seguinte ao fim do tempo

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| GE.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GE.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GE.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| G28 | EMG_OK=0 | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=0, T_ENCH.ET=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=0, T_ENCH.ET=0 | PASSA |
| G29 | EMG_OK=1 | 1 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1 | PASSA |

### SEQ-B-LIMITES — Comportamentos declarados nos limites

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| GX1 | S_PECA=1 | 1 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, T_ENCH.ET=66 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, T_ENCH.ET=66 | PASSA |
| GX2 | S_PECA=0 | 59 | fim: T_ENCH.ET=3960; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=3960; em todas as 59 varreduras: confere | PASSA |
| GX3 | — | 1 | fim: T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | fim: T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | PASSA |
| GX4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, TR20=0, C_LOTE.CV=0, M_EST=1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, TR20=0, C_LOTE.CV=0, M_EST=1 | PASSA |
| GX5 | — | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1 | PASSA |
| GX6 | S_PECA=1 | 1 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, T_ENCH.ET=66 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, T_ENCH.ET=66 | PASSA |
| GX7 | — | 59 | fim: T_ENCH.ET=3960, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | fim: T_ENCH.ET=3960, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | PASSA |
| GX8 | — | 1 | fim: T_ENCH.Q=1 | fim: T_ENCH.Q=1 | PASSA |
| GX9 | — | 1 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1 | PASSA |
| GX10 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2 | PASSA |
| GX11 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, C_LOTE.CV=2 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, C_LOTE.CV=2 | PASSA |
| GX12 | RESET_LOTE=1 | 59 | fim: T_ENCH.ET=3960; em todas as 59 varreduras: C_LOTE.CV=0, LOTE_OK=0 | fim: T_ENCH.ET=3960; em todas as 59 varreduras: confere | PASSA |
| GX13 | — | 1 | fim: T_ENCH.Q=1, C_LOTE.CV=0 | fim: T_ENCH.Q=1, C_LOTE.CV=0 | PASSA |
| GX14 | — | 1 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, C_LOTE.CV=0 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, C_LOTE.CV=0 | PASSA |
| GX15 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=0, LOTE_OK=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=0, LOTE_OK=0 | PASSA |
| GX16 | RESET_LOTE=0 | 1 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=0, M_EST=1 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=0, M_EST=1 | PASSA |

### SEQ-B-PRESO — Sensor preso em 1 depois do enchimento

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| GP.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GP.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GP.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GP.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| G30 | — | 200 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, C_LOTE.CV=0; em todas as 200 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=0 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, C_LOTE.CV=0; em todas as 200 varreduras: confere | PASSA |
| G31 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1 | PASSA |

### SEQ-B-RESET — Zeragem durante o ciclo e simultânea à contagem

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| GR1.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GR1.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GR1.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GR1.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GR1.5 | — | 2 | fim: C_LOTE.CV=0; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=0 | fim: C_LOTE.CV=0; em todas as 2 varreduras: confere | PASSA |
| GR1.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GR1.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=1 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| GR2.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GR2.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GR2.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GR2.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GR2.5 | — | 2 | fim: C_LOTE.CV=1; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| GR2.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GR2.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |
| G40a | S_PECA=1 | 1 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, T_ENCH.ET=66 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, T_ENCH.ET=66 | PASSA |
| G40b | — | 9 | fim: T_ENCH.ET=660, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | fim: T_ENCH.ET=660, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | PASSA |
| G40 | RESET_LOTE=1 | 1 | fim: C_LOTE.CV=0, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, T_ENCH.ET=726 | fim: C_LOTE.CV=0, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, T_ENCH.ET=726 | PASSA |
| G40c | RESET_LOTE=0 | 49 | fim: T_ENCH.ET=3960, C_LOTE.CV=0 | fim: T_ENCH.ET=3960, C_LOTE.CV=0 | PASSA |
| G40d | — | 1 | fim: T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | fim: T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | PASSA |
| G40e | — | 1 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1 | PASSA |
| G40f | — | 2 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, C_LOTE.CV=0 | fim: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, C_LOTE.CV=0 | PASSA |
| G41 | S_PECA=0, RESET_LOTE=1 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=0, LOTE_OK=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=0, LOTE_OK=0 | PASSA |
| G41b | RESET_LOTE=0 | 1 | fim: C_LOTE.CV=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0 | fim: C_LOTE.CV=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0 | PASSA |
| GR3.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GR3.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GR3.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GR3.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GR3.5 | — | 2 | fim: C_LOTE.CV=0; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=0 | fim: C_LOTE.CV=0; em todas as 2 varreduras: confere | PASSA |
| GR3.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GR3.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=1 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |

### SEQ-B-PARADA — Parada e retomada da simulação

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| GQ1.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GQ1.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GQ1.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GQ1.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GQ1.5 | — | 2 | fim: C_LOTE.CV=0; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=0 | fim: C_LOTE.CV=0; em todas as 2 varreduras: confere | PASSA |
| GQ1.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GQ1.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=1 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| GQ2.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GQ2.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GQ2.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GQ2.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GQ2.5 | — | 2 | fim: C_LOTE.CV=1; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=1 | fim: C_LOTE.CV=1; em todas as 2 varreduras: confere | PASSA |
| GQ2.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GQ2.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |
| GQ3.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GQ3.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GQ3.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GQ3.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GQ3.5 | — | 2 | fim: C_LOTE.CV=2; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=2 | fim: C_LOTE.CV=2; em todas as 2 varreduras: confere | PASSA |
| GQ3.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=3, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=3, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GQ3.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=3; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=3 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=3; em todas as 2 varreduras: confere | PASSA |
| GQ4.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GQ4.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GQ4.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GQ4.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GQ4.5 | — | 2 | fim: C_LOTE.CV=3; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=3 | fim: C_LOTE.CV=3; em todas as 2 varreduras: confere | PASSA |
| GQ4.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=4, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=4, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GQ4.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=4; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=4 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=4; em todas as 2 varreduras: confere | PASSA |
| GQ5.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GQ5.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GQ5.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GQ5.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GQ5.5 | — | 2 | fim: C_LOTE.CV=4; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=4 | fim: C_LOTE.CV=4; em todas as 2 varreduras: confere | PASSA |
| GQ5.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=5, LOTE_OK=0, M_EST=1, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=5, LOTE_OK=0, M_EST=1, Y_VALV=0 | PASSA |
| GQ5.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=5; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=1, C_LOTE.CV=5 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=5; em todas as 2 varreduras: confere | PASSA |
| GQ6.1 | S_PECA=1 | 1 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | fim: TR01=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.ET=66 | PASSA |
| GQ6.2 | — | 59 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, M_EST=0, T_ENCH.Q=0 | fim: T_ENCH.ET=3960, T_ENCH.Q=0; em todas as 59 varreduras: confere | PASSA |
| GQ6.3 | — | 1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | fim: T_ENCH.ET=4000, T_ENCH.Q=1, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1 | PASSA |
| GQ6.4 | — | 1 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | fim: TR12=1, E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, Y_VALV=0, M_EST=1, T_ENCH.ET=0, T_ENCH.Q=0 | PASSA |
| GQ6.5 | — | 2 | fim: C_LOTE.CV=5; em todas as 2 varreduras: E0_TRANSP=0, E1_ENCHER=0, E2_LIBERAR=1, M_EST=1, TR20=0, C_LOTE.CV=5 | fim: C_LOTE.CV=5; em todas as 2 varreduras: confere | PASSA |
| GQ6.6 | S_PECA=0 | 1 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=6, LOTE_OK=1, M_EST=0, Y_VALV=0 | fim: TR20=1, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=6, LOTE_OK=1, M_EST=0, Y_VALV=0 | PASSA |
| GQ6.7 | — | 2 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=6; em todas as 2 varreduras: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=0, C_LOTE.CV=6 | fim: TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, C_LOTE.CV=6; em todas as 2 varreduras: confere | PASSA |
| G50a | S_PECA=1 | 3 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=0 | fim: E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, M_EST=0 | PASSA |
| G50 | parar a simulação | 1 | fim: M_EST=0, Y_VALV=0, LOTE_OK=0, TR01=0, TR12=0, TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, INIT=1, C_LOTE.CV=6, C_LOTE.QU=1, T_ENCH.ET=0 | fim: M_EST=0, Y_VALV=0, LOTE_OK=0, TR01=0, TR12=0, TR20=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, INIT=1, C_LOTE.CV=6, C_LOTE.QU=1, T_ENCH.ET=0 | PASSA |
| G51 | — | 1 | fim: LOTE_OK=1, TR01=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, Y_VALV=0, M_EST=0, C_LOTE.CV=6 | fim: LOTE_OK=1, TR01=0, E0_TRANSP=1, E1_ENCHER=0, E2_LIBERAR=0, Y_VALV=0, M_EST=0, C_LOTE.CV=6 | PASSA |
| G51b | RESET_LOTE=1 | 1 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, C_LOTE.CV=0, Y_VALV=1 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, C_LOTE.CV=0, Y_VALV=1 | PASSA |
| G51c | RESET_LOTE=0 | 29 | fim: T_ENCH.ET=1980, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | fim: T_ENCH.ET=1980, E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0 | PASSA |
| G52 | parar a simulação | 1 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=0, M_EST=0, T_ENCH.ET=0, C_LOTE.CV=0 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=0, M_EST=0, T_ENCH.ET=0, C_LOTE.CV=0 | PASSA |
| G53 | — | 1 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, T_ENCH.ET=66 | fim: E0_TRANSP=0, E1_ENCHER=1, E2_LIBERAR=0, Y_VALV=1, T_ENCH.ET=66 | PASSA |

## Programa C — caracterização do TOF

### SEQ-C-TOF — TOF de 2 s: ET decrescente e queda de Q

| Caso | Ação | Varreduras | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| C00 | — | 3 | fim: T_TOF.ET=0, T_TOF.Q=0; em todas as 3 varreduras: T_TOF.Q=0, Q_TOF=0 | fim: T_TOF.ET=0, T_TOF.Q=0; em todas as 3 varreduras: confere | PASSA |
| C01 | IN_TOF=1 | 5 | fim: T_TOF.ET=2000, T_TOF.Q=1; em todas as 5 varreduras: T_TOF.ET=2000, T_TOF.Q=1, Q_TOF=1 | fim: T_TOF.ET=2000, T_TOF.Q=1; em todas as 5 varreduras: confere | PASSA |
| C02 | IN_TOF=0 | 31 | fim: T_TOF.ET=0, T_TOF.Q=0, Q_TOF=0; varredura a varredura (31 leituras de T_TOF.ET, T_TOF.Q, Q_TOF) pela fórmula da especificação | fim: T_TOF.ET=0, T_TOF.Q=0, Q_TOF=0; 31/31 leituras conferem | PASSA |
| C03 | IN_TOF=1 | 1 | fim: T_TOF.ET=2000, T_TOF.Q=1 | fim: T_TOF.ET=2000, T_TOF.Q=1 | PASSA |
| C04 | IN_TOF=0 | 10 | fim: T_TOF.ET=1340, T_TOF.Q=1 | fim: T_TOF.ET=1340, T_TOF.Q=1 | PASSA |
| C05 | IN_TOF=1 | 1 | fim: T_TOF.ET=2000, T_TOF.Q=1 | fim: T_TOF.ET=2000, T_TOF.Q=1 | PASSA |
| C06 | IN_TOF=0 | 10 | fim: T_TOF.ET=1340, T_TOF.Q=1 | fim: T_TOF.ET=1340, T_TOF.Q=1 | PASSA |
| C07 | parar a simulação | 1 | fim: T_TOF.ET=0, T_TOF.Q=0, Q_TOF=0 | fim: T_TOF.ET=0, T_TOF.Q=0, Q_TOF=0 | PASSA |

## Invariantes (toda varredura com a simulação ligada)

| Invariante | Descrição | Violações |
|---|---|---|
| INV-A1 | MOTOR_DELAY = T1.Q | 0 |
| INV-A2 | T1.Q = 1 se e somente se T1.ET = 3000 | 0 |
| INV-A3 | LAMPADA = PISCA | 0 |
| INV-A4 | P_PECA nunca em 1 em duas varreduras seguidas | 0 |
| INV-A5 | LOTE_OK = (C_LOTE.CV ≥ 5) = C_LOTE.QU | 0 |
| INV-A6 | PISCA não inverte em duas varreduras seguidas | 0 |
| INV-A7 | C_LOTE.CV só sobe com P_PECA = 1, de 1 em 1, e só vai a 0 com RESET_LOTE = 1 | 0 |
| INV-B1 | exatamente uma etapa ativa (B: toda varredura depois da de inicialização) | 0 |
| INV-B2 | Y_VALV = E1_ENCHER · EMG_OK | 0 |
| INV-B3 | M_EST = EMG_OK · (E0_TRANSP·¬LOTE_OK + E2_LIBERAR) | 0 |
| INV-B4 | M_EST e Y_VALV nunca juntos | 0 |
| INV-B5 | LOTE_OK = (C_LOTE.CV ≥ 6) | 0 |
| INV-B6 | C_LOTE.CV só sobe com TR20 = 1, de 1 em 1, e só vai a 0 com RESET_LOTE = 1 | 0 |

## Mutantes

Cada mutante é o programa com um defeito proposital; os mesmos casos precisam reprová-lo.

| Mutante | Defeito | Deve reprovar em | Casos reprovados | Invariantes violadas | Resultado |
|---|---|---|---|---|---|
| MUT-A1 | permissivos só na saída: STOP e emergência não zeram o temporizador | T03, T03c, T04 | 7 (I03, T03, T03b, T03c, T04, T05c, T05d) | INV-A1 | REPROVADO COMO ESPERADO |
| MUT-A2 | pisca com um TON sem fase: PISCA inverte a cada varredura depois do 1º segundo | P01 | 2 (P01, PA0b) | INV-A6 | REPROVADO COMO ESPERADO |
| MUT-A3 | memória do valor anterior atualizada antes do pulso: nenhuma borda é vista | L1a | 80 (L1a, L1b, L1c, L2a, L2b, L2c, L3a, L3b, … (+72)) | — | REPROVADO COMO ESPERADO |
| MUT-A4 | contagem por nível: soma 1 a cada varredura com S_PECA = 1 | L1b, L3b | 87 (L1b, L1c, L2a, L2b, L2c, L3a, L3b, L3c, … (+79)) | INV-A5, INV-A7 | REPROVADO COMO ESPERADO |
| MUT-A5 | LOTE_OK por igualdade (EQU): apaga quando passa do lote | L6a | 2 (L6a, L6b) | INV-A5 | REPROVADO COMO ESPERADO |
| MUT-A6 | zeragem escrita depois do contador: a contagem simultânea passa na frente | R04 | 4 (R02, R03, R04, R05a) | INV-A7 | REPROVADO COMO ESPERADO |
| MUT-A7 | CTU alimentado direto pelo nível de S_PECA: só erra ao religar a simulação com o sensor em 1 | PA2 (e só nele) | 1 (PA2) | INV-A7 | REPROVADO COMO ESPERADO |
| MUT-B1 | receptividade de E0→E1 sem o contato da etapa E0: recipiente no sensor reativa E1 em E2 | G06 | 125 (G06, G07, G08, G09.1, G09.2, G09.3, G09.4, G09.5, … (+117)) | INV-B1, INV-B4 | REPROVADO COMO ESPERADO |
| MUT-B2 | M_EST escrita em duas bobinas: a de E2 apaga a de E0 | G01 | 34 (G01, G07, G08, G09.6, G09.7, G12, G27, GL1.6, … (+26)) | INV-B3 | REPROVADO COMO ESPERADO |
| MUT-B3 | válvula sem EMG_OK: continua aberta na emergência | G23 | 2 (G23, G23b) | INV-B2 | REPROVADO COMO ESPERADO |
| MUT-B4 | zeragem escrita depois do contador | G40, G41 | 10 (G11, G12, G12a, G12b, G12c, G40, G41, G51b, … (+2)) | INV-B6 | REPROVADO COMO ESPERADO |
| MUT-B5 | lote calculado depois das transições e etapas (ordem ingênua) | G11, G51 | 7 (G11, G12, G12a, G12b, G12c, G51, G51c) | — | REPROVADO COMO ESPERADO |

## Arquivos e hashes (SHA-256)

- `p07-temporizacao-contagem.json`: `a361d89b47c48c177c74b34c44f2a7b418377bb50b19239f73f7bc10e1748e8e`
- `p07-enchimento-grafcet.json`: `6339b6a66de3df54d858add170fda7d1cd4d6ba886122c243bb880ccc596980e`
- `caracterizacao.json`: `75110eb2dfcf51d4a28cbddd7768afd469e695c2eaf8880f013a52607b7927bf`
- `casos.json` (ferramental): `5a8c14ada2cca5495671f00b05e99c70d372e5077b84d5fbd9d068642b6e4f52`
