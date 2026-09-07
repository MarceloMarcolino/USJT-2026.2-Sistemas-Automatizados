# TP03 — Sinais analógicos e digitais

**Autor:** Marcelo Antonio Pereira Marcolino — USJT — ESO1AN-MCE3<br>
**Estado:** completo e validado<br>
**Data da validação:** 7 de setembro de 2026

## Links e artefatos

- [Projeto público no Wokwi](https://wokwi.com/projects/474526759232547841)
- [Planilha compartilhável em formato Excel](planilha-tp03.xlsx), com
  fórmulas, tabelas e gráfico preservados; o arquivo pode ser importado
  diretamente no Google Planilhas
- [Registro dos 44 casos de teste](testes/casos-de-teste.md)
- [Captura do circuito no Wokwi](evidencias/circuito-wokwi.png)
- [Gráfico e painel da planilha](evidencias/planilha-grafico.png)
- [Evidência A/B/Q](evidencias/testes-a-b-q.png),
  [média móvel](evidencias/media-movel.png) e
  [cálculo inverso/diagnóstico](evidencias/inverso-diagnostico.png)

O projeto do Wokwi, o código e o `diagram.json` desta pasta representam a mesma
montagem. O endereço público foi verificado por acesso HTTP sem autenticação.

## Objetivo

Adquirir uma entrada discreta e uma entrada analógica, preservar o valor bruto
do ADC, escaloná-lo para percentual e para uma grandeza de engenharia de
0–100 °C, classificar o estado do processo e registrar cada amostra em CSV. O
LED vermelho sinaliza exclusivamente **PERIGO**. A planilha refaz os cálculos
por fórmula, apresenta a tendência e documenta os adicionais de filtragem,
cálculo inverso e diagnóstico de um sinal 4–20 mA.

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

1. Abra o [projeto público no Wokwi](https://wokwi.com/projects/474526759232547841).
2. Inicie a simulação e abra o Monitor Serial em 9600 baud.
3. Gire o potenciômetro e observe `bruto`, `pct`, `tempC`, `estado` e o LED.
4. Teste valores próximos das transições: 716/717 para NORMAL→ATENCAO e
   869/870 para ATENCAO→PERIGO.
5. Pressione o botão e confirme que apenas a coluna `botao` muda.
6. Baixe [planilha-tp03.xlsx](planilha-tp03.xlsx) ou importe-a no Google
   Planilhas. As células calculadas mantêm as fórmulas visíveis.
7. Consulte [testes/casos-de-teste.md](testes/casos-de-teste.md) para repetir
   entradas, valores esperados e critérios de aprovação.

Para compilar localmente, abra `sketch.ino`, `classificacao.h` e `diagram.json`
no mesmo projeto Arduino/Wokwi. Nenhuma biblioteca externa é necessária; veja
`libraries.txt`.

## Validação

Foram aprovados **44 de 44 casos distintos**:

| Grupo | Cobertura | Resultado |
|---|---|---:|
| A1–A4 | aquisição do botão e do ADC | 4/4 |
| B1–B8 | limites percentuais e FALHA injetada | 8/8 |
| Q1–Q9 | quantização, escalonamento, estado e LED | 9/9 |
| M1–M11 | média móvel de cinco amostras | 11/11 |
| I1–I5 | cálculo inverso | 5/5 |
| G1–G7 | diagnóstico elétrico 4–20 mA | 7/7 |
| **Total** |  | **44/44** |

O firmware obrigatório, o teste isolado da classificação e o sketch adicional
da média móvel foram compilados para `arduino:avr:uno`. A execução automatizada
registrou data/hora UTC e hashes SHA-256 no resultado canônico. O sketch
entregue tem SHA-256
`ac4b7aeb87e7aac2057f2fe70027b0e91ca2d8538d844e0815658d71c391b074`.
O arquivo da planilha tem SHA-256
`01233dd98d58887dcc9caea27db429212892859bfe3dd221c243b0777a74bfe6`.

As evidências visuais estão em `evidencias/`; os resultados completos, com
entrada, esperado, obtido e situação, estão em
[`testes/casos-de-teste.md`](testes/casos-de-teste.md).

## Planilha e tendência

A pasta de trabalho contém abas de instruções, parâmetros, tabela de E/S,
dados brutos, análise, testes B/Q, média móvel, cálculo inverso e diagnóstico
4–20 mA. As grandezas derivadas e os estados são calculados por fórmula.

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

O Wokwi e a planilha validam lógica, escalonamento, quantização, transições e
documentação. Eles não comprovam tolerância real do resistor, ruído
eletromagnético, isolamento, aterramento, corrente física de um laço 4–20 mA,
precisão metrológica, linearidade de um sensor real, atraso de hardware ou
segurança funcional. A corrente e a tensão industriais são cálculos
equivalentes, não sinais fisicamente gerados pelo circuito do Arduino.
