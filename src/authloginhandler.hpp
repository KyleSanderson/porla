#pragma once

#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <sqlite3.h>

#include "httpcontext.hpp"

namespace porla
{
    struct AuthLoginHandlerOptions
    {
        sqlite3* db;
        std::string secret_key;
    };

    class AuthLoginHandler
    {
    public:
        explicit AuthLoginHandler(boost::asio::io_context& io, const AuthLoginHandlerOptions& opts);

        AuthLoginHandler(const AuthLoginHandler&) = delete;
        AuthLoginHandler(AuthLoginHandler&&) = delete;
        AuthLoginHandler& operator=(const AuthLoginHandler&) = delete;
        AuthLoginHandler& operator=(AuthLoginHandler&&) = delete;

        void operator()(const std::shared_ptr<HttpContext>&);

    private:
        boost::asio::io_context& m_io;
        sqlite3* m_db;
        std::string m_secret_key;
        std::vector<std::thread> m_threads;
    };
}
