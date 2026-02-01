/*
 * CNPJ.h
 *
 *  Created on: Jan 31, 2026
 *      Author: jordan
 */

#ifndef CNPJ_H_
#define CNPJ_H_

#include <string>
#include <string_view>

class CNPJ final {
	std::string alfabeto;
	std::string numeros;

public:
	CNPJ();
	bool validar(std::string_view cnpj);

	CNPJ(CNPJ &&) = delete;
	CNPJ &operator=(CNPJ &&) = delete;

	CNPJ(const CNPJ &) = delete;
	CNPJ &operator=(const CNPJ &) = delete;
};

#endif /* CNPJ_H_ */
