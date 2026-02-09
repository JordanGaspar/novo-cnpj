/*
 * post_method.cpp
 *
 *  Created on: Feb 8, 2026
 *      Author: jordan
 */

#include "internal_impl.h"
#include <boost/asio/awaitable.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/http/field.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/json/parse.hpp>
#include <boost/json/parse_options.hpp>

namespace http = boost::beast::http;

boost::asio::awaitable<Keep>
Session::post_method(http::request<http::string_body> &&request) noexcept {
	if (!request.at(http::field::content_type).contains("application/json")) {
		co_return co_await bad_request(std::move(request));
	}

	auto json = boost::json::parse(request.body()).as_object();

	if (!json.contains("cnpj")) {
		co_return co_await bad_request(std::move(request));
	}

	auto key = json.at("cnpj").as_string();

	co_return co_await validate(std::move(request), key);
}