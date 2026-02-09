/*
 * test2.cpp
 *
 *  Created on: Feb 8, 2026
 *      Author: jordan
 */

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/beast.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/http/field.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/status.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/verb.hpp>
#include <boost/json.hpp>
#include <boost/json/object.hpp>
#include <cassert>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <print>
#include <rest.h>
#include <stdexcept>
#include <thread>

bool validate_post(boost::beast::tcp_stream &stream, std::string_view target,
				   std::string_view body) {
	boost::beast::http::request<boost::beast::http::string_body> request{
		boost::beast::http::verb::post, target, 11};

	request.set(boost::beast::http::field::content_type, "application/json");
	request.body() = body;
	request.prepare_payload();

	boost::beast::http::write(stream, std::move(request));

	boost::beast::flat_buffer buffer;

	boost::beast::http::response<boost::beast::http::string_body> response;

	boost::beast::http::read(stream, buffer, response);

	if (response.result() != boost::beast::http::status::ok) {
		return false;
	}

	if (response.at(boost::beast::http::field::content_type) !=
		"application/json") {
		return false;
	}

	auto json = boost::json::parse(response.body()).as_object();

	if (!json.contains("valid")) {
		return false;
	}

	return json.at("valid").as_bool();
}

bool validate_get(boost::beast::tcp_stream &stream, std::string_view target) {
	boost::beast::http::request<boost::beast::http::string_body> request{
		boost::beast::http::verb::get, target, 11};

	request.prepare_payload();

	boost::beast::http::write(stream, std::move(request));

	boost::beast::flat_buffer buffer;

	boost::beast::http::response<boost::beast::http::string_body> response;

	boost::beast::http::read(stream, buffer, response);

	if (response.result() != boost::beast::http::status::ok) {
		return false;
	}

	if (response.at(boost::beast::http::field::content_type) !=
		"application/json") {
		return false;
	}

	auto json = boost::json::parse(response.body()).as_object();

	if (!json.contains("valid")) {
		return false;
	}

	return json.at("valid").as_bool();
}

void assert_get(boost::beast::tcp_stream &stream, std::string_view target,
				bool expected) {

	std::print("Testing get method with target: \"{}\" and expecting \"{}\"",
			   target, expected);

	if (validate_get(stream, target) != expected) {
		throw std::runtime_error(" - Fail!");
	}

	std::println(" - Pass!");
}

void assert_post(boost::beast::tcp_stream &stream, std::string_view target,
				 std::string_view cnpj, bool expected) {

	std::print("Testing post method with target: \"{}\", CNPJ: \"{}\" and "
			   "expecting \"{}\"",
			   target, cnpj, expected);

	boost::json::value json = {{"cnpj", cnpj}};

	if (validate_post(stream, target, boost::json::serialize(json)) !=
		expected) {
		throw std::runtime_error(" - Fail!");
	}

	std::println(" - Pass!");
}

int main() {

	auto host = "localhost";
	auto service = "0"; // Qualquer porta disponível

	std::thread th([&]() {
		Rest rest(host, service, "/validate");
		rest.run();
	});

	th.detach();

	std::println("Waiting 2 seconds to server startup");
	std::this_thread::sleep_for(std::chrono::seconds(2));

	boost::asio::io_context ctx{1};

	boost::asio::ip::tcp::resolver resolver(ctx);

	auto result = resolver.resolve(host, std::to_string(Rest::port()));

	if (result.empty()) {
		throw std::runtime_error("Result was empty");
	}

	boost::asio::ip::tcp::socket socket(ctx);
	socket.connect(result.begin()->endpoint());

	if (!socket.is_open()) {
		throw std::runtime_error("Socket was not opened");
	}

	boost::beast::tcp_stream stream(std::move(socket));

	/* Validation */

	try {
		assert_get(stream, "/validate", false);
		assert_get(stream, "/validate?00.000.000/0001-91", true);
		assert_get(stream, "/validate?00.000.000/0001-97", false);
		assert_get(stream, "/validate?12.345.678/000A-08", true);

		assert_post(stream, "/invalidate", "12.345.678/000A-08", false);
		assert_post(stream, "/validate", "00.000.000/0001-91", true);
		assert_post(stream, "/validate", "00.000.000/0001-97", false);
		assert_post(stream, "/validate", "12.345.678/000A-08", true);
	} catch (const std::exception &ec) {
		std::println("{}", ec.what());
		return EXIT_FAILURE;
	}

	/* End Validation */

	socket.close();

	return EXIT_SUCCESS;
}
