# Casos de teste — TP04

Registro gerado dos resultados observados nos artefatos reais dos simuladores. As baterias de integração e de emergência foram executadas após importar os arquivos finais nas plataformas. Os resultados completos e hashes estão em [resultados-integracao.json](resultados-integracao.json) e [resultados-emergencia.json](resultados-emergencia.json). As observações anteriores das partes não alteradas permanecem identificadas como histórico; não têm a mesma proveniência por hash.

## Resumo

| Plataforma | Observações | Aprovadas | Fonte |
|---|---:|---:|---|
| Integração — um scan por amostra, ambas as plataformas | 166 | 166 | `resultados-integracao.json` |
| Emergência nos adicionais, ambas as plataformas | 72 | 72 | `resultados-emergencia.json` |
| CircuitVerse — histórico preservado | 39 | 39 | `resultados-circuitverse.json` (repo de trabalho) |
| PLC Simulator Online — histórico | 40 | 40 | `resultados-plc.json` (repo de trabalho) |

A integração executa um scan por amostra (Ladder pausado; CYCLE_SCAN único; CircuitVerse com MB_ANT explícito): portas básicas (só CircuitVerse), partida, alarme, XOR, os 32 estados CA/CB/E × MA/MB anteriores do intertravamento, I01–I06, E01–E05 com o estado anterior registrado e T01–T05 do slide 62. A bateria de emergência cobre as 16 combinações DGFE da ventilação, as oito CA/CB/E da arbitragem, três sequências E=0→1→0 (ventilação, motor A, motor B) e uma sequência F=0→1→0. Cada sequência preserva o estado entre suas amostras. Os comandos continuam ativos: ao liberar E, as saídas retornam, comprovando a ausência de memória de rearme. Tags equivalentes: D↔D_DEM, MA↔MA_ARB e MB↔MB_ARB.

## Revisão atual — integração, um scan por amostra

| Plataforma | Caso | Entrada | MA/MB anteriores | Esperado | Obtido | Situação |
|---|---|---|---|---|---|---|
| CircuitVerse | P01 | S=0; G=0; E=0 | — | M=0 | M=0 | PASSA |
| PLC Simulator Online | P01 | S=0; G=0; E=0 | — | M=0 | M=0 | PASSA |
| CircuitVerse | P02 | S=0; G=0; E=1 | — | M=0 | M=0 | PASSA |
| PLC Simulator Online | P02 | S=0; G=0; E=1 | — | M=0 | M=0 | PASSA |
| CircuitVerse | P03 | S=0; G=1; E=0 | — | M=0 | M=0 | PASSA |
| PLC Simulator Online | P03 | S=0; G=1; E=0 | — | M=0 | M=0 | PASSA |
| CircuitVerse | P04 | S=0; G=1; E=1 | — | M=0 | M=0 | PASSA |
| PLC Simulator Online | P04 | S=0; G=1; E=1 | — | M=0 | M=0 | PASSA |
| CircuitVerse | P05 | S=1; G=0; E=0 | — | M=0 | M=0 | PASSA |
| PLC Simulator Online | P05 | S=1; G=0; E=0 | — | M=0 | M=0 | PASSA |
| CircuitVerse | P06 | S=1; G=0; E=1 | — | M=0 | M=0 | PASSA |
| PLC Simulator Online | P06 | S=1; G=0; E=1 | — | M=0 | M=0 | PASSA |
| CircuitVerse | P07 | S=1; G=1; E=0 | — | M=1 | M=1 | PASSA |
| PLC Simulator Online | P07 | S=1; G=1; E=0 | — | M=1 | M=1 | PASSA |
| CircuitVerse | P08 | S=1; G=1; E=1 | — | M=0 | M=0 | PASSA |
| PLC Simulator Online | P08 | S=1; G=1; E=1 | — | M=0 | M=0 | PASSA |
| CircuitVerse | A01 | T=0; P=0; MNT=0 | — | AL=0 | AL=0 | PASSA |
| PLC Simulator Online | A01 | T=0; P=0; MNT=0 | — | AL=0 | AL=0 | PASSA |
| CircuitVerse | A02 | T=0; P=1; MNT=0 | — | AL=1 | AL=1 | PASSA |
| PLC Simulator Online | A02 | T=0; P=1; MNT=0 | — | AL=1 | AL=1 | PASSA |
| CircuitVerse | A03 | T=1; P=0; MNT=0 | — | AL=1 | AL=1 | PASSA |
| PLC Simulator Online | A03 | T=1; P=0; MNT=0 | — | AL=1 | AL=1 | PASSA |
| CircuitVerse | A04 | T=1; P=1; MNT=0 | — | AL=1 | AL=1 | PASSA |
| PLC Simulator Online | A04 | T=1; P=1; MNT=0 | — | AL=1 | AL=1 | PASSA |
| CircuitVerse | A05 | T=0; P=0; MNT=1 | — | AL=0 | AL=0 | PASSA |
| PLC Simulator Online | A05 | T=0; P=0; MNT=1 | — | AL=0 | AL=0 | PASSA |
| CircuitVerse | A06 | T=0; P=1; MNT=1 | — | AL=0 | AL=0 | PASSA |
| PLC Simulator Online | A06 | T=0; P=1; MNT=1 | — | AL=0 | AL=0 | PASSA |
| CircuitVerse | A07 | T=1; P=0; MNT=1 | — | AL=0 | AL=0 | PASSA |
| PLC Simulator Online | A07 | T=1; P=0; MNT=1 | — | AL=0 | AL=0 | PASSA |
| CircuitVerse | A08 | T=1; P=1; MNT=1 | — | AL=0 | AL=0 | PASSA |
| PLC Simulator Online | A08 | T=1; P=1; MNT=1 | — | AL=0 | AL=0 | PASSA |
| CircuitVerse | X01 | SENS_A=0; SENS_B=0 | — | D_XOR=0 | D_XOR=0 | PASSA |
| PLC Simulator Online | X01 | SENS_A=0; SENS_B=0 | — | D_XOR=0 | D_XOR=0 | PASSA |
| CircuitVerse | X02 | SENS_A=0; SENS_B=1 | — | D_XOR=1 | D_XOR=1 | PASSA |
| PLC Simulator Online | X02 | SENS_A=0; SENS_B=1 | — | D_XOR=1 | D_XOR=1 | PASSA |
| CircuitVerse | X03 | SENS_A=1; SENS_B=0 | — | D_XOR=1 | D_XOR=1 | PASSA |
| PLC Simulator Online | X03 | SENS_A=1; SENS_B=0 | — | D_XOR=1 | D_XOR=1 | PASSA |
| CircuitVerse | X04 | SENS_A=1; SENS_B=1 | — | D_XOR=0 | D_XOR=0 | PASSA |
| PLC Simulator Online | X04 | SENS_A=1; SENS_B=1 | — | D_XOR=0 | D_XOR=0 | PASSA |
| CircuitVerse | PB-AND-00 | A=0; B=0 | — | Y_AND=0 | Y_AND=0 | PASSA |
| CircuitVerse | PB-AND-01 | A=0; B=1 | — | Y_AND=0 | Y_AND=0 | PASSA |
| CircuitVerse | PB-AND-10 | A=1; B=0 | — | Y_AND=0 | Y_AND=0 | PASSA |
| CircuitVerse | PB-AND-11 | A=1; B=1 | — | Y_AND=1 | Y_AND=1 | PASSA |
| CircuitVerse | PB-OR-00 | A=0; B=0 | — | Y_OR=0 | Y_OR=0 | PASSA |
| CircuitVerse | PB-OR-01 | A=0; B=1 | — | Y_OR=1 | Y_OR=1 | PASSA |
| CircuitVerse | PB-OR-10 | A=1; B=0 | — | Y_OR=1 | Y_OR=1 | PASSA |
| CircuitVerse | PB-OR-11 | A=1; B=1 | — | Y_OR=1 | Y_OR=1 | PASSA |
| CircuitVerse | PB-NOT-0 | A=0; B=0 | — | Y_NOT=1 | Y_NOT=1 | PASSA |
| CircuitVerse | PB-NOT-1 | A=1; B=0 | — | Y_NOT=0 | Y_NOT=0 | PASSA |
| CircuitVerse | IS-000-00 | CA=0; CB=0; E=0 | MA=0; MB=0 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | IS-000-00 | CA=0; CB=0; E=0 | MA=0; MB=0 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | IS-000-01 | CA=0; CB=0; E=0 | MA=0; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | IS-000-01 | CA=0; CB=0; E=0 | MA=0; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | IS-000-10 | CA=0; CB=0; E=0 | MA=1; MB=0 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | IS-000-10 | CA=0; CB=0; E=0 | MA=1; MB=0 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | IS-000-11 | CA=0; CB=0; E=0 | MA=1; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | IS-000-11 | CA=0; CB=0; E=0 | MA=1; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | IS-001-00 | CA=0; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-001-00 | CA=0; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-001-01 | CA=0; CB=0; E=1 | MA=0; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-001-01 | CA=0; CB=0; E=1 | MA=0; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-001-10 | CA=0; CB=0; E=1 | MA=1; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-001-10 | CA=0; CB=0; E=1 | MA=1; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-001-11 | CA=0; CB=0; E=1 | MA=1; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-001-11 | CA=0; CB=0; E=1 | MA=1; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-010-00 | CA=0; CB=1; E=0 | MA=0; MB=0 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| PLC Simulator Online | IS-010-00 | CA=0; CB=1; E=0 | MA=0; MB=0 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| CircuitVerse | IS-010-01 | CA=0; CB=1; E=0 | MA=0; MB=1 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| PLC Simulator Online | IS-010-01 | CA=0; CB=1; E=0 | MA=0; MB=1 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| CircuitVerse | IS-010-10 | CA=0; CB=1; E=0 | MA=1; MB=0 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| PLC Simulator Online | IS-010-10 | CA=0; CB=1; E=0 | MA=1; MB=0 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| CircuitVerse | IS-010-11 | CA=0; CB=1; E=0 | MA=1; MB=1 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| PLC Simulator Online | IS-010-11 | CA=0; CB=1; E=0 | MA=1; MB=1 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| CircuitVerse | IS-011-00 | CA=0; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-011-00 | CA=0; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-011-01 | CA=0; CB=1; E=1 | MA=0; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-011-01 | CA=0; CB=1; E=1 | MA=0; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-011-10 | CA=0; CB=1; E=1 | MA=1; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-011-10 | CA=0; CB=1; E=1 | MA=1; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-011-11 | CA=0; CB=1; E=1 | MA=1; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-011-11 | CA=0; CB=1; E=1 | MA=1; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-100-00 | CA=1; CB=0; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | IS-100-00 | CA=1; CB=0; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| CircuitVerse | IS-100-01 | CA=1; CB=0; E=0 | MA=0; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | IS-100-01 | CA=1; CB=0; E=0 | MA=0; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | IS-100-10 | CA=1; CB=0; E=0 | MA=1; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | IS-100-10 | CA=1; CB=0; E=0 | MA=1; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| CircuitVerse | IS-100-11 | CA=1; CB=0; E=0 | MA=1; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | IS-100-11 | CA=1; CB=0; E=0 | MA=1; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | IS-101-00 | CA=1; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-101-00 | CA=1; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-101-01 | CA=1; CB=0; E=1 | MA=0; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-101-01 | CA=1; CB=0; E=1 | MA=0; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-101-10 | CA=1; CB=0; E=1 | MA=1; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-101-10 | CA=1; CB=0; E=1 | MA=1; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-101-11 | CA=1; CB=0; E=1 | MA=1; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-101-11 | CA=1; CB=0; E=1 | MA=1; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-110-00 | CA=1; CB=1; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | IS-110-00 | CA=1; CB=1; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| CircuitVerse | IS-110-01 | CA=1; CB=1; E=0 | MA=0; MB=1 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| PLC Simulator Online | IS-110-01 | CA=1; CB=1; E=0 | MA=0; MB=1 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| CircuitVerse | IS-110-10 | CA=1; CB=1; E=0 | MA=1; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | IS-110-10 | CA=1; CB=1; E=0 | MA=1; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| CircuitVerse | IS-110-11 | CA=1; CB=1; E=0 | MA=1; MB=1 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| PLC Simulator Online | IS-110-11 | CA=1; CB=1; E=0 | MA=1; MB=1 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| CircuitVerse | IS-111-00 | CA=1; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-111-00 | CA=1; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-111-01 | CA=1; CB=1; E=1 | MA=0; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-111-01 | CA=1; CB=1; E=1 | MA=0; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-111-10 | CA=1; CB=1; E=1 | MA=1; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-111-10 | CA=1; CB=1; E=1 | MA=1; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | IS-111-11 | CA=1; CB=1; E=1 | MA=1; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | IS-111-11 | CA=1; CB=1; E=1 | MA=1; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | I01 | CA=0; CB=0; E=0 | MA=0; MB=0 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | I01 | CA=0; CB=0; E=0 | MA=0; MB=0 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | I02 | CA=1; CB=0; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | I02 | CA=1; CB=0; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| CircuitVerse | I03 | CA=0; CB=1; E=0 | MA=0; MB=0 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| PLC Simulator Online | I03 | CA=0; CB=1; E=0 | MA=0; MB=0 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| CircuitVerse | I04 | CA=0; CB=1; E=0 | MA=1; MB=0 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| PLC Simulator Online | I04 | CA=0; CB=1; E=0 | MA=1; MB=0 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| CircuitVerse | I05 | CA=1; CB=0; E=0 | MA=0; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | I05 | CA=1; CB=0; E=0 | MA=0; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | I06 | CA=1; CB=1; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | I06 | CA=1; CB=1; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| CircuitVerse | I05-primeiro-scan | CA=1; CB=0; E=0 | MA=0; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | I05-primeiro-scan | CA=1; CB=0; E=0 | MA=0; MB=1 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | I05-segundo-scan | CA=1; CB=0; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | I05-segundo-scan | CA=1; CB=0; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| CircuitVerse | E01-antes | CA=0; CB=0; E=0 | MA=0; MB=0 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | E01-antes | CA=0; CB=0; E=0 | MA=0; MB=0 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | E01 | CA=0; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | E01 | CA=0; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | E02-antes | CA=1; CB=0; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | E02-antes | CA=1; CB=0; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| CircuitVerse | E02 | CA=1; CB=0; E=1 | MA=1; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | E02 | CA=1; CB=0; E=1 | MA=1; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | E03-antes | CA=0; CB=1; E=0 | MA=0; MB=0 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| PLC Simulator Online | E03-antes | CA=0; CB=1; E=0 | MA=0; MB=0 | MA=0; MB=1; AL_E=0 | MA=0; MB=1; AL_E=0 | PASSA |
| CircuitVerse | E03 | CA=0; CB=1; E=1 | MA=0; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | E03 | CA=0; CB=1; E=1 | MA=0; MB=1 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | E04-antes | CA=0; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | E04-antes | CA=0; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | E04 | CA=1; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| PLC Simulator Online | E04 | CA=1; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0; AL_E=1 | MA=0; MB=0; AL_E=1 | PASSA |
| CircuitVerse | E05-sem-comandos | CA=0; CB=0; E=0 | MA=0; MB=0 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | E05-sem-comandos | CA=0; CB=0; E=0 | MA=0; MB=0 | MA=0; MB=0; AL_E=0 | MA=0; MB=0; AL_E=0 | PASSA |
| CircuitVerse | T01-antes | S=0; G=1; E=0 | — | M=0 | M=0 | PASSA |
| PLC Simulator Online | T01-antes | S=0; G=1; E=0 | — | M=0 | M=0 | PASSA |
| CircuitVerse | T01 | S=1; G=1; E=0 | — | M=1 | M=1 | PASSA |
| PLC Simulator Online | T01 | S=1; G=1; E=0 | — | M=1 | M=1 | PASSA |
| CircuitVerse | T02 | S=1; G=0; E=0 | — | M=0 | M=0 | PASSA |
| PLC Simulator Online | T02 | S=1; G=0; E=0 | — | M=0 | M=0 | PASSA |
| CircuitVerse | T03-antes | S=1; G=1; E=0 | — | M=1 | M=1 | PASSA |
| PLC Simulator Online | T03-antes | S=1; G=1; E=0 | — | M=1 | M=1 | PASSA |
| CircuitVerse | T03 | S=1; G=1; E=1 | — | M=0 | M=0 | PASSA |
| PLC Simulator Online | T03 | S=1; G=1; E=1 | — | M=0 | M=0 | PASSA |
| CircuitVerse | T04-antes | CA=1; CB=0; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | T04-antes | CA=1; CB=0; E=0 | MA=0; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| CircuitVerse | T04 | CA=1; CB=1; E=0 | MA=1; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| PLC Simulator Online | T04 | CA=1; CB=1; E=0 | MA=1; MB=0 | MA=1; MB=0; AL_E=0 | MA=1; MB=0; AL_E=0 | PASSA |
| CircuitVerse | T05-antes | S=1; G=1; E=0; CA=1; CB=1; D_DEM=1; F=0 | MA=0; MB=0 | M=1; MA=1; MB=0; AL_E=0; V=1; MA_ARB=1; MB_ARB=0 | M=1; MA=1; MB=0; AL_E=0; V=1; MA_ARB=1; MB_ARB=0 | PASSA |
| PLC Simulator Online | T05-antes | S=1; G=1; E=0; CA=1; CB=1; D_DEM=1; F=0 | MA=0; MB=0 | M=1; MA=1; MB=0; AL_E=0; V=1; MA_ARB=1; MB_ARB=0 | M=1; MA=1; MB=0; AL_E=0; V=1; MA_ARB=1; MB_ARB=0 | PASSA |
| CircuitVerse | T05 | S=1; G=1; E=1; CA=1; CB=1; D_DEM=1; F=0 | MA=1; MB=0 | M=0; MA=0; MB=0; AL_E=1; V=0; MA_ARB=0; MB_ARB=0 | M=0; MA=0; MB=0; AL_E=1; V=0; MA_ARB=0; MB_ARB=0 | PASSA |
| PLC Simulator Online | T05 | S=1; G=1; E=1; CA=1; CB=1; D_DEM=1; F=0 | MA=1; MB=0 | M=0; MA=0; MB=0; AL_E=1; V=0; MA_ARB=0; MB_ARB=0 | M=0; MA=0; MB=0; AL_E=1; V=0; MA_ARB=0; MB_ARB=0 | PASSA |

Notas:

- I04, I05: Segue as equações sem retenção; diverge da permanência indicada na Tabela 11.
- E05-sem-comandos: Comandos liberados. Não prova trava de rearme com comandos mantidos.

## Revisão atual — equivalência e emergência

| Plataforma | Caso | Entrada | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| CircuitVerse | VE-0000 | D=0; G=0; F=0; E=0 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-0000 | D=0; G=0; F=0; E=0 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-0001 | D=0; G=0; F=0; E=1 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-0001 | D=0; G=0; F=0; E=1 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-0010 | D=0; G=0; F=1; E=0 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-0010 | D=0; G=0; F=1; E=0 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-0011 | D=0; G=0; F=1; E=1 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-0011 | D=0; G=0; F=1; E=1 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-0100 | D=0; G=1; F=0; E=0 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-0100 | D=0; G=1; F=0; E=0 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-0101 | D=0; G=1; F=0; E=1 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-0101 | D=0; G=1; F=0; E=1 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-0110 | D=0; G=1; F=1; E=0 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-0110 | D=0; G=1; F=1; E=0 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-0111 | D=0; G=1; F=1; E=1 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-0111 | D=0; G=1; F=1; E=1 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-1000 | D=1; G=0; F=0; E=0 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-1000 | D=1; G=0; F=0; E=0 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-1001 | D=1; G=0; F=0; E=1 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-1001 | D=1; G=0; F=0; E=1 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-1010 | D=1; G=0; F=1; E=0 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-1010 | D=1; G=0; F=1; E=0 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-1011 | D=1; G=0; F=1; E=1 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-1011 | D=1; G=0; F=1; E=1 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-1100 | D=1; G=1; F=0; E=0 | V=1 | V=1 | PASSA |
| PLC Simulator Online | VE-1100 | D=1; G=1; F=0; E=0 | V=1 | V=1 | PASSA |
| CircuitVerse | VE-1101 | D=1; G=1; F=0; E=1 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-1101 | D=1; G=1; F=0; E=1 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-1110 | D=1; G=1; F=1; E=0 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-1110 | D=1; G=1; F=1; E=0 | V=0 | V=0 | PASSA |
| CircuitVerse | VE-1111 | D=1; G=1; F=1; E=1 | V=0 | V=0 | PASSA |
| PLC Simulator Online | VE-1111 | D=1; G=1; F=1; E=1 | V=0 | V=0 | PASSA |
| CircuitVerse | RE-000 | CA=0; CB=0; E=0 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| PLC Simulator Online | RE-000 | CA=0; CB=0; E=0 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| CircuitVerse | RE-001 | CA=0; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| PLC Simulator Online | RE-001 | CA=0; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| CircuitVerse | RE-010 | CA=0; CB=1; E=0 | MA=0; MB=1 | MA=0; MB=1 | PASSA |
| PLC Simulator Online | RE-010 | CA=0; CB=1; E=0 | MA=0; MB=1 | MA=0; MB=1 | PASSA |
| CircuitVerse | RE-011 | CA=0; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| PLC Simulator Online | RE-011 | CA=0; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| CircuitVerse | RE-100 | CA=1; CB=0; E=0 | MA=1; MB=0 | MA=1; MB=0 | PASSA |
| PLC Simulator Online | RE-100 | CA=1; CB=0; E=0 | MA=1; MB=0 | MA=1; MB=0 | PASSA |
| CircuitVerse | RE-101 | CA=1; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| PLC Simulator Online | RE-101 | CA=1; CB=0; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| CircuitVerse | RE-110 | CA=1; CB=1; E=0 | MA=1; MB=0 | MA=1; MB=0 | PASSA |
| PLC Simulator Online | RE-110 | CA=1; CB=1; E=0 | MA=1; MB=0 | MA=1; MB=0 | PASSA |
| CircuitVerse | RE-111 | CA=1; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| PLC Simulator Online | RE-111 | CA=1; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| CircuitVerse | V-EM1 | D=1; G=1; F=0; E=0 | V=1 | V=1 | PASSA |
| PLC Simulator Online | V-EM1 | D=1; G=1; F=0; E=0 | V=1 | V=1 | PASSA |
| CircuitVerse | V-EM2 | D=1; G=1; F=0; E=1 | V=0 | V=0 | PASSA |
| PLC Simulator Online | V-EM2 | D=1; G=1; F=0; E=1 | V=0 | V=0 | PASSA |
| CircuitVerse | V-EM3 | D=1; G=1; F=0; E=0 | V=1 | V=1 | PASSA |
| PLC Simulator Online | V-EM3 | D=1; G=1; F=0; E=0 | V=1 | V=1 | PASSA |
| CircuitVerse | V-F1 | D=1; G=1; F=0; E=0 | V=1 | V=1 | PASSA |
| PLC Simulator Online | V-F1 | D=1; G=1; F=0; E=0 | V=1 | V=1 | PASSA |
| CircuitVerse | V-F2 | D=1; G=1; F=1; E=0 | V=0 | V=0 | PASSA |
| PLC Simulator Online | V-F2 | D=1; G=1; F=1; E=0 | V=0 | V=0 | PASSA |
| CircuitVerse | V-F3 | D=1; G=1; F=0; E=0 | V=1 | V=1 | PASSA |
| PLC Simulator Online | V-F3 | D=1; G=1; F=0; E=0 | V=1 | V=1 | PASSA |
| CircuitVerse | R-A-EM1 | CA=1; CB=1; E=0 | MA=1; MB=0 | MA=1; MB=0 | PASSA |
| PLC Simulator Online | R-A-EM1 | CA=1; CB=1; E=0 | MA=1; MB=0 | MA=1; MB=0 | PASSA |
| CircuitVerse | R-A-EM2 | CA=1; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| PLC Simulator Online | R-A-EM2 | CA=1; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| CircuitVerse | R-A-EM3 | CA=1; CB=1; E=0 | MA=1; MB=0 | MA=1; MB=0 | PASSA |
| PLC Simulator Online | R-A-EM3 | CA=1; CB=1; E=0 | MA=1; MB=0 | MA=1; MB=0 | PASSA |
| CircuitVerse | R-B-EM1 | CA=0; CB=1; E=0 | MA=0; MB=1 | MA=0; MB=1 | PASSA |
| PLC Simulator Online | R-B-EM1 | CA=0; CB=1; E=0 | MA=0; MB=1 | MA=0; MB=1 | PASSA |
| CircuitVerse | R-B-EM2 | CA=0; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| PLC Simulator Online | R-B-EM2 | CA=0; CB=1; E=1 | MA=0; MB=0 | MA=0; MB=0 | PASSA |
| CircuitVerse | R-B-EM3 | CA=0; CB=1; E=0 | MA=0; MB=1 | MA=0; MB=1 | PASSA |
| PLC Simulator Online | R-B-EM3 | CA=0; CB=1; E=0 | MA=0; MB=1 | MA=0; MB=1 | PASSA |

## CircuitVerse — histórico

| Grupo | ID | Entrada | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| PB | PB01[AND 00] | — | Y_AND=0 | Y_AND=0 | PASSA |
| PB | PB02[AND 01] | — | Y_AND=0 | Y_AND=0 | PASSA |
| PB | PB03[AND 10] | — | Y_AND=0 | Y_AND=0 | PASSA |
| PB | PB04[AND 11] | — | Y_AND=1 | Y_AND=1 | PASSA |
| PB | PB05[OR 00] | — | Y_OR=0 | Y_OR=0 | PASSA |
| PB | PB06[OR 01] | — | Y_OR=1 | Y_OR=1 | PASSA |
| PB | PB07[OR 10] | — | Y_OR=1 | Y_OR=1 | PASSA |
| PB | PB08[OR 11] | — | Y_OR=1 | Y_OR=1 | PASSA |
| PB | PB09[NOT 0] | — | Y_NOT=1 | Y_NOT=1 | PASSA |
| PB | PB10[NOT 1] | — | Y_NOT=0 | Y_NOT=0 | PASSA |
| P | P01 | S=0; G=0; E=0 | 0 | 0 | PASSA |
| P | P02 | S=0; G=0; E=1 | 0 | 0 | PASSA |
| P | P03 | S=0; G=1; E=0 | 0 | 0 | PASSA |
| P | P04 | S=0; G=1; E=1 | 0 | 0 | PASSA |
| P | P05 | S=1; G=0; E=0 | 0 | 0 | PASSA |
| P | P06 | S=1; G=0; E=1 | 0 | 0 | PASSA |
| P | P07 | S=1; G=1; E=0 | 1 | 1 | PASSA |
| P | P08 | S=1; G=1; E=1 | 0 | 0 | PASSA |
| A | A01 | T=0; P=0; MNT=0 | 0 | 0 | PASSA |
| A | A02 | T=0; P=1; MNT=0 | 1 | 1 | PASSA |
| A | A03 | T=1; P=0; MNT=0 | 1 | 1 | PASSA |
| A | A04 | T=1; P=1; MNT=0 | 1 | 1 | PASSA |
| A | A05 | T=0; P=0; MNT=1 | 0 | 0 | PASSA |
| A | A06 | T=0; P=1; MNT=1 | 0 | 0 | PASSA |
| A | A07 | T=1; P=0; MNT=1 | 0 | 0 | PASSA |
| A | A08 | T=1; P=1; MNT=1 | 0 | 0 | PASSA |
| INTER | I01[CA0 CB0 E0] | — | MA=0 MB=0 AL_E=0 | MA=0 MB=0 AL_E=0 | PASSA |
| INTER | I02[CA1 CB0 E0] | — | MA=1 MB=0 AL_E=0 | MA=1 MB=0 AL_E=0 | PASSA |
| INTER | I03[CA0 CB1 E0] | — | MA=0 MB=1 AL_E=0 | MA=0 MB=1 AL_E=0 | PASSA |
| INTER | I06[CA1 CB1 E0 política A] | — | MA=1 MB=0 AL_E=0 | MA=1 MB=0 AL_E=0 | PASSA |
| INTER | E01[tudo 0, E1] | — | MA=0 MB=0 AL_E=1 | MA=0 MB=0 AL_E=1 | PASSA |
| INTER | E02[CA1 E1] | — | MA=0 MB=0 AL_E=1 | MA=0 MB=0 AL_E=1 | PASSA |
| INTER | E03[CB1 E1] | — | MA=0 MB=0 AL_E=1 | MA=0 MB=0 AL_E=1 | PASSA |
| INTER | E04[CA1 CB1 E1] | — | MA=0 MB=0 AL_E=1 | MA=0 MB=0 AL_E=1 | PASSA |
| INTER | E05[E volta a 0, sem comandos] | — | MA=0 MB=0 AL_E=0 | MA=0 MB=0 AL_E=0 | PASSA |
| X | X01[00] | — | D=0 | D=0 | PASSA |
| X | X02[01] | — | D=1 | D=1 | PASSA |
| X | X03[10] | — | D=1 | D=1 | PASSA |
| X | X04[11] | — | D=0 | D=0 | PASSA |

## PLC Simulator Online — histórico

| Grupo | ID | Entrada | Esperado | Obtido | Situação |
|---|---|---|---|---|---|
| Ladder | P01 | S=0; G=0; E=0 | M=0 | M=0 | PASSA |
| Ladder | P02 | S=0; G=0; E=1 | M=0 | M=0 | PASSA |
| Ladder | P03 | S=0; G=1; E=0 | M=0 | M=0 | PASSA |
| Ladder | P04 | S=0; G=1; E=1 | M=0 | M=0 | PASSA |
| Ladder | P05 | S=1; G=0; E=0 | M=0 | M=0 | PASSA |
| Ladder | P06 | S=1; G=0; E=1 | M=0 | M=0 | PASSA |
| Ladder | P07 | S=1; G=1; E=0 | M=1 | M=1 | PASSA |
| Ladder | P08 | S=1; G=1; E=1 | M=0 | M=0 | PASSA |
| Ladder | A01 | T=0; P=0; MNT=0 | AL=0 | AL=0 | PASSA |
| Ladder | A02 | T=0; P=1; MNT=0 | AL=1 | AL=1 | PASSA |
| Ladder | A03 | T=1; P=0; MNT=0 | AL=1 | AL=1 | PASSA |
| Ladder | A04 | T=1; P=1; MNT=0 | AL=1 | AL=1 | PASSA |
| Ladder | A05 | T=0; P=0; MNT=1 | AL=0 | AL=0 | PASSA |
| Ladder | A06 | T=0; P=1; MNT=1 | AL=0 | AL=0 | PASSA |
| Ladder | A07 | T=1; P=0; MNT=1 | AL=0 | AL=0 | PASSA |
| Ladder | A08 | T=1; P=1; MNT=1 | AL=0 | AL=0 | PASSA |
| Ladder | X01 | SENS_A=0; SENS_B=0 | D_XOR=0 | D_XOR=0 | PASSA |
| Ladder | X02 | SENS_A=0; SENS_B=1 | D_XOR=1 | D_XOR=1 | PASSA |
| Ladder | X03 | SENS_A=1; SENS_B=0 | D_XOR=1 | D_XOR=1 | PASSA |
| Ladder | X04 | SENS_A=1; SENS_B=1 | D_XOR=0 | D_XOR=0 | PASSA |
| Ladder | V01 | D_DEM=0; G=0; F=0 | V=0 | V=0 | PASSA |
| Ladder | V02 | D_DEM=0; G=0; F=1 | V=0 | V=0 | PASSA |
| Ladder | V03 | D_DEM=0; G=1; F=0 | V=0 | V=0 | PASSA |
| Ladder | V04 | D_DEM=0; G=1; F=1 | V=0 | V=0 | PASSA |
| Ladder | V05 | D_DEM=1; G=0; F=0 | V=0 | V=0 | PASSA |
| Ladder | V06 | D_DEM=1; G=0; F=1 | V=0 | V=0 | PASSA |
| Ladder | V07 | D_DEM=1; G=1; F=0 | V=1 | V=1 | PASSA |
| Ladder | V08 | D_DEM=1; G=1; F=1 | V=0 | V=0 | PASSA |
| Ladder | R01 | CA=0; CB=0 | MA_ARB=0; MB_ARB=0 | MA_ARB=0; MB_ARB=0 | PASSA |
| Ladder | R02 | CA=0; CB=1 | MA_ARB=0; MB_ARB=1 | MA_ARB=0; MB_ARB=1 | PASSA |
| Ladder | R03 | CA=1; CB=0 | MA_ARB=1; MB_ARB=0 | MA_ARB=1; MB_ARB=0 | PASSA |
| Ladder | R04 | CA=1; CB=1 | MA_ARB=1; MB_ARB=0 | MA_ARB=1; MB_ARB=0 | PASSA |
| Ladder | E02 | CA=1; E=1 | MA=0; MB=0; AL_E=1; MA_ARB=0; MB_ARB=0; V=0 | MA=0; MB=0; AL_E=1; MA_ARB=0; MB_ARB=0; V=0 | PASSA |
| Ladder | E03 | CB=1; E=1 | MA=0; MB=0; AL_E=1; MA_ARB=0; MB_ARB=0; V=0 | MA=0; MB=0; AL_E=1; MA_ARB=0; MB_ARB=0; V=0 | PASSA |
| Ladder | E04 | CA=1; CB=1; E=1; D_DEM=1; G=1 | MA=0; MB=0; AL_E=1; MA_ARB=0; MB_ARB=0; V=0 | MA=0; MB=0; AL_E=1; MA_ARB=0; MB_ARB=0; V=0 | PASSA |
| Ladder | I02 | CA=1 | MA=1; MB=0 | MA=1; MB=0 | PASSA |
| Ladder | I03 | CB=1 | MA=0; MB=1 | MA=0; MB=1 | PASSA |
| Ladder | I06 | CA=1; CB=1 | MA=1; MB=0 | MA=1; MB=0 | PASSA |
| Ladder | V09 | D_DEM=1; G=1; F=1 | V=0 | V=0 | PASSA |
| Ladder | R05 | CA=1; CB=1; E=1 | MA_ARB=0; MB_ARB=0 | MA_ARB=0; MB_ARB=0 | PASSA |

