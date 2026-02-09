/*
 * rest.h
 *
 *  Created on: Feb 8, 2026
 *      Author: jordan
 */

#ifndef REST_H_
#define REST_H_

#include <string_view>

class Rest {
	struct impl;
	impl *pimpl;

public:
	Rest(std::string_view host = "localhost", std::string_view service = "0",
		 std::string_view target = "/validar_cnpj");
	~Rest();

	void run();

	static int &port();
};

#endif /* REST_H_ */
