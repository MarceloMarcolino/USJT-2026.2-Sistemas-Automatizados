# Porta automática de acesso a um edifício

Exercício obrigatório — Semana 1, Fundamentos dos Sistemas Automatizados.

Arquivos desta pasta:

- `diagrama.drawio` — arquivo editável, construído no diagrams.net
- `diagrama.png` — exportação do mesmo diagrama
- `README.md` — este documento

[![Diagrama funcional da porta automática](diagrama.png)](diagrama.png)

*Clique no diagrama para ampliá-lo. Os títulos numerados organizam percepção,
controle e atuação/monitoramento; a legenda relaciona as cores dos blocos a
sensoriamento, lógica, atuação e sinalização. Cor, padrão, espessura e ponta das
linhas distinguem fluxo normal, ação física, intertravamento, realimentação,
perturbação externa, vínculo de regra e emergência. Somente `Posição atual`, em
verde espesso, é realimentação verdadeira.*

## Objetivo

Abrir automaticamente a porta quando uma pessoa se aproxima e fechá-la, com
segurança, quando a passagem estiver livre.

## Classificação

**Grau: automático.** O sistema percebe a presença, decide e atua segundo uma
lógica previamente definida, sem autorização humana a cada ciclo. O comando de
emergência é intervenção do operador, não parte do ciclo normal.

**Tipo: automação fixa.** A porta executa sempre o mesmo ciclo
(abrir → aguardar → fechar), incorporado ao próprio equipamento: repete-o
milhares de vezes por dia e não é reconfigurada para tarefas diferentes.

## Fronteira

**Dentro do sistema:** sensores de presença (externo e interno), barreira de
segurança do vão (feixe), sensores de posição da porta (aberta/fechada), lógica
da porta, acionamento do motor e mecanismo da porta, sinalização de estado e
falha.

**Ambiente:** pessoas e objetos que cruzam o vão, comando de emergência do
edifício, rede elétrica, condições do saguão.

**Entradas que atravessam a fronteira:** aproximação física de pessoas (o sensor
que a converte em sinal está dentro do sistema); comando de emergência;
habilitação (chave de modo, também usada para o rearme manual após falha ou
emergência).

**Saídas que afetam o ambiente:** movimento da porta; sinalização.

## Modelo funcional

**Entradas da lógica:** presença detectada; feixe da barreira do vão
(livre/interrompido — sinal interno protetivo); posição da porta (fins de curso
aberto/fechado — sinal interno de realimentação); comando de emergência e
habilitação do sistema.

**Processamento — decisões verificáveis:**

1. Se habilitado ∧ presença detectada ∧ porta não aberta ∧ sem falha ativa ∧
   fora de emergência → comandar abertura (em emergência, quem abre é a regra 5).
2. Se habilitado ∧ porta aberta ∧ nenhuma presença detectada ∧ vão livre por
   T segundos ∧ sem falha ativa ∧ fora de emergência → comandar fechamento
   (T configurável; valor nominal de referência: T = 3 s).
3. Se barreira interrompida durante o fechamento → parar e reabrir.
4. Se sinais de posição incoerentes — aberta e fechada simultâneas, ou ausência
   de transição após comando (falha do sensor de posição OU do acionamento,
   indistinguíveis pela lógica) → declarar falha ativa, impedir o fechamento
   automático, parar comandos e sinalizar.
5. Se comando de emergência → adotar o estado seguro.

**Prioridade e fallback:** a regra 5 prevalece sobre todas as demais, inclusive
sobre a falha ativa da regra 4 — em emergência a abertura é comandada mesmo com
falha declarada. Se o motor não responder ao comando de abertura em emergência,
o fallback é o desacoplamento mecânico fail-safe (porta abrível manualmente,
rota de passagem preservada), com alarme.

**Saídas:** comando do motor (abrir/fechar/parar); sinalização de estado e de
falha.

## Realimentação

A estrutura mínima do sistema é Sensores → Lógica da porta → Motor. A
**realimentação verdadeira é a posição medida da porta**, que retorna à lógica e
confirma que o movimento comandado ocorreu — ou dispara falha por ausência de
transição. No diagrama ela está destacada em cor e espessura diferentes das
demais setas.

O **feixe da barreira é entrada protetiva (intertravamento de segurança)**:
interrompe o fechamento em andamento, mas não informa o resultado de um movimento
comandado, portanto não é realimentação do processo. No diagrama essa
classificação está escrita no próprio rótulo da seta.

## Perturbação

Obstáculo no vão durante o fechamento (pessoa parada, objeto) e fluxo contínuo de
pessoas que impede o fechamento por longos períodos. O obstáculo age em dois
pontos: sobre o movimento da porta e sobre o feixe da barreira, que é o que o
detecta.

## Falhas e matriz de riscos

| Falha | Efeito | Detecção | Resposta segura |
|---|---|---|---|
| Sensor de presença travado em "detectado" | Porta permanece aberta (com a regra 2 exigindo ausência de presença, o fechamento nunca é comandado) | Não distinguível, pela lógica, de fluxo legítimo contínuo de pessoas — o sinal é o mesmo; identificada por inspeção/manutenção periódica | Efeito intrinsecamente seguro (porta aberta, passagem preservada); correção por manutenção |
| Sensor de posição travado ou inválido | Decisão incorreta de movimento | Incoerência temporal — ausência de transição após comando — ou sinais de posição mutuamente incoerentes, com aberta e fechada simultâneas (regra 4; sintoma que também pode indicar falha do acionamento) | Bloquear a atuação normal, impedir fechamento automático, parar comandos e alarmar |
| Queda de alimentação elétrica | O sistema deixa de operar por completo | Percebida pela própria falta de tensão — tratada fora da lógica: nenhuma regra numerada participa | Segurança garantida mecanicamente (fail-safe de projeto): a porta se desacopla e pode ser aberta à mão, preservando a rota de passagem |
| Motor não responde | Movimento comandado não ocorre | Ausência de transição de posição após comando (regra 4 — indistinguível, pela lógica, de falha do sensor de posição; resposta comum de falha ativa) | Parar comandos, impedir o fechamento automático, sinalizar (regra 4) |
| Comando indevido (solicitação de movimento fora das condições permitidas — p. ex. fechar com o feixe interrompido ou com falha ativa; abrir com o sistema desabilitado) | Ação perigosa ou fora de sequência | Permissivas das regras 1 e 2 (habilitado ∧ sem falha ativa ∧ fora de emergência ∧ condições do vão), verificadas antes dos comandos normais de abertura e fechamento | Rejeitar o comando: nenhuma saída para o motor; o sistema permanece no estado atual (e as regras prioritárias 3 e 5 continuam aptas a parar/reabrir ou abrir em emergência) |

## Comportamento seguro

Nunca fechar com a barreira interrompida. Em emergência, abrir e manter aberta
(preservar a passagem) e exigir rearme manual — feito pela chave de habilitação —
para retorno ao modo automático. Nenhuma retomada automática após falha: a
operação normal só retorna com intervenção autorizada.

## Casos de teste e resultados

Os cinco cenários abaixo são os prescritos para este exercício. Como o diagrama é
um modelo estático, a validação é analítica: cada cenário é percorrido sobre o
desenho, e a coluna **Resultado** registra o caminho efetivamente percorrido no
diagrama — nomeando os blocos e as setas atravessados, não repetindo a resposta
esperada.

| Cenário | Entrada/precondição | Caminho esperado no modelo | Resposta esperada | Resultado (caminho percorrido no diagrama) | Status |
|---|---|---|---|---|---|
| Aproximação válida | Sistema habilitado; presença detectada; porta fechada; sem falha; fora de emergência | "Detectar presença" → lógica (regra 1) → comando abrir → motor → posição "aberta" retorna à lógica | Abrir porta | Entrada `Aproximação de pessoas` → `Detectar presença` → `Presença detectada` → `Avaliar abertura e fechamento` → `Abrir/fechar/parar` → `Comandar motor` → `Acionamento` → `Mover porta (motor/mecanismo)` → `Movimento mecânico` → `Medir posição da porta` → `Posição atual` (realimentação destacada) → lógica | Conforme |
| Passagem concluída | Sistema habilitado; porta aberta; sem presença detectada; vão livre por T s; sem falha; fora de emergência | "Monitorar barreira do vão" (feixe livre) + "Medir posição" (aberta) → lógica (regra 2, temporização de T s anotada no bloco) → comando fechar → posição "fechada" retorna | Fechar após espera | `Monitorar barreira do vão` → `Feixe da barreira (livre/interrompido)` e `Medir posição da porta` → `Posição atual` → lógica, cuja `R2 · FECHAR` registra as permissivas e a ação `→ fechar`, além de `T configurável · referência: 3 s` → `Abrir/fechar/parar` → `Comandar motor` → `Acionamento` → `Mover porta` → `Movimento mecânico` → `Medir posição da porta` → `Posição atual` → lógica | Conforme |
| Obstáculo | Fechamento em andamento; feixe interrompido | "Monitorar barreira do vão" → lógica (regra 3) → parar → reabrir | Parar e reabrir | Origem externa `Perturbação: obstáculo / fluxo de pessoas (ambiente)` → seta tracejada `Interrompe o feixe` → `Monitorar barreira do vão` → `Feixe da barreira (livre/interrompido) / Entrada protetiva (intertravamento)` → lógica → `Abrir/fechar/parar` → `Comandar motor` → `Acionamento` → `Mover porta`. Da mesma origem, a seta tracejada `Ação física sobre o vão` também chega a `Mover porta` | Conforme |
| Falha de sensor | Sinais de posição incoerentes | "Medir posição da porta" (sinais incoerentes) → lógica (regra 4) → falha ativa → parar comandos → bloqueio do fechamento automático → sinalização | Parar comandos (o movimento cessa), impedir fechamento automático e sinalizar | `Medir posição da porta` → `Posição atual` → lógica, que declara a falha ativa — detalhada na nota `R4 · FALHA ATIVA`, anexa pela ligação tracejada `R4 · falha ativa` — → seta `Estado e falhas` (partindo da lógica) → `Sinalizar estado e falhas` → saída `Sinalização` | Conforme |
| Emergência | Comando prioritário acionado | Emergência → lógica (regra 5 + estado seguro) → comando abrir → motor → manter aberta (bloqueio até rearme pela habilitação) | Abrir e manter aberta; rearme manual pela chave de habilitação | Entrada `Comando de emergência` → lógica → `Abrir/fechar/parar` → `Comandar motor` → `Acionamento` → `Mover porta` → saída `Movimento da porta`. A ligação tracejada `R5 · estado seguro` associa a lógica ao quadro `R5 · ESTADO SEGURO — prevalece sobre R1–R4`, e a entrada `Habilitação (modo/rearme)` fecha o rearme | Conforme |

Os cinco cenários foram percorridos sobre o diagrama construído e todos são
rastreáveis do início ao fim por blocos e setas existentes no desenho.

## Autoria

Diagrama elaborado no app.diagrams.net a partir de um arquivo em branco, sem uso
de modelo pronto.
