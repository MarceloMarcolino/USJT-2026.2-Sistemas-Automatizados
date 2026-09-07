#ifndef TP03_MEDIA_MOVEL5_H
#define TP03_MEDIA_MOVEL5_H

class MediaMovel5 {
 public:
  MediaMovel5() : soma_(0), indice_(0), quantidade_(0) {
    for (unsigned char i = 0; i < 5; ++i) {
      janela_[i] = 0;
    }
  }

  float adicionar(int amostra) {
    if (quantidade_ < 5) {
      janela_[indice_] = amostra;
      soma_ += amostra;
      ++quantidade_;
    } else {
      soma_ -= janela_[indice_];
      janela_[indice_] = amostra;
      soma_ += amostra;
    }
    indice_ = (indice_ + 1) % 5;
    return static_cast<float>(soma_) / quantidade_;
  }

 private:
  int janela_[5];
  long soma_;
  unsigned char indice_;
  unsigned char quantidade_;
};

#endif
