// Copyright 2018 Your Name <your_email>

#include <header.hpp>
std::string mythreads::get_hash() {
    std::string randomString = std::to_string(std::rand());
    const std::string hash = picosha2::hash256_hex_string(randomString);
    return hash;
}

bool mythreads::checkHash(const std::string &hash) {
    return hash.substr(hash.size() - correctEND.size()) == correctEND;
}


void mythreads::makeHash() {
    ++mythreads::currentCount;
    while (true) {
        std::string hash = get_hash();
        if (checkHash(hash)) {
            mythreads::mute.lock();
            BOOST_LOG_TRIVIAL(info)
                    << "Thread with ID: " << std::this_thread::get_id()
                    << " found hash " << hash
                    << "!";
            mythreads::mute.unlock();
        } else {
            BOOST_LOG_TRIVIAL(trace)
                    << "Thread with ID: " << std::this_thread::get_id()
                    << " with hash " << hashOfRandString
                    << "!";
        }
    }
}


void mythreads::startLogging() {
    if (_threadCount >= 1 && _threadCount <= std::thread::hardware_concurrency()) {
        std::vector<std::thread> threads;
        threads.reserve(_threadCount);
        std::thread thr(mythreads::makeHash);
        std::thread thr1(mythreads::makeHash);
        std::thread thr2(mythreads::makeHash);

        thr.join();
        thr1.join();
        thr2.join();
    } else return;
}

int main() {
    ++mythreads::currentCount;
    mythreads ths(8);
    ths.startLogging();
    return 0;
}
