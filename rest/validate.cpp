/*
 * validate.cpp
 *
 *  Created on: Feb 9, 2026
 *      Author: jordan
 */

#include "internal_impl.h"

#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/json.hpp>

boost::asio::awaitable<Keep>
Session::validate(http::request<http::string_body> &&request,
				  std::string_view key) noexcept {
	auto valid = cnpj.validar(key);

	boost::json::value json = {{"valid", valid}};

	http::response<http::string_body> response(http::status::ok,
											   request.version());

	response.set(http::field::content_type, "application/json");
	response.body() = boost::json::serialize(json);
	response.keep_alive(request.keep_alive());
	response.prepare_payload();

	co_await http::async_write(stream, std::move(response),
							   boost::asio::use_awaitable);

	co_return request.keep_alive() ? Keep::yes : Keep::no;
}
