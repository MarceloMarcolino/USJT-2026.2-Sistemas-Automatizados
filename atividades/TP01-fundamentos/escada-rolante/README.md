# Escada rolante com espera econômica e supervisão de segurança

Exercício adicional 3 — proposta própria, Semana 1, Fundamentos dos Sistemas
Automatizados.

Arquivos desta pasta:

- `diagrama.drawio` — modelo funcional editável no diagrams.net
- `diagrama.png` — exportação visual do mesmo diagrama
- `README.md` — especificação, análise de riscos e validação do modelo

[![Diagrama funcional da escada rolante](diagrama.png)](diagrama.png)

## Objetivo e usuários

Transportar pedestres entre dois pavimentos com movimento previsível e seguro,
acionando a escada quando houver demanda e interrompendo-a de forma segura em
caso de emergência, obstrução ou falha.

**Usuários:** pedestres transportados e equipe autorizada de operação e
manutenção. Os passageiros participam do processo como demanda e carga; somente
a equipe autorizada pode habilitar o modo de manutenção, inspecionar e executar
o rearme.

## Classificação

**Grau: automático no ciclo normal.** Sensores detectam demanda, ocupação e
velocidade; a lógica decide e comanda acionamento e freio sem autorização humana
a cada passageiro. Emergência, manutenção e rearme são intervenções humanas de
segurança, não etapas do ciclo normal.

**Tipo: automação fixa/dedicada.** A função e a direção de transporte são
definidas no projeto. Tempos e velocidade nominal são parâmetros configuráveis,
mas o equipamento não é reprogramado para executar outra tarefa.

**Estratégia:** controle sequencial com malha fechada de velocidade. A posição
da demanda na sequência define partida, transporte e espera; a velocidade dos
degraus e do corrimão confirma o resultado do comando. Dispositivos de pente,
entrada e emergência são intertravamentos, não realimentação do movimento.

## Fronteira

**Dentro do sistema:** sensores de aproximação e ocupação; dispositivos de
segurança do pente e da entrada; circuito de emergência; sensores de velocidade
dos degraus e do corrimão; lógica de controle; inversor/acionamento; motor;
freio; mecanismo de degraus e corrimão; sinalização de estado e falha.

**Ambiente:** pedestres, objetos transportados ou soltos, fluxo de pessoas,
carga variável, rede elétrica e equipe autorizada.

**Entradas externas que atravessam a fronteira:** aproximação/ocupação de
passageiros; comando de emergência; habilitação, modo de manutenção e rearme
manual após inspeção.

**Saídas que afetam o ambiente:** movimento de transporte dos degraus e do
corrimão; sinalização de estado, advertência e falha.

**Perturbações não controladas:** objeto preso no pente ou na entrada, carga
variável sobre os degraus e fluxo intenso de pessoas. No diagrama elas partem de
uma origem ambiental comum e atuam tanto no mecanismo quanto nos dispositivos
de segurança.

## Entrada–processamento–saída

| Etapa | Elementos do modelo |
|---|---|
| Entradas | Aproximação e ocupação; estado dos dispositivos do pente/entrada; comando de emergência; habilitação/manutenção/rearme; velocidades medidas dos degraus e do corrimão |
| Processamento | `Avaliar demanda e transporte`: aplicar R0–R5, permissivas, temporização de espera, prioridade de segurança, retenção de falha e rejeição de partida indevida |
| Saídas | Referência de velocidade e comandos partir/manter/desacelerar/parar; liberar/aplicar freio; sinalização; movimento físico de transporte |

## Modelo funcional e decisões verificáveis

As entradas da lógica são demanda e ocupação da zona transportada, estado dos
dispositivos de segurança, emergência, habilitação/manutenção/rearme e
velocidades medidas.

0. **R0 — desabilitada/manutenção:** bloquear o acionamento, manter o freio
   aplicado e não avaliar R1–R3.
1. **R1 — iniciar:** se habilitada, houver aproximação, a zona e os dispositivos
   de segurança estiverem livres e não houver falha ou emergência → liberar o
   freio e acelerar, na direção definida, até a velocidade nominal.
2. **R2 — transportar:** enquanto houver ocupação/demanda e as velocidades
   medidas estiverem coerentes → manter a velocidade nominal.
3. **R3 — espera econômica:** se não houver presença e a zona permanecer livre
   por `T_espera` → desacelerar, parar e aplicar o freio. O parâmetro é
   configurável; o valor de referência do modelo é `T_espera = 30 s`.
4. **R4 — proteção/emergência:** se um dispositivo de segurança atuar, houver
   objeto preso ou o comando de emergência for acionado → retirar o comando do
   acionamento, executar parada de segurança, aplicar o freio, alarmar e reter
   o bloqueio até inspeção e rearme manual.
5. **R5 — falha de movimento:** se o motor for comandado e não houver velocidade,
   ocorrer sobrevelocidade ou houver diferença anormal entre degraus e corrimão
   → retirar o comando, aplicar o freio, alarmar e exigir rearme manual.

**Prioridade e permissivas:** R4 e R5 prevalecem sobre R1–R3. A ausência de
demanda nunca inicia parada enquanto a zona transportada estiver ocupada. Fora
das permissivas normais, a partida é rejeitada. Uma proteção ou falha permanece
retida; restaurar o sinal que a originou não provoca reinício automático.

## Realimentação e intertravamentos

A **realimentação verdadeira** é `Velocidades medidas (degraus / corrimão)`, em
verde espesso no diagrama. O laço completo é:

`Avaliar demanda e transporte` → `Comandar acionamento e freio` →
`Mover degraus e corrimão (motor/mecanismo)` → `Medir velocidades` → lógica.

Essa medida confirma partida, velocidade nominal, coerência entre degraus e
corrimão e parada. Ausência de velocidade após comando, sobrevelocidade ou
diferença anormal leva à R5.

O sinal `Dispositivos livres/atuados — Intertravamento de segurança`, em azul
traço-ponto, bloqueia ou interrompe movimento, mas não mede o resultado do
comando. Por isso não é realimentação. O comando de emergência é uma entrada
prioritária separada, em vermelho espesso.

## Perturbação

A origem externa `Perturbação: objeto / carga / fluxo de pessoas (ambiente)` se
divide em dois ramos magenta tracejados e com ponta aberta:

- `Atua pente / entrada` chega a `Monitorar dispositivos de segurança`;
- `Carga / objeto no mecanismo` chega a `Mover degraus e corrimão`.

Assim, o diagrama distingue a ação física ambiental da informação interna
gerada pelo intertravamento.

## Falhas e matriz de riscos

| Falha/condição | Efeito | Detecção | Resposta segura |
|---|---|---|---|
| Objeto preso no pente ou na entrada | Aprisionamento ou dano | Dispositivo de segurança atuado | R4: retirar comando, parada de segurança, aplicar freio, alarmar e reter bloqueio até inspeção/rearme |
| Sensor de presença travado em ocupado | Operação contínua e perda da economia | Ocupação contínua além do tempo plausível, sem condição independente para distinguir imediatamente passageiro real | Manter o movimento permitido — efeito mais seguro — e sinalizar manutenção; não forçar parada com zona possivelmente ocupada |
| Sensor de velocidade travado, ausente ou incoerente | Decisão incorreta sobre o movimento | Ausência de transição após comando, sobrevelocidade indicada ou divergência degraus–corrimão | R5: retirar comando, aplicar freio, alarmar e bloquear até inspeção/rearme |
| Motor ou inversor não responde | O movimento comandado não ocorre | Realimentação permanece em velocidade zero após comando | R5: retirar comando, aplicar freio, alarmar e bloquear |
| Sobrevelocidade ou diferença anormal degraus–corrimão | Queda ou perda de estabilidade | Comparação contínua das duas velocidades medidas | R5: retirar comando, aplicar freio, alarmar e bloquear |
| Perda de energia | Acionamento deixa de operar | Ausência de alimentação | Freio fail-safe aplicado mecanicamente; equipamento permanece parado e não retoma automaticamente |
| Comando indevido de partida | Movimento em condição perigosa ou fora de sequência | Permissivas de R1: habilitada, zona/dispositivos livres e ausência de falha/emergência | Rejeitar comando; manter acionamento bloqueado e freio aplicado |

## Estado seguro e rearme

O estado seguro é **acionamento sem energia, degraus e corrimão parados e freio
aplicado**. Depois de R4 ou R5, o retorno exige eliminação da causa, inspeção e
rearme manual por pessoa autorizada; não há reinício automático. Em perda de
energia, o freio fail-safe é aplicado mecanicamente, fora da lógica. No modo R0,
o acionamento permanece bloqueado e o freio aplicado.

## Melhoria possível — manutenção preditiva

Registrar tendências de **vibração do mecanismo e corrente do motor** durante
partidas e operação nominal permitiria identificar desgaste de rolamentos,
desalinhamento ou esforço crescente antes de uma parada inesperada. A tendência
é mais útil que um único limite instantâneo porque permite comparar cada ciclo
com o comportamento histórico e programar manutenção antes da falha funcional.

Essa melhoria aumenta disponibilidade e planejamento de manutenção. Ela não
substitui intertravamentos locais, não autoriza manter o equipamento em operação
com proteção atuada e não altera o estado seguro.

## Casos de teste e resultados

O diagrama é um modelo estático; portanto, a validação é analítica. Cada linha
abaixo registra o caminho efetivamente percorrido pelos blocos e setas do
desenho.

| Cenário | Entrada/precondição | Resposta esperada | Resultado rastreado no diagrama | Status |
|---|---|---|---|---|
| Aproximação válida | Habilitada; aproximação; zona e dispositivos livres; sem falha/emergência | Iniciar e atingir velocidade nominal | `Aproximação / ocupação de passageiros` → `Detectar aproximação e ocupação` → `Demanda; zona ocupada/livre` → lógica `R1 · INICIAR` → `Referência de velocidade + freio` → `Comandar acionamento e freio` → `Torque / freio liberado` → `Mover degraus e corrimão` → `Rotação mecânica` → `Medir velocidades` → `Velocidades medidas (degraus / corrimão)` retorna à lógica | Conforme |
| Transporte ocupado | Passageiros na zona; velocidades coerentes | Manter velocidade nominal | `Detectar aproximação e ocupação` → `Demanda; zona ocupada/livre` → lógica `R2 · TRANSPORTAR` → `Referência de velocidade + freio` → `Comandar acionamento e freio` → `Torque / freio liberado` → `Mover degraus e corrimão` → `Rotação mecânica` → `Medir velocidades` → realimentação verde `Velocidades medidas (degraus / corrimão)` à lógica | Conforme |
| Espera sem demanda | Zona livre e nenhuma presença por `T_espera = 30 s` de referência | Desacelerar, parar e aplicar freio | Sinal `Demanda; zona ocupada/livre` → lógica `R3 · ESPERA ECONÔMICA` → `Referência de velocidade + freio` → `Comandar acionamento e freio` → `Torque / freio liberado` → `Mover degraus e corrimão` → `Rotação mecânica` → `Medir velocidades` → velocidade zero retorna pela seta `Velocidades medidas (degraus / corrimão)` | Conforme |
| Objeto no pente | Perturbação externa; dispositivo de segurança atuado | Parada de segurança, freio, alarme e bloqueio retido | Origem `Perturbação: objeto / carga / fluxo de pessoas (ambiente)` → `Atua pente / entrada` → `Monitorar dispositivos de segurança` → seta azul `Dispositivos livres/atuados — Intertravamento de segurança` → `Avaliar demanda e transporte`; o vínculo `R4/R5 · proteção/falha retida` associa a lógica à nota `R4 · PROTEÇÃO / EMERGÊNCIA`, e a lógica envia `Referência de velocidade + freio` e `Estado e falhas`; o segundo ramo `Carga / objeto no mecanismo` registra a ação física simultânea | Conforme |
| Emergência | Comando prioritário acionado | Parar, frear, alarmar e exigir inspeção/rearme | `Comando de emergência` → `Avaliar demanda e transporte`; o vínculo `R4/R5 · proteção/falha retida` associa a resposta à nota `R4 · PROTEÇÃO / EMERGÊNCIA`, enquanto a lógica envia `Referência de velocidade + freio` e `Estado e falhas`; `Estado seguro + rearme` aponta para o quadro de estado seguro, e `Habilitação / manutenção / rearme manual` representa o único retorno autorizado | Conforme |
| Falha de velocidade | Comando ativo e velocidade ausente, excessiva ou incoerente | Retirar comando, frear, alarmar e bloquear | `Mover degraus e corrimão` → `Rotação mecânica` → `Medir velocidades` → realimentação `Velocidades medidas (degraus / corrimão)` → `Avaliar demanda e transporte`; vínculo `R4/R5 · proteção/falha retida` → nota `R5 · FALHA DE MOVIMENTO`; a lógica envia `Referência de velocidade + freio` e `Estado e falhas` | Conforme |
| Manutenção/desabilitada | Modo de manutenção ou habilitação retirada | Impedir partida e manter freio aplicado | `Habilitação / manutenção / rearme manual` → lógica `R0 · DESABILITADA/MANUTENÇÃO` → partida rejeitada; quadro `Estado seguro / rearme` registra acionamento sem energia e freio aplicado | Conforme |

Os sete cenários são rastreáveis por elementos existentes no desenho. R1–R3 e
R0 estão no controlador; R4/R5 estão na nota identificada; estado seguro,
retenção e rearme estão em quadro próprio.

## Autoria

Modelo elaborado no app.diagrams.net a partir de um diagrama em branco, seguindo
as convenções funcionais da prática e a proposta própria de escada rolante.
