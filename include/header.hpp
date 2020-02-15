// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <picosha2.h>
#include <future>
#include <thread>
#include <vector>
#include <mutex>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks.hpp>

class mythreads {
public:
    mythreads() = default;

    explicit mythreads(std::size_t threadCount) {
        _threadCount = threadCount;
    }

    static std::string get_hash();

    static bool checkHash(const std::string &);

    static void startLogging();

    static void makeHash();

    static void logInfo(const std::string &);

    static void logTrace(const std::string &);

    static void logInFile();

    static std::size_t _threadCount;
    static std::atomic_uint infoCount;
    static std::size_t currentCount;
    static std::mutex mute;
};

std::size_t mythreads::_threadCount = std::thread::hardware_concurrency();
std::atomic_uint mythreads::infoCount = 0;
std::size_t mythreads::currentCount = 0;
std::mutex mythreads::mute;
#endif // INCLUDE_HEADER_HPP_
