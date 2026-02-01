/*
 * main.cpp
 *
 *  Created on: Jan 31, 2026
 *      Author: jordan
 */

#include <CNPJ.h>
#include <print>

int main() {
	CNPJ cnpj;

	std::print("{}\n", cnpj.validar("12.ABC.345/01DE-35"));

	return 0;
}
