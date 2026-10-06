# TP06 — Casos de teste do Ladder (partida com selo)

Gerado em 2026-10-06T23:25:04+00:00 (UTC) por `simulacao/verifica_tp06.py`. Execução nativa registrada em 2026-10-06T23:12:32.440Z (UTC).

| Arquivo | SHA-256 |
|---|---|
| `plc-simulator/diagrama-ladder.json` | `51df0ea13cd820acae3b5a9c4dc94dce35825f599ac8d94115b8c014d67c973a` |
| `simulacao/casos.json` | `93ec52899ba99cefae092a3dea3dc7505bdf3ec688c0f6265661a97597974d83` |
| `simulacao/testa_nativo.mjs` | `f6784313b556ba2764fb31f49456cfb4c61bb0e5708165dec648323549b6ba5d` |
| `simulacao/cdp.mjs` | `3b0ddf29f840359482f4dce157b26f5525728b16f776352385eb14d4ea28a161` |
| `simulacao/ladder_interpreta.py` | `16f386fc43d7fb4139c042d4472a429371eb0c0d2e0867b22b93adab5e86f9c4` |
| `simulacao/verifica_tp06.py` | `a3637b826465a3f43076218d3b85fe33265294d9b4d3e7bf2e025d089d915af0` |
| `simulacao/mutantes/mut-a-parada-no-ramo.json` | `ee21a673912bfbbf703e090de102a31b62453cf1ae0ec107fddd26c5ace70a5b` |
| `simulacao/mutantes/mut-b-sem-selo.json` | `e07cb26ba6340af734d94f502473379e0c0c37d20fb37011fcd6e1eb05450ede` |
| `simulacao/mutantes/mut-c-sem-intertravamento.json` | `66ccb6b065de633ee88b5b13175f4c33adc5a06a8ef3019ca948553a219092ab` |
| `simulacao/mutantes/mut-d-run-antes-de-motor.json` | `a1aa43750be3f582c07927c9a7cb29450337eb53098e757c32837b7762318aed` |

## Resumo

**109 de 109 passos passam** no motor nativo do simulador (0 falhas).
Nativo × interpretador: **905 de 905 observações idênticas** (5 programas: original e 4 mutantes, 181 varreduras cada).
Invariantes no original: **0 violações**. Mutantes: **4 de 4 reprovam onde devem**.

| Grupo | IDs | Passos | Passam | Falham |
|---|---|---:|---:|---:|
| obrigatório | T01–T05 | 5 | 5 | 0 |
| estados | M01–M06 | 6 | 6 | 0 |
| traço | TR0–TR4 | 5 | 5 | 0 |
| falha | F01–F16 | 16 | 16 | 0 |
| indicação | RN01–RN04, RD01–RD08 | 12 | 12 | 0 |
| reversão | V01–V17 | 17 | 17 | 0 |
| reversão exaustiva | VX-* | 48 | 48 | 0 |
| **total** | | **109** | **109** | **0** |

Plataforma registrada pelo executor nativo:

- `plataforma`: PLC Simulator Online (app.plcsimulator.online), motor nativo via store Redux da aplicação
- `bundle`: index-52YZHsrG.js
- `userAgent`: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/154.0.0.0 Safari/537.36
- `metodo`: IMPORT_PROJECT do JSON; por passo: SET_SIMULATION false → SET_VAR_VALUE das entradas → leitura "antes" → SET_SIMULATION true → um CYCLE_SCAN → SET_SIMULATION false → leitura "depois". Cada sequência começa com o programa reimportado, todas as variáveis zeradas e o estado_inicial aplicado; o estado é carregado de um passo para o seguinte. Sem julgamento de aprovação.

## Método

- **Esperado**: fixado antes da execução, como dados literais em `simulacao/casos.json` (gerado por `simulacao/gera_casos.py`), a partir da especificação do trabalho: tabela de testes obrigatória, tabela de estados de referência e traço de referência, testes de falha e retomada, e as tabelas dos adicionais. A tabela exaustiva da reversão (VX-*) é derivada da **política** escrita na especificação, não do Ladder. Nada no esperado é lido do diagrama.
- **Obtido**: valores das saídas lidos no **motor nativo do PLC Simulator Online** pelo executor `simulacao/testa_nativo.mjs`: o diagrama entregue é importado pela ação nativa da aplicação, as entradas são escritas e cada passo é **uma varredura**; o valor de cada saída é lido antes e depois dela. A coluna *obtido* traz o valor nativo das saídas que o caso confere (`MOTOR_antes` é o valor de MOTOR imediatamente antes da varredura).
- **Conferência independente**: `simulacao/ladder_interpreta.py` interpreta o mesmo JSON nativo (rungs na ordem da `runglist`, elementos em série, ramos como OU dos sub-rungs, `XIC`/`XIO`/`OTE`, escrita imediata da bobina) e executa as mesmas sequências. Nativo e interpretador precisam produzir observações **idênticas** (sequência, passo, ação, entradas, saídas antes e depois), no original e em cada mutante.
- Cada sequência parte do estado inicial (START=0, STOP_OK=EMG_OK=OL_OK=1, comandos de reversão em 0, saídas em 0) e carrega o estado de um passo para o seguinte. Passos de preparo levam à condição inicial pedida; também são conferidos, mas não entram na contagem.
- *Condição inicial*: texto da tabela de origem quando existe; senão, o passo anterior da sequência e o estado que ele estabelece.

## Tabela completa

| ID | Grupo | Sequência | Condição inicial | Ação | Esperado | Obtido | Situação |
|---|---|---|---|---|---|---|---|
| T01 | obrigatório | SEQ-T01-T03 | tudo saudável, MOTOR=0 | START=1 | MOTOR=1 | MOTOR=1 | PASSA |
| T02 | obrigatório | SEQ-T01-T03 | MOTOR=1 | START=0 | MOTOR=1 | MOTOR=1 | PASSA |
| T03 | obrigatório | SEQ-T01-T03 | MOTOR=1 | STOP_OK=0 | MOTOR=0 | MOTOR=0 | PASSA |
| T04 | obrigatório | SEQ-T04 | MOTOR=1 | EMG_OK=0 | MOTOR=0 | MOTOR=0 | PASSA |
| T05 | obrigatório | SEQ-T05 | MOTOR=0, EMG_OK=0 | START=1 | MOTOR=0 | MOTOR=0 | PASSA |
| M01 | estados | SEQ-M | estado inicial (START=0, permissivos=1, comandos de reversão=0, saídas=0) | START=0, STOP_OK=1, EMG_OK=1, OL_OK=1 | MOTOR=0 | MOTOR=0 | PASSA |
| M02 | estados | SEQ-M | após M01 (MOTOR=0) | START=1, STOP_OK=1, EMG_OK=1, OL_OK=1 | MOTOR=1 | MOTOR=1 | PASSA |
| M03 ¹ | estados | SEQ-M | após M02 (MOTOR=1) | START=0, STOP_OK=1, EMG_OK=1, OL_OK=1 | MOTOR=1 | MOTOR=1 | PASSA |
| M04 | estados | SEQ-M | após M03 (MOTOR=1) | START=0, STOP_OK=0, EMG_OK=1, OL_OK=1 | MOTOR=0 | MOTOR=0 | PASSA |
| M05 | estados | SEQ-M | após M04 (MOTOR=0) | START=1, STOP_OK=1, EMG_OK=0, OL_OK=1 | MOTOR=0 | MOTOR=0 | PASSA |
| M06 | estados | SEQ-M | após M05 (MOTOR=0) | START=1, STOP_OK=1, EMG_OK=1, OL_OK=0 | MOTOR=0 | MOTOR=0 | PASSA |
| TR0 | traço | SEQ-TR | estado inicial (START=0, permissivos=1, comandos de reversão=0, saídas=0) | — | MOTOR_antes=0, MOTOR=0 | MOTOR_antes=0, MOTOR=0 | PASSA |
| TR1 | traço | SEQ-TR | após TR0 (MOTOR=0) | START=1 | MOTOR_antes=0, MOTOR=1 | MOTOR_antes=0, MOTOR=1 | PASSA |
| TR2 | traço | SEQ-TR | após TR1 (MOTOR=1) | START=0 | MOTOR_antes=1, MOTOR=1 | MOTOR_antes=1, MOTOR=1 | PASSA |
| TR3 | traço | SEQ-TR | após TR2 (MOTOR=1) | STOP_OK=0 | MOTOR_antes=1, MOTOR=0 | MOTOR_antes=1, MOTOR=0 | PASSA |
| TR4 | traço | SEQ-TR | após TR3 (MOTOR=0) | STOP_OK=1 | MOTOR_antes=0, MOTOR=0 | MOTOR_antes=0, MOTOR=0 | PASSA |
| F01 | falha | SEQ-F-OL | MOTOR=1 | OL_OK=0 | MOTOR=0 | MOTOR=0 | PASSA |
| F02 | falha | SEQ-F-OL | MOTOR=0, OL_OK=0 | START=1 | MOTOR=0 | MOTOR=0 | PASSA |
| F03 | falha | SEQ-F-OL | MOTOR=0, START=1, OL_OK=0 | START=0, OL_OK=1 | MOTOR=0 | MOTOR=0 | PASSA |
| F04 | falha | SEQ-F-OL | MOTOR=0, tudo saudável | START=1 | MOTOR=1 | MOTOR=1 | PASSA |
| F05 | falha | SEQ-F-OL | MOTOR=1 | START=0 | MOTOR=1 | MOTOR=1 | PASSA |
| F06 | falha | SEQ-F-EMG | MOTOR=1 | EMG_OK=0 | MOTOR=0 | MOTOR=0 | PASSA |
| F07 | falha | SEQ-F-EMG | MOTOR=0, EMG_OK=0 | EMG_OK=1 | MOTOR=0 | MOTOR=0 | PASSA |
| F08 | falha | SEQ-F-EMG | MOTOR=0, tudo saudável | START=1 | MOTOR=1 | MOTOR=1 | PASSA |
| F09 | falha | SEQ-F-STOP | tudo saudável, MOTOR=0 | START=1 | MOTOR=1 | MOTOR=1 | PASSA |
| F10 | falha | SEQ-F-STOP | MOTOR=1, START=1 | STOP_OK=0 | MOTOR=0 | MOTOR=0 | PASSA |
| F11 ¹ | falha | SEQ-F-STOP | MOTOR=0, START=1, STOP_OK=0 | STOP_OK=1 | MOTOR=1 | MOTOR=1 | PASSA |
| F12 | falha | SEQ-F-NIVEL | tudo saudável, MOTOR=0 | START=1 | MOTOR=1 | MOTOR=1 | PASSA |
| F13 | falha | SEQ-F-NIVEL | MOTOR=1, START=1 | EMG_OK=0 | MOTOR=0 | MOTOR=0 | PASSA |
| F14 ¹ | falha | SEQ-F-NIVEL | MOTOR=0, START=1, EMG_OK=0 | EMG_OK=1 | MOTOR=1 | MOTOR=1 | PASSA |
| F15 | falha | SEQ-F-NIVEL | MOTOR=1, START=1 | OL_OK=0 | MOTOR=0 | MOTOR=0 | PASSA |
| F16 ¹ | falha | SEQ-F-NIVEL | MOTOR=0, START=1, OL_OK=0 | OL_OK=1 | MOTOR=1 | MOTOR=1 | PASSA |
| RN01 | indicação | SEQ-RN | tudo saudável, MOTOR=0 | START=1 | MOTOR=1, RUN=1, READY=1 | MOTOR=1, RUN=1, READY=1 | PASSA |
| RN02 | indicação | SEQ-RN | MOTOR=1 | START=0 | MOTOR=1, RUN=1, READY=1 | MOTOR=1, RUN=1, READY=1 | PASSA |
| RN03 | indicação | SEQ-RN | MOTOR=1 | STOP_OK=0 | MOTOR=0, RUN=0, READY=0 | MOTOR=0, RUN=0, READY=0 | PASSA |
| RN04 | indicação | SEQ-RN | MOTOR=0 | STOP_OK=1 | MOTOR=0, RUN=0, READY=1 | MOTOR=0, RUN=0, READY=1 | PASSA |
| RD01 | indicação | SEQ-RDY | estado inicial (START=0, permissivos=1, comandos de reversão=0, saídas=0) | EMG_OK=1, STOP_OK=1, OL_OK=1 | READY=1, MOTOR=0 | READY=1, MOTOR=0 | PASSA |
| RD02 | indicação | SEQ-RDY | após RD01 (READY=1, MOTOR=0) | EMG_OK=0, STOP_OK=1, OL_OK=1 | READY=0, MOTOR=0 | READY=0, MOTOR=0 | PASSA |
| RD03 | indicação | SEQ-RDY | após RD02 (READY=0, MOTOR=0) | EMG_OK=1, STOP_OK=0, OL_OK=1 | READY=0, MOTOR=0 | READY=0, MOTOR=0 | PASSA |
| RD04 | indicação | SEQ-RDY | após RD03 (READY=0, MOTOR=0) | EMG_OK=1, STOP_OK=1, OL_OK=0 | READY=0, MOTOR=0 | READY=0, MOTOR=0 | PASSA |
| RD05 | indicação | SEQ-RDY | após RD04 (READY=0, MOTOR=0) | EMG_OK=0, STOP_OK=0, OL_OK=1 | READY=0, MOTOR=0 | READY=0, MOTOR=0 | PASSA |
| RD06 | indicação | SEQ-RDY | após RD05 (READY=0, MOTOR=0) | EMG_OK=0, STOP_OK=1, OL_OK=0 | READY=0, MOTOR=0 | READY=0, MOTOR=0 | PASSA |
| RD07 | indicação | SEQ-RDY | após RD06 (READY=0, MOTOR=0) | EMG_OK=1, STOP_OK=0, OL_OK=0 | READY=0, MOTOR=0 | READY=0, MOTOR=0 | PASSA |
| RD08 | indicação | SEQ-RDY | após RD07 (READY=0, MOTOR=0) | EMG_OK=0, STOP_OK=0, OL_OK=0 | READY=0, MOTOR=0 | READY=0, MOTOR=0 | PASSA |
| V01 | reversão | SEQ-V | parado | START_FWD=1 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| V02 | reversão | SEQ-V | FWD=1 | START_FWD=0 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| V03 | reversão | SEQ-V | FWD=1 | START_REV=1 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| V04 | reversão | SEQ-V | FWD=1 | START_REV=0, STOP_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| V05 | reversão | SEQ-V | parado | STOP_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| V06 | reversão | SEQ-V | parado | START_REV=1 | FWD=0, REV=1 | FWD=0, REV=1 | PASSA |
| V07 | reversão | SEQ-V | REV=1 | START_REV=0 | FWD=0, REV=1 | FWD=0, REV=1 | PASSA |
| V08 | reversão | SEQ-V | REV=1 | EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| V09 | reversão | SEQ-V | parado, EMG_OK=0 | EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| V13 | reversão | SEQ-V-NIVEL | parado | START_FWD=1 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| V14 | reversão | SEQ-V-NIVEL | FWD=1 | START_FWD=0 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| V15 | reversão | SEQ-V-NIVEL | FWD=1 | START_REV=1 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| V16 | reversão | SEQ-V-NIVEL | FWD=1, START_REV=1 | STOP_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| V17 ¹ | reversão | SEQ-V-NIVEL | parado, START_REV=1, STOP_OK=0 | STOP_OK=1 | FWD=0, REV=1 | FWD=0, REV=1 | PASSA |
| V10 ¹ | reversão | SEQ-VS | parado | START_FWD=1, START_REV=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| V11 | reversão | SEQ-VS | parado | START_REV=0 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| V12 | reversão | SEQ-VS | FWD=1 | START_REV=1 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| VX-parado-0000 | reversão exaustiva | VX-parado-0000 | parado | START_FWD=0, START_REV=0, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-0001 | reversão exaustiva | VX-parado-0001 | parado | START_FWD=0, START_REV=0, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-0010 | reversão exaustiva | VX-parado-0010 | parado | START_FWD=0, START_REV=0, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-0011 | reversão exaustiva | VX-parado-0011 | parado | START_FWD=0, START_REV=0, STOP_OK=1, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-0100 | reversão exaustiva | VX-parado-0100 | parado | START_FWD=0, START_REV=1, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-0101 | reversão exaustiva | VX-parado-0101 | parado | START_FWD=0, START_REV=1, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-0110 | reversão exaustiva | VX-parado-0110 | parado | START_FWD=0, START_REV=1, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-0111 | reversão exaustiva | VX-parado-0111 | parado | START_FWD=0, START_REV=1, STOP_OK=1, EMG_OK=1 | FWD=0, REV=1 | FWD=0, REV=1 | PASSA |
| VX-parado-1000 | reversão exaustiva | VX-parado-1000 | parado | START_FWD=1, START_REV=0, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-1001 | reversão exaustiva | VX-parado-1001 | parado | START_FWD=1, START_REV=0, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-1010 | reversão exaustiva | VX-parado-1010 | parado | START_FWD=1, START_REV=0, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-1011 | reversão exaustiva | VX-parado-1011 | parado | START_FWD=1, START_REV=0, STOP_OK=1, EMG_OK=1 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| VX-parado-1100 | reversão exaustiva | VX-parado-1100 | parado | START_FWD=1, START_REV=1, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-1101 | reversão exaustiva | VX-parado-1101 | parado | START_FWD=1, START_REV=1, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-1110 | reversão exaustiva | VX-parado-1110 | parado | START_FWD=1, START_REV=1, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-parado-1111 | reversão exaustiva | VX-parado-1111 | parado | START_FWD=1, START_REV=1, STOP_OK=1, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-0000 | reversão exaustiva | VX-FWD-0000 | FWD | START_FWD=0, START_REV=0, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-0001 | reversão exaustiva | VX-FWD-0001 | FWD | START_FWD=0, START_REV=0, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-0010 | reversão exaustiva | VX-FWD-0010 | FWD | START_FWD=0, START_REV=0, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-0011 | reversão exaustiva | VX-FWD-0011 | FWD | START_FWD=0, START_REV=0, STOP_OK=1, EMG_OK=1 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| VX-FWD-0100 | reversão exaustiva | VX-FWD-0100 | FWD | START_FWD=0, START_REV=1, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-0101 | reversão exaustiva | VX-FWD-0101 | FWD | START_FWD=0, START_REV=1, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-0110 | reversão exaustiva | VX-FWD-0110 | FWD | START_FWD=0, START_REV=1, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-0111 | reversão exaustiva | VX-FWD-0111 | FWD | START_FWD=0, START_REV=1, STOP_OK=1, EMG_OK=1 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| VX-FWD-1000 | reversão exaustiva | VX-FWD-1000 | FWD | START_FWD=1, START_REV=0, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-1001 | reversão exaustiva | VX-FWD-1001 | FWD | START_FWD=1, START_REV=0, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-1010 | reversão exaustiva | VX-FWD-1010 | FWD | START_FWD=1, START_REV=0, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-1011 | reversão exaustiva | VX-FWD-1011 | FWD | START_FWD=1, START_REV=0, STOP_OK=1, EMG_OK=1 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| VX-FWD-1100 | reversão exaustiva | VX-FWD-1100 | FWD | START_FWD=1, START_REV=1, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-1101 | reversão exaustiva | VX-FWD-1101 | FWD | START_FWD=1, START_REV=1, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-1110 | reversão exaustiva | VX-FWD-1110 | FWD | START_FWD=1, START_REV=1, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-FWD-1111 | reversão exaustiva | VX-FWD-1111 | FWD | START_FWD=1, START_REV=1, STOP_OK=1, EMG_OK=1 | FWD=1, REV=0 | FWD=1, REV=0 | PASSA |
| VX-REV-0000 | reversão exaustiva | VX-REV-0000 | REV | START_FWD=0, START_REV=0, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-0001 | reversão exaustiva | VX-REV-0001 | REV | START_FWD=0, START_REV=0, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-0010 | reversão exaustiva | VX-REV-0010 | REV | START_FWD=0, START_REV=0, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-0011 | reversão exaustiva | VX-REV-0011 | REV | START_FWD=0, START_REV=0, STOP_OK=1, EMG_OK=1 | FWD=0, REV=1 | FWD=0, REV=1 | PASSA |
| VX-REV-0100 | reversão exaustiva | VX-REV-0100 | REV | START_FWD=0, START_REV=1, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-0101 | reversão exaustiva | VX-REV-0101 | REV | START_FWD=0, START_REV=1, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-0110 | reversão exaustiva | VX-REV-0110 | REV | START_FWD=0, START_REV=1, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-0111 | reversão exaustiva | VX-REV-0111 | REV | START_FWD=0, START_REV=1, STOP_OK=1, EMG_OK=1 | FWD=0, REV=1 | FWD=0, REV=1 | PASSA |
| VX-REV-1000 | reversão exaustiva | VX-REV-1000 | REV | START_FWD=1, START_REV=0, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-1001 | reversão exaustiva | VX-REV-1001 | REV | START_FWD=1, START_REV=0, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-1010 | reversão exaustiva | VX-REV-1010 | REV | START_FWD=1, START_REV=0, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-1011 | reversão exaustiva | VX-REV-1011 | REV | START_FWD=1, START_REV=0, STOP_OK=1, EMG_OK=1 | FWD=0, REV=1 | FWD=0, REV=1 | PASSA |
| VX-REV-1100 | reversão exaustiva | VX-REV-1100 | REV | START_FWD=1, START_REV=1, STOP_OK=0, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-1101 | reversão exaustiva | VX-REV-1101 | REV | START_FWD=1, START_REV=1, STOP_OK=0, EMG_OK=1 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-1110 | reversão exaustiva | VX-REV-1110 | REV | START_FWD=1, START_REV=1, STOP_OK=1, EMG_OK=0 | FWD=0, REV=0 | FWD=0, REV=0 | PASSA |
| VX-REV-1111 | reversão exaustiva | VX-REV-1111 | REV | START_FWD=1, START_REV=1, STOP_OK=1, EMG_OK=1 | FWD=0, REV=1 | FWD=0, REV=1 | PASSA |

¹ Notas:

- **M03**: 1 pelo selo.
- **F11**: comportamento declarado: a partida é por nível, não por borda; START mantido religa ao liberar STOP.
- **F14**: comportamento declarado: com START mantido, liberar a emergência religa; numa máquina real o rearme da emergência não pode provocar partida.
- **F16**: comportamento declarado: com START mantido, rearmar a sobrecarga religa.
- **V17**: comportamento declarado: um botão de sentido mantido parte ao liberar STOP, sem novo comando; a parada é só do comando, sem espera de rotação zero.
- **V10**: política: comandos simultâneos a partir do repouso não partem nenhum sentido.

## Invariantes

Vigiados ao fim de **toda** varredura de todas as sequências, inclusive os passos de preparo.

| ID | Propriedade | Varreduras vigiadas (nativo) | Varreduras vigiadas (interpretador) | Violações | Situação |
|---|---|---:|---:|---:|---|
| INV-RUN | RUN = MOTOR ao fim de toda varredura | 181 | 181 | 0 | PASSA |
| INV-RDY | READY = EMG_OK · STOP_OK · OL_OK ao fim de toda varredura | 181 | 181 | 0 | PASSA |
| INV-REV | FWD e REV nunca em 1 ao mesmo tempo | 181 | 181 | 0 | PASSA |

## Mutantes

Programas com um erro introduzido de propósito, executados com as mesmas sequências. Um teste só tem valor se reprova o programa errado: cada mutante precisa reprovar **pelo menos** nos IDs listados, nas duas execuções. Reprovações além das exigidas são consequências do mesmo erro em outros passos; passos de preparo reprovados aparecem como `SEQUÊNCIA/passo`.

| ID | Erro introduzido | Deve reprovar | Reprovou (nativo) | Reprovou (interpretador) | Situação |
|---|---|---|---|---|---|
| MUT-A | STOP_OK apenas no caminho de START, fora do ramo de selo | T03, TR3, M04, RN03, F10 | 7 IDs: T03, M04, TR3, TR4, F10, RN03, RN04 | 7 IDs: T03, M04, TR3, TR4, F10, RN03, RN04 | PASSA |
| MUT-B | sem o contato de selo: partida simples, sem retenção | T02, TR2, M03, F05, RN02 | 9 IDs: T02, SEQ-T04/prep-solta, M03, TR2, TR3, SEQ-F-OL/prep-solta, F05, SEQ-F-EMG/prep-solta, RN02 | 9 IDs: T02, SEQ-T04/prep-solta, M03, TR2, TR3, SEQ-F-OL/prep-solta, F05, SEQ-F-EMG/prep-solta, RN02 | PASSA |
| MUT-C | sem ¬REV/¬FWD e sem bloqueio de comandos simultâneos | V03, V10, V12, INV-REV | 11 IDs: V03, V15, V10, V11, V12, VX-parado-1111, VX-FWD-0111, VX-FWD-1111, VX-REV-1011, VX-REV-1111, INV-REV | 11 IDs: V03, V15, V10, V11, V12, VX-parado-1111, VX-FWD-0111, VX-FWD-1111, VX-REV-1011, VX-REV-1111, INV-REV | PASSA |
| MUT-D | rung de RUN antes do rung de MOTOR (ordem de varredura) | INV-RUN | 3 IDs: RN01, RN03, INV-RUN | 3 IDs: RN01, RN03, INV-RUN | PASSA |

**MUT-A** — STOP_OK fica só no caminho de START; o caminho de selo (MOTOR) contorna a parada, então STOP não desliga um motor já em marcha.

- T03: esperado MOTOR=0; obtido MOTOR=1 (nativo)
- TR3: esperado MOTOR_antes=1, MOTOR=0; obtido MOTOR_antes=1, MOTOR=1 (nativo)
- M04: esperado MOTOR=0; obtido MOTOR=1 (nativo)
- RN03: esperado MOTOR=0, RUN=0, READY=0; obtido MOTOR=1, RUN=1, READY=0 (nativo)
- F10: esperado MOTOR=0; obtido MOTOR=1 (nativo)

**MUT-B** — sem o contato de selo, MOTOR só vale 1 enquanto START está pressionado; ao soltar, desliga.

- T02: esperado MOTOR=1; obtido MOTOR=0 (nativo)
- TR2: esperado MOTOR_antes=1, MOTOR=1; obtido MOTOR_antes=1, MOTOR=0 (nativo)
- M03: esperado MOTOR=1; obtido MOTOR=0 (nativo)
- F05: esperado MOTOR=1; obtido MOTOR=0 (nativo)
- RN02: esperado MOTOR=1, RUN=1, READY=1; obtido MOTOR=0, RUN=0, READY=1 (nativo)

**MUT-C** — sem ¬REV/¬FWD e sem o bloqueio do comando oposto, o comando oposto em marcha e os comandos simultâneos energizam os dois sentidos.

- V03: esperado FWD=1, REV=0; obtido FWD=1, REV=1 (nativo)
- V10: esperado FWD=0, REV=0; obtido FWD=1, REV=1 (nativo)
- V12: esperado FWD=1, REV=0; obtido FWD=1, REV=1 (nativo)
- INV-REV: 10 varreduras violadas (primeira: SEQ-V/V03) (nativo)

**MUT-D** — o rung de RUN é avaliado antes de MOTOR ser escrito e copia o valor da varredura anterior: RUN fica uma varredura atrasado em relação a MOTOR.

- INV-RUN: 24 varreduras violadas (primeira: SEQ-T01-T03/T01) (nativo)

## Limites

- Simulação lógica: não valida hardware, tempo real de varredura, latência de E/S, ruído, contatos soldados nem falhas de fiação.
- O simulador não separa a imagem das entradas da memória de tags; cada passo escreve as entradas e executa uma varredura. Mudanças de entrada *durante* uma varredura não são exercitadas; o efeito de ordem de varredura é demonstrado pelo mutante MUT-D.
- O interpretador cobre só o subconjunto usado (`XIC`, `XIO`, `OTE` e ramos) e rejeita qualquer outro tipo de elemento; a equivalência com o motor nativo vale para as sequências executadas, não para qualquer programa.
- A tabela exaustiva cobre as 16 combinações de (START_FWD, START_REV, STOP_OK, EMG_OK) a partir de três estados (parado, avanço, retorno), uma varredura cada; não cobre sequências longas arbitrárias.
- Partida por nível: com o botão de partida mantido, a volta de qualquer permissivo religa — soltar STOP (F11), liberar a emergência (F14), rearmar a sobrecarga (F16); na reversão, um botão de sentido mantido parte ao liberar STOP (V17). Comportamentos declarados; melhoria: partida por borda (contato OSP do simulador).
- Emergência por software não é função de segurança certificada; o intertravamento FWD/REV aqui é só lógico.
