#ifndef TP03_CLASSIFICACAO_H
#define TP03_CLASSIFICACAO_H

// Fonte unica da regra de classificacao. O firmware de producao e o sketch
// de teste incluem este mesmo arquivo: nao ha uma segunda implementacao.
static inline const char* classificar(float pct) {
  if (pct < 0.0f || pct > 100.0f) {
    return "FALHA";
  }
  if (pct >= 85.0f) {
    return "PERIGO";
  }
  if (pct >= 70.0f) {
    return "ATENCAO";
  }
  return "NORMAL";
}

#endif
