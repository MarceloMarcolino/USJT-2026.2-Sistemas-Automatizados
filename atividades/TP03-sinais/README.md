# TP03 — Sinais analógicos e digitais

**Autor:** Marcelo Antonio Pereira Marcolino — USJT — ESO1AN-MCE3<br>
**Estado:** 44/44 na validação local; nove pontos Q confirmados no CSV do simulador<br>
**Data da validação:** 7 de setembro de 2026; execução no Wokwi em 8 de setembro de 2026

## Links e artefatos

- [Projeto público no Wokwi](https://wokwi.com/projects/474557584187065345)
- [Planilha em formato Excel](planilha-tp03.xlsx), com fórmulas, tabelas e
  gráfico preservados, pronta para importação no Google Planilhas
- [Planilha no Google Planilhas](https://docs.google.com/spreadsheets/d/16w3p_f5MQBg-DLSTNbvDAoJ_X1VzGSah5y_wFk_xl0U/edit) — acesso por link, somente leitura
- [Registro dos 44 casos de teste](testes/casos-de-teste.md)
- [Monitor Serial da execução no Wokwi](evidencias/monitor-serial-wokwi.txt) e
  [captura da simulação em andamento](evidencias/execucao-wokwi.png)
- [Captura do circuito no Wokwi](evidencias/circuito-wokwi.png)
- [Gráfico e painel da planilha](evidencias/planilha-grafico.png)
- [Evidência A/B/Q](evidencias/testes-a-b-q.png),
  [média móvel](evidencias/media-movel.png) e
  [cálculo inverso/diagnóstico](evidencias/inverso-diagnostico.png)

O projeto do Wokwi está salvo na conta do autor, onde aparece em "Your
Projects". Sua estrutura foi auditada:
`sketch.ino` e `classificacao.h` são idênticos aos arquivos desta pasta; o
`diagram.json` contém os mesmos seis componentes, onze ligações, resistor de
220 Ω e nenhuma biblioteca externa. Em 8 de setembro de 2026 o projeto compilou
e **foi executado no simulador**. Foram preservados 29 registros selecionados
da sessão, cobrindo os nove códigos Q e o acionamento do botão. Os recortes
estão em [`evidencias/monitor-serial-wokwi.txt`](evidencias/monitor-serial-wokwi.txt)
e a captura da tela em execução, com o LED aceso, em
[`evidencias/execucao-wokwi.png`](evidencias/execucao-wokwi.png).

## Objetivo

Adquirir uma entrada discreta e uma entrada analógica, preservar o valor bruto
do ADC, escaloná-lo para percentual e para uma grandeza de engenharia de
0–100 °C, classificar o estado do processo e registrar cada amostra em CSV. O
LED vermelho sinaliza exclusivamente **PERIGO**. A planilha refaz os cálculos
por fórmula, apresenta a tendência e documenta os adicionais de filtragem,
cálculo inverso e diagnóstico de um sinal 4–20 mA.

## Classificação dos sinais

Etapa 1 da prática: para cada elemento, a direção, a natureza e o papel.

| Elemento | Direção | Natureza | Papel |
|---|---|---|---|
| Pushbutton em D2 | Entrada | Discreta | comando/estado |
| Potenciômetro em A0 | Entrada | Analógica convertida pelo ADC | variável simulada |
| DHT22 em D4 | Entrada | Digital codificada | temperatura/umidade; herdado da Semana 2 e fora da lógica do TP03 |
| LED em D8 | Saída | Discreta | sinalização |
| Percentual calculado | Interno | Numérico | variável derivada |

O percentual **não é uma entrada física**: ele é produzido pelo software a
partir da leitura bruta do ADC. Essa distinção é o que separa, na tabela de E/S
abaixo, os endereços de hardware das variáveis mantidas em memória.

## Circuito e tabela de E/S

| Tag | Pino | Tipo | Faixa/estado | Função |
|---|---|---|---|---|
| `BTN_COMANDO` | D2 | entrada discreta | HIGH/LOW | registrar o botão; `INPUT_PULLUP`, pressionado = LOW |
| `POT_BRUTO` | A0 | entrada analógica | 0–1023 | simular a variável de processo |
| `TEMP_DHT22` | D4 | entrada digital codificada | protocolo DHT | componente herdado e classificado; fora da lógica do TP03 |
| `LED_ALARME` | D8 | saída discreta | OFF/ON | acender somente em PERIGO |
| `NIVEL_PCT` | memória | variável interna | 0–100 % | valor normalizado do ADC |
| `TEMP_SIM_C` | memória | variável interna | 0–100 °C | grandeza de engenharia simulada pelo potenciômetro |

Ligações: botão entre D2 e GND; potenciômetro em 5 V, GND e A0; D8 →
resistor de 220 Ω → ânodo do LED, com cátodo no GND; DHT22 em 5 V, GND e
D4. Todos os componentes compartilham o mesmo GND.

O DHT22 permanece na estação porque o circuito evolui o protótipo da Semana 2,
mas o programa obrigatório do TP03 lê somente D2 e A0. Consequentemente, a
coluna `tempC` é a temperatura **simulada pelo potenciômetro**, não uma leitura
do DHT22.

## Aquisição, escalonamento e classificação

O Arduino Uno possui ADC de 10 bits. Para cada leitura `bruto`:

```text
pct   = 100,0 × bruto / 1023,0
tempC = pct
mA    = 4 + 16 × pct / 100
V     = 10 × pct / 100
```

`tempC = pct` porque ambas as escalas escolhidas variam de 0 a 100. A função
`classificar()` aplica as condições na ordem:

1. `pct < 0` ou `pct > 100` → **FALHA**;
2. `pct >= 85` → **PERIGO**;
3. `pct >= 70` → **ATENCAO**;
4. demais valores → **NORMAL**.

O LED em D8 acende apenas em PERIGO. O botão aparece no registro, mas não muda
o estado nem a saída. Em operação normal, `analogRead()` produz apenas valores
entre 0 e 1023; por isso os testes de FALHA são injeções controladas de software
na mesma função de classificação, conforme o método proposto no gabarito.

## Formato dos dados

O Monitor Serial opera a **9600 baud**, imprime o cabeçalho uma vez e gera uma
linha a cada 500 ms:

```csv
amostra,botao,bruto,pct,tempC,estado
```

`botao` vale `1` quando pressionado e `0` quando liberado. `pct` e `tempC` são
impressos com duas casas decimais.

## Como reproduzir

1. Abra o [projeto público no Wokwi](https://wokwi.com/projects/474557584187065345).
2. Inicie a simulação e abra o Monitor Serial em 9600 baud.
3. Gire o potenciômetro e observe `bruto`, `pct`, `tempC`, `estado` e o LED.
4. Teste valores próximos das transições: 716/717 para NORMAL→ATENCAO e
   869/870 para ATENCAO→PERIGO.
5. Pressione o botão e confirme que apenas a coluna `botao` muda.
6. Baixe [planilha-tp03.xlsx](planilha-tp03.xlsx) ou importe-a no Google
   Planilhas. As células calculadas mantêm as fórmulas visíveis.
7. Consulte [testes/casos-de-teste.md](testes/casos-de-teste.md) para repetir
   entradas, valores esperados e critérios de aprovação.

No Wokwi, mantenha `sketch.ino`, `classificacao.h` e `diagram.json` no mesmo
projeto. Na compilação Arduino local, bastam o sketch e o cabeçalho. Nenhuma
biblioteca externa é necessária; veja `libraries.txt`.

## Validação

Foram aprovadas **44 de 44 verificações locais controladas**. O valor
**esperado** vem das tabelas literais da especificação. O valor **obtido** vem
do artefato entregue indicado em cada grupo — código C++ executado no
computador ou fórmulas do XLSX recalculadas no Microsoft Excel — e não de uma
segunda função Python que repetisse a mesma regra.

| Grupo | Cobertura | Origem do valor obtido | Resultado |
|---|---|---|---:|
| A1–A4 | cadeia do sketch para botão/ADC, CSV, contador e LED | `sketch.ino` via harness nativo | 4/4 |
| B1–B8 | limites percentuais e FALHA injetada | `classificacao.h` via harness + Excel | 8/8 |
| Q1–Q9 | quantização, escalonamento, estado e LED | `sketch.ino` via harness + Excel | 9/9 |
| M1–M11 | média móvel de cinco amostras | sketch adicional + `media_movel5.h` via harness | 11/11 |
| I1–I5 | cálculo inverso | fórmulas recalculadas no Excel | 5/5 |
| G1–G7 | diagnóstico elétrico 4–20 mA | fórmulas recalculadas no Excel | 7/7 |
| **Total** |  |  | **44/44** |

O harness inclui diretamente os fontes entregues e oferece apenas a camada
mínima da API Arduino necessária no computador. A e Q executam `setup()` e
`loop()` do `sketch.ino`; M executa `setup()` e `loop()` do sketch adicional.
Também são conferidos contador de amostras, cabeçalho CSV, período de 500 ms e
LED. Um ensaio complementar pressiona o botão na faixa PERIGO e confirma que
ele altera somente o campo `botao`, não o estado nem o LED. B e Q são ainda
confirmados pela planilha, por caminho independente: 8/8 e 9/9 concordantes.

Antes da medição, a verificação estrutural confere o cabeçalho CSV exato, os
pinos e a regra do LED no sketch; a ausência do DHT22 na lógica obrigatória; a
identidade byte a byte das quatro cópias de `classificacao.h` com a fonte
canônica; as onze ligações contra o mapa aprovado; e o resistor de 220 Ω.

O firmware obrigatório, o teste isolado da classificação e o sketch adicional
também foram compilados nesta auditoria para `arduino:avr:uno`. Os artefatos
gerados foram conferidos como ELF AVR e Intel HEX válidos. Os 44 casos acima são
uma execução nativa no computador e cálculos do Excel; a execução do binário AVR
no simulador é registrada à parte, na seção seguinte.

### Execução no simulador Wokwi

Em 8 de setembro de 2026 o projeto compilou sem erro e a simulação rodou.
O potenciômetro foi levado a cada código de teste operando o próprio componente,
e o botão foi pressionado e solto nele. Os 29 registros preservados são recortes
organizados por caso, e não o log integral da sessão. Eles confirmam os nove
códigos da tabela Q no Monitor Serial. As observações do LED registradas no
componente abrangem 716, 717, 869, 870 e 1023, além do botão pressionado em 870.
O LED não é um campo do CSV; a tabela distingue as observações disponíveis:

| Caso | bruto | pct e tempC | estado | LED | Amostra |
|---|---:|---:|---|---|---:|
| Q1 | 0 | 0,00 | NORMAL | não registrado | 0 |
| Q2 | 256 | 25,02 | NORMAL | não registrado | 885 |
| Q3 | 512 | 50,05 | NORMAL | não registrado | 197 |
| Q4 | 716 | 69,99 | NORMAL | apagado | 339 |
| Q5 | 717 | 70,09 | **ATENCAO** | apagado | 356 |
| Q6 | 768 | 75,07 | ATENCAO | não registrado | 758 |
| Q7 | 869 | 84,95 | ATENCAO | apagado | 391 |
| Q8 | 870 | 85,04 | **PERIGO** | **aceso** | 416 |
| Q9 | 1023 | 100,00 | PERIGO | aceso | 640 |

As duas transições apareceram nos códigos previstos, em amostras consecutivas:
716 → 717 muda de NORMAL para ATENCAO, e 869 → 870 muda de ATENCAO para PERIGO
acendendo o LED. Com o botão pressionado em 870, a saída passou a
`581,1,870,85.04,85.04,PERIGO`: apenas a coluna `botao` mudou, confirmando que
ele não participa da classificação nem comanda a saída. Nos campos do CSV,
os nove pontos conferem com os resultados locais — 9/9 concordantes.

O caso A2 (`botao=1; bruto=0`) foi aprovado na validação nativa, mas não aparece
nestes recortes do simulador. O acionamento preservado ocorreu com `bruto=870`.
A evidência on-line de A2 e as observações do LED marcadas como não registradas
na tabela permanecem fora da cobertura documentada desta sessão.

As evidências visuais estão em `evidencias/`; os resultados completos, com
entrada, esperado, obtido e situação, estão em
[`testes/casos-de-teste.md`](testes/casos-de-teste.md).

## Planilha e tendência

A pasta de trabalho contém abas de instruções, parâmetros, tabela de E/S,
dados brutos, análise, testes B/Q, média móvel, cálculo inverso e diagnóstico
4–20 mA. As grandezas derivadas e os estados são calculados por fórmula.

**Sobre as quinze amostras da aba `Dados_Brutos`.** São **códigos de ADC
escolhidos** para cobrir a faixa inteira e, principalmente, as duas transições
de estado — 716/717 e 869/870 — além de uma subida e uma descida que produzem
a tendência do gráfico. **Não são capturas do Monitor Serial.** A coluna
`Origem` registra `código escolhido`; o uso de casos controlados é deliberado,
pois valores casuais do potenciômetro dificilmente cairiam nos códigos exatos
onde a classificação muda.

O gráfico de tendência usa a amostra no eixo horizontal e `tempC` (°C) no eixo
vertical. A série atravessa as faixas NORMAL, ATENCAO e PERIGO, permitindo
visualizar as mudanças de estado nos limites de 70 °C e 85 °C.

As três últimas abas — `Media_Movel`, `Calculo_Inverso` e `Diagnostico_4_20` —
correspondem aos exercícios adicionais, detalhados na seção seguinte.

## Exercícios adicionais

### Adicional 1 — filtragem por média móvel

Implementado em `adicionais/media-movel/`, num sketch separado para não alterar
o CSV obrigatório. A classe `MediaMovel5` guarda cinco valores num vetor
circular, mantém a soma incremental e divide pela quantidade realmente
preenchida, o que evita que os zeros iniciais puxem as primeiras médias para
baixo. O CSV publica `bruto` e `filtrado` lado a lado, permitindo a comparação
direta. O ensaio M1–M11 injeta um pico isolado em M6 (620 entre leituras
próximas de 500) e é verificado em 11/11 pelo harness e pela aba `Media_Movel`.

**O atraso introduzido.** Cada saída é a média das cinco leituras mais
recentes — um valor construído com o passado. Diante de uma mudança real do
processo, a janela ainda carrega amostras antigas e só reflete inteiramente o
novo patamar após cinco ciclos: a 500 ms por amostra, 2,5 s. O deslocamento
médio da resposta corresponde a (N−1)/2 = 2 amostras, cerca de 1 s. O pico de
M6 evidencia o mesmo mecanismo por outro ângulo: ele é atenuado porque entra
dividido por cinco, e persiste até M10 porque permanece na janela por cinco
ciclos. Suavização e atraso são, portanto, o mesmo efeito visto de dois lados —
ampliar a janela rejeita mais ruído e responde mais devagar; encurtá-la devolve
rapidez junto com o ruído. Num alarme de processo a escolha é explícita: uma
janela longa demais adia a detecção de uma excursão verdadeira.

### Adicional 2 — cálculo inverso

Na aba `Calculo_Inverso`, a temperatura desejada é a entrada e os sinais
industriais são calculados a partir dela: `mA = 4 + 16 × tempC/100` e
`V = 10 × tempC/100`. As colunas `tempC via mA` e `tempC via V` aplicam o
cálculo direto de volta sobre os valores obtidos e devem recuperar a
temperatura original; a coluna `Situação` marca CONFORME apenas quando as duas
reconversões batem com a entrada dentro de 10⁻⁴. Os cinco pontos pedidos —
0, 25, 50, 75 e 100 °C — resultam em 4, 8, 12, 16 e 20 mA e em 0; 2,5; 5; 7,5 e
10 V, todos conferidos (I1–I5, 5/5). Como as células guardam a fórmula
completa, a volta é exata: eventuais diferenças seriam apenas de arredondamento
de exibição.

### Adicional 3 — diagnóstico elétrico

Na aba `Diagnostico_4_20`, a coluna `corrente_teste` recebe 3,2; 4; 12; 15,2;
17,6; 20 e 20,8 mA. O limite elétrico de falha é a própria faixa do laço:
abaixo de 4 mA ou acima de 20 mA o sinal é declarado `FALHA ELETRICA`. G1 e G7
são os casos deliberadamente fora da faixa, um de cada lado.

**Por que não limitar antes de diagnosticar.** O percentual é calculado sem
saturação, e por isso 3,2 mA produz −5 % e 20,8 mA produz 105 %. Se a planilha
truncasse o resultado para 0–100 % antes do diagnóstico, 3,2 mA viraria 0 %,
indistinguível de um processo legitimamente no fundo de escala, e 20,8 mA
viraria 100 %, um alarme de perigo com a causa errada. Nos dois casos o número
continuaria parecendo uma medição, quando o que existe é um laço rompido ou um
transmissor em saturação. O valor fora de faixa é justamente a informação de
diagnóstico; limitá-lo a destrói.

**Por que a falha tem prioridade.** A ordem é falha elétrica → perigo →
atenção → normal. Uma corrente fora de 4–20 mA não sustenta afirmação alguma
sobre a variável de processo, então classificar o processo antes seria traduzir
um defeito de instrumentação em um estado de planta. O caso mais perigoso é o
inferior: sem o diagnóstico, um laço rompido — corrente próxima de zero — seria
reportado como NORMAL, o estado que menos convida à ação. É a mesma prioridade
adotada no firmware, onde `pct < 0 || pct > 100` decide antes dos limites de
85 % e 70 %, e a mesma razão pela qual 4 mA é o *zero vivo*: existir corrente no
zero da escala é o que permite distinguir o zero válido do cabo interrompido.

**O que este ensaio não valida** está registrado em
[Limitações](#limitações): a corrente e a tensão são equivalências calculadas,
não sinais fisicamente gerados pelo circuito.

## Conclusão

O protótipo preserva a leitura original e mantém rastreabilidade entre sinal
elétrico, percentual, unidade de engenharia, decisão e atuação. Os limites
percentuais e os primeiros códigos ADC realizáveis em cada faixa foram
verificados separadamente, evitando confundir requisito contínuo com
quantização. A planilha reproduz os cálculos e acrescenta uma leitura visual da
tendência.

## Limitações

A simulação no Wokwi confirma o comportamento do binário AVR no circuito
modelado; o harness nativo e a planilha validam lógica, escalonamento,
quantização, transições e documentação. Nenhum dos três comprova tolerância
real do resistor, ruído eletromagnético, isolamento, aterramento, corrente
física de um laço 4–20 mA, precisão metrológica, linearidade de um sensor real,
atraso de hardware ou segurança funcional. O Wokwi é um modelo do circuito, não
o circuito: a corrente e a tensão industriais continuam sendo cálculos
equivalentes, não sinais fisicamente gerados por um Arduino.
