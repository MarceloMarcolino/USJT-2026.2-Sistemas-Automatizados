# TP05 — Sistemas sequenciais e GRAFCET/SFC

**Autor:** Marcelo Antonio Pereira Marcolino — USJT — ESO1AN-MCE3<br>
**Estado:** completo — 77/77 casos aprovados executando o próprio `.drawio`; PNG, PDF e visualizador público abaixo<br>
**Data:** redação em 29 de setembro de 2026; execução do verificador em 30 de setembro de 2026, 03:44 UTC

## Links e artefatos

- [`grafcet.drawio`](grafcet.drawio) — arquivo-fonte editável, cinco páginas
  (misturador, semáforo, porta automática, esteira separadora, percurso
  manual), XML não comprimido
- [`grafcet.png`](grafcet.png) — página 2, o exercício obrigatório (semáforo)
- [`grafcet.pdf`](grafcet.pdf) — todas as páginas, em ordem
- [`casos_teste.csv`](casos_teste.csv) — cenários com esperado, obtido e
  resultado, gerado pela execução do próprio `.drawio`
- [`NOTAS.md`](NOTAS.md) — limites e melhorias, decisões de projeto e
  alternativas descartadas
- Evidências por página:
  [p1 misturador](evidencias/grafcet-p1-misturador.png),
  [p2 semáforo](evidencias/grafcet-p2-semaforo.png),
  [p3 porta](evidencias/grafcet-p3-porta.png),
  [p4 esteira](evidencias/grafcet-p4-esteira.png) e
  [p5 percurso](evidencias/grafcet-p5-percurso.png)
- [Relatório legível dos casos](testes/casos-de-teste.md) e
  [registro com hashes e data UTC](testes/resultados.json)
- Visualizador público — o diagrams.net abrindo o arquivo bruto deste
  repositório, com as cinco páginas navegáveis:
  <https://viewer.diagrams.net/?highlight=0000ff&nav=1&title=grafcet.drawio#Uhttps://raw.githubusercontent.com/MarceloMarcolino/USJT-2026.2-Sistemas-Automatizados/main/atividades/TP05-grafcet/grafcet.drawio>.
  Não depende de conta; se o serviço estiver indisponível, o PNG e o PDF
  versionados são a evidência estática.

O `.drawio` é a fonte única: PNG, PDF e CSV derivam dele. O registro
`testes/resultados.json` guarda o SHA-256 do `.drawio` entregue
(`39ba03dfcb001ef1…`), do interpretador e do verificador,
de modo que qualquer edição posterior do diagrama seja detectável.

## Objetivo

Construir e validar, no diagrams.net, GRAFCETs conforme IEC 60848 para as
atividades da prática da Semana 5: identificar os elementos de um sistema
sequencial (misturador), modelar o semáforo veicular temporizado (exercício
obrigatório) e, como adicionais, uma porta automática com emergência e uma
esteira separadora com seleção exclusiva e retorno sincronizado. Cada diagrama tem tabela de E/S, etapas
com ações, transições com receptividades testáveis e casos de teste normais, de
limite e de falha. O percurso manual do semáforo é registrado passo a passo na
quinta página.

## Convenção gráfica e notação

A convenção gráfica segue o enunciado da Semana 5 e a IEC 60848:

| Elemento | Como está desenhado nesta entrega |
|---|---|
| Etapa | quadrado de 40×40 com o número da etapa; o nome fica em legenda cinza à esquerda |
| Etapa inicial | o mesmo quadrado com contorno duplo — uma por página |
| Ação | caixa à direita da etapa, unida a ela por um traço sem ponta de seta; texto na forma `TAG = 1` ou verbo + objeto |
| Transição | barra preta curta (30×4) cortando o arco vertical entre duas etapas |
| Receptividade | expressão lógica escrita à direita da barra |

Os arcos descem sem seta; arcos que sobem (retorno de ciclo) levam seta.
Receptividades usam `∧` (E), `∨` (OU), `¬` (NÃO) e parênteses; `=1` é a
receptividade sempre verdadeira.

**Temporização.** `8 s/X0` lê-se "a etapa 0 está ativa há pelo menos 8 s":
`X0` é a variável de estado da etapa 0 (1 quando ativa) e o relógio parte de
zero na ativação da etapa. É a forma normativa do "X0 ativa por 8 s" do
enunciado. Com vírgula decimal: `0,5 s/X1`. O interpretador conta décimos de
segundo inteiros, de modo que `8 s/X0` é verdadeira a partir do 80.º décimo de
atividade e falsa no 79.º — daí os casos de fronteira "7,9 s / 8,0 s / 8,1 s".

**Ações.** `TAG = 1` é ação contínua: a saída fica em 1 enquanto a etapa está
ativa. `TAG = 0` é explicitação didática (por exemplo, `Y_A = 0 · Y_B = 0` na
etapa de recolhimento) e não liga nada; o verificador a trata como a
obrigação de que nenhuma outra etapa ativa mantenha aquela saída em 1. Texto
sem `=` (`AGUARDAR presença`, `LER tipo`) é descritivo e não corresponde a
saída física. Várias ações na mesma etapa são separadas por ` · `.

## Hipóteses e critérios de segurança

- Lógica positiva em todas as entradas: `1` é a condição declarada presente
  (`EMERG = 1` significa emergência acionada; `FC_FECHADA = 1`, porta fechada).
- Estado seguro de partida: apenas a etapa inicial ativa, relógios zerados e
  todas as saídas de movimento em 0; a única saída ligada na inicialização é
  sinalização (`LAMP_PRONTO`, `VERMELHO`) ou o transporte de rotina (`M_EST`).
- Emergência domina: em cada etapa de operação da porta existe uma transição
  para a etapa SEGURO com receptividade `EMERG`, e toda receptividade normal
  carrega `¬EMERG`; o rearme exige `RESET ∧ ¬EMERG`.
- Nunca dois sentidos de motor ao mesmo tempo (`M_ABRIR ∧ M_FECHAR` proibido)
  nem dois desviadores atuados juntos (`Y_A ∧ Y_B` proibido); no ciclo de desvio,
  a esteira permanece parada até T8 confirmar `FC_RET_A ∧ FC_RET_B`.
  Nos cenários executados, com partida recolhida e manutenção dos sinais fora
  do movimento previsto, observou-se `M_EST = 1 ⇒ FC_RET_A ∧ FC_RET_B` (IN6).
  Isso não é um intertravamento contínuo: perder a confirmação de retorno em
  E0 ou E6 não desliga automaticamente o motor; essa falha não está modelada.
- Toda seleção é exclusiva por construção: as receptividades que saem da
  mesma etapa são mutuamente excludentes em todas as combinações das
  variáveis envolvidas, não apenas nas esperadas em operação.
- Os tempos de esgotamento (120 s de enchimento, 2 s de classificação) são
  hipóteses de projeto e não valores do enunciado; ver `NOTAS.md`.

## Atividade 23 — Identificar elementos: misturador

Enquadramento: obrigatória (identificação de estados, transições e ações de um
sistema sequencial). Página 1 do `.drawio`.

| Tag | Tipo | Significado | Estado seguro |
|---|---|---|---|
| `START` | E digital | comando de partida | 0 |
| `NIVEL_BAIXO` | E digital | tanque no nível baixo (vazio) | 1 |
| `NIVEL_ALTO` | E digital | tanque no nível alto (cheio) | 0 |
| `RESET` | E digital | rearme após falha | 0 |
| `LAMP_PRONTO` | S digital | sinaliza disponível | 0 |
| `V_ENT` | S digital | válvula de entrada | 0 |
| `M_AGIT` | S digital | motor do agitador | 0 |
| `V_DRENO` | S digital | válvula de dreno | 0 |
| `ALARME` | S digital | alarme de falha | 0 |

| Etapa | Situação | Ação |
|---|---|---|
| 0 (inicial) | AGUARDANDO | `LAMP_PRONTO = 1` |
| 1 | ENCHENDO | `V_ENT = 1` |
| 2 | MISTURANDO | `M_AGIT = 1` |
| 3 | DRENANDO | `V_DRENO = 1` |
| 4 | FALHA | `ALARME = 1` |

| Transição | De → para | Receptividade |
|---|---|---|
| T0 | 0 → 1 | `START ∧ NIVEL_BAIXO` |
| T1 | 1 → 2 | `NIVEL_ALTO` |
| T2 | 2 → 3 | `30 s/X2` |
| T3 | 3 → 0 | `NIVEL_BAIXO` |
| T4 | 1 → 4 | `¬NIVEL_ALTO ∧ 120 s/X1` — tempo de enchimento excedido |
| T5 | 4 → 0 | `RESET` |

Itens pedidos na atividade: as quatro etapas do ciclo são 0–3, cada uma com
uma única ação; as três receptividades entre elas são T0, T1 e T2, e T3 fecha
o ciclo; a etapa inicial é a 0 (contorno duplo); a condição de falha é T4
(`¬NIVEL_ALTO ∧ 120 s/X1`), que leva à etapa 4 com `ALARME = 1` e rearme por
`RESET`.

Leitura do diagrama: o ciclo principal é uma sequência linear fechada
(0 → 1 → 2 → 3 → 0). A etapa 1 é a única com seleção — T1 e T4 — e as duas
receptividades são exclusivas pelo literal `NIVEL_ALTO`/`¬NIVEL_ALTO`,
independentemente do temporizador: se o nível alto chega aos 119,9 s, o
caminho normal vence; se o tempo se esgota sem nível, só T4 pode disparar. A
partida exige `NIVEL_BAIXO`, o que impede encher um tanque que não drenou; a
falha isola o alarme em uma etapa própria, de onde só o rearme devolve o
sistema a AGUARDANDO.

## Atividade 24 — Semáforo veicular (exercício obrigatório)

Enquadramento: exercício obrigatório da prática. Página 2 do `.drawio`; é a
página exportada como `grafcet.png`.

| Tag | Tipo | Significado | Estado seguro |
|---|---|---|---|
| `VERMELHO` | S digital | lâmpada vermelha | 1 (etapa inicial) |
| `VERDE` | S digital | lâmpada verde | 0 |
| `AMARELO` | S digital | lâmpada amarela | 0 |

Não há entradas de processo: as três receptividades são temporizações.

| Etapa | Situação | Ação |
|---|---|---|
| 0 (inicial) | VERMELHO | `VERMELHO = 1` |
| 1 | VERDE | `VERDE = 1` |
| 2 | AMARELO | `AMARELO = 1` |

| Transição | De → para | Receptividade |
|---|---|---|
| T0 | 0 → 1 | `8 s/X0` |
| T1 | 1 → 2 | `10 s/X1` |
| T2 | 2 → 0 | `3 s/X2` |

Leitura do diagrama: cada etapa acende exatamente uma lâmpada; o ciclo fecha
em 21 s (8 + 10 + 3); cada tempo está escrito na receptividade que o consome; e
a etapa inicial é única e visível, em VERMELHO — o estado seguro de um semáforo
é o que impede a passagem. Como não
há seleção nem paralelismo, exatamente uma etapa está ativa a cada instante e,
por consequência, exatamente uma lâmpada está acesa; esse invariante é
conferido a cada 0,1 s ao longo do ciclo inteiro (caso S12).

## Atividade 25 — Porta automática com emergência (adicional)

Enquadramento: atividade adicional. Página 3 do `.drawio`. As tags são ASCII
maiúsculo, como nas demais páginas: `PRESENCA` é o sensor de presença
(PRESENÇA) e `EMERG` é o botão de emergência (EMERGÊNCIA) pedidos na
atividade; `FC_ABERTA` e `FC_FECHADA` são os fins de curso.

| Tag | Tipo | Significado | Estado seguro |
|---|---|---|---|
| `PRESENCA` | E digital | pessoa na zona da porta | 0 |
| `FC_ABERTA` | E digital | fim de curso: porta aberta | 0 |
| `FC_FECHADA` | E digital | fim de curso: porta fechada | 1 |
| `EMERG` | E digital | botão de emergência acionado | 0 |
| `RESET` | E digital | rearme seguro | 0 |
| `M_ABRIR` | S digital | motor no sentido de abrir | 0 |
| `M_FECHAR` | S digital | motor no sentido de fechar | 0 |
| `LAMP_EMERG` | S digital | sinalização de emergência | 0 |

| Etapa | Situação | Ação |
|---|---|---|
| 0 (inicial) | FECHADA | `AGUARDAR presença` |
| 1 | ABRINDO | `M_ABRIR = 1` |
| 2 | ABERTA | `MANTER aberta` |
| 3 | FECHANDO | `M_FECHAR = 1` |
| 4 | SEGURO | `LAMP_EMERG = 1 · PARAR motores` |

| Transição | De → para | Receptividade |
|---|---|---|
| T0 | 0 → 1 | `PRESENCA ∧ ¬EMERG` |
| T1 | 1 → 2 | `FC_ABERTA ∧ ¬EMERG` |
| T2 | 2 → 3 | `5 s/X2 ∧ ¬PRESENCA ∧ ¬EMERG` — permanência mínima de 5 s e zona livre |
| T3 | 3 → 0 | `FC_FECHADA ∧ ¬PRESENCA ∧ ¬EMERG` |
| T4 | 3 → 1 | `PRESENCA ∧ ¬EMERG` — reabertura de segurança durante o fechamento |
| T5–T8 | 0, 1, 2, 3 → 4 | `EMERG` — emergência domina em qualquer etapa de operação |
| T9 | 4 → 3 | `RESET ∧ ¬EMERG` — retomada sempre por fechamento controlado |

Leitura do diagrama: a dominância da emergência é obtida por transições
explícitas, e não por prioridade implícita — cada etapa de operação tem uma
saída com receptividade `EMERG`, e todas as demais receptividades carregam
`¬EMERG`, de modo que a seleção em cada etapa é exclusiva pela própria
sintaxe. Em SEGURO os dois motores estão em 0 e apenas a sinalização está
ligada. Na etapa 3 a seleção entre T3 e T4 é exclusiva por
`¬PRESENCA`/`PRESENCA`: alguém entrar na zona durante o fechamento reabre a
porta sem passar por FECHADA. A retomada após emergência vai sempre para
FECHANDO (T9): se a porta já estiver fechada, T3 dispara na mesma evolução e a
etapa 3 é apenas transitória, sem chegar a ligar `M_FECHAR`; se houver
presença, T4 reabre. Como o GRAFCET só tem uma etapa ativa por vez nesta
página, `M_ABRIR` e `M_FECHAR` nunca coincidem — invariante conferido em todos
os cenários (P18).

## Atividade 26 — Esteira separadora de peças A e B (adicional)

Enquadramento: atividade adicional. Página 4 do `.drawio`.

| Tag | Tipo | Significado | Estado seguro |
|---|---|---|---|
| `S_PECA` | E digital | peça na estação de leitura | 0 |
| `TIPO_A` | E digital | sensor classifica como A | 0 |
| `TIPO_B` | E digital | sensor classifica como B | 0 |
| `FC_AV_A`, `FC_RET_A` | E digital | desviador A avançado / recolhido | 0 / 1 |
| `FC_AV_B`, `FC_RET_B` | E digital | desviador B avançado / recolhido | 0 / 1 |
| `RESET` | E digital | rearme após falha | 0 |
| `M_EST` | S digital | motor da esteira | 0 |
| `Y_A` | S digital | solenoide do desviador A | 0 |
| `Y_B` | S digital | solenoide do desviador B | 0 |
| `ALARME` | S digital | alarme de falha | 0 |

Tempos: estabilização da leitura 0,5 s; tempo máximo sem classificação 2 s;
confirmação do desvio 0,3 s.

| Etapa | Situação | Ação |
|---|---|---|
| 0 (inicial) | TRANSPORTANDO | `M_EST = 1` |
| 1 | LENDO | `M_EST = 0 · LER tipo` |
| 2 | DESVIANDO A | `Y_A = 1` |
| 3 | DESVIANDO B | `Y_B = 1` |
| 4 | CONFIRMANDO | `AGUARDAR desvio` |
| 5 | RECOLHENDO | `Y_A = 0 · Y_B = 0` |
| 6 | LIBERANDO | `M_EST = 1` |
| 7 | FALHA | `ALARME = 1` |

| Transição | De → para | Receptividade |
|---|---|---|
| T0 | 0 → 1 | `S_PECA` |
| T1 | 1 → 2 | `0,5 s/X1 ∧ TIPO_A ∧ ¬TIPO_B` |
| T2 | 1 → 3 | `0,5 s/X1 ∧ ¬TIPO_A ∧ TIPO_B` |
| T3 | 1 → 7 | `TIPO_A ∧ TIPO_B` — inconsistência sensorial |
| T4 | 1 → 7 | `2 s/X1 ∧ ¬TIPO_A ∧ ¬TIPO_B` — sem classificação, tempo esgotado |
| T5 | 2 → 4 | `FC_AV_A` |
| T6 | 3 → 4 | `FC_AV_B` |
| T7 | 4 → 5 | `0,3 s/X4` — confirmação do desvio |
| T8 | 5 → 6 | `FC_RET_A ∧ FC_RET_B` — retorno confirmado antes de liberar |
| T9 | 6 → 0 | `¬S_PECA` — estação livre, ciclo reinicia |
| T10 | 7 → 0 | `RESET ∧ ¬S_PECA` — peça retirada e rearme |

Leitura do diagrama: a seleção na etapa 1 tem quatro saídas (T1–T4) que são
mutuamente exclusivas já no par (`TIPO_A`, `TIPO_B`): A puro, B puro, ambos
(inconsistência) e nenhum (tempo esgotado) cobrem as quatro combinações sem
sobreposição, e os temporizadores só atrasam, nunca criam concorrência — a
verificação estática enumera as 16 combinações (C19). As duas etapas de
desvio convergem por seleção na etapa 4. Depois da confirmação (0,3 s), o
desviador é recolhido com a esteira parada — ambos os `Y` em 0; o desviador
não usado já estava recolhido, por isso a receptividade `FC_RET_A ∧
FC_RET_B` — e só com o retorno confirmado (T8) a esteira religa para liberar
a estação (T9, `¬S_PECA`). A ordem é a do exemplo de referência da aula:
retorno confirmado antes de liberar, e a estação livre antes de reiniciar. Se
a estação ficasse vazia antes do retorno confirmado, o modelo permanece em
RECOLHENDO com `M_EST = 0` (C14); se o retorno se confirma com a peça ainda na
estação, LIBERANDO religa a esteira até ela sair (C12, C13). `Y_A` e `Y_B`
nunca coincidem, `M_EST` está em 0 sempre que um solenoide está energizado e
nos cenários executados `M_EST` só vale 1 com os dois desviadores recolhidos
(C18, IN6, sob as hipóteses acima); no traço do ciclo de desvio, T8 dispara
antes de T9 (C20).

## Atividade 27 — Percurso manual (obrigatória)

Enquadramento: obrigatória. Página 5 do `.drawio`, desenhada como tabelas;
usa as E/S do semáforo (Atividade 24) e, no percurso de falha, as do
misturador (Atividade 23). O percurso é o traço literal pedido no
enunciado da Semana 5:

| Passo | Marcação ativa | Entradas/eventos | Transição | Nova marcação |
|---|---|---|---|---|
| 0 | E0 | tempo < 8 s | nenhuma | E0 |
| 1 | E0 | tempo = 8 s | T0 | E1 |
| 2 | E1 | tempo = 10 s | T1 | E2 |
| 3 | E2 | tempo = 3 s | T2 | E0 |

Leitura: cada linha mostra o par (marcação, evento) que habilita uma
transição e a marcação resultante — é o mesmo procedimento que o
interpretador aplica a todas as páginas. O verificador confere o conteúdo
desta tabela contra o traço executado do semáforo (caso S13). A página 5
traz ainda, no mesmo formato, o percurso das **fronteiras temporais** do
semáforo (7,9/8,1 s, 9,9/10,1 s, 2,9/3,1 s) e o percurso de **falha** do
misturador (enchimento sem nível alto por 119,9 s e por 120 s, depois o
rearme com `RESET`); cada linha dessas duas tabelas é executada e conferida —
marcação inicial, entradas e tempo, transição disparada e nova marcação —
nos casos S14 e M14. Os demais cenários de todas as páginas estão em
`casos_teste.csv` e em [testes/casos-de-teste.md](testes/casos-de-teste.md).

## Como reproduzir

1. **No diagrams.net:** abra <https://app.diagrams.net>, escolha
   *Arquivo → Abrir de → Dispositivo* (ou *Arquivo → Importar de → Dispositivo*)
   e selecione `grafcet.drawio`. As cinco páginas aparecem como abas na parte
   inferior; a página 2 é o semáforo. O arquivo é XML não comprimido, então
   também pode ser inspecionado em qualquer editor de texto.
2. **No VS Code:** instale a extensão *Draw.io Integration* (`hediet.vscode-drawio`)
   e abra `grafcet.drawio` diretamente; a extensão renderiza o diagrama com o
   mesmo editor e o seletor de páginas na barra inferior.
3. **Percorrendo um cenário à mão:** escolha a página, marque a etapa
   inicial (contorno duplo) como ativa e zere o relógio dela; aplique as
   entradas do caso (por exemplo, na porta, `PRESENCA = 1`); percorra as
   transições que saem das etapas ativas e dispare as que têm receptividade
   verdadeira — para `N s/Xk`, verifique se a etapa k está ativa há N s ou
   mais; desative as etapas anteriores, ative as posteriores e repita até
   nada mais disparar; só então leia as ações das etapas ativas. Compare com
   as colunas **Esperado** e **Obtido** de `casos_teste.csv`.
4. **No repositório de trabalho:** o próprio `grafcet.drawio` é gerado por
   `gera_grafcet.py` a partir da especificação de projeto (o cabeçalho do XML
   registra isso no atributo `agent`) e depois aberto e inspecionado no
   diagrams.net. `python Entregas/TP05/simulacao/verifica_tp05.py`
   lê o `.drawio` do pacote, executa os cenários pelo interpretador
   (`grafcet_interpreta.py`) e regrava `casos_teste.csv`,
   `testes/casos-de-teste.md` e `testes/resultados.json`. As exportações
   PNG/PDF são feitas por `exporta.ps1`, que chama o draw.io desktop 31.5.3 em
   linha de comando. Esses scripts ficam fora do pacote publicado, como nos TPs
   anteriores.

## Validação

Foram aprovados **77 de 77** casos — 67 cenários dos grupos S, M, P e C, mais
4 auditorias estáticas (uma por página) e 6 invariantes dinâmicos. O valor **esperado** foi
fixado antes da execução, na especificação de projeto deste trabalho, e
codificado como texto literal no verificador: S01–S04 reproduzem a tabela de
referência do enunciado para o semáforo; os demais cenários — fronteiras
"antes, no limite e depois", falhas, emergência e sincronização — foram
definidos pelo autor. O valor **obtido**
vem da execução do próprio `grafcet.drawio` entregue: um interpretador lê o
XML do arquivo (etapas, transições, arcos, receptividades e ações), reconstrói
o grafo e aplica as regras de evolução da IEC 60848 — disparo quando todas as
etapas anteriores estão ativas e a receptividade é verdadeira; desativação e
ativação atômicas; disparos simultâneos; busca de situação estável antes de
calcular as ações; base de tempo de 0,1 s em inteiros. Não há uma segunda
implementação da lógica em Python que pudesse concordar consigo mesma: o que
se executa é o desenho.

| Grupo | Cobertura | Página | Resultado |
|---|---|---|---:|
| S01–S14 | semáforo: literais do enunciado, fronteiras 7,9/8,0/8,1 s etc., ciclo de 21 s, inicialização, invariante "uma lâmpada", percurso manual e percurso de fronteiras da página 5 conferidos contra a execução | 2 e 5 | 14/14 |
| M01–M14 | misturador: ciclo normal, fronteiras 29,9/30,0 s e 119,9/120,0 s, falha e rearme, exclusividade T1/T4, percurso de falha da página 5 conferido contra a execução | 1 e 5 | 14/14 |
| P01–P19 | porta: ciclo normal, permanência 4,9/5,0 s, reabertura, emergência em E0–E3, rearme, invariante dos motores, exclusividade | 3 | 19/19 |
| C01–C20 | esteira: fronteiras 0,4/0,5 s, 1,9/2,0 s e 0,2/0,3 s, falhas, sincronização do retorno antes de liberar (a esteira não religa com a estação vazia enquanto o retorno não é confirmado), invariantes, exclusividade nas 16 combinações, ordem T8 antes de T9 | 4 | 20/20 |
| ES1–ES4 | verificações estáticas do interpretador por página: inicial única, identificadores numéricos únicos, receptividades válidas, arcos admitidos, exclusividade enumerada, alcançabilidade e geometria da convenção | 1–4 | 4/4 |
| IN1–IN6 | invariantes vigiados a cada décimo e a cada leitura de entradas de todos os cenários: nenhuma etapa ativa com `TAG = 0` enquanto outra mantém `TAG = 1` (por página); na porta, os dois motores em 0 em SEGURO; na esteira, `M_EST = 1` somente com os dois desviadores recolhidos — 15.061 instantes vigiados (IN5 e IN6 recontam os instantes das páginas 3 e 4) | 1–4 | 6/6 |
| **Total** |  |  | **77/77** |

Antes dos cenários, o interpretador aplica verificações estáticas sobre o
XML: exatamente uma etapa inicial por página de GRAFCET; identificadores
únicos e numéricos; toda transição com receptividade não vazia e
sintaticamente válida; todo arco ligando apenas etapa→transição,
transição→etapa ou etapa/transição↔barra dupla; **exclusividade de seleção**
por enumeração de todas as combinações das variáveis de cada etapa com duas
ou mais saídas (temporizadores como booleanos independentes); ausência de
becos sem saída (toda etapa alcança a inicial de volta); e a geometria da
convenção (etapa quadrada, inicial com contorno duplo, transição como barra
baixa e larga, ação ligada por traço sem seta).

Durante todos os cenários são vigiados os invariantes: semáforo com
exatamente uma lâmpada em 1 a cada instante; porta com `M_ABRIR` e `M_FECHAR`
nunca simultâneos e ambos em 0 em SEGURO; esteira com `Y_A` e `Y_B` nunca
simultâneos, `M_EST = 0` sempre que um `Y` estiver em 1 e `M_EST = 1` somente
com `FC_RET_A ∧ FC_RET_B`; e nenhuma etapa ativa com `TAG = 0` enquanto outra
ativa mantém `TAG = 1`.

O registro `testes/resultados.json` traz o SHA-256 do `.drawio`, do
interpretador e do verificador e a data UTC da execução
(execução de 2026-09-30T03:44:05+00:00; `grafcet.drawio`
`39ba03dfcb001ef13a6a8f987515d882d4419cf5536edcaf89c8f1dfc70f469c`;
`grafcet_interpreta.py` `336521a15f7a3ddbd98b26624f59b34656d83eaaba3e8cab92f7b34d3437da60`;
`verifica_tp05.py` `c330985bf3f3fc769d0b2a64fa4a4da878b3065ffa3efe0b02f09cdcf856030b`).

## Checklist de aceitação

| # | Critério, em palavras próprias | Onde é provado |
|---|---|---|
| 1 | inicial marcada de forma inequívoca | verificação estática (contorno duplo, uma por página) e PNG/PDF |
| 2 | etapas identificadas e nomeadas | número único + nome no diagrama + tabelas de etapas deste README |
| 3 | receptividades testáveis | o parser aceita todas; cada uma é exercitada por ao menos um caso do CSV |
| 4 | seleções sem ambiguidade | exclusividade enumerada: M13, P19, C19 |
| 5 | paralelismo sincronizado | não se aplica: nenhum modelo entregue usa barras duplas — a esteira exige o retorno confirmado *antes* de liberar, o que é sequência (C12, C14, C20); o interpretador implementa divergência e convergência paralelas e as exercita no autoteste |
| 6 | emergência com saída segura | P09–P17 e invariante P18 |
| 7 | cobertura normal, limite e falha | grupos `normal`, `limite`, `falha`, `emergencia`, `sincronizacao`, `invariante`, `estatico` do CSV |

## Fundamentos aplicados

**Quando a mesma entrada produz ações diferentes?** Quando o sistema é
sequencial: a saída depende da etapa ativa, não só das entradas. `PRESENCA = 1`
liga `M_ABRIR` em FECHADA, reabre a porta em FECHANDO e não faz nada em
SEGURO — a memória do estado está na marcação, não na entrada.

**Quais são as duas condições de disparo?** A transição precisa estar
habilitada — todas as etapas imediatamente anteriores ativas — e a
receptividade precisa ser verdadeira. Uma sem a outra não dispara: `8 s/X0`
verdadeira com E0 inativa é irrelevante, e E0 ativa com 7,9 s ainda não basta.

**Por que receptividades de seleção devem ser exclusivas?** Porque, se duas
saídas da mesma etapa fossem verdadeiras ao mesmo tempo, as duas disparariam
juntas e dois ramos alternativos ficariam ativos — na esteira, `Y_A` e `Y_B`
atuados ao mesmo tempo. A exclusividade garante que a escolha é uma decisão,
não uma coincidência.

**O que uma convergência paralela aguarda?** Que todas as etapas anteriores à
barra dupla estejam ativas simultaneamente; só então a receptividade é
avaliada; se apenas um ramo chegou, a transição fica bloqueada. Nos modelos
entregues não há convergência paralela: na esteira, o retorno do desviador
precisa estar confirmado *antes* de a estação ser liberada, o que é uma
sequência (T8 e depois T9), não dois ramos simultâneos.

**GRAFCET (IEC 60848) e SFC (IEC 61131-3).** O GRAFCET é linguagem de
especificação do comportamento, independente de tecnologia: descreve o que o
sistema deve fazer. O SFC é linguagem de programação de CLP derivada dele, com
semântica de implementação — qualificadores de ação (N, S, R, D, L, P),
varredura cíclica e detalhes que variam entre fabricantes. Especifica-se em
GRAFCET; programa-se em SFC.

## Limitações

O interpretador é uma execução didática do GRAFCET, não um CLP: não modela
tempo de varredura, atrasos de atuadores nem falhas elétricas, e as ações são
apenas contínuas. Nenhum modelo usa
divergência ou convergência paralela. A emergência está modelada por
transições explícitas para uma etapa segura, e não por ordem de forçamento
hierárquico; a permanência da
porta aberta é mínima e não reinicia com nova presença; os tempos de
esgotamento do enchimento e da classificação são hipóteses de projeto. O
detalhamento de cada limite, com a melhoria correspondente e as alternativas
descartadas, está em [NOTAS.md](NOTAS.md).
