# TP05 — Notas: limites, melhorias e decisões de projeto

**Autor:** Marcelo Antonio Pereira Marcolino — USJT — ESO1AN-MCE3<br>
**Estado:** acompanha o `README.md` desta pasta (validação 77/77)<br>
**Data:** 29 de setembro de 2026

Este documento reúne o que os GRAFCETs entregues **não** cobrem, por que cada
limite existe e qual seria a melhoria correspondente, além das decisões de
projeto tomadas onde o enunciado deixava alternativas. O que está validado
está no `README.md` e em `testes/`; aqui está o que fica declarado como
fronteira do trabalho.

## Limites e melhorias

### 1. Execução didática, não CLP

O interpretador que executa o `.drawio` aplica as regras de evolução da IEC
60848 sobre uma base de tempo discreta de 0,1 s: lê entradas, dispara tudo o
que está disparável até alcançar situação estável e só então calcula as
ações. Isso é uma execução do modelo, não a execução de um controlador. Não
há tempo de varredura, nem ordem de resolução de rede, nem latência entre a
mudança de uma entrada e sua leitura; os atuadores respondem instantaneamente
(um fim de curso "aparece" quando o cenário o liga, e não porque um motor
percorreu um curso); e não existem falhas elétricas — sensor travado, cabo
rompido, contato colado — que num sistema real alterariam a leitura sem
alterar o processo. As passagens de fronteira ("7,9 s permanece, 8,0 s
dispara") são exatas porque o relógio do modelo é exato. **Melhoria:** portar
o GRAFCET obrigatório para SFC num ambiente IEC 61131-3 (ou traduzi-lo para
Ladder com uma bobina por etapa) e repetir os mesmos casos com varredura real,
registrando o jitter observado nas fronteiras; acrescentar um modelo de planta
que ligue `M_ABRIR` ao aparecimento de `FC_ABERTA` após um tempo, para que os
fins de curso deixem de ser eventos injetados.

### 2. Ações apenas contínuas

Toda ação dos diagramas é do tipo contínuo: `TAG = 1` mantém a saída em 1
enquanto a etapa está ativa e a desliga quando ela sai. Não há ações
memorizadas (ligar em uma etapa e desligar em outra), condicionais (ação que
depende de uma expressão além da atividade da etapa) nem de evento (pulso na
ativação ou desativação). Isso obriga a repetir `M_EST = 1` em duas etapas
distintas da esteira (TRANSPORTANDO e LIBERANDO) e a escrever, na etapa
RECOLHENDO, `Y_A = 0 · Y_B = 0`, que é apenas explicitação didática — as
saídas já cairiam pela saída das etapas de desvio. A restrição foi
deliberada: ações contínuas são as únicas cujo efeito é lido diretamente da
marcação, o que mantém a verificação de invariantes trivial e sem estado
oculto. **Melhoria:** introduzir ações memorizadas com sintaxe explícita
(`S M_EST` / `R M_EST`) e estender o interpretador com uma tabela de saídas
retidas; a esteira ficaria mais compacta e a validação passaria a verificar
também a consistência entre pares set/reset.

### 3. Emergência por transições explícitas, não por forçamento

A porta automática trata a emergência com uma transição `EMERG` saindo de
cada etapa de operação para a etapa SEGURO, e com `¬EMERG` em toda
receptividade normal. O resultado é correto e verificável — a exclusividade
de cada seleção é provada por enumeração e os casos P09–P17 exercitam a
emergência em todas as etapas —, mas o custo é gráfico e de manutenção:
quatro transições T5–T8 que dizem a mesma coisa, e cada etapa nova exigiria
mais uma. A IEC 60848 oferece o mecanismo próprio para isso: um GRAFCET
hierárquico em que um grafo de segurança força a situação do grafo de
operação por ordem de forçamento (`F/G_operacao:{}` para esvaziar a
marcação, ou `F/G_operacao:{4}` para impor a etapa segura). **Melhoria:**
separar o diagrama da porta em dois grafos parciais — segurança e operação —
com uma única ordem de forçamento na etapa SEGURO; o interpretador precisaria
de suporte a grafos parciais e a ordens de forçamento, que hoje não tem.

### 4. Permanência da porta não reinicia com nova presença

A transição T2 (`5 s/X2 ∧ ¬PRESENCA ∧ ¬EMERG`) fecha a porta quando ela está
aberta há ao menos 5 s **e** a zona está livre. Se alguém entra na zona aos
3 s e sai aos 4 s, a porta fecha aos 5 s contados desde a abertura — não 5 s
depois da última presença. É uma permanência mínima somada a uma condição de
zona livre, e não um temporizador de inatividade. O comportamento é seguro
(com presença a porta nunca fecha, caso P06) mas pode fechar "cedo demais"
do ponto de vista de conforto. Reiniciar o relógio a cada presença exigiria
uma etapa intermediária — por exemplo, ABERTA-OCUPADA, ativada por `PRESENCA`
e que retorna a ABERTA por `¬PRESENCA`, reiniciando o relógio de ABERTA no
retorno — porque em GRAFCET o relógio de uma etapa só reinicia quando a etapa
é desativada e reativada. **Melhoria:** acrescentar essa etapa intermediária
e os casos de teste correspondentes (presença intermitente antes e depois do
limite de 5 s), mantendo a exclusividade da seleção em ABERTA.

### 5. Timeouts como hipóteses de projeto

O tempo máximo de enchimento do misturador (120 s, transição T4) e o tempo
máximo sem classificação na esteira (2 s, transição T4) não constam do
enunciado: foram escolhidos para que os dois sistemas tenham um caminho de
falha detectável e testável nas fronteiras (119,9/120,0 s e 1,9/2,0 s). Os
valores são plausíveis, mas arbitrários — dependem da vazão da válvula, do
volume do tanque e da velocidade de resposta do sensor de tipo, que o
enunciado não fixa. O que está validado é a **estrutura** (seleção exclusiva
entre caminho normal e falha, rearme por `RESET`), não a adequação numérica.
**Melhoria:** parametrizar esses tempos como constantes nomeadas no diagrama
(por exemplo, `T_ENCH_MAX`) e derivá-los de dados de planta; acrescentar um
caso de teste que verifique que a falha não dispara antes do tempo nominal de
enchimento com nível chegando no último décimo (já coberto em M12) e um
caso equivalente para a esteira.

### 6. Limites de engenharia não modelados na porta e no misturador

Porta: não há esgotamento de tempo nos cursos de abertura e fechamento — um
motor que nunca chega ao fim de curso deixa a etapa ativa indefinidamente; a
reversão FECHANDO → ABRINDO por presença é imediata, sem pausa do motor; fins
de curso contraditórios (`FC_ABERTA` e `FC_FECHADA` em 1) não são detectados;
e `EMERG` está em lógica positiva por simplicidade didática, quando um botão
de emergência real é normalmente fechado e a emergência é a *ausência* do
sinal. Misturador: `START` é nível, não borda — mantido em 1, um novo ciclo
começa assim que a drenagem termina; e o rearme após falha de enchimento
devolve o sistema a AGUARDANDO com o tanque parcialmente cheio
(`NIVEL_BAIXO = 0`), sem caminho automático de dreno. **Melhoria:**
temporizações de curso com etapa de falha; etapa de pausa na reversão;
verificação de fins de curso contraditórios; `EMERG` em lógica negativa com a
receptividade invertida; `START` por borda (etapa de espera de soltura) e
dreno de segurança no rearme.

### 7. Sem paralelismo nos modelos entregues

Nenhuma das quatro páginas usa divergência ou convergência paralela. A
esteira, único candidato natural, exige que o retorno do desviador esteja
confirmado antes de liberar a estação — uma sequência, não dois ramos. O
interpretador implementa as barras duplas segundo a IEC 60848 (uma transição
ativa várias etapas; a convergência só dispara com todas as anteriores
ativas) e as exercita no autoteste. **Melhoria:** um processo com atividades
realmente independentes — por exemplo, contagem e sinalização em paralelo com
um movimento — permitiria demonstrar o construto num modelo entregue.

## Decisões de projeto e alternativas descartadas

**Transporte religado só com o retorno confirmado.** A primeira versão
deste diagrama liberava a estação em paralelo com o recolhimento — uma
divergência paralela após CONFIRMANDO, com LIBERANDO (`M_EST = 1`) correndo ao
mesmo tempo que RECOLHENDO e uma convergência antes de reiniciar. Os testes
passavam porque o esperado incorporava a mesma escolha. A revisão independente
apontou o erro: o exemplo de referência da aula exige retorno confirmado
antes de liberar, e com a esteira andando enquanto o desviador ainda está
avançado a peça seguinte colidiria com ele. Corrigir apenas apagando
`M_EST = 1` do ramo de liberação também não serviria: `¬S_PECA` depende de a
esteira andar, e o ramo ficaria em espera sem progresso. A versão entregue é
sequencial — CONFIRMANDO → RECOLHENDO → LIBERANDO → TRANSPORTANDO — e ganhou
um invariante que teria denunciado a versão anterior: `M_EST = 1` somente com
`FC_RET_A ∧ FC_RET_B` (IN6), além do caso C14, em que a estação vazia não
religa a esteira enquanto o retorno não é confirmado. O custo é o tempo de
retorno somado a cada ciclo; a segurança da sequência vale mais que esse
ganho.

**Alcance do IN6.** A implicação `M_EST = 1 ⇒ FC_RET_A ∧ FC_RET_B` foi
observada nos cenários executados, com partida recolhida e manutenção dos
sinais fora do movimento previsto. T8 confirma o retorno antes da liberação,
mas o modelo não supervisiona a perda posterior dessa confirmação em E0 ou
E6: nesse caso, o motor não é desligado automaticamente. IN6 é uma verificação
dos cenários, não uma prova universal nem um intertravamento contínuo.
**Melhoria:** acrescentar supervisão dos fins de curso durante o transporte,
resposta de falha e os casos de perda de confirmação correspondentes.

**Timeouts como hipóteses, não como omissão.** A alternativa era não modelar
falha alguma no misturador e na esteira, deixando a etapa de enchimento ou de
leitura sem saída caso o sensor nunca responda. Foi descartada porque violaria
o critério de que toda etapa tem retorno alcançável (nenhum beco sem saída) e
porque a prática pede casos de falha. Os tempos ficam declarados como
hipóteses no `README.md` e aqui, e não como requisito.

**Emergência por transições explícitas em vez de forçamento.** Foi escolhida
por ser verificável com as ferramentas desta entrega: cada transição de
emergência é uma aresta do XML, a exclusividade de cada seleção é enumerável
e o interpretador não precisa de hierarquia. O forçamento hierárquico é a
forma normativa mais elegante e fica registrado como melhoria (item 3), mas
exigiria um interpretador com grafos parciais e uma convenção gráfica
adicional que o enunciado não pede.

**Retomada após emergência pela etapa FECHANDO.** Três alternativas foram
consideradas para a transição T9 (`RESET ∧ ¬EMERG`): voltar para FECHADA
(etapa inicial), voltar para ABRINDO, ou voltar para FECHANDO. Voltar para
FECHADA seria mentir sobre a posição da porta quando ela parou aberta ou a
meio curso — a marcação diria "fechada" com `FC_FECHADA = 0` e a próxima
presença ligaria `M_ABRIR` numa porta já aberta. Voltar para ABRINDO
acionaria um motor sem necessidade. FECHANDO é o único destino que leva a
porta a um estado conhecido por movimento controlado, e o faz sem efeito
colateral quando a porta já está fechada: T3 dispara na mesma evolução, a
etapa 3 é transitória e `M_FECHAR` não chega a ligar (caso P15). Se houver
alguém na zona, T4 reabre (P17). Essa decisão depende de o interpretador
respeitar a regra de que etapas transitórias na busca de situação estável não
executam ações — o que é comportamento normativo da IEC 60848 e está coberto
pelo caso P15.

**Permanência mínima da porta em vez de temporizador de inatividade.** A
alternativa (relógio reiniciado a cada presença) foi descartada nesta versão
porque exige etapa intermediária e mais uma seleção a provar exclusiva; a
versão entregue é mais simples, permanece segura (`¬PRESENCA` em T2) e o
limite está declarado no item 4. A escolha privilegia a demonstrabilidade
sobre o conforto de uso.

**Receptividade `FC_RET_A ∧ FC_RET_B` no recolhimento.** A etapa RECOLHENDO
poderia esperar apenas o fim de curso do desviador que foi usado — o que
exigiria lembrar qual foi (duas etapas de recolhimento, uma por tipo, ou
uma ação memorizada). A alternativa adotada usa uma única etapa e exige os
dois fins de curso recolhidos, o que é válido porque o desviador não usado já
estava recolhido (estado seguro `FC_RET_A = FC_RET_B = 1`) e nunca foi
atuado: a receptividade é verdadeira assim que o desviador usado retorna. O
ganho é uma única etapa de recolhimento independente do tipo; o custo é que,
se o desviador não usado saísse da posição recolhida por causa externa, o
ciclo ficaria parado em RECOLHENDO — o que é o comportamento desejável, pois
a esteira não deve reiniciar com um desviador fora de posição.

## Registros

- Validação de 30 de setembro de 2026 (2026-09-30T03:44:05+00:00): 77/77 casos,
  0 achados estáticos, 0 violações de invariantes — detalhes em
  `testes/casos-de-teste.md` e hashes em `testes/resultados.json`
  (`grafcet.drawio` `39ba03dfcb001ef1…`).
- Visualizador público do `.drawio`: <https://viewer.diagrams.net/?highlight=0000ff&nav=1&title=grafcet.drawio#Uhttps://raw.githubusercontent.com/MarceloMarcolino/USJT-2026.2-Sistemas-Automatizados/main/atividades/TP05-grafcet/grafcet.drawio>.

## Conferência da publicação

Em 30/09/2026, às 03:59 UTC, foi conferida a publicação inicial no commit
`703f90ae1bbd241ac8f65f45e81adfe2dabd5da7` do repositório público de entrega.
Os 13 arquivos do pacote foram baixados de `raw.githubusercontent.com`, sem
autenticação nem cookies: todos responderam HTTP 200 e os 13 SHA-256
coincidiram com os arquivos versionados naquele commit.

O visualizador acima foi aberto em um perfil temporário do Chrome, sem login.
As cinco páginas foram percorridas pelos controles de navegação, de 1/5 a
5/5, com títulos e conteúdo conferidos; a página da esteira mostra T8
confirmando os dois retornos antes de LIBERANDO. A conferência terminou às
03:59:44 UTC. Não foi exigida conta para visualizar o diagrama.

Este registro verifica acesso público e integridade da publicação. Não
substitui nem altera a execução dos 77 casos registrada em `testes/`.
