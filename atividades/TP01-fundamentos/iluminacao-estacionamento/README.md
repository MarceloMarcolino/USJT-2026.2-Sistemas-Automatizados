# Iluminação automática de estacionamento

Exercício adicional 2 — Semana 1, Fundamentos dos Sistemas Automatizados.

Arquivos deste pacote:

- `diagrama.drawio` — diagrama funcional editável, construído no diagrams.net
- `diagrama.png` — exportação visual do mesmo diagrama
- `README.md` — especificação, análise de falhas e validação do modelo

[![Diagrama funcional da iluminação automática do estacionamento](diagrama.png)](diagrama.png)

## Objetivo

Iluminar o estacionamento quando necessário, conciliando economia de energia
com a segurança das pessoas.

## Classificação

**Grau: automático no modo automático.** O sistema mede luminosidade, presença
e horário, decide pela lógica booleana e comanda as luminárias sem autorização
humana a cada ciclo. No modo manual, o operador assume a decisão, respeitando a
permissiva de segurança que impede apagar durante o fallback noturno.

**Tipo: automação fixa/dedicada.** A função executada é sempre a iluminação do
estacionamento. O limiar de luminosidade, as janelas de movimento e o tempo
`T_des` são parâmetros ajustáveis, mas não alteram a finalidade do sistema.

**Natureza do processamento:** lógica booleana com temporização. A
temporização de desligamento introduz memória do tempo decorrido e do estado
das luminárias.

## Fronteira

**Dentro do sistema:** sensor de luminosidade, sensores de presença,
relógio/calendário, seletor automático/manual, lógica de iluminação, circuito
de comando, luminárias, medição de corrente/status e sinalização de estado e
diagnóstico.

**Ambiente:** pessoas e veículos, luz natural, nuvens, faróis, animais ou
vegetação que alcancem os sensores, operador e rede elétrica.

**Entradas que atravessam a fronteira:** luminosidade ambiente; movimento de
pessoas; referência de horário; modo selecionado; comando manual
`LIGAR/DESLIGAR`; alimentação elétrica da rede.

**Saídas que atravessam a fronteira:** luz no estacionamento e sinalização de
estado/diagnóstico ao operador.

## Modelo funcional e lógica booleana

As variáveis booleanas do modelo são:

- `LuzBaixa`: verdadeira quando a luminosidade medida está abaixo do limiar
  configurado.
- `Presença`: verdadeira quando o sensor detecta movimento/pessoa.
- `HorárioDeMovimento`: verdadeira nas janelas configuradas de troca de turno;
  referência do modelo: 06h–08h e 17h–19h.
- `PeríodoNoturno`: condição configurada pelo relógio; referência do modelo:
  19h–06h.
- `DemandaAuto`: pedido automático de iluminação.

A expressão principal, escrita também no diagrama, é:

`DemandaAuto = LuzBaixa ∧ (Presença ∨ HorárioDeMovimento)`

Em português: há demanda automática quando a luz está baixa **e** existe
presença **ou** a janela de movimento está ativa.

**Decisões verificáveis:**

1. **R1 — automático/acender:** se o modo é automático e `DemandaAuto` é
   verdadeira, comandar `LIGAR`.
2. **R2 — automático/apagar:** se o modo é automático e `DemandaAuto` permanece
   continuamente falsa por `T_des`, comandar `DESLIGAR`. Referência:
   `T_des = 10 min`, configurável. Se a demanda voltar antes do fim do tempo, a
   temporização é cancelada e reiniciará somente em uma nova transição para
   falso.
3. **R3 — manual:** no modo manual, o comando `LIGAR/DESLIGAR` do operador
   determina o estado e fica registrado na sinalização, exceto se a permissiva
   segura da R4 bloquear o desligamento.
4. **R4 — falha de presença:** detecção contínua por mais de 60 min ativa o
   diagnóstico de sinal travado em "detectado". Em período noturno, manter
   acesa, sinalizar a falha e rejeitar qualquer comando manual de desligar. De
   dia, `LuzBaixa` falsa permite que a R2 desligue após `T_des`, mantendo o
   diagnóstico.

**Prioridade:** fallback noturno da R4 > modo manual da R3 > operação automática
das R1/R2. R1 e R2 são ramos opostos da mesma demanda ao longo do tempo, não
comandos simultâneos.

**Diagnóstico pelo retorno:** se o comando e o estado elétrico confirmado
divergirem, sinalizar falha. Se foi comandado `LIGAR` e o circuito não confirma
energização, manter o comando ativo e alarmar; se foi comandado `DESLIGAR` e o
circuito continua energizado, manter o comando de desligar e alarmar para
manutenção.

## Modo manual

O seletor recebe separadamente o modo e o comando do operador. Em manual, a R3
ignora a demanda automática para decidir o estado, mas não contorna a segurança:
`DESLIGAR` é rejeitado enquanto houver falha de presença ativa em período
noturno. A ação manual e eventual rejeição ficam disponíveis na saída de
estado/diagnóstico.

## Realimentação

A única realimentação é `Confirmar estado do circuito` → lógica, rotulada
`Circuito energizado/não energizado — REALIMENTAÇÃO`. A medição de corrente ou
status confirma se o circuito foi energizado ou desenergizado após o comando.

Luminosidade, presença e horário são entradas do ambiente, não realimentação. O
retorno elétrico também **não comprova emissão real de luz** nem identifica uma
luminária individual queimada; isso exigiria retorno fotométrico ou inspeção,
fora do escopo deste modelo.

## Perturbações

- Nuvens e faróis podem causar variações rápidas na luminosidade medida.
- Animais ou vegetação podem produzir falsas detecções de presença.

No diagrama, ambas entram lateralmente nos sensores como setas magenta
tracejadas, diferentes dos sinais normais.

## Falhas e matriz de riscos

| Falha ou evento | Efeito | Detecção | Resposta segura |
|---|---|---|---|
| Sensor de presença travado em "detectado" | Iluminação permanentemente acesa e desperdício | Presença contínua por mais de 60 min (referência configurável) | À noite, manter acesa e diagnosticar; de dia, permitir desligamento pela R2 após `T_des`; encaminhar à manutenção |
| Sensor de presença travado em "livre" | Área pode ficar escura com pessoas presentes | Não comprovável pela instrumentação atual; ausência de detecção também pode ser uso legitimamente baixo | Janela de horário acende independentemente da presença; modo manual permite forçar ligada; corrigir por inspeção/manutenção |
| Circuito não confirma comando `LIGAR` | Área pode permanecer escura | Corrente/status diverge do comando | Manter comando `LIGAR`, alarmar e diagnosticar; a medição não garante luz emitida |
| Contator/circuito permanece energizado após comando `DESLIGAR` | Desperdício e perda de controle | Corrente/status permanece energizado | Manter comando `DESLIGAR`, alarmar e exigir manutenção |
| Comando indevido: `DESLIGAR` manual durante fallback noturno | Retirada da iluminação em condição de risco | Permissiva `FalhaPresença ∧ PeríodoNoturno` ativa | Rejeitar o comando, manter acesa, registrar a rejeição e sinalizar |
| Indisponibilidade de energia da rede | Estacionamento às escuras enquanto durar a interrupção | Ausência de tensão/status | Não alegar iluminação sem fonte independente; quando a energia voltar, recalcular pelas condições atuais. Iluminação de emergência independente está fora do escopo |

## Comportamento seguro

Em falha ou dúvida sobre o sensor de presença durante o período noturno, a
segurança prevalece sobre a economia: manter as luminárias comandadas acesas,
rejeitar `DESLIGAR` manual, sinalizar o diagnóstico e conservar esse fallback
até normalização/manutenção.

Uma falta de energia externa impede fisicamente o circuito comum de iluminar.
Quando a alimentação retornar, a lógica avalia as condições atuais e não
restaura cegamente um estado anterior. Eventual iluminação de emergência com
fonte independente pertence a outro sistema.

## Casos de teste e resultados

Esta validação contém **exatamente quatro casos**, conforme o exercício. O
resultado registra o caminho realmente percorrido nos blocos e setas do
diagrama.

| Cenário | Entrada/precondição | Caminho esperado no modelo | Resposta esperada | Resultado (caminho percorrido no diagrama) | Status |
|---|---|---|---|---|---|
| Noite com presença | Automático; `LuzBaixa`; presença detectada; fora da janela de movimento; sem falha | Entradas → lógica (R1) → ligar → luminárias → confirmação retorna | Acender | `Luminosidade ambiente` → `Medir luminosidade` → `LuzBaixa (0/1)` = verdadeiro; `Movimento de pessoas` → `Detectar presença` → `Presença (0/1)` = verdadeiro; `Referência de horário` → `Ler horário` → `HorárioDeMovimento / PeríodoNoturno` = falso/verdadeiro; `Modo selecionado` → `Selecionar modo automático/manual` → `Modo + comando manual` = automático → `Avaliar acionamento — lógica booleana e temporização` → R1 → `LIGAR/DESLIGAR` = ligar → `Comandar luminárias` → `Energização comandada` → `Luminárias (circuito de iluminação)` → `Estado elétrico observado` → `Confirmar estado do circuito` → `Circuito energizado/não energizado — REALIMENTAÇÃO` → lógica; saída `Luz no estacionamento` | Conforme |
| Dia com presença | Automático; luminosidade alta; presença detectada; luminárias inicialmente apagadas | `LuzBaixa` falsa torna `DemandaAuto` falsa; R1 não comanda ligar | Permanecer apagada | `Luminosidade ambiente` → `Medir luminosidade` → `LuzBaixa (0/1)` = falso e `Movimento de pessoas` → `Detectar presença` → `Presença (0/1)` = verdadeiro → lógica; na expressão `LuzBaixa E (Presença OU HorárioDeMovimento)`, o primeiro termo falso produz `DemandaAuto` falsa. Como a precondição já é apagada, nenhuma mudança de saída é comandada | Conforme |
| Noite sem presença, fora da janela | Automático; luminárias acesas; `LuzBaixa`; presença falsa; `HorárioDeMovimento` falso durante todo `T_des` | Demanda falsa continuamente → R2 → desligar → confirmação retorna | Apagar após `T_des` | `Detectar presença` → `Presença (0/1)` = falso; `Ler horário` → `HorárioDeMovimento / PeríodoNoturno` = falso/verdadeiro; `Medir luminosidade` → `LuzBaixa (0/1)` = verdadeiro; `Selecionar modo automático/manual` → `Modo + comando manual` = automático → lógica; `DemandaAuto` permanece falsa por `T_des = 10 min` → R2 → `LIGAR/DESLIGAR` = desligar → `Comandar luminárias` → `Energização comandada` → `Luminárias (circuito de iluminação)` → `Estado elétrico observado` → `Confirmar estado do circuito` → `Circuito energizado/não energizado — REALIMENTAÇÃO` confirma desenergizado | Conforme |
| Falha do sensor de presença | Detecção contínua por mais de 60 min; período noturno; falha ativa | R4 → fallback noturno → manter ligada + sinalizar diagnóstico | Manter acesa e diagnosticar | `Detectar presença` → `Presença (0/1)` continuamente verdadeira por mais de 60 min e `Ler horário` → `HorárioDeMovimento / PeríodoNoturno` = qualquer/verdadeiro → lógica → vínculo `R4 · falha de presença` → nota `R4 · FALHA DO SENSOR DE PRESENÇA`; pela prioridade `R4 noturna > R3 > R1/R2`, vínculo `R4 · fallback noturno` → quadro `R4 · ESTADO SEGURO`; lógica mantém `LIGAR` → `Comandar luminárias` → `Luminárias (circuito de iluminação)` e envia `Estado + diagnóstico` → `Sinalizar estado e diagnóstico` → saída `Sinalização ao operador` | Conforme |

## Verificações complementares — não são casos adicionais

**Modo manual:** `Modo selecionado` e `Comando manual LIGAR/DESLIGAR` entram em
`Selecionar modo automático/manual`; `Modo + comando manual` chega à lógica e a
R3 determina a saída. Se o pedido for `DESLIGAR` durante o fallback noturno da
R4, a permissiva o rejeita, mantém `LIGAR` e registra o diagnóstico.

**Acionamento apenas pelo horário:** com modo automático, `LuzBaixa` verdadeira,
ausência de presença e `HorárioDeMovimento` verdadeiro, o termo entre parênteses
da expressão é verdadeiro; `DemandaAuto` torna-se verdadeira e a R1 comanda
`LIGAR`.

## Autoavaliação pela rubrica

- **Modelo funcional:** fronteira, entradas, processamento e saídas estão
  nomeados; informação, ação elétrica, realimentação e perturbações têm estilos
  distintos.
- **Coerência:** a expressão booleana e as prioridades permitem reproduzir as
  decisões dos quatro cenários.
- **Falhas:** falha de sensor, divergência de atuação, comando indevido e perda
  de energia possuem detecção, limitação e resposta segura explícitas.
- **Evidência:** o arquivo editável e este README permitem compreender e auditar
  o modelo sem explicação oral.

## Autoria

Diagrama construído no formato editável do diagrams.net a partir de uma
estrutura em branco, sem uso de modelo pronto.
