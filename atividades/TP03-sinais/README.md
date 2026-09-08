# TP03 — Sinais analógicos e digitais

**Autor:** Marcelo Antonio Pereira Marcolino — USJT — ESO1AN-MCE3<br>
**Estado:** completo — validação local 44/44; Wokwi e planilha publicados<br>
**Data da validação:** 7 de setembro de 2026

## Links e artefatos

- [Projeto público no Wokwi](https://wokwi.com/projects/474557584187065345)
- [Planilha em formato Excel](planilha-tp03.xlsx), com fórmulas, tabelas e
  gráfico preservados, pronta para importação no Google Planilhas
- [Planilha no Google Planilhas](https://docs.google.com/spreadsheets/d/16w3p_f5MQBg-DLSTNbvDAoJ_X1VzGSah5y_wFk_xl0U/edit) — acesso por link, somente leitura
- [Registro dos 44 casos de teste](testes/casos-de-teste.md)
- [Captura do circuito no Wokwi](evidencias/circuito-wokwi.png)
- [Gráfico e painel da planilha](evidencias/planilha-grafico.png)
- [Evidência A/B/Q](evidencias/testes-a-b-q.png),
  [média móvel](evidencias/media-movel.png) e
  [cálculo inverso/diagnóstico](evidencias/inverso-diagnostico.png)

O projeto do Wokwi está salvo na conta do autor, onde aparece em "Your
Projects". Sua estrutura foi auditada:
`sketch.ino` e `classificacao.h` são idênticos aos arquivos desta pasta; o
`diagram.json` contém os mesmos seis componentes, onze ligações, resistor de
220 Ω e nenhuma biblioteca externa. Quatro tentativas de compilação on-line
terminaram com `Build Servers Busy`; portanto, não se declara aqui execução no
simulador nem observação do Monitor Serial.

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
gerados foram conferidos como ELF AVR e Intel HEX válidos. Isso comprova a
compilação, mas os 44 casos são uma execução nativa no computador e cálculos do
Excel — não uma execução do binário AVR nem uma simulação elétrica no Wokwi.

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

A média móvel usa uma janela de cinco amostras. No ensaio M1–M11, um pico
isolado em M6 afeta exatamente cinco saídas (M6–M10) e deixa a janela em M11,
demonstrando tanto a suavização quanto o atraso do filtro.

O cálculo inverso confirma os pontos 0, 25, 50, 75 e 100 °C nas escalas
4–20 mA e 0–10 V. O diagnóstico elétrico classifica 3,2 mA e 20,8 mA como
FALHA e mantém 4–20 mA como faixa válida de processo.

## Conclusão

O protótipo preserva a leitura original e mantém rastreabilidade entre sinal
elétrico, percentual, unidade de engenharia, decisão e atuação. Os limites
percentuais e os primeiros códigos ADC realizáveis em cada faixa foram
verificados separadamente, evitando confundir requisito contínuo com
quantização. A planilha reproduz os cálculos e acrescenta uma leitura visual da
tendência.

## Limitações

O Wokwi foi auditado estruturalmente, mas sua execução on-line não foi
confirmada devido à indisponibilidade da fila de compilação. O harness nativo e
a planilha validam lógica, escalonamento, quantização, transições e
documentação. Eles não comprovam tolerância real do resistor, ruído
eletromagnético, isolamento, aterramento, corrente física de um laço 4–20 mA,
precisão metrológica, linearidade de um sensor real, atraso de hardware ou
segurança funcional. A corrente e a tensão industriais são cálculos
equivalentes, não sinais fisicamente gerados pelo circuito do Arduino.
