/*
 * internal_impl.h
 *
 *  Created on: Feb 8, 2026
 *      Author: jordan
 */

#ifndef INTERNAL_IMPL_H_
#define INTERNAL_IMPL_H_

#include <CNPJ.h>
#include <boost/asio/awaitable.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/url/url_view.hpp>

namespace http = boost::beast::http;

enum Keep { yes = true, no = false };

boost::asio::awaitable<void> start_session(boost::beast::tcp_stream &&stream,
										   std::string_view target) noexcept;

class Session {
	boost::beast::tcp_stream stream;
	std::string_view target;
	CNPJ cnpj;

public:
	Session(boost::beast::tcp_stream &&stream, std::string_view target) :
		stream{std::move(stream)}, target{target} {};

	boost::asio::awaitable<Keep>
	not_implemented(http::request<http::string_body> &&request) noexcept;

	boost::asio::awaitable<Keep>
	not_found(http::request<http::string_body> &&request) noexcept;

	boost::asio::awaitable<Keep>
	bad_request(http::request<http::string_body> &&request) noexcept;

	boost::asio::awaitable<Keep>
	get_method(http::request<http::string_body> &&request,
			   boost::urls::url_view &&origin) noexcept;

	boost::asio::awaitable<Keep>
	post_method(http::request<http::string_body> &&request) noexcept;

	boost::asio::awaitable<Keep>
	validate(http::request<http::string_body> &&request,
			 std::string_view key) noexcept;

	boost::asio::awaitable<void> run() noexcept;
};

#endif /* INTERNAL_IMPL_H_ */
