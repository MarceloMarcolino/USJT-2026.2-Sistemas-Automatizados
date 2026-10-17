# TP08 — Sistemas supervisórios: protótipo navegável de HMI do reservatório R-101

**Autor:** Marcelo Antonio Pereira Marcolino — USJT — ESO1AN-MCE3<br>
**Estado:** protótipo construído no Figma a partir de arquivo vazio, estrutura conferida quadro a quadro com o
desenho (65/65), 19/19 casos de navegação executados no modo Present **sem login** (link "qualquer pessoa com o
link pode ver"), 32/32 casos de lógica e de CLP e 14/14 mutantes reprovados<br>
**Data:** construção e verificação em 17 de outubro de 2026; execução sem login no Present às 02:54 UTC
(16 de outubro, 23:54 em Brasília)

## Links e artefatos

- **Protótipo no Figma** (Present começa em "N · Processo"): ver
  [`prototipo/link-figma.txt`](prototipo/link-figma.txt). Arquivo "TP08 Supervisório R101", páginas
  **Protótipo** (65 quadros) e **Componentes** (6 componentes, 23 variantes).
- [`testes/tags.csv`](testes/tags.csv) — dicionário de 11 tags (as seis primeiras são as do enunciado):
  nome, tipo, unidade, faixa, acesso, origem, descrição e uso na tela.
- [`casos_teste.csv`](casos_teste.csv) — 51 casos com procedimento, esperado, obtido e situação: os 5
  obrigatórios (T01–T04 no modelo e de novo no Present como T01p–T04p; T05 no Present), os 6 da prática do
  gabarito, os do exemplo da teoria, permissivos, falhas e o lado do CLP.
- [`testes/alarmes.csv`](testes/alarmes.csv) — matriz de alarmes A01–A05;
  [`testes/navegacao.csv`](testes/navegacao.csv) — as 681 ligações (origem, ação, destino e se o destino
  volta direto à origem); [`testes/resultados.json`](testes/resultados.json) — placar, mutantes,
  resultado de cada caso e SHA-256 dos arquivos do pacote.
- [`evidencias/`](evidencias/) — 12 capturas feitas no modo Present (ver *Capturas*).

## Objetivo

Especificar e testar a interface de supervisão do reservatório R-101 com a bomba de entrada P-101:
mostrar nível, qualidade, modo e estado da bomba; gerar e tratar alarmes; solicitar comandos sem fingir
que foram executados; e deixar claro quando o dado não merece confiança. O protótipo é uma
**especificação navegável**, não um SCADA: não fala com CLP, não guarda histórico real e não usa protocolo
industrial.

## Como o protótipo foi construído

O enunciado adota o Figma (o diagrams.net é só contingência para login bloqueado). Por decisão do Marcelo,
o arquivo foi criado vazio na conta dele e montado pelo **conector oficial do Figma** (autorização OAuth
dada por ele; nenhuma senha ou token passou pelo assistente), que executa código na Plugin API do Figma:

1. o comportamento da tela está num modelo em Python (`hmi.py`, no ferramental): tags, alarmes,
   permissivos e o que cada tela mostra para um instantâneo das tags;
2. dezesseis cenários (`cenarios.py`) viram 65 quadros com textos, variantes e ligações gerados desse
   modelo (`desenho.py`);
3. o código enviado ao Figma cria os componentes com variantes, desenha os quadros e liga os elementos
   ("On click → Navigate to");
4. a estrutura é lida de volta do arquivo e comparada com o desenho por um resumo SHA-256 de cada quadro
   (textos, ligações, variantes das instâncias e caixas clicáveis);
5. os casos de navegação são executados no modo Present, com cliques reais no visualizador do Figma.

## Decisões de projeto

Numeração da especificação de trabalho (D1, plataforma, e D14, extensão 3, estão nas seções acima e em *Limites*).

| # | Decisão | Por quê |
|---|---|---|
| D2 | Limites **H = 75 %** e **HH = 90 %**; normalizam abaixo de 73 % e de 88 % | As matrizes de alarmes usam 75/90; os gráficos de tendência do material marcam "HH 80 %", o que não confere com elas. A banda morta evita alarme que liga e desliga sem parar (*chattering*) |
| D3 | `COMM_PLC` é ENUM **GOOD/BAD** | É o tipo do dicionário mínimo e do caso T04; o gabarito usa BOOL (BAD aqui equivale a `COMM_PLC=0` lá) |
| D4 | Nomes de tag do dicionário mínimo (`LT_101.PV`, `P_101.CMD`...) | Não misturar com a grafia do gabarito (`LT_101_PV`, `P101_CMD`) |
| D5 | `P_101.MODE` = **MANUAL / AUTO / LOCAL**, somente leitura; só MANUAL aceita comando remoto | São os três modos da situação-problema; em AUTO decide a sequência do CLP, em LOCAL o painel de campo |
| D6 | Prioridades: A01 (H) **Média**; A02 (HH), A03 (bomba), A04 (comunicação) e A05 (transmissor) **Alta** | O material da aula classifica H como baixa e a falha da bomba como média; adotou-se o gabarito. Com a bomba enchendo, H antecede HH em poucos minutos |
| D7 | Sem comunicação, **todo** valor do CLP vira "---" ou UNKNOWN, inclusive o modo; alarmes de processo continuam listados com "Dado incerto desde …" | Evitar falsa confiança; não esconder o HH quando a comunicação cai |
| D8 | Intertravamento HH e falha segura **no CLP**, em qualquer modo; em MANUAL o CLP zera `P_101.CMD`; nenhum modo religa sozinho | A tela não substitui o intertravamento; ela mostra o motivo da parada |
| D9 | Sem P-102 e sem o permissivo "nível acima do mínimo" | O enunciado define só a P-101; nível baixo não impede a partida de uma bomba de **entrada** |
| D10 | Lista de alarmes por prioridade, depois estado, depois do mais recente | Com HH e falha de comunicação, a comunicação fica no topo e o HH continua visível |
| D11 | **PARAR P-101** abre um quadro de confirmação com alvo, estado atual e consequência; PARTIR é avaliado pelos permissivos | Confirmação específica pedida no T05; quadro inteiro para o teste em Present registrar a troca de tela |
| D12 | Cada cenário tem quatro telas com o mesmo instantâneo; a troca de cenário e o "retorno do CLP" ficam numa **faixa de demonstração** tracejada | A navegação nunca mistura situações diferentes; os atalhos de teste não se passam por comandos do processo |
| D13 | Data e hora simuladas (16/10/2026) | O protótipo não lê CLP; o cabeçalho diz "(simulado)" |
| D15 | Cor só para anormalidade e sempre com texto e forma: NORMAL círculo, ATENÇÃO losango, ALARME triângulo, FALHA "X"; bomba em marcha cheia, parada vazada, desconhecida tracejada | Estado legível sem depender só da cor |

## Dicionário de tags

| Tag | Tipo | Unid. | Valores | Acesso | O que é |
|---|---|---|---|---|---|
| `LT_101.PV` | REAL | % | 0,0 a 100,0 | R | Nível medido no R-101 |
| `LT_101.QUALITY` | ENUM | - | GOOD, BAD | R | Qualidade da medida |
| `P_101.CMD` | BOOL | - | 0 parar, 1 partir | RW | Pedido remoto à P-101 (vale em MANUAL) |
| `P_101.STATUS` | ENUM | - | RUN, STOP | R | Retorno real da bomba |
| `P_101.MODE` | ENUM | - | MANUAL, AUTO, LOCAL | R | Quem comanda a bomba |
| `COMM_PLC` | ENUM | - | GOOD, BAD | R | Comunicação HMI–CLP |
| `P_101.FAIL` | BOOL | - | 0, 1 | R | Falha da bomba |
| `EMG_OK` | BOOL | - | 1 = íntegra | R | Emergência não acionada |
| `ALM_L_H` | BOOL | - | 0, 1 | R | Nível alto (≥ 75 %) |
| `ALM_L_HH` | BOOL | - | 0, 1 | R | Nível muito alto (≥ 90 %); intertrava a P-101 |
| `COMM_PLC.LAST_OK` | TIME | hh:mm:ss | - | R | Última leitura válida |

## Alarmes e permissivos

| ID | Condição | Prioridade | Mensagem | Ação recomendada |
|---|---|---|---|---|
| A01 | `ALM_L_H = 1` | Média | Nível alto no R-101 (H ≥ 75 %) | Acompanhar a tendência e a vazão de entrada |
| A02 | `ALM_L_HH = 1` | Alta | Nível muito alto no R-101 (HH ≥ 90 %) | Confirmar a P-101 parada e verificar a válvula de entrada |
| A03 | `P_101.FAIL = 1` | Alta | Falha na bomba P-101 | Manter parada e acionar a manutenção |
| A04 | `COMM_PLC = BAD` | Alta | Falha de comunicação com o CLP | Comandos bloqueados: verificar a rede e o processo em campo |
| A05 | `LT_101.QUALITY = BAD` | Alta | Medição de nível inválida (LT-101) | Validar o transmissor; P-101 parada pelo CLP |

Reconhecer registra que o operador viu o alarme; não faz a condição sumir. Um alarme reconhecido e já
normalizado sai da lista e fica no registro de eventos.

Partida da P-101 — a tela de Manutenção mostra cada condição como VERDADEIRO, FALSO ou DESCONHECIDO e
destaca a **primeira causa** que impede a partida, com uma orientação:
P1 `COMM_PLC = GOOD` · P2 `P_101.MODE = MANUAL` · P3 `EMG_OK = 1` · P4 `P_101.FAIL = 0` ·
P5 `LT_101.QUALITY = GOOD` · P6 `ALM_L_HH = 0`. Sem comunicação, P2 a P6 aparecem como DESCONHECIDO.

## Telas e navegação

- **Processo · visão geral**: tanque com H e HH marcados, indicador de estado, campos `LT_101.PV`,
  `LT_101.QUALITY`, `P_101.STATUS` (retorno) e `P_101.MODE`, bloco da bomba com retorno, comando e
  transição ("PARANDO · aguardando retorno"), faixa com o alarme mais importante e comandos PARTIR/PARAR
  com o motivo quando indisponíveis. Clicar na faixa abre Alarmes; clicar na bomba abre Manutenção.
- **Alarmes**: hora, prioridade (texto, cor e forma), fonte, mensagem, estado, ação recomendada, botão
  Reconhecer nos não reconhecidos; a fonte leva de volta ao Processo; registro de eventos com usuário.
- **Tendência** (extensão 1): 60 min, H e HH tracejados, faixa de qualidade, lacuna marcada quando não há
  dado válido, marcas de comando e de intertravamento.
- **Manutenção** (inclui a extensão 2): comunicação e idade do dado, qualidade do instrumento, modo,
  último pedido e retorno separados, falhas ativas, matriz de permissivos e funções de manutenção
  separadas, indisponíveis ao perfil OPERADOR, com o perfil exigido.
- A barra de navegação de toda tela volta ao Processo em um clique. A faixa de demonstração leva à mesma
  tela em outro cenário e, nos cenários de comando, simula o retorno do CLP.

**Ciclo do comando:** Normal → PARAR → confirmação → Cancelar (nada muda) ou Confirmar → "Parada
solicitada" (pedido enviado, retorno ainda RUN) → retorno simulado → "Parada confirmada" (STOP) → PARTIR →
"Partida solicitada" → retorno simulado → Normal.

| Cenário | Situação | Estado | Alarmes |
|---|---|---|---|
| Normal · 58 % | MANUAL, P-101 em marcha | NORMAL | — |
| Parada solicitada / confirmada / partida solicitada | ciclo do comando | NORMAL | — |
| Atenção H · 78 % (e reconhecido) | AUTO | ATENÇÃO | A01 |
| Alarme HH · 92 % (e reconhecido) | AUTO, P-101 parada pelo intertravamento | ALARME | A02 e A01 |
| Comunicação BAD (e reconhecido) | sem comunicação depois do HH | FALHA | A04, A02 e A01 incertos |
| LT-101 BAD (e reconhecido) | AUTO, falha segura | FALHA | A05 |
| Falha P-101 (e reconhecida) | MANUAL, bomba em falha | NORMAL | A03 |
| Modo LOCAL · 70 % (e encerrado) | LOCAL; H normalizado sem reconhecimento | NORMAL | A01 normalizado |

## Componentes (página "Componentes")

| Componente | Variantes | Textos editáveis |
|---|---|---|
| Indicador de estado | NORMAL, ATENÇÃO, ALARME, FALHA | Detalhe |
| Campo de valor | GOOD, BAD, UNKNOWN | Tag, Valor, Selo |
| Botão | Habilitado, Desabilitado, Pressionado | Rótulo |
| Linha de alarme | Alta, Média, Baixa × ativo não reconhecido, ativo reconhecido, normalizado não reconhecido | Hora, Fonte, Mensagem, Ação, Nota |
| Item de navegação | Selecionado sim/não | Rótulo |
| Chip de demonstração | Atual sim/não | Rótulo |

## Validação

O esperado de cada caso foi escrito antes de executar o modelo ou abrir o protótipo.

| Verificação | Resultado |
|---|---|
| Casos de lógica de apresentação (modelo) | **24/24** |
| Casos do lado do CLP (bits de alarme e política de intertravamento, varredura a varredura) | **8/8** |
| Coerência de cada cenário com a política do CLP e com a matriz de alarmes | sem violação |
| Mutantes do modelo (defeitos plantados que os casos têm de pegar) | **14/14** reprovados |
| Navegação no grafo do desenho (cada tela volta ao Processo em um passo; todos os 65 quadros alcançáveis; botão habilitado sempre com ação) | 19/19 casos, invariantes sem violação |
| Arquivo real do Figma: resumo SHA-256 de cada quadro igual ao do desenho; componentes; ponto de partida | **65/65** quadros; 6 componentes e 23 variantes; início "N · Processo" |
| **Casos executados no modo Present, sem login** (veredito calculado pelo verificador a partir do nó observado em cada clique) | **19/19** |
| Ensaios contra o próprio verificador (registros forjados, incompletos ou contraditórios devem reprovar) | 12/12 |

Os cinco casos obrigatórios:

| ID | Cenário | Esperado | Obtido no modelo | Obtido no Present (sem login) |
|---|---|---|---|---|
| T01 | Nível 58 %, GOOD | NORMAL, 58,0 %, sem alarmes; PARAR disponível com confirmação; PARTIR indisponível porque a bomba já está em operação | conforme esperado | T01p: abre em "N · Processo" com esses textos |
| T02 | Nível 78 % | ATENÇÃO; A01 Média, ativo não reconhecido, na faixa e na lista | conforme esperado | T02p: "H · Processo" com 78,0 % e a faixa de A01 |
| T03 | Nível 92 % | ALARME; A02 Alta no topo; P-101 parada pelo intertravamento | conforme esperado | T03p: "HH · Processo"; a lista em P05 ("HH · Alarmes") |
| T04 | `COMM_PLC = BAD` | "---", BAD e UNKNOWN; comandos bloqueados com o motivo; A04 no topo, A02 e A01 marcados como incertos | conforme esperado | T04p e P06: "CB · Processo" com "---", UNKNOWN e o bloqueio |
| T05 | Parar P-101 | quadro de confirmação com alvo, estado atual, consequência, Cancelar e Confirmar | — (caso de navegação) | "N · Processo · confirmar parada" |

**Histórico de execuções no Present (17/10/2026).** O visualizador ficou preto com o parâmetro `hide-ui=1`
e, sem o id do quadro, abria a primeira página do arquivo (Componentes); a página Protótipo passou para a
primeira posição e `hide-ui` deixou de ser usado. Na primeira execução completa, 14/15: no P04c o coletor
localizou o quadro durante o carregamento (escala 1,08 em vez de 1) e o clique caiu fora do botão. O coletor
passou a conferir a altura da faixa do cabeçalho antes de clicar, e a execução completa seguinte deu 15/15
(com a sessão do Marcelo; registro em `present-sessao-marcelo.json` no ferramental). Depois, por apontamento
do revisor, os obrigatórios T01–T04 ganharam versões de navegação (T01p–T04p) com o esperado escrito antes; com o
protótipo compartilhado só para visualização, os 19 casos e as 12 capturas foram executados num Chrome com perfil
novo, **sem login**: 19/19.

## Capturas

Feitas no modo Present (1280 × 720), pelo link de visualização, sem login:

| Arquivo | Quadro |
|---|---|
| `processo-normal.png` | Normal — 58 %, GOOD, PARAR disponível |
| `processo-hh.png` | HH — 92 %, ALARME, P-101 parada pelo intertravamento |
| `falha-comunicacao.png` | Comunicação BAD — "---", UNKNOWN, comandos bloqueados |
| `confirmacao-parada.png` | Confirmação específica da parada |
| `parada-solicitada.png` | Pedido enviado, retorno ainda RUN |
| `alarmes-hh.png`, `alarmes-comunicacao.png`, `alarmes-falha-bomba.png` | Listas de alarmes com estados diferentes |
| `manutencao-permissivos.png`, `manutencao-comunicacao.png` | Permissivos com primeira causa; sem comunicação |
| `tendencia-hh.png` | Tendência de 60 min com H, HH e marca do intertravamento |
| `modo-local.png` | Modo LOCAL: comandos remotos indisponíveis |

## Checklist de entrega (gabarito, apêndice A)

| Verificação | Situação |
|---|---|
| Telas Processo, Alarmes e Manutenção completas | sim (e Tendência) |
| Tags com nome, tipo, unidade, acesso e descrição | sim — `testes/tags.csv` |
| Estados normal, atenção, alarme e falha | sim — componente Indicador de estado e cenários |
| Links testados nos dois sentidos | sim — 19/19 no Present; `testes/navegacao.csv` |
| Comando com confirmação e retorno separados | sim — T05, P03, P04a–c |
| Bloqueio sob BAD e indicação de perfil | sim — T04, P06; funções de manutenção com perfil exigido |
| Evidências: link, capturas, CSV e README | sim (link em `prototipo/`) |
| Repositório e protótipo testados anonimamente | protótipo: sim, 19/19 sem login; repositório: depois da publicação |

## Limites

- O protótipo especifica a HMI; não executa SCADA, histórico nem comunicação real. Valores e horas são
  simulados.
- Em Present, os estados são quadros: o retorno do CLP e a troca de cenário são botões de demonstração.
- Reconhecimento, perfil e confirmação não têm autenticação real; o perfil OPERADOR é fixo.
- Os filtros da lista de alarmes estão especificados, mas inativos.
- A revisão por outro estudante (extensão 3) não foi feita: ela depende de um colega.
- O lado do CLP (banda morta, intertravamento, falha segura, comando zerado, parada retida) foi descrito e
  testado num modelo em Python; não foi programado em CLP nesta TP.

## Fontes

- Material da disciplina Sistemas Automatizados, Semana 8 (sistemas supervisórios), USJT, 2026: deck da
  aula e gabarito detalhado da TP08 — enunciado e critério de correção; requisitos reescritos com palavras
  próprias, nomes de tags e IDs de testes mantidos.
- Figma: documentação do servidor MCP (ferramentas e limites de uso), em developers.figma.com, e as
  instruções do conector oficial para a Plugin API, consultadas em 16 e 17 de outubro de 2026.
- Não consultadas diretamente: ISA-101, ISA-18.2 e IEC 62443, citadas no material da disciplina. Nada neste
  README depende delas.
