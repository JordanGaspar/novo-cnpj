/*
 * get_method.cpp
 *
 *  Created on: Feb 8, 2026
 *      Author: jordan
 */

#include "internal_impl.h"
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/json.hpp>
#include <boost/url.hpp>

namespace http = boost::beast::http;

boost::asio::awaitable<Keep>
Session::get_method(http::request<http::string_body> &&request,
					boost::urls::url_view &&origin) noexcept {

	auto query = origin.encoded_params();

	if (query.empty()) {
		co_return co_await bad_request(std::move(request));
	}

	auto key = query.begin()->key;

	co_return co_await validate(std::move(request), key);
}
