// Copyright (c) 2019 Shine Xia <shine.xgh@gmail.com>

#include "boost_impl_test.hpp"
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

namespace pt = boost::property_tree;

int read_json(boost::optional<pt::ptree&> node, std::string& out) {
    if (!node) {
        out.clear();
        return 0;
    }
    out = node->get_value<std::string>();
    return 1;
}

int read_json(boost::optional<pt::ptree&> node, int& out) {
    if (!node) {
        out = 0;
        return 0;
    }
    out = node->get_value<int>();
    return 1;
}

int read_json(boost::optional<pt::ptree&> node, bool& out) {
    if (!node) {
        out = false;
        return 0;
    }
    out = node->get_value<bool>();
    return 1;
}

template <typename T>
int read_json(boost::optional<pt::ptree&> node, std::vector<T>& out) {
    if (!node) {
        out.clear();
        return 0;
    }
    int ret = 0;
    for (auto it = node->begin(); it != node->end(); ++it) {
        T t;
        ret += read_json(boost::optional<pt::ptree&>(it->second), t);
        out.push_back(std::move(t));
    }
    return ret;
}

int read_json(boost::optional<pt::ptree&> node, Slot& slot) {
    if (!node) {
        return 0;
    }
    int ret = 0;
    ret += read_json(node->get_child_optional("name"), slot.name);
    ret += read_json(node->get_child_optional("values"), slot.values);
    ret += read_json(node->get_child_optional("replace"), slot.replace);
    ret += read_json(node->get_child_optional("type"), slot.type);
    return ret;
}

int read_json(boost::optional<pt::ptree&> node, Intent& intent) {
    if (!node) {
        return 0;
    }
    int ret = 0;
    ret += read_json(node->get_child_optional("name"), intent.name);
    ret += read_json(node->get_child_optional("patterns"), intent.patterns);
    ret += read_json(node->get_child_optional("replace"), intent.replace);
    ret += read_json(node->get_child_optional("type"), intent.type);
    return ret;
}

int read_json(boost::optional<pt::ptree&> node, Domain& domain) {
    if (!node) {
        return 0;
    }
    int ret = 0;
    ret += read_json(node->get_child_optional("name"), domain.name);
    ret += read_json(node->get_child_optional("slots"), domain.slots);
    ret += read_json(node->get_child_optional("intents"), domain.intents);
    return ret;
}

int read_domain(const std::string& filepath, Domain& domain) {
    pt::ptree root;
    pt::read_json(filepath, root);
    boost::optional<pt::ptree&> node(root);
    return read_json(node, domain);
}
