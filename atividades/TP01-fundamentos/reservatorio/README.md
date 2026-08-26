# Controle de nível de reservatório

Exercício adicional 1 — Semana 1, Fundamentos dos Sistemas Automatizados.

Arquivos desta pasta:

- `diagrama.drawio` — diagrama funcional editável no diagrams.net
- `diagrama.png` — exportação visual do mesmo diagrama
- `README.md` — especificação, análise de falhas e validação do modelo

[![Diagrama funcional do controle de nível do reservatório](diagrama.png)](diagrama.png)

## Objetivo

Manter o nível do reservatório dentro da faixa operacional, repondo com a
bomba o líquido retirado pelo consumo, sem transbordar.

## Classificação

**Grau: automático.** O sistema mede o nível, decide e comanda a reposição sem
depender do operador no ciclo normal. O operador participa apenas da
habilitação, manutenção e recuperação após uma condição anormal.

**Estratégia: malha fechada liga/desliga com histerese.** O nível resultante da
planta retorna ao sensor e ao controlador. Dois limites de comutação evitam
liga/desliga rápido da bomba e formam uma faixa operacional estável.

## Fronteira

**Dentro do sistema:** sensor de nível, controlador, bomba de reposição,
reservatório e tubulações (planta) e sinalização/alarme.

**Ambiente:** consumo dos usuários, alimentação elétrica e operador de
manutenção.

**Entradas que atravessam a fronteira:** habilitação do sistema e rearme manual
após inspeção. O nível medido não atravessa a fronteira: é um sinal interno
produzido pelo sensor.

**Saída que atravessa a fronteira:** sinalização/alarme ao operador.

**Perturbação externa:** consumo variável, que retira líquido da planta sem ser
controlado pelo sistema.

## Variáveis, condição desejada e limites

| Elemento | Definição no modelo |
|---|---|
| Variável controlada | Nível do reservatório, medido pelo sensor |
| Variável manipulada | Estado da bomba: ligada ou desligada |
| Condição desejada (setpoint) | Nível mantido dentro da faixa operacional |
| `L_baixo` | Limite inferior de comutação: liga a bomba |
| `L_alto` | Limite superior de comutação: desliga a bomba |
| `LAA` | Limite de proteção alto-alto, acima de `L_alto` |
| `T_diag` | Janela máxima para observar tendência de subida após comando `LIGAR` |
| Premissa diagnóstica | Vazão da bomba maior que o consumo máximo admissível de projeto |
| Perturbação | Consumo variável, que reduz o nível |

`L_baixo` e `L_alto` são dois limites de uma única faixa desejada, não dois
setpoints. Vale `L_baixo < L_alto < LAA`. Os valores são simbólicos e devem ser
definidos no comissionamento; o exercício não determina percentuais.

## Modelo funcional

O caminho normal da malha é:

`Medir nível (sensor)` → `Decidir liga/desliga (controlador)` →
`Acionar bomba` → `Reservatório e tubulações (planta)` →
`Nível resultante (realimentação)` → `Medir nível (sensor)`.

As entradas da lógica são o nível medido, a habilitação e o rearme manual. As
saídas da lógica são o comando da bomba e o estado/alarme.

### Regras verificáveis

A prioridade é **R0 > R5 > R4 > R1–R3**. Assim, repouso e segurança prevalecem
sobre a operação normal.

0. **R0 — repouso:** se o sistema estiver desabilitado, desligar a bomba. As
   demais regras só são avaliadas com o sistema habilitado.
1. **R1 — repor:** se `nível ≤ L_baixo` e não houver falha ativa, ligar a bomba.
2. **R2 — limitar:** se `nível ≥ L_alto`, desligar a bomba.
3. **R3 — histerese:** se `L_baixo < nível < L_alto`, manter o estado atual da
   bomba.
4. **R4 — proteção alto-alto:** se `nível ≥ LAA`, desligar a bomba, alarmar e
   exigir rearme manual. R4 prevalece sobre R2: ambas desligam a bomba, mas
   somente R4 retém a falha e exige alarme e rearme.
5. **R5 — sensor/resposta incoerente:** sob a premissa de projeto de que a vazão
   da bomba supera o consumo máximo admissível, declarar **suspeita** se o sinal
   estiver fora da faixa física **ou** se, após `LIGAR`, o nível medido não
   apresentar tendência de subida durante `T_diag`. Desligar a bomba, alarmar,
   reter a falha e exigir rearme manual. `T_diag` é configurável no
   comissionamento. O modelo não identifica a causa: sensor travado em valor
   plausível, bomba sem resposta ou consumo fora da faixa de projeto recebem a
   mesma resposta segura. R5 prevalece sobre R4 e sobre a operação normal.

As permissivas de ligação são: sistema habilitado, ausência de falha retida e
nível compatível com reposição. Fora delas, qualquer solicitação de ligação é
rejeitada e a bomba permanece desligada.

R0 é somente repouso, não falha retida: ao reabilitar o sistema, as regras
operacionais podem voltar a ser avaliadas se não existir latch de R4/R5. Apenas
R4 e R5 exigem inspeção e rearme manual.

As regras R4 e R5 declaram uma **falha retida (latch)**. Uma vez ativa, ela
mantém a bomba desligada e bloqueia R1–R3 mesmo que a condição de detecção
desapareça. O latch sobrevive à perda de energia e só é liberado por rearme
manual após inspeção.

## Significado dos fluxos

| Rótulo no diagrama | Origem → destino | Significado |
|---|---|---|
| `Nível medido` | Sensor → controlador | Informação usada pelas regras R1–R5 |
| `Comando liga/desliga` | Controlador → bomba | Variável manipulada |
| `Vazão de reposição` | Bomba → planta | Ação física que adiciona líquido |
| `Nível resultante (realimentação)` | Planta → sensor | Realimentação verdadeira da malha |
| `Estado e alarme` | Controlador → sinalização | Estado normal ou condição anormal |
| `Sinalização / alarme ao operador` | Sinalização → ambiente | Saída externa do sistema |
| `Consumo variável (retirada)` | Ambiente → planta | Perturbação que remove líquido |

## Realimentação e perturbação

A bomba altera fisicamente o nível da planta. O **nível resultante** retorna ao
sensor, que gera o **nível medido** para o controlador; esse retorno fecha a
malha e permite desligar em `L_alto`, detectar `LAA` e verificar a resposta ao
comando da bomba. Como premissa diagnóstica, a vazão de reposição deve superar o
consumo máximo admissível; assim, após `LIGAR`, espera-se tendência de subida do
nível dentro de `T_diag`.

A proteção `LAA` continua baseada no nível medido. Portanto, um sensor travado
em valor plausível pode ocultar o nível alto-alto. A R5 apenas declara uma
suspeita de resposta incoerente; ela não separa sensor travado, bomba sem
resposta e consumo acima da faixa de projeto.

O consumo variável é uma perturbação: age diretamente sobre a planta e pode
reduzir o nível de forma não comandada. Ele não é uma entrada de decisão do
controlador; seu efeito chega à lógica por meio da realimentação de nível.

## Falhas e matriz de riscos

| Falha ou condição anormal | Efeito | Detecção | Resposta segura |
|---|---|---|---|
| Sensor/resposta incoerente | Decisão incorreta de liga/desliga, com risco de esvaziamento ou transbordo | Sinal fora da faixa física ou, após `LIGAR`, ausência de tendência de subida por `T_diag`, considerando vazão da bomba maior que o consumo máximo admissível (R5) | Declarar suspeita; desligar bomba, alarmar, reter a falha e exigir rearme manual |
| Bomba/atuador não responde | A reposição comandada não ocorre; o nível pode continuar caindo | Ausência de tendência de subida após `LIGAR` por `T_diag` (R5); causa não identificável apenas pelo nível | Aplicar a resposta comum da R5: desligar, alarmar, reter a falha e exigir inspeção e rearme manual |
| Consumo acima da faixa de projeto | A vazão retirada pode anular a reposição e esvaziar o reservatório | Mesmo sintoma diagnóstico: ausência de tendência de subida após `LIGAR` por `T_diag` | Aplicar a resposta comum da R5 e inspecionar consumo, bomba e sensor antes do rearme |
| Nível alto-alto | Risco de transbordamento | `nível ≥ LAA` (R4) | Desligar bomba, alarmar, reter a falha e exigir rearme manual |
| Comando indevido de ligação fora das permissivas | Energização insegura, reposição fora de sequência ou risco de transbordo | Controlador verifica habilitação, ausência de latch e condição de nível antes de emitir `LIGAR` | Rejeitar a ligação e manter a bomba desligada; sinalizar se a solicitação persistir |
| Queda de alimentação elétrica | Controlador e reposição param | Ausência de alimentação; não há decisão ativa | A bomba para passivamente. Uma falha previamente retida permanece retida no retorno da energia |

## Estado seguro e recuperação

O estado físico compartilhado é **bomba desligada**, mas as recuperações são
distintas. Em R0, trata-se de repouso: ao reabilitar, a avaliação pode continuar
se não houver latch. Em R4/R5, trata-se de estado seguro retido: nível alto-alto
ou suspeita de sensor/resposta incoerente gera alarme e impede retomada
automática; o retorno exige inspeção e rearme manual. A manutenção só pode
ocorrer com o sistema desabilitado.

Na perda de energia, a bomba para passivamente, fora da lógica. Quando a energia
retorna, uma falha que já estava retida continua exigindo rearme; sem falha
retida e com o sistema habilitado, as regras voltam a ser avaliadas.

## Casos de teste e resultados

O diagrama é um modelo estático; a validação é analítica. A coluna **Resultado**
nomeia os blocos e as setas efetivamente percorridos no desenho.

| Cenário | Entrada/precondição | Caminho esperado | Resposta esperada | Resultado no diagrama | Status |
|---|---|---|---|---|---|
| Consumo esvazia até `L_baixo` | Sistema habilitado; sem falha; nível cruza `L_baixo` em queda | Sensor → controlador (R1) → bomba → planta | Bomba liga | `Consumo variável (retirada)` → `Reservatório e tubulações (planta)` → `Nível resultante (realimentação)` → `Medir nível (sensor)` → `Nível medido` → `Decidir liga/desliga (controlador)` (R1) → `Comando liga/desliga` → `Acionar bomba` → `Vazão de reposição` → `Reservatório e tubulações (planta)` | Conforme |
| Reposição atinge `L_alto` | Sistema habilitado; sem falha; nível cruza `L_alto` em subida | Sensor → controlador (R2) → bomba | Bomba desliga | `Reservatório e tubulações (planta)` → `Nível resultante (realimentação)` → `Medir nível (sensor)` → `Nível medido` → `Decidir liga/desliga (controlador)` (R2) → `Comando liga/desliga` com desligamento → `Acionar bomba`; a `Vazão de reposição` torna-se nula | Conforme |
| Consumo intenso contínuo | Sistema habilitado; sem falha; bomba ligada; nível permanece entre os limites porque a reposição compensa o consumo | Sensor → controlador (R3) → manter estado → planta | Bomba permanece ligada, sem oscilar | `Consumo variável (retirada)` → `Reservatório e tubulações (planta)` → `Nível resultante (realimentação)` → `Medir nível (sensor)` → `Nível medido` → `Decidir liga/desliga (controlador)` (R3) → `Comando liga/desliga` mantendo o estado → `Acionar bomba` → `Vazão de reposição` → `Reservatório e tubulações (planta)` | Conforme |
| Sensor/resposta incoerente | Sistema habilitado; sinal fora da faixa física | Sensor → controlador (R5) → bomba e alarme | Bomba desligada; alarme; rearme manual | `Medir nível (sensor)` → `Nível medido` fora da faixa física → `Decidir liga/desliga (controlador)` (R5) →, em paralelo, `Comando liga/desliga` → `Acionar bomba` (desligar) e `Estado e alarme` → `Sinalizar e alarmar` → `Sinalização / alarme ao operador`; a nota `R4/R5 · falha retida` registra o bloqueio até o rearme | Conforme |
| Nível alto-alto | Sistema habilitado; `LAA` atingido | Sensor → controlador (R4, antes de R2) → bomba e alarme | Bomba desligada; alarme; rearme manual | `Reservatório e tubulações (planta)` → `Nível resultante (realimentação)` → `Medir nível (sensor)` → `Nível medido` → `Decidir liga/desliga (controlador)` (R4) →, em paralelo, `Comando liga/desliga` → `Acionar bomba` (desligar) e `Estado e alarme` → `Sinalizar e alarmar` → `Sinalização / alarme ao operador`; a nota `R4/R5 · falha retida` registra o latch | Conforme |

## Verificações complementares — não são casos adicionais

### Resposta inválida após comando (`T_diag`)

Com o sistema habilitado e a R1 ativa, `Decidir liga/desliga (controlador)` envia
`Comando liga/desliga` = ligar para `Acionar bomba`. Pela premissa explícita de
que a vazão da bomba supera o consumo máximo admissível, o `Nível medido`
recebido pela realimentação deve mostrar tendência de subida dentro de
`T_diag`. Se isso não ocorrer, a R5 declara suspeita e é retida: o controlador
envia desligamento pelo mesmo `Comando liga/desliga` e, em paralelo, `Estado e
alarme` → `Sinalizar e alarmar` → `Sinalização / alarme ao operador`. A nota
`R4/R5 · falha retida` registra a inspeção e o rearme. O modelo não identifica
se a causa foi sensor travado, bomba sem resposta ou consumo acima da faixa de
projeto. **Status: Conforme.**

### Rejeição de comando indevido

Se houver solicitação de ligação com o sistema desabilitado, falha retida ou
nível fora da permissiva de reposição, `Decidir liga/desliga (controlador)`
aplica `Fora das permissivas → rejeitar ligação` e mantém `Comando liga/desliga`
= desligar rumo a `Acionar bomba`. **Status: Conforme.**

### Repouso pela R0

Com o sistema desabilitado, a entrada `Habilitação do sistema (R0)` chega ao
controlador, que aplica R0 e envia `Comando liga/desliga` para manter a bomba
desligada. Nenhuma regra operacional é avaliada. R0 não cria latch: ao
reabilitar, as regras voltam a ser avaliadas se não houver falha R4/R5 retida,
sem exigir o `Rearme manual (libera o latch)`. **Status: Conforme.**

## Autoria

Diagrama elaborado especificamente para este exercício no formato editável do
diagrams.net, sem uso de modelo pronto.
