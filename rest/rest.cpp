/*
 * rest.cpp
 *
 *  Created on: Feb 8, 2026
 *      Author: jordan
 */

#include "internal_impl.h"
#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/detail/string_view.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/this_coro.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/beast.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <print>
#include <rest.h>
#include <string_view>

int &Rest::port() {
	static int port_ = 0;
	return port_;
}

boost::asio::awaitable<void> accept(std::string_view host,
									std::string_view service,
									std::string_view target) {
	auto &&executor = co_await boost::asio::this_coro::executor;
	boost::asio::ip::tcp::resolver resolver(executor);

	auto &&result = co_await resolver.async_resolve(host, service,
													boost::asio::use_awaitable);

	boost::asio::ip::tcp::acceptor acceptor(executor,
											result.begin()->endpoint());

	Rest::port() = acceptor.local_endpoint().port();

	std::println("Server running at: http://{}:{}", result.begin()->host_name(),
				 Rest::port());

	for (;;) {
		auto &&socket =
			co_await acceptor.async_accept(boost::asio::use_awaitable);

		boost::beast::tcp_stream stream(std::move(socket));

		co_spawn(executor, start_session(std::move(stream), target),
				 boost::asio::detached);
	}
}

struct Rest::impl {
	impl() :
		ctx{1} {}

	boost::asio::io_context ctx;
};

Rest::Rest(std::string_view host, std::string_view service,
		   std::string_view target) :
	pimpl{new impl} {
	boost::asio::co_spawn(pimpl->ctx, accept(host, service, target),
						  boost::asio::detached);
}

Rest::~Rest() { delete pimpl; }

void Rest::run() { pimpl->ctx.run(); }
