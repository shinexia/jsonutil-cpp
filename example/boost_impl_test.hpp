// Copyright (c) 2019 Shine Xia <shine.xgh@gmail.com>

#ifndef JSONUTIL_BOOST_IMPL_TEST_H
#define JSONUTIL_BOOST_IMPL_TEST_H


#include <string>
#include <vector>

struct Slot {
    std::string name;
    std::vector<std::string> values;
    bool replace;
    int type;
};

struct Intent {
    std::string name;
    std::vector<std::string> patterns;
    bool replace;
    int type;
};

struct Domain {
    std::string name;
    std::vector<Slot> slots;
    std::vector<Intent> intents;
};

int read_domain(const std::string& filepath, Domain& domain);


#endif //JSONUTIL_BOOST_IMPL_TEST_H
