/*
 * session.cpp
 *
 *  Created on: Feb 8, 2026
 *      Author: jordan
 */

#include "internal_impl.h"
#include <boost/asio/as_tuple.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/url.hpp>
#include <memory>

boost::asio::awaitable<void> Session::run() noexcept {

	Keep keep = Keep::yes;

	boost::beast::flat_buffer buffer;

	while (keep == Keep::yes) {
		http::request<http::string_body> request = {};

		auto [err, bytes_read] = co_await http::async_read(
			stream, buffer, request,
			boost::asio::as_tuple(boost::asio::use_awaitable));

		auto target_ = request.target();

		auto url_parsed = boost::urls::parse_origin_form(target_);

		if (!url_parsed) {
			keep = co_await not_found(std::move(request));
			continue;
		}

		auto origin = url_parsed.value();

		if (origin.encoded_path() != target) {
			keep = co_await not_found(std::move(request));
			continue;
		}

		auto method = request.method();

		if (method == http::verb::get) {
			keep = co_await get_method(std::move(request), std::move(origin));
		} else if (method == http::verb::post) {
			keep = co_await post_method(std::move(request));
		} else {
			keep = co_await not_implemented(std::move(request));
		}
	}
}

boost::asio::awaitable<void> start_session(boost::beast::tcp_stream &&stream,
										   std::string_view target) noexcept {
	auto session = std::make_unique<Session>(std::move(stream), target);
	co_await session->run();
}
