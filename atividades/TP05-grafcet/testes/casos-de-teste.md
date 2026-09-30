# TP05 — Casos de teste dos GRAFCETs

Gerado em 2026-09-30T03:44:05+00:00 (UTC) por `simulacao/verifica_tp05.py` a partir de `grafcet.drawio`.

| Arquivo | SHA-256 |
|---|---|
| `grafcet.drawio` | `39ba03dfcb001ef13a6a8f987515d882d4419cf5536edcaf89c8f1dfc70f469c` |
| `simulacao/grafcet_interpreta.py` | `336521a15f7a3ddbd98b26624f59b34656d83eaaba3e8cab92f7b34d3437da60` |
| `simulacao/verifica_tp05.py` | `c330985bf3f3fc769d0b2a64fa4a4da878b3065ffa3efe0b02f09cdcf856030b` |

## Resumo

**77 de 77 casos passam** (0 falhas); verificações estáticas de página: 0 achados; invariantes: 0 violações.

| Grupo | Página | Casos | Passam | Falham |
|---|---|---|---|---|
| S | 2 | 14 | 14 | 0 |
| M | 1 | 14 | 14 | 0 |
| P | 3 | 19 | 19 | 0 |
| C | 4 | 20 | 20 | 0 |
| ES (página) | 1–4 | 4 | 4 | 0 |
| IN (invariantes) | 1–4 | 6 | 6 | 0 |

| Categoria (CSV) | Casos | Passam |
|---|---|---|
| normal | 27 | 27 |
| limite | 14 | 14 |
| invariante | 9 | 9 |
| falha | 8 | 8 |
| estatico | 7 | 7 |
| emergencia | 9 | 9 |
| sincronizacao | 3 | 3 |

## Método

- **Esperado**: foi fixado antes da execução, na especificação de projeto deste trabalho (S01–S04 reproduzem a tabela de referência do enunciado; os demais cenários foram definidos pelo autor) e codificado como texto literal no verificador.
- **Obtido**: marcação ativa e saídas observadas após executar o cenário no `grafcet.drawio` entregue, com o interpretador `simulacao/grafcet_interpreta.py` (parser do XML do draw.io + regras de evolução IEC 60848 + busca de situação estável + base de tempo de 0,1 s em décimos inteiros).
- **Marcação inicial** "em Ek": obtida levando o modelo desde a situação inicial até Ek com o preparo indicado; o instante (em décimos) em que o cenário começa é registrado na coluna.
- Entradas são níveis mantidos até o cenário alterá-las; na inicialização valem os estados seguros das tabelas de E/S (misturador `NIVEL_BAIXO=1`; porta `FC_FECHADA=1`; esteira `FC_RET_A=FC_RET_B=1`).
- `N s/Xk` é verdadeira quando a etapa k acumula ≥ 10·N décimos; "7,9 s" leva a 79 décimos e observa; "8,0 s" leva a 80 e observa.
- Resultado PASSA quando a leitura estrutural do esperado (marcação, saídas citadas, "demais 0", sequência de marcações, disparos, etapa transitória) coincide com o obtido.

## Tabela completa

| ID | Pág. | Grupo | Descrição | Marcação inicial | Entradas e tempo | Esperado | Obtido | Resultado |
|---|---|---|---|---|---|---|---|---|
| S01 | 2 | normal | E0, 7,9 s | E0 (t=0 décimos) | 79 décimos (7,9 s) | E0; VERMELHO=1 | E0; VERMELHO=1, VERDE=0, AMARELO=0 | PASSA |
| S02 | 2 | normal | E0, 8,0 s | E0 (t=0 décimos) | 80 décimos (8,0 s) | E1; VERDE=1 | E1; VERMELHO=0, VERDE=1, AMARELO=0 | PASSA |
| S03 | 2 | normal | E1, 10,0 s | E1 (t=80 décimos; preparo: 80 décimos (8,0 s)) | 100 décimos (10,0 s) | E2; AMARELO=1 | E2; VERMELHO=0, VERDE=0, AMARELO=1 | PASSA |
| S04 | 2 | normal | E2, 3,0 s | E2 (t=180 décimos; preparo: 180 décimos (18,0 s)) | 30 décimos (3,0 s) | E0; VERMELHO=1 | E0; VERMELHO=1, VERDE=0, AMARELO=0 | PASSA |
| S05 | 2 | limite | E0, 8,1 s | E0 (t=0 décimos) | 81 décimos (8,1 s) | E1 | E1; VERMELHO=0, VERDE=1, AMARELO=0 | PASSA |
| S06 | 2 | limite | E1, 9,9 s | E1 (t=80 décimos; preparo: 80 décimos (8,0 s)) | 99 décimos (9,9 s) | E1 | E1; VERMELHO=0, VERDE=1, AMARELO=0 | PASSA |
| S07 | 2 | limite | E1, 10,1 s | E1 (t=80 décimos; preparo: 80 décimos (8,0 s)) | 101 décimos (10,1 s) | E2 | E2; VERMELHO=0, VERDE=0, AMARELO=1 | PASSA |
| S08 | 2 | limite | E2, 2,9 s | E2 (t=180 décimos; preparo: 180 décimos (18,0 s)) | 29 décimos (2,9 s) | E2 | E2; VERMELHO=0, VERDE=0, AMARELO=1 | PASSA |
| S09 | 2 | limite | E2, 3,1 s | E2 (t=180 décimos; preparo: 180 décimos (18,0 s)) | 31 décimos (3,1 s) | E0 | E0; VERMELHO=1, VERDE=0, AMARELO=0 | PASSA |
| S10 | 2 | normal | E0, 21,0 s (ciclo completo) | E0 (t=0 décimos) | 210 décimos (21,0 s) | E0; sequência E0→E1→E2→E0 com disparos em 8,0 / 18,0 / 21,0 s | E0; VERMELHO=1, VERDE=0, AMARELO=0 [sequência E0→E1→E2→E0; disparos T0 em 8,0 s, T1 em 18,0 s, T2 em 21,0 s] | PASSA |
| S11 | 2 | normal | inicialização, 0 s | inicialização (t=0 décimos) | — | E0 ativa, VERMELHO=1, demais 0 (saídas perigosas desativadas na inicialização) | E0; VERMELHO=1, VERDE=0, AMARELO=0 | PASSA |
| S12 | 2 | invariante | ciclo de 21 s, a cada 0,1 s | ciclo de 21 s | — | exatamente uma lâmpada em 1 | 2577 eventos (décimos e leituras de entrada) verificados; 0 violações | PASSA |
| S13 | 2 | normal | percurso manual da Atividade 27, passos 0–3 | tabela da página 5 | — | traço idêntico à tabela da página 5 | traço executado: 0 / E0 / tempo < 8 s / nenhuma / E0 \| 1 / E0 / tempo = 8 s / T0 / E1 \| 2 / E1 / tempo = 10 s / T1 / E2 \| 3 / E2 / tempo = 3 s / T2 / E0; página 5 (25 células agrupadas por geometria): 5 linhas, 4/4 linhas literais encontradas | PASSA |
| S14 | 2 | limite | percursos de fronteira na página 5 | tabela da página 5 (linhas 0–5) | entradas e tempo de cada linha da tabela | tabela «Fronteiras temporais (semáforo)» presente na página 5 e confirmada pela execução: 0 \| E0 \| tempo = 7,9 s \| nenhuma \| E0; 1 \| E0 \| tempo = 8,1 s \| T0 \| E1; 2 \| E1 \| tempo = 9,9 s \| nenhuma \| E1; 3 \| E1 \| tempo = 10,1 s \| T1 \| E2; 4 \| E2 \| tempo = 2,9 s \| nenhuma \| E2; 5 \| E2 \| tempo = 3,1 s \| T2 \| E0 | execução: 0: E0 + 7,9 s → E0, nenhuma \| 1: E0 + 8,1 s → E1, T0 aos 8,0 s \| 2: E1 + 9,9 s → E1, nenhuma \| 3: E1 + 10,1 s → E2, T1 aos 10,0 s \| 4: E2 + 2,9 s → E2, nenhuma \| 5: E2 + 3,1 s → E0, T2 aos 3,0 s; página 5 (35 células agrupadas por geometria): 6/6 linhas literais, cabeçalho: sim, título: sim | PASSA |
| M01 | 1 | normal | inicialização | inicialização (t=0 décimos) | — | E0; LAMP_PRONTO=1, demais 0 | E0; LAMP_PRONTO=1, V_ENT=0, M_AGIT=0, V_DRENO=0, ALARME=0 | PASSA |
| M02 | 1 | normal | START=1 com NIVEL_BAIXO=0 | E0 (t=0 décimos) | NIVEL_BAIXO=0, START=1; 10 décimos (1,0 s) | permanece E0 | E0; LAMP_PRONTO=1, V_ENT=0, M_AGIT=0, V_DRENO=0, ALARME=0 | PASSA |
| M03 | 1 | normal | START=1 ∧ NIVEL_BAIXO=1 | E0 (t=0 décimos) | START=1 | E1; V_ENT=1, LAMP_PRONTO=0 | E1; LAMP_PRONTO=0, V_ENT=1, M_AGIT=0, V_DRENO=0, ALARME=0 | PASSA |
| M04 | 1 | normal | em E1, NIVEL_ALTO=1 (e NIVEL_BAIXO=0) | em E1 (t=0 décimos; preparo: START=1; START=0) | NIVEL_ALTO=1, NIVEL_BAIXO=0 | E2; M_AGIT=1, V_ENT=0 | E2; LAMP_PRONTO=0, V_ENT=0, M_AGIT=1, V_DRENO=0, ALARME=0 | PASSA |
| M05 | 1 | normal | em E2, 29,9 s | em E2 (t=0 décimos; preparo: START=1; START=0; NIVEL_ALTO=1, NIVEL_BAIXO=0) | 299 décimos (29,9 s) | E2 | E2; LAMP_PRONTO=0, V_ENT=0, M_AGIT=1, V_DRENO=0, ALARME=0 | PASSA |
| M06 | 1 | normal | em E2, 30,0 s | em E2 (t=0 décimos; preparo: START=1; START=0; NIVEL_ALTO=1, NIVEL_BAIXO=0) | 300 décimos (30,0 s) | E3; V_DRENO=1 | E3; LAMP_PRONTO=0, V_ENT=0, M_AGIT=0, V_DRENO=1, ALARME=0 | PASSA |
| M07 | 1 | normal | em E3, NIVEL_BAIXO=1 | em E3 (t=300 décimos; preparo: START=1; START=0; NIVEL_ALTO=1, NIVEL_BAIXO=0; 300 décimos (30,0 s)) | NIVEL_BAIXO=1 | E0; ciclo fechado | E0; LAMP_PRONTO=1, V_ENT=0, M_AGIT=0, V_DRENO=0, ALARME=0 [sequência E0→E1→E2→E3→E0] | PASSA |
| M08 | 1 | falha | em E1, NIVEL_ALTO=0 por 119,9 s | em E1 (t=0 décimos; preparo: START=1; START=0) | NIVEL_ALTO=0; 1199 décimos (119,9 s) | E1 | E1; LAMP_PRONTO=0, V_ENT=1, M_AGIT=0, V_DRENO=0, ALARME=0 | PASSA |
| M09 | 1 | falha | em E1, NIVEL_ALTO=0 por 120,0 s | em E1 (t=0 décimos; preparo: START=1; START=0) | NIVEL_ALTO=0; 1200 décimos (120,0 s) | E4; ALARME=1, V_ENT=0 | E4; LAMP_PRONTO=0, V_ENT=0, M_AGIT=0, V_DRENO=0, ALARME=1 | PASSA |
| M10 | 1 | normal | em E4, RESET=0 | em E4 (t=1200 décimos; preparo: START=1; START=0; NIVEL_ALTO=0; 1200 décimos (120,0 s)) | RESET=0; 10 décimos (1,0 s) | permanece E4 | E4; LAMP_PRONTO=0, V_ENT=0, M_AGIT=0, V_DRENO=0, ALARME=1 | PASSA |
| M11 | 1 | normal | em E4, RESET=1 | em E4 (t=1200 décimos; preparo: START=1; START=0; NIVEL_ALTO=0; 1200 décimos (120,0 s)) | RESET=1 | E0 | E0; LAMP_PRONTO=1, V_ENT=0, M_AGIT=0, V_DRENO=0, ALARME=0 | PASSA |
| M12 | 1 | limite | em E1, NIVEL_ALTO=1 aos 119,9 s | em E1 (t=0 décimos; preparo: START=1; START=0) | NIVEL_ALTO=0; 1199 décimos (119,9 s); NIVEL_ALTO=1, NIVEL_BAIXO=0 | E2 (caminho normal vence antes do tempo esgotar) | E2; LAMP_PRONTO=0, V_ENT=0, M_AGIT=1, V_DRENO=0, ALARME=0 | PASSA |
| M13 | 1 | estatico | seleção em E1 | — | — | T1 e T4 exclusivas em todas as combinações | E1: T1/T4 sobre (NIVEL_ALTO, 120 s/X1) = 4 combinações, 0 violações | PASSA |
| M14 | 1 | falha | percurso de falha na página 5 | tabela da página 5 (linhas 0–3) | entradas e tempo de cada linha da tabela | tabela «Falha (misturador, página 1)» presente na página 5 e confirmada pela execução: 0 \| E1 \| ¬NIVEL_ALTO, tempo = 119,9 s \| nenhuma \| E1; 1 \| E1 \| ¬NIVEL_ALTO, tempo = 120 s \| T4 \| E4; 2 \| E4 \| RESET = 0 \| nenhuma \| E4; 3 \| E4 \| RESET = 1 \| T5 \| E0 | execução: 0: E1 + NIVEL_ALTO=0; 119,9 s → E1, nenhuma \| 1: E1 + NIVEL_ALTO=0; 120,0 s → E4, T4 aos 120,0 s \| 2: E4 + RESET=0; observado por 1,0 s → E4, nenhuma \| 3: E4 + RESET=1; observado por 1,0 s → E0, T5 aos 0,0 s; página 5 (25 células agrupadas por geometria): 4/4 linhas literais, cabeçalho: sim, título: sim | PASSA |
| P01 | 3 | normal | inicialização (FC_FECHADA=1) | inicialização (t=0 décimos) | — | E0; M_ABRIR=M_FECHAR=LAMP_EMERG=0 | E0; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=0 | PASSA |
| P02 | 3 | normal | PRESENCA=1 | E0 (t=0 décimos) | PRESENCA=1 | E1; M_ABRIR=1 | E1; M_ABRIR=1, M_FECHAR=0, LAMP_EMERG=0 | PASSA |
| P03 | 3 | normal | em E1, FC_ABERTA=1 (FC_FECHADA=0) | em E1 (t=0 décimos; preparo: PRESENCA=1) | FC_ABERTA=1, FC_FECHADA=0 | E2; M_ABRIR=0 | E2; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=0 | PASSA |
| P04 | 3 | limite | em E2, PRESENCA=0, 4,9 s | em E2 (t=0 décimos; preparo: PRESENCA=1; FC_ABERTA=1, FC_FECHADA=0) | PRESENCA=0; 49 décimos (4,9 s) | E2 | E2; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=0 | PASSA |
| P05 | 3 | limite | em E2, PRESENCA=0, 5,0 s | em E2 (t=0 décimos; preparo: PRESENCA=1; FC_ABERTA=1, FC_FECHADA=0) | PRESENCA=0; 50 décimos (5,0 s) | E3; M_FECHAR=1 | E3; M_ABRIR=0, M_FECHAR=1, LAMP_EMERG=0 | PASSA |
| P06 | 3 | normal | em E2, PRESENCA=1 aos 5,0 s e além | em E2 (t=0 décimos; preparo: PRESENCA=1; FC_ABERTA=1, FC_FECHADA=0) | PRESENCA=1; 50 décimos (5,0 s); 100 décimos (10,0 s) | permanece E2 (não fecha com zona ocupada) | E2; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=0 | PASSA |
| P07 | 3 | normal | em E3, FC_FECHADA=1, PRESENCA=0 | em E3 (t=50 décimos; preparo: PRESENCA=1; FC_ABERTA=1, FC_FECHADA=0; PRESENCA=0; 50 décimos (5,0 s); FC_ABERTA=0) | FC_FECHADA=1, PRESENCA=0 | E0 | E0; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=0 | PASSA |
| P08 | 3 | falha | em E3, PRESENCA=1 antes de FC_FECHADA | em E3 (t=50 décimos; preparo: PRESENCA=1; FC_ABERTA=1, FC_FECHADA=0; PRESENCA=0; 50 décimos (5,0 s); FC_ABERTA=0) | PRESENCA=1 | E1; M_FECHAR=0, M_ABRIR=1 (reabertura) | E1; M_ABRIR=1, M_FECHAR=0, LAMP_EMERG=0 | PASSA |
| P09 | 3 | emergencia | EMERG=1 em E0 | em E0 (t=0 décimos) | EMERG=1 | E4; M_ABRIR=M_FECHAR=0, LAMP_EMERG=1 | E4; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=1 | PASSA |
| P10 | 3 | emergencia | EMERG=1 em E1 | em E1 (t=0 décimos; preparo: PRESENCA=1) | EMERG=1 | E4; M_ABRIR=M_FECHAR=0, LAMP_EMERG=1 | E4; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=1 | PASSA |
| P11 | 3 | emergencia | EMERG=1 em E2 | em E2 (t=0 décimos; preparo: PRESENCA=1; FC_ABERTA=1, FC_FECHADA=0) | EMERG=1 | E4; M_ABRIR=M_FECHAR=0, LAMP_EMERG=1 | E4; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=1 | PASSA |
| P12 | 3 | emergencia | EMERG=1 em E3 | em E3 (t=50 décimos; preparo: PRESENCA=1; FC_ABERTA=1, FC_FECHADA=0; PRESENCA=0; 50 décimos (5,0 s); FC_ABERTA=0) | EMERG=1 | E4; M_ABRIR=M_FECHAR=0, LAMP_EMERG=1 | E4; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=1 | PASSA |
| P13 | 3 | emergencia | em E4, PRESENCA=1, EMERG=1 | em E4 (t=0 décimos; preparo: EMERG=1) | PRESENCA=1, EMERG=1; 10 décimos (1,0 s) | permanece E4 (dominância) | E4; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=1 | PASSA |
| P14 | 3 | emergencia | em E4, RESET=1 com EMERG=1 | em E4 (t=0 décimos; preparo: EMERG=1) | RESET=1, EMERG=1; 10 décimos (1,0 s) | permanece E4 (rearme exige emergência liberada) | E4; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=1 | PASSA |
| P15 | 3 | emergencia | em E4 com FC_FECHADA=1, EMERG=0, RESET=1 | em E4 (t=0 décimos; preparo: EMERG=1) | FC_FECHADA=1, EMERG=0, RESET=1 | E0 direto; M_FECHAR nunca foi 1 (etapa 3 transitória) | E0; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=0 [M_FECHAR nunca foi 1; etapa 3 transitória (rodadas [['T9'], ['T3']])] | PASSA |
| P16 | 3 | emergencia | em E4 com porta aberta (FC_FECHADA=0), PRESENCA=0, EMERG=0, RESET=1 | em E4 (t=0 décimos; preparo: EMERG=1; FC_FECHADA=0) | PRESENCA=0, EMERG=0, RESET=1; FC_FECHADA=1 | E3; M_FECHAR=1; depois FC_FECHADA=1 → E0 | E3; M_ABRIR=0, M_FECHAR=1, LAMP_EMERG=0 → depois: E0; M_ABRIR=0, M_FECHAR=0, LAMP_EMERG=0 | PASSA |
| P17 | 3 | emergencia | em E4 com porta aberta e PRESENCA=1, EMERG=0, RESET=1 | em E4 (t=0 décimos; preparo: EMERG=1; FC_FECHADA=0) | PRESENCA=1, EMERG=0, RESET=1 | E1 (reabre por segurança) | E1; M_ABRIR=1, M_FECHAR=0, LAMP_EMERG=0 | PASSA |
| P18 | 3 | invariante | todos os cenários | todos os cenários | — | M_ABRIR ∧ M_FECHAR nunca | 482 eventos (décimos e leituras de entrada) verificados; 0 violações | PASSA |
| P19 | 3 | estatico | seleções em E0–E4 | — | — | exclusivas em todas as combinações | E0: T0/T5 sobre (PRESENCA, EMERG) = 4 combinações, 0 violações; E1: T1/T6 sobre (FC_ABERTA, EMERG) = 4 combinações, 0 violações; E2: T2/T7 sobre (5 s/X2, PRESENCA, EMERG) = 8 combinações, 0 violações; E3: T3/T4/T8 sobre (FC_FECHADA, PRESENCA, EMERG) = 8 combinações, 0 violações; E4: sem seleção (uma única transição de saída) | PASSA |
| C01 | 4 | normal | inicialização (FC_RET_A=FC_RET_B=1) | inicialização (t=0 décimos) | — | E0; M_EST=1, Y_A=Y_B=ALARME=0 | E0; M_EST=1, Y_A=0, Y_B=0, ALARME=0 | PASSA |
| C02 | 4 | normal | S_PECA=1 | E0 (t=0 décimos) | S_PECA=1 | E1; M_EST=0 | E1; M_EST=0, Y_A=0, Y_B=0, ALARME=0 | PASSA |
| C03 | 4 | limite | em E1, TIPO_A=1, 0,4 s | em E1 (t=0 décimos; preparo: S_PECA=1) | TIPO_A=1; 4 décimos (0,4 s) | E1 | E1; M_EST=0, Y_A=0, Y_B=0, ALARME=0 | PASSA |
| C04 | 4 | limite | em E1, TIPO_A=1, 0,5 s | em E1 (t=0 décimos; preparo: S_PECA=1) | TIPO_A=1; 5 décimos (0,5 s) | E2; Y_A=1 | E2; M_EST=0, Y_A=1, Y_B=0, ALARME=0 | PASSA |
| C05 | 4 | normal | em E1, TIPO_B=1, 0,5 s | em E1 (t=0 décimos; preparo: S_PECA=1) | TIPO_B=1; 5 décimos (0,5 s) | E3; Y_B=1 | E3; M_EST=0, Y_A=0, Y_B=1, ALARME=0 | PASSA |
| C06 | 4 | falha | em E1, TIPO_A=TIPO_B=1 | em E1 (t=0 décimos; preparo: S_PECA=1) | TIPO_A=1, TIPO_B=1 | E7 imediato; ALARME=1, Y_A=Y_B=M_EST=0 | E7; M_EST=0, Y_A=0, Y_B=0, ALARME=1 [T3 disparou no mesmo instante (0 décimos)] | PASSA |
| C07 | 4 | limite | em E1, TIPO_A=TIPO_B=0, 1,9 s | em E1 (t=0 décimos; preparo: S_PECA=1) | TIPO_A=0, TIPO_B=0; 19 décimos (1,9 s) | E1 | E1; M_EST=0, Y_A=0, Y_B=0, ALARME=0 | PASSA |
| C08 | 4 | falha | em E1, TIPO_A=TIPO_B=0, 2,0 s | em E1 (t=0 décimos; preparo: S_PECA=1) | TIPO_A=0, TIPO_B=0; 20 décimos (2,0 s) | E7 | E7; M_EST=0, Y_A=0, Y_B=0, ALARME=1 | PASSA |
| C09 | 4 | normal | em E2, FC_AV_A=1 (FC_RET_A=0) | em E2 (t=5 décimos; preparo: S_PECA=1; TIPO_A=1; 5 décimos (0,5 s)) | FC_AV_A=1, FC_RET_A=0 | E4; Y_A=0, M_EST=0 | E4; M_EST=0, Y_A=0, Y_B=0, ALARME=0 | PASSA |
| C10 | 4 | limite | em E4, 0,2 s | em E4 (t=5 décimos; preparo: S_PECA=1; TIPO_A=1; 5 décimos (0,5 s); FC_AV_A=1, FC_RET_A=0) | 2 décimos (0,2 s) | E4 | E4; M_EST=0, Y_A=0, Y_B=0, ALARME=0 | PASSA |
| C11 | 4 | limite | em E4, 0,3 s | em E4 (t=5 décimos; preparo: S_PECA=1; TIPO_A=1; 5 décimos (0,5 s); FC_AV_A=1, FC_RET_A=0) | 3 décimos (0,3 s) | E5; M_EST=0, Y_A=Y_B=0 — esteira parada até o retorno | E5; M_EST=0, Y_A=0, Y_B=0, ALARME=0 | PASSA |
| C12 | 4 | sincronizacao | em E5, FC_RET_A=1 com S_PECA=1 | em E5 (t=8 décimos; preparo: S_PECA=1; TIPO_A=1; 5 décimos (0,5 s); FC_AV_A=1, FC_RET_A=0; 3 décimos (0,3 s)) | FC_RET_A=1, FC_AV_A=0 | E6; M_EST=1 — retorno confirmado libera | E6; M_EST=1, Y_A=0, Y_B=0, ALARME=0 | PASSA |
| C13 | 4 | normal | em E6, S_PECA=0 | em E6 (t=8 décimos; preparo: S_PECA=1; TIPO_A=1; 5 décimos (0,5 s); FC_AV_A=1, FC_RET_A=0; 3 décimos (0,3 s); FC_RET_A=1, FC_AV_A=0) | S_PECA=0 | E0; M_EST=1 | E0; M_EST=1, Y_A=0, Y_B=0, ALARME=0 | PASSA |
| C14 | 4 | sincronizacao | em E5 com FC_RET_A=0, S_PECA=0; depois FC_RET_A=1 | em E5 (t=8 décimos; preparo: S_PECA=1; TIPO_A=1; 5 décimos (0,5 s); FC_AV_A=1, FC_RET_A=0; 3 décimos (0,3 s)) | S_PECA=0; 10 décimos (1,0 s); FC_RET_A=1, FC_AV_A=0 | permanece E5, M_EST=0 — sem retorno confirmado a esteira não religa mesmo com a estação vazia; depois FC_RET_A=1 → E6 transitória → E0 na mesma evolução | E5; M_EST=0, Y_A=0, Y_B=0, ALARME=0 → depois: E0; M_EST=1, Y_A=0, Y_B=0, ALARME=0 [disparos ['T8', 'T9'] na mesma evolução; E6 transitória; E6 nunca esteve ativa em situação estável (ações de E6 não executadas)] | PASSA |
| C15 | 4 | normal | caminho B completo (E3 → E4 → E5 → E6 → E0) | E0 (t=0 décimos) | S_PECA=1; TIPO_B=1; 5 décimos (0,5 s); FC_AV_B=1, FC_RET_B=0; 3 décimos (0,3 s); FC_RET_B=1, FC_AV_B=0; S_PECA=0 | ciclo fechado | E0; M_EST=1, Y_A=0, Y_B=0, ALARME=0 [sequência E0→E1→E3→E4→E5→E6→E0] | PASSA |
| C16 | 4 | falha | em E7, RESET=1 com S_PECA=1 | em E7 (t=0 décimos; preparo: S_PECA=1; TIPO_A=1, TIPO_B=1) | RESET=1, S_PECA=1; 10 décimos (1,0 s) | permanece E7 | E7; M_EST=0, Y_A=0, Y_B=0, ALARME=1 | PASSA |
| C17 | 4 | falha | em E7, RESET=1 com S_PECA=0 | em E7 (t=0 décimos; preparo: S_PECA=1; TIPO_A=1, TIPO_B=1) | RESET=1, S_PECA=0 | E0 | E0; M_EST=1, Y_A=0, Y_B=0, ALARME=0 | PASSA |
| C18 | 4 | invariante | todos os cenários | todos os cenários | — | Y_A ∧ Y_B nunca; M_EST=0 sempre que Y_A ∨ Y_B; M_EST=1 somente com FC_RET_A ∧ FC_RET_B | 203 eventos (décimos e leituras de entrada) verificados; 0 violações | PASSA |
| C19 | 4 | estatico | seleção em E1 | — | — | T1–T4 exclusivas nas 16 combinações de (TIPO_A,TIPO_B,0,5 s/X1,2 s/X1) | E1: T1/T2/T3/T4 sobre (0,5 s/X1, TIPO_A, TIPO_B, 2 s/X1) = 16 combinações, 0 violações | PASSA |
| C20 | 4 | sincronizacao | ciclo A completo, traço | E0 (t=0 décimos) | S_PECA=1; TIPO_A=1; 5 décimos (0,5 s); FC_AV_A=1, FC_RET_A=0; 3 décimos (0,3 s); FC_RET_A=1, FC_AV_A=0; S_PECA=0 | T8 dispara antes de T9 em todo ciclo; nenhum disparo de T9 sem T8 no mesmo ciclo | E0; M_EST=1, Y_A=0, Y_B=0, ALARME=0 [sequência E0→E1→E2→E4→E5→E6→E0; disparos T0 → T1 → T5 → T7 → T8 → T9: T8 antes de T9 em 1 ciclo(s)] | PASSA |
| IN1 | 1 | invariante | todos os cenários da página | todos os cenários | — | nenhuma etapa ativa tem TAG = 0 enquanto outra ativa tem TAG = 1 | 11799 eventos (décimos e leituras de entrada) verificados; 0 violações | PASSA |
| IN2 | 2 | invariante | todos os cenários da página | todos os cenários | — | nenhuma etapa ativa tem TAG = 0 enquanto outra ativa tem TAG = 1 | 2577 eventos (décimos e leituras de entrada) verificados; 0 violações | PASSA |
| IN3 | 3 | invariante | todos os cenários da página | todos os cenários | — | nenhuma etapa ativa tem TAG = 0 enquanto outra ativa tem TAG = 1 | 482 eventos (décimos e leituras de entrada) verificados; 0 violações | PASSA |
| IN4 | 4 | invariante | todos os cenários da página | todos os cenários | — | nenhuma etapa ativa tem TAG = 0 enquanto outra ativa tem TAG = 1 | 203 eventos (décimos e leituras de entrada) verificados; 0 violações | PASSA |
| IN5 | 3 | invariante | todos os cenários da página | todos os cenários | — | em E4 as duas (M_ABRIR, M_FECHAR) em 0 | 482 eventos (décimos e leituras de entrada) verificados; 0 violações | PASSA |
| IN6 | 4 | invariante | todos os cenários da página | todos os cenários | — | M_EST = 1 ⇒ FC_RET_A ∧ FC_RET_B (a esteira só anda com os dois desviadores recolhidos) | 203 eventos (décimos e leituras de entrada) verificados; 0 violações | PASSA |
| ES1 | 1 | estatico | verificações estáticas do interpretador (inicial única, ids numéricos únicos, receptividades válidas, arcos admitidos, exclusividade, alcançabilidade, geometria) | — | — | sem achados | 0 achados | PASSA |
| ES2 | 2 | estatico | verificações estáticas do interpretador (inicial única, ids numéricos únicos, receptividades válidas, arcos admitidos, exclusividade, alcançabilidade, geometria) | — | — | sem achados | 0 achados | PASSA |
| ES3 | 3 | estatico | verificações estáticas do interpretador (inicial única, ids numéricos únicos, receptividades válidas, arcos admitidos, exclusividade, alcançabilidade, geometria) | — | — | sem achados | 0 achados | PASSA |
| ES4 | 4 | estatico | verificações estáticas do interpretador (inicial única, ids numéricos únicos, receptividades válidas, arcos admitidos, exclusividade, alcançabilidade, geometria) | — | — | sem achados | 0 achados | PASSA |

## Verificações estáticas do interpretador

### Página 1 — A23 Misturador

- Etapas: E0*, E1, E2, E3, E4 (* inicial); transições: 6; entradas: START, NIVEL_BAIXO, NIVEL_ALTO, RESET; saídas: LAMP_PRONTO, V_ENT, M_AGIT, V_DRENO, ALARME.
- Achados: 0
- Alcançabilidade: alcançáveis [0, 1, 2, 3, 4]; não alcançáveis []; sem retorno []; becos [].

| Etapa | Transições | Átomos | Combinações | Violações |
|---|---|---|---|---|
| E1 | T1, T4 | NIVEL_ALTO, 120 s/X1 | 4 | 0 |

| Transição | Anteriores | Posteriores | Receptividade |
|---|---|---|---|
| T0 | [0] | [1] | `START ∧ NIVEL_BAIXO` |
| T1 | [1] | [2] | `NIVEL_ALTO` |
| T2 | [2] | [3] | `30 s/X2` |
| T3 | [3] | [0] | `NIVEL_BAIXO` |
| T4 | [1] | [4] | `¬NIVEL_ALTO ∧ 120 s/X1` |
| T5 | [4] | [0] | `RESET` |

### Página 2 — A24 Semaforo

- Etapas: E0*, E1, E2 (* inicial); transições: 3; entradas: —; saídas: VERMELHO, VERDE, AMARELO.
- Achados: 0
- Alcançabilidade: alcançáveis [0, 1, 2]; não alcançáveis []; sem retorno []; becos [].

| Transição | Anteriores | Posteriores | Receptividade |
|---|---|---|---|
| T0 | [0] | [1] | `8 s/X0` |
| T1 | [1] | [2] | `10 s/X1` |
| T2 | [2] | [0] | `3 s/X2` |

### Página 3 — A25 Porta automatica

- Etapas: E0*, E1, E2, E3, E4 (* inicial); transições: 10; entradas: PRESENCA, EMERG, FC_ABERTA, FC_FECHADA, RESET; saídas: M_ABRIR, M_FECHAR, LAMP_EMERG.
- Achados: 0
- Alcançabilidade: alcançáveis [0, 1, 2, 3, 4]; não alcançáveis []; sem retorno []; becos [].

| Etapa | Transições | Átomos | Combinações | Violações |
|---|---|---|---|---|
| E0 | T0, T5 | PRESENCA, EMERG | 4 | 0 |
| E1 | T1, T6 | FC_ABERTA, EMERG | 4 | 0 |
| E2 | T2, T7 | 5 s/X2, PRESENCA, EMERG | 8 | 0 |
| E3 | T3, T4, T8 | FC_FECHADA, PRESENCA, EMERG | 8 | 0 |

| Transição | Anteriores | Posteriores | Receptividade |
|---|---|---|---|
| T0 | [0] | [1] | `PRESENCA ∧ ¬EMERG` |
| T1 | [1] | [2] | `FC_ABERTA ∧ ¬EMERG` |
| T2 | [2] | [3] | `5 s/X2 ∧ ¬PRESENCA ∧ ¬EMERG` |
| T3 | [3] | [0] | `FC_FECHADA ∧ ¬PRESENCA ∧ ¬EMERG` |
| T4 | [3] | [1] | `PRESENCA ∧ ¬EMERG` |
| T5 | [0] | [4] | `EMERG` |
| T6 | [1] | [4] | `EMERG` |
| T7 | [2] | [4] | `EMERG` |
| T8 | [3] | [4] | `EMERG` |
| T9 | [4] | [3] | `RESET ∧ ¬EMERG` |

### Página 4 — A26 Esteira separadora

- Etapas: E0*, E1, E2, E3, E4, E5, E6, E7 (* inicial); transições: 11; entradas: S_PECA, TIPO_A, TIPO_B, FC_AV_A, FC_AV_B, FC_RET_A, FC_RET_B, RESET; saídas: M_EST, Y_A, Y_B, ALARME.
- Achados: 0
- Alcançabilidade: alcançáveis [0, 1, 2, 3, 4, 5, 6, 7]; não alcançáveis []; sem retorno []; becos [].

| Etapa | Transições | Átomos | Combinações | Violações |
|---|---|---|---|---|
| E1 | T1, T2, T3, T4 | 0,5 s/X1, TIPO_A, TIPO_B, 2 s/X1 | 16 | 0 |

| Transição | Anteriores | Posteriores | Receptividade |
|---|---|---|---|
| T0 | [0] | [1] | `S_PECA` |
| T1 | [1] | [2] | `0,5 s/X1 ∧ TIPO_A ∧ ¬TIPO_B` |
| T2 | [1] | [3] | `0,5 s/X1 ∧ ¬TIPO_A ∧ TIPO_B` |
| T3 | [1] | [7] | `TIPO_A ∧ TIPO_B` |
| T4 | [1] | [7] | `2 s/X1 ∧ ¬TIPO_A ∧ ¬TIPO_B` |
| T5 | [2] | [4] | `FC_AV_A` |
| T6 | [3] | [4] | `FC_AV_B` |
| T7 | [4] | [5] | `0,3 s/X4` |
| T8 | [5] | [6] | `FC_RET_A ∧ FC_RET_B` |
| T9 | [6] | [0] | `¬S_PECA` |
| T10 | [7] | [0] | `RESET ∧ ¬S_PECA` |

### Página 5 — A27 Percurso manual

Página sem GRAFCET (tabela): 89 rótulos; ignorada pelo interpretador.

## Invariantes dinâmicos (verificados a cada décimo e a cada leitura de entradas)

| Página | Invariante | Eventos | Violações | Resultado |
|---|---|---|---|---|
| 2 | exatamente uma lâmpada em 1 | 2577 | 0 | PASSA |
| 3 | M_ABRIR ∧ M_FECHAR nunca | 482 | 0 | PASSA |
| 4 | Y_A ∧ Y_B nunca; M_EST=0 sempre que Y_A ∨ Y_B; M_EST=1 somente com FC_RET_A ∧ FC_RET_B | 203 | 0 | PASSA |
| 1 | nenhuma etapa ativa tem TAG = 0 enquanto outra ativa tem TAG = 1 | 11799 | 0 | PASSA |
| 2 | nenhuma etapa ativa tem TAG = 0 enquanto outra ativa tem TAG = 1 | 2577 | 0 | PASSA |
| 3 | nenhuma etapa ativa tem TAG = 0 enquanto outra ativa tem TAG = 1 | 482 | 0 | PASSA |
| 4 | nenhuma etapa ativa tem TAG = 0 enquanto outra ativa tem TAG = 1 | 203 | 0 | PASSA |
| 3 | em E4 as duas (M_ABRIR, M_FECHAR) em 0 | 482 | 0 | PASSA |
| 4 | M_EST = 1 ⇒ FC_RET_A ∧ FC_RET_B (a esteira só anda com os dois desviadores recolhidos) | 203 | 0 | PASSA |

## Percurso manual (página 5) × traço executado (S10)

| Passo | Marcação ativa | Entradas/eventos | Transição | Nova marcação |
|---|---|---|---|---|
| 0 | E0 | tempo < 8 s | nenhuma | E0 |
| 1 | E0 | tempo = 8 s | T0 | E1 |
| 2 | E1 | tempo = 10 s | T1 | E2 |
| 3 | E2 | tempo = 3 s | T2 | E0 |

Página 5: 25 células agrupadas por geometria; linhas literais encontradas: 4/4; cabeçalho literal: sim. Resultado: PASSA.

## Tabelas de fronteiras e de falha (página 5) × execução (S14, M14)

Cada linha é executada no GRAFCET da página indicada: o modelo é levado à marcação ativa da linha, recebe as entradas e o tempo da coluna Entradas/eventos (linhas sem tempo são observadas por 1,0 s) e a(s) transição(ões) disparada(s) no intervalo e a nova marcação são comparadas com o texto da linha. Uma transição que dispara antes do fim do intervalo (por exemplo T0 aos 8,0 s numa linha de 8,1 s) é registrada com o instante do disparo.

### S14 — Fronteiras temporais (semáforo) (página 2)

| Passo | Marcação ativa | Entradas/eventos | Transição | Nova marcação | Execução | Resultado |
|---|---|---|---|---|---|---|
| 0 | E0 | tempo = 7,9 s | nenhuma | E0 | 0: E0 + 7,9 s → E0, nenhuma | PASSA |
| 1 | E0 | tempo = 8,1 s | T0 | E1 | 1: E0 + 8,1 s → E1, T0 aos 8,0 s | PASSA |
| 2 | E1 | tempo = 9,9 s | nenhuma | E1 | 2: E1 + 9,9 s → E1, nenhuma | PASSA |
| 3 | E1 | tempo = 10,1 s | T1 | E2 | 3: E1 + 10,1 s → E2, T1 aos 10,0 s | PASSA |
| 4 | E2 | tempo = 2,9 s | nenhuma | E2 | 4: E2 + 2,9 s → E2, nenhuma | PASSA |
| 5 | E2 | tempo = 3,1 s | T2 | E0 | 5: E2 + 3,1 s → E0, T2 aos 3,0 s | PASSA |

Página 5 (35 células agrupadas por geometria): 7 linhas lidas; cabeçalho literal: sim; título literal: sim. Resultado: PASSA.

### M14 — Falha (misturador, página 1) (página 1)

| Passo | Marcação ativa | Entradas/eventos | Transição | Nova marcação | Execução | Resultado |
|---|---|---|---|---|---|---|
| 0 | E1 | ¬NIVEL_ALTO, tempo = 119,9 s | nenhuma | E1 | 0: E1 + NIVEL_ALTO=0; 119,9 s → E1, nenhuma | PASSA |
| 1 | E1 | ¬NIVEL_ALTO, tempo = 120 s | T4 | E4 | 1: E1 + NIVEL_ALTO=0; 120,0 s → E4, T4 aos 120,0 s | PASSA |
| 2 | E4 | RESET = 0 | nenhuma | E4 | 2: E4 + RESET=0; observado por 1,0 s → E4, nenhuma | PASSA |
| 3 | E4 | RESET = 1 | T5 | E0 | 3: E4 + RESET=1; observado por 1,0 s → E0, T5 aos 0,0 s | PASSA |

Página 5 (25 células agrupadas por geometria): 5 linhas lidas; cabeçalho literal: sim; título literal: sim. Resultado: PASSA.

## Limites

- O interpretador executa a semântica didática do GRAFCET (não é um CLP): sem tempo de varredura, atrasos de atuadores ou falhas elétricas; ações apenas contínuas.
- Temporizações são contadas em décimos inteiros; frações menores que 0,1 s não são representáveis.
- A exclusividade de seleção trata cada temporização como booleano independente (por exemplo, `0,5 s/X1` e `2 s/X1` são enumeradas como se pudessem variar livremente), o que é mais exigente que a física do relógio.
- A alcançabilidade usa o grafo etapa→etapa induzido pelas transições (aproximação suficiente para estes diagramas; não é uma análise do espaço de marcações).
- Nenhum modelo entregue usa divergência/convergência paralela (barras duplas): a esteira exige o retorno confirmado antes de liberar (T8), o que é sequência. O interpretador suporta barras duplas e as exercita no autoteste (`paralelo_minimo`).
- "Em E4 com porta aberta" foi modelado como `FC_FECHADA=0` e `FC_ABERTA=0` após a emergência (porta fora dos dois fins de curso); o preparo está registrado em cada caso.
- O parser de receptividades não trata um token `Xn` isolado como variável de atividade de etapa (só dentro de `N s/Xn`); um `Xn` isolado seria lido como entrada comum. Nenhum modelo entregue usa `Xn` isolado.
- A regra 5 (etapa desativada e ativada na mesma evolução preserva o relógio) é aplicada por rodada de disparo dentro do mesmo instante: uma etapa desativada numa rodada e reativada na rodada seguinte recebe relógio zerado. Nenhum modelo entregue tem essa estrutura.
