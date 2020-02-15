// Copyright 2018 Your Name <your_email>

#include <header.hpp>
std::string mythreads::get_hash() {
    static unsigned int rand = time(nullptr);
    std::string randomString = std::to_string(rand_r(&rand));
    const std::string hash = picosha2::hash256_hex_string(randomString);
    return hash;
}


bool mythreads::checkHash(const std::string &hash) {
    return hash.substr(hash.size() - correctEND.size()) == correctEND;
}


void mythreads::makeHash() {
    ++mythreads::currentCount;
    while (infoCount < 10) {
        mythreads::mute.lock();
        std::string hash = get_hash();
        mythreads::mute.unlock();

        if (checkHash(hash)) {
            logInfo(hash);
            infoCount++;
        } else {
            logTrace(hash);
        }
    }
}


void mythreads::startLogging() {
    if (_threadCount >= 1 && _threadCount
    <= std::thread::hardware_concurrency()) {
        std::vector<std::thread> threads;
        threads.reserve(_threadCount);
        for (size_t i = 0; i < _threadCount; ++i) {
            threads.emplace_back(makeHash);
        }
        for (auto &th : threads) {
            th.join();
        }
    } else{
        return;
    }
}


void mythreads::logInfo(const std::string &hash) {
    BOOST_LOG_TRIVIAL(info) << "Thread with ID: "
                            << std::this_thread::get_id() << " found hash - "
                            << hash << std::endl;
}


void mythreads::logTrace(const std::string &hash) {
    BOOST_LOG_TRIVIAL(trace) << "Thread with ID: "
                             << std::this_thread::get_id() << " found hash - "
                             << hash << std::endl;
}


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;


void mythreads::logInFile() {
    logging::add_file_log
            (
                    keywords::file_name = "/home/mora/Desktop/info.log",
                    keywords::rotation_size = 256 * 1024 * 1024,
                    keywords::time_based_rotation =
                            sinks::file::rotation_at_time_point(0, 0, 0),
                    keywords::filter =
                            logging::trivial::severity
                            >= logging::trivial::info,
                    keywords::format =
                            (
                                    expr::stream
                                            << boost::posix_time
                                            ::second_clock::local_time()
                                            << " : <" << logging
                                            ::trivial::severity
                                            << "> " << expr::smessage
                            ));

    logging::add_file_log
            (
                    keywords::file_name = "/home/mora/Desktop/trace.log",
                    keywords::rotation_size = 256 * 1024 * 1024,
                    keywords::time_based_rotation = sinks::file
                            ::rotation_at_time_point(0, 0, 0),
                    keywords::filter = logging::trivial::severity
                            >= logging::trivial::trace,
                    keywords::format =
                            (
                                    expr::stream
                                            << boost::posix_time
                                            ::second_clock::local_time()
                                            << " : <" << logging::
                                            trivial::severity
                                            << "> " << expr::smessage
                            ));
}
