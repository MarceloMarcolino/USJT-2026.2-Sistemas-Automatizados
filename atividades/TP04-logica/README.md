# TP04 — Sistemas discretos e lógica combinacional

Autor: Marcelo Antonio Pereira Marcolino. Revisão registrada em 16/09/2026.

Implementação e validação da lógica combinacional da Semana 4, com CircuitVerse
e PLC Simulator Online. A convenção é lógica positiva: `1` representa a condição
declarada como presente; por isso `E=1` significa **emergência acionada**.

## Estado da entrega

Validação concluída nos motores nativos das duas plataformas, sobre os
arquivos finais desta revisão: **166/166 observações na integração** (um scan
por amostra, incluindo os 32 estados do intertravamento, I01–I06, E01–E05 e
T01–T05) e **72/72 na bateria de emergência** dos adicionais, todas vinculadas
por SHA-256 aos artefatos e executores. A aba 04 explicita uma varredura:
`MB_ANT` recebe o MB observado antes do scan; MA é calculado antes de MB.
O CircuitVerse está em
[`circuitverse/USJT-2026.2-SA-TP04-LogicaCombinacional-MarceloMarcolino.cv`](circuitverse/USJT-2026.2-SA-TP04-LogicaCombinacional-MarceloMarcolino.cv)
e o Ladder nativo está em
[`plc-simulator/diagrama-ladder.json`](plc-simulator/diagrama-ladder.json).

## Links públicos

| Plataforma | Link | Conferência em contexto anônimo (16/09/2026) |
|---|---|---|
| CircuitVerse (projeto com os sete circuitos nomeados) | <https://circuitverse.org/users/458921/projects/2032603> | acesso público confirmado sem sessão; as sete abas e todos os rótulos de entradas/saídas coincidem com o `.cv` versionado, incluindo `MB_ANT` na aba 04 |
| PLC Simulator Online (Ladder com tags legíveis) | <https://app.plcsimulator.online/HBFJRsCQV3LNX1uKhUm8> | carrega sem sessão; a estrutura normalizada completa do diagrama (ordem dos rungs, ramos, tipos de contato/bobina e variáveis por nome) é idêntica à do JSON versionado |

A conferência foi automatizada em contexto de navegador sem cookies ou
sessão (equivalente a janela anônima); o registro com data e hashes está em
`../simulacao/resultados-links.json` no repo de trabalho. Atenção: o link do
PLC Simulator reflete o estado atual daquele workspace — ele não deve ser
editado após a entrega. A reprodução também é garantida pelos arquivos
versionados: o `.cv` importa em qualquer conta e o JSON do Ladder carrega
pela ação nativa descrita em *Como reproduzir*.

## Variáveis e expressões

| Sinal | Valor 1 |
|---|---|
| `S`, `G`, `E`, `M` | START pressionado; proteção fechada; emergência acionada; motor autorizado |
| `T`, `P`, `MNT`, `AL` | temperatura alta; pressão alta; manutenção ativa; alarme condicionado |
| `CA`, `CB`, `MA`, `MB`, `AL_E` | comandos e autorizações A/B; alarme de emergência |
| `SENS_A`, `SENS_B`, `D_XOR` | sensores redundantes e divergência detectada |
| `D_DEM`, `F`, `V` | demanda de ventilação; falha; ventilação autorizada |

No CircuitVerse, cada aba tem entradas independentes. Na ventilação, `D`
equivale a `D_DEM` no Ladder; na arbitragem, `MA`/`MB` equivalem a
`MA_ARB`/`MB_ARB`. A entrada `E` deve ser acionada na aba que está em teste.

1. Partida: `M = S · G · ¬E`.
2. Alarme: `AL = (T + P) · ¬MNT`.
3. Intertravamento didático no Ladder: `MA = CA · ¬MB · ¬E` e
   `MB = CB · ¬MA · ¬E`, com R3 avaliado antes de R4. A aba 04 do
   CircuitVerse representa um scan: `MA = CA · ¬MB_ANT · ¬E`, seguido de
   `MB = CB · ¬MA · ¬E`. Para o scan seguinte, transfira o MB obtido para
   `MB_ANT`. Não é um sensor novo nem um latch físico: é o estado anterior
   explicitado para analisar a varredura sem realimentação circular em gates.
4. Emergência: `AL_E = E`; `¬E` inibe todas as saídas de movimento.
5. Divergência: `D_XOR = (SENS_A · ¬SENS_B) + (¬SENS_A · SENS_B)`. O sinal
   indica apenas inconsistência entre os sensores; a interpretação e os
   limites estão em *Limites do protótipo*.
6. Ventilação: expressão-base `V = D_DEM · G · ¬F`; no modelo completo,
   a prioridade global acrescenta `· ¬E`.
7. Arbitragem determinística (prioridade A):
   `MA_ARB = CA · ¬E`; `MB_ARB = CB · ¬CA · ¬E`.

## Artefatos e evidências

- CircuitVerse: sete circuitos nomeados — portas básicas, partida, alarme,
  intertravamento/emergência e os três adicionais.
- Ladder: nove rungs e 21 tags booleanas, construídos no PLC Simulator Online.
- [Casos de teste](testes/casos-de-teste.md): **238/238 observações da
  revisão atual** — 166 na integração (portas básicas só no CircuitVerse;
  partida, alarme, XOR, os 32 estados `CA/CB/E × MA/MB` anteriores do
  intertravamento, I01–I06, E01–E05 com estado anterior registrado e
  T01–T05 nas duas plataformas) e 72 na emergência dos adicionais (todas
  as 16 combinações `DGFE`, as oito `CA/CB/E`, emergência durante
  funcionamento de V, MA e MB, liberação de E e entrada/saída de falha F).
  O relatório mantém separadamente 79 observações históricas das etapas
  anteriores; elas não são contadas como reexecuções da revisão atual.
- Registros com hashes: [testes/resultados-integracao.json](testes/resultados-integracao.json)
  e [testes/resultados-emergencia.json](testes/resultados-emergencia.json)
  identificam os dois arquivos importados e os executores usados na revisão.
- [P07 no Ladder](evidencias/plc-01-partida-P07.png): `S=1`, `G=1`, `E=0`
  energiza somente `M`.
- [E04 no Ladder](evidencias/plc-02-emergencia-E04.png): `E=1` bloqueia
  `M`, `MA`, `MB`, `MA_ARB`, `MB_ARB` e `V`, enquanto `AL_E=1`.
- Capturas `cv-*.png`: portas, partida, alarme, conflito, emergência, XOR,
  ventilação e arbitragem no CircuitVerse.
- [Ventilação bloqueada por E](evidencias/cv-06-ventilacao-emergencia.png):
  `D=1, G=1, F=0, E=1 → V=0`.
- [Arbitragem bloqueada por E](evidencias/cv-07-arbitragem-emergencia.png):
  `CA=CB=E=1 → MA=MB=0`. As capturas dos estados ativos das abas 06/07
  também foram atualizadas para mostrar os circuitos corrigidos.
- Integração: [I04](evidencias/cv-04-I04.png) e [I05](evidencias/cv-04-I05.png)
  na aba 04 (linhas da Tabela 11 discutidas nas notas),
  [conflito CA=CB=1](evidencias/cv-04-intertravamento-conflito.png),
  [emergência dominante](evidencias/cv-04-emergencia-dominante.png),
  `cv-T01.png`–`cv-T04.png` para a tabela do slide 62 e
  [T05 no Ladder](evidencias/plc-T05.png) com `E=1` bloqueando o modelo
  integrado inteiro.

## Como reproduzir

1. No CircuitVerse, use **Project → Import Project**, selecione o arquivo
   `.cv`, confirme **IMPORT** e execute cada aba nomeada.
2. No PLC Simulator Online, utilize o modelo já carregado nesta sessão.
   O JSON é um backup do estado nativo; a importação por arquivo na interface
   não foi confirmada. No repo de trabalho, `simulacao/testa_emergencia.mjs`
   o carrega usando a ação nativa `IMPORT_PROJECT` antes dos testes.
3. Coloque o modo de simulação em execução e altere as tags conforme as linhas
   de `testes/casos-de-teste.md`.
4. Confira que o resultado coincide com a coluna **Obtido**; as tabelas de
   referência do repo de trabalho estão em `../simulacao/tabelas-esperadas.md`
   (fora do pacote de publicação).

No repo de trabalho, execute `node Entregas/TP04/simulacao/testa_integracao.mjs`
e `node Entregas/TP04/simulacao/testa_emergencia.mjs` com as duas plataformas
abertas no Chrome de validação (porta 9223). Os executores importam os
arquivos locais e leem as saídas dos motores nativos. Na integração, a
simulação do Ladder é habilitada apenas dentro do bloco síncrono de um
`CYCLE_SCAN`, garantindo exatamente um scan por amostra; a bateria de
emergência mantém a simulação ligada — as lógicas dos adicionais são
puramente combinacionais e não dependem do número de scans. Depois, rode
`python3 Entregas/TP04/simulacao/verifica_tp04.py` e
`node Entregas/TP04/simulacao/gera_casos_de_teste.mjs`.
O verificador interpreta as conexões do `.cv` e os ramos/contatos do Ladder,
confere 24 combinações entre os arquivos e vincula por hash as 72 observações
da emergência e as 166 da integração, conferindo cada registro contra uma
tabela canônica por ID (grupo, entradas, precondições e plataformas) e
recalculando cada expectativa e o encadeamento MA/MB entre amostras.
Dois ensaios negativos removem `¬E` em cópias em memória e exigem reprovação.

## Pendências para aprovação integral

Nenhuma pendência de validação: baterias nativas, auditoria independente e
links públicos conferidos. Resta somente a publicação no repositório oficial.

Nota sobre a Tabela 11: o gabarito indica permanência de motor após retirar
seu comando, mas isso não decorre das equações sem retenção, nem somente da
ordem de varredura. Pela ordem implementada, I04 resulta em MA=0/MB=1; I05
resulta em 0/0 no primeiro scan e 1/0 no segundo, mantendo CA=1/CB=0 — ambos
confirmados na bateria cruzada (`I04`, `I05-primeiro-scan`,
`I05-segundo-scan`) nas duas plataformas. Essas linhas não são contadas como
correspondências com o gabarito; a divergência está registrada nas notas do
verificador.

## Limites do protótipo

Portas e Ladder demonstram equivalência lógica; não certificam função de
segurança, componentes, fiação física, arquitetura, diagnóstico ou nível de
desempenho. O intertravamento didático depende da ordem de varredura/estado
anterior; a arbitragem adicional elimina essa ambiguidade com prioridade A.
As sequências atuais confirmam que, mantendo os comandos ativos, liberar E
volta a autorizar ventilação/motores. Não há trava de rearme manual; o
intertravamento por realimentação do Ladder pode depender do estado anterior.
Não há temporização ou implementação de rearme sequencial.

O XOR dos sensores redundantes detecta divergência, não correção
(slide 63, item 5): `D_XOR=0` não comprova leitura correta — os dois
sensores podem falhar do mesmo modo (causa comum) e concordar no valor
errado; e `D_XOR=1` sinaliza a inconsistência sem identificar qual sensor
está certo. O tratamento da divergência (qual sensor prevalece, parada
segura, diagnóstico) fica fora do escopo combinacional desta semana.
