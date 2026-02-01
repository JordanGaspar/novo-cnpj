# novo-cnpj
Novo CNPJ em C++ para Unicode e EBCDIC.

## Como usar?
```cpp
#include <print>
#include <CNPJ.h>

class Objeto {
  CNPJ cnpj; // Deve, preferencialmente, ser mantido na memória durante a existência do programa.

  public:
  void rotina() {
    bool valido = cnpj.validar("12.ABC.345/01DE-35");

    if (valido) {
      std::print("Válido!\n");
    } else {
      std::print("Inválido!\n");
    }
  }
};
``
