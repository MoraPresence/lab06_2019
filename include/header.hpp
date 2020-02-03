// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <cstdlib>
#include <iostream>
#include <ctime>
#include "picosha2.h"
#include <future>
#include <thread>
#include <vector>
#include <mutex>
#include <boost/log/trivial.hpp>

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

    static std::size_t _threadCount;
    static std::string correctEND;
    static std::atomic_uint infoCount;
    static std::size_t currentCount;
    static std::mutex mute;
};

std::string mythreads::correctEND = "0000";
std::size_t mythreads::_threadCount = std::thread::hardware_concurrency();
std::atomic_uint mythreads::infoCount = 0;
std::size_t mythreads::currentCount = 0;
std::mutex mythreads::mute;

#endif // INCLUDE_HEADER_HPP_
