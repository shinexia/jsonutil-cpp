//
// Created by shine on 3/21/19.
//

#ifndef JSONUTIL_JSONUTIL_H
#define JSONUTIL_JSONUTIL_H

#include "rapidjson/document.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/prettywriter.h"

#include <sstream>
#include <memory>
#include <vector>
#include <map>

namespace rapidjson {
    const Value Null;
}

// 序列化
// 特例
std::string ToJSON(const std::string &v);

// 通例
template<typename T>
std::string ToJSON(const std::unique_ptr<T> &v) {
    if (!v) {
        return "null";
    }
    std::ostringstream oss;
    oss << ToJSON(*v);
    return oss.str();
}

template<typename T>
std::string ToJSON(const std::shared_ptr<T> &v) {
    if (!v) {
        return "null";
    }
    std::ostringstream oss;
    oss << ToJSON(*v);
    return oss.str();
}

template<typename T>
std::string ToJSON(const std::vector<T> &v) {
    std::ostringstream os;
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        if (i > 0) {
            os << ",";
        }
        os << ToJSON(v[i]);
    }
    os << "]";
    return os.str();
}

template<typename K, typename V>
std::string ToJSON(const std::map<K, V> &in) {
    std::ostringstream os;
    os << "{";
    for (auto it = in.begin(); it != in.end(); ++it) {
        if (it != in.begin()) {
            os << ",";
        }
        os << "\"" << it->first << "\":" << ToJSON(it->second);
    }
    os << "}";
    return os.str();
}

template<typename T>
std::string ToJSON(const T &v) {
    std::ostringstream oss;
    oss << v;
    return oss.str();
}

// 效率很低, 仅用于调试
template<typename T>
std::string ToPrettyJSON(const T &v) {
    auto json = ToJSON(v);
    rapidjson::Document doc;
    doc.Parse(json.c_str());
    std::ostringstream oss;
    if (doc.HasParseError()) {
        oss << "{\"error\":\"" << doc.GetParseError() << "\"}";
        return oss.str();
    }
    rapidjson::OStreamWrapper osw(oss);
    rapidjson::PrettyWriter <rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
    return oss.str();
}

template<typename T>
std::string PtrToJSON(const T *v) {
    if (v == nullptr) {
        return "null";
    }
    std::ostringstream oss;
    oss << ToJSON(*v);
    return oss.str();
}

template<typename T>
std::string PtrToPrettyJSON(const T *v) {
    if (v == nullptr) {
        return "null";
    }
    std::ostringstream oss;
    oss << ToPrettyJSON(*v);
    return oss.str();
}


// 反序列化
// 特例
int FromJSON(const rapidjson::Value &in, bool &out);

int FromJSON(const rapidjson::Value &in, int &out);

int FromJSON(const rapidjson::Value &in, int64_t &out);

int FromJSON(const rapidjson::Value &in, float &out);

int FromJSON(const rapidjson::Value &in, double &out);

int FromJSON(const rapidjson::Value &in, std::string &out);

// 通例
template<typename T>
int FromJSON(const rapidjson::Value &v, std::unique_ptr<T> &out) {
    if (v.IsNull()) {
        out.reset();
        return 0;
    }
    if (out == nullptr) {
        out.reset(new T());
    }
    return FromJSON(v, *out);
}

template<typename T>
int FromJSON(const rapidjson::Value &v, std::shared_ptr<T> &out) {
    if (v.IsNull()) {
        out.reset();
        return 0;
    }
    if (out == nullptr) {
        out.reset(new T());
    }
    return FromJSON(v, *out);
}

template<typename T>
int FromJSON(const rapidjson::Value &in, std::vector<T> &out) {
    out.clear();
    if (in.IsNull()) {
        return 0;
    }
    if (!in.IsArray()) {
        return -1;
    }
    auto v = in.GetArray();
    for (auto &v1: v) {
        T t;
        int ret = FromJSON(v1, t);
        if (ret != 0) {
            out.clear();
            return -1;
        }
        out.push_back(std::move(t));
    }
    return 0;
}

template<typename K, typename V>
int FromJSON(const rapidjson::Value &in, std::map<K, V> &out) {
    out.clear();
    if (in.IsNull()) {
        return 0;
    }
    if (!in.IsObject()) {
        return -1;
    }
    auto v = in.GetObject();
    for (auto it = v.begin(); it != v.end(); ++it) {
        V t;
        int ret = FromJSON(it->value, t);
        if (ret != 0) {
            return ret;
        }
        K k;
        std::istringstream(it->name.GetString()) >> k;
        out.insert(std::pair<K, V>(std::move(k), std::move(t)));
    }
    return 0;
}

// in["some_key"] 在`some_key`不存在时会报错, 所以需要多一重检查
template <typename T>
int FromJSON(const rapidjson::Value &in, const char *key, T &out) {
    auto m = in.FindMember(key);
    if (m == in.MemberEnd()) {
        return FromJSON(rapidjson::Null, out);
    }
    return FromJSON(m->value, out);
}

template<typename T>
int ParseJSON(const std::string &in, T &t) {
    rapidjson::Document doc;
    doc.Parse(in.c_str());
    if(doc.HasParseError()) {
        return doc.GetParseError();
    }
    return FromJSON(doc, t);
}

#endif //JSONUTIL_JSONUTIL_H
