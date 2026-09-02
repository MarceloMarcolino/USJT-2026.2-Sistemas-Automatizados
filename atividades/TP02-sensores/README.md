# TP02 — Processos, Sensores e Transdutores

Estação de monitoramento simulada no Wokwi, com Arduino Uno, para a prática da
Semana 2 da UC Sistemas Automatizados.

> **Estado: em andamento.** O circuito e o programa estão completos e
> verificados; a bateria de testes integrados ainda não foi executada. O que já
> foi validado e o que falta estão discriminados na seção
> [Estado da validação](#estado-da-validação), e o registro caso a caso está em
> [`testes/casos-de-teste.md`](testes/casos-de-teste.md).

## Objetivo

Adquirir uma entrada digital, uma entrada analógica e uma medição de
temperatura; classificar a condição do processo em **NORMAL**, **ATENÇÃO**,
**ALARME** ou **FALHA DE SENSOR**; e publicar esse estado no Monitor Serial em
formato verificável.

## Circuito

[![Circuito da estação de monitoramento](circuito.png)](circuito.png)

Arquivos desta pasta:

- [`sketch.ino`](sketch.ino) — programa
- [`diagram.json`](diagram.json) — circuito do Wokwi
- [`libraries.txt`](libraries.txt) — dependências do projeto
- [`circuito.png`](circuito.png) — imagem do circuito montado
- [`testes/casos-de-teste.md`](testes/casos-de-teste.md) — registro dos testes

## Variável, sensor, entrada e resposta

| Variável do processo | Sensor/componente | Entrada no controlador | Resposta do sistema |
|---|---|---|---|
| Acionamento manual (evento discreto) | Pushbutton | D2, digital, com `INPUT_PULLUP` | LED em D8 acende enquanto pressionado |
| Variável analógica contínua | Potenciômetro | A0, analógica, 0–1023 | Contribui para NORMAL/ATENÇÃO/ALARME |
| Temperatura | DHT22 | D4, digital, protocolo próprio | Contribui para o estado; leitura inválida gera FALHA DE SENSOR |

## Ligações

| Componente | Pino | Ligação complementar |
|---|---|---|
| Pushbutton | D2 | outro contato → GND |
| LED + resistor | D8 | D8 → 220 Ω → ânodo; cátodo → GND |
| Potenciômetro | A0 | VCC → 5 V; GND → GND; cursor → A0 |
| DHT22 | D4 | VCC → 5 V; GND → GND; DATA → D4 |

O **GND é comum** a todos os componentes: sem referência elétrica compartilhada
as leituras não têm significado.

## Regras de classificação

| Variável | Normal | Atenção | Alarme |
|---|---|---|---|
| Potenciômetro (valor bruto) | 0–399 | 400–749 | 750–1023 |
| Temperatura | < 30 °C | 30 a < 40 °C | ≥ 40 °C |

A decisão é avaliada em ordem de prioridade, **falha > alarme > atenção >
normal**:

1. Leitura de temperatura inválida → **FALHA DE SENSOR**
2. Senão, `t ≥ 40` **ou** `bruto ≥ 750` → **ALARME**
3. Senão, `t ≥ 30` **ou** `bruto ≥ 400` → **ATENÇÃO**
4. Senão → **NORMAL**

A falha é avaliada primeiro porque uma medida inválida não sustenta uma decisão
de normalidade: se a verificação viesse depois, um sensor mudo com o
potenciômetro em faixa baixa seria reportado como condição normal.

**Sobre o operador entre as duas grandezas.** A tabela do gabarito da atividade
escreve a linha de alarme como `t ≥ 40 °C` **e** `bruto ≥ 750`. A implementação
usa **ou**, por três evidências convergentes: o código de referência do próprio
gabarito, o material da disciplina sobre composição de condições, e os casos de
teste previstos — potenciômetro em 800 com 25 °C, e potenciômetro em 200 com
45 °C — que só produzem alarme com o operador **ou**. Com **e**, uma das duas
grandezas em faixa crítica nunca dispararia o alarme sozinha, o que contraria o
propósito do monitoramento.

## Papel do botão

O pino do botão usa `INPUT_PULLUP`, que liga o resistor interno do
microcontrolador entre o pino e a alimentação. Com o botão solto o circuito fica
aberto e o pino permanece em **HIGH**; ao pressionar, o botão fecha o caminho até
o GND e o pino é puxado para **LOW**. A leitura é, portanto, invertida em relação
à intuição, e por isso o programa compara `digitalRead(BTN) == LOW`.

O botão **controla apenas o LED e não participa da classificação**: o
acionamento manual não altera o estado do processo.

## Formato da saída serial

Uma linha por ciclo, campos sempre na mesma ordem, a 9600 baud:

```
BTN=<LIBERADO|PRESSIONADO> | POT=<0..1023> | TEMP=<valor, 1 decimal> C | ESTADO=<NORMAL|ATENCAO|ALARME|FALHA DE SENSOR>
```

Com leitura inválida o campo de temperatura vira `TEMP=INVALIDA` e o estado,
`FALHA DE SENSOR`. O formato fixo é o que torna as capturas comparáveis entre si.

## Provocar a leitura inválida do DHT22

Protocolo reprodutível, com a simulação parada nas trocas de fio:

1. Parar a simulação
2. Desconectar o fio de DATA (D4) do DHT22
3. Executar e observar `TEMP=INVALIDA` com `ESTADO=FALHA DE SENSOR`
4. Parar novamente
5. Reconectar o fio de DATA
6. Executar e confirmar o retorno a uma leitura válida

## Estado da validação

Executado e registrado:

| Grupo | Casos | Resultado |
|---|---|---|
| Digitais | D1–D4 | Aprovados |
| Fronteiras do potenciômetro | F1–F4 (399/400 e 749/750) | Aprovados, nos valores exatos |
| Ensaio do DHT22 | leitura, variação e falha provocada | Aprovado |

Pendente: os casos integrados (T1–T7), as fronteiras de temperatura (F5–F8) e os
exercícios adicionais de prioridade e histerese. A execução depende da fila de
compilação do simulador, que não concluiu durante esta sessão de trabalho.

## Limitações da simulação

A simulação demonstra a estrutura funcional da aquisição, a prioridade e a
coerência da lógica, a atuação e o diagnóstico no Monitor Serial. Ela **não
valida** alcance, exatidão, repetibilidade, tempo de resposta real, ruído
elétrico, aterramento, compatibilidade eletromagnética, montagem, cabeamento,
invólucro, grau de proteção, calibração metrológica nem segurança funcional.

## Autoria

Projeto criado do zero no Wokwi, com o circuito montado e o programa digitado e
testado de forma incremental, etapa a etapa, sem partir de projeto de terceiros.
