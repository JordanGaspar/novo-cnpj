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
