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
 * main.cpp
 *
 *  Created on: Jan 31, 2026
 *      Author: jordan
 */

#include <CNPJ.h>
#include <cstdlib>
#include <exception>
#include <print>
#include <sstream>
#include <stdexcept>

using namespace std;

int main() {

	try {
		CNPJ cnpj;

		auto output = [&](const char *value, bool expected) {
			bool result = cnpj.validar(value);

			if (result != expected) {
				stringstream stream;

				print(
					stream,
					R"(Error: the value: "{}" expected "{}" but evaluated to "{}" instead!)",
					value, expected, result);

				throw runtime_error(stream.str());
			}

			print(R"(Value: "{}" is {}.)"
				  "\n",
				  value, result);
		};

		output("12.ABC.345/01DE-35", true);
		output("lixolixolixolixoli", false);
		output("çççççççççççççççççç", false);
		output("çççççççççççççç", false);
		output("\n\r\n\r\n\r\0\0\r", false);
		output("00.000.000/0001-91", true);

	} catch (const std::exception &e) {
		print("{}\n", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
