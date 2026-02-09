# novo-cnpj
Novo CNPJ em C++ para Unicode e EBCDIC.

## Requisitos
CMake e C++ 23. Mas é facilmente adaptável para versões anteriores.
O servidor Rest também requer a biblioteca Boost, porém ele é opcional.

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
```
## Como Adicionar no seu projeto?

```git
git clone https://github.com/JordanGaspar/novo-cnpj.git
```

No seu CMakeLists.txt:
```CMake
add_subdirectory(novo-cnpj)
target_link_libraries(${PROJECT_NAME} PRIVATE CNPJ)
```
## Servidor Rest

Há a opção de ativar o sistema utilizando um servidor Rest que entrega a validação no formato json.

No seu CMakeLists.txt:
```CMake
add_subdirectory(novo-cnpj)
target_link_libraries(${PROJECT_NAME} PUBLIC Rest)
```

A utilização em código é simpes.

```cpp

#include <Rest.h>

int main() {
  Rest rest("localhost", "8080", "/validar_cnpj");
  rest.run();
}

```
O servidor aceita requisições POST e GET no target definido na construção ("/validar_cnpj" no exemplo).

Por exemplo:
```
GET: http://localhost:8080/validar_cnpj?12.345.678/0001-90

ou também:

POST: http://localhost:8080/validar_cnpj
Contendo o seguinte json:
{"cnpj": "12.345.678/0001-90"}

Em ambos os casos retornando: {"valid" : false}
```
