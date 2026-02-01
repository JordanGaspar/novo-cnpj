/*novo-cnpj - programa para validação de cnpj em C++ para ASCII e EBCDIC
Copyright (C) 2026 Jordan Gaspar Alves Silva

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/*
 * CNPJ.cpp
 *
 *  Created on: Jan 31, 2026
 *      Author: jordan
 */

#include <CNPJ.h>

#include <algorithm>
#include <charconv>

using namespace std;

static int getASCII(char character) {
	bool check = character == '/' or character == '.' or character == '-';

	if (check) {
		return -1;
	}

	char result = character - 'A';
	return result + 65 - 48;
}

static int operar(int fator, string_view element) {
	int soma = 0;

	for (const auto &c : element) {
		int n = (c - '0');

		if (n > 9 or n < 0) {
			n = getASCII(c);

			if (n == -1) {
				continue;
			}
		}

		soma += n * fator;

		fator++;

		if (fator > 9) {
			fator = 2;
		}
	}

	return soma;
}

CNPJ::CNPJ() :
	alfabeto("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/-."), numeros{"0123456789"} {
	sort(alfabeto.begin(), alfabeto.end());
	sort(numeros.begin(), numeros.end());
}

bool CNPJ::validar(string_view cnpj) {

	auto sz = cnpj.size();

	bool stop =
		sz != 14 and ((sz != 18) or (cnpj[2] != '.' or cnpj[6] != '.' or
									 cnpj[10] != '/' or cnpj[15] != '-'));

	if (stop) {
		return false;
	}

	auto tail = cnpj.substr(cnpj.size() - 2, 2);

	for (auto &c : tail) {
		if (!binary_search(numeros.begin(), numeros.end(), c)) {
			return false;
		}
	}

	auto head = cnpj.substr(0, cnpj.size() - 2);

	for (auto &c : head) {
		if (!binary_search(alfabeto.begin(), alfabeto.end(), c)) {
			return false;
		}
	}

	int dv{};

	from_chars(tail.begin(), tail.end(), dv);

	int soma = operar(6, head);

	if ((soma % 11) != (dv / 10)) {
		// return false;
	}

	soma = operar(5, cnpj.substr(0, cnpj.size() - 1));

	if ((soma % 11) != (dv % 10)) {
		return false;
	}

	return true;
}
