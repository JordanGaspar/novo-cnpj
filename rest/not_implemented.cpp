/*
 * not_implemented.cpp
 *
 *  Created on: Feb 8, 2026
 *      Author: jordan
 */

#include "internal_impl.h"
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/http/empty_body.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>

namespace http = boost::beast::http;

boost::asio::awaitable<Keep>
Session::not_implemented(http::request<http::string_body> &&request) noexcept {
	http::response<http::empty_body> response{http::status::not_implemented,
											  request.version()};

	response.keep_alive(request.keep_alive());
	response.prepare_payload();

	auto len = co_await http::async_write(stream, std::move(response),
										  boost::asio::use_awaitable);

	co_return request.keep_alive() ? Keep::yes : Keep::no;
}