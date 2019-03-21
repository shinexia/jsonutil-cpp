//
// Created by shine on 3/21/19.
//

#include "jsonutil/jsonutil.h"

std::string ToJSON(const std::string &v) { return "\"" + v + "\""; }

int FromJSON(const rapidjson::Value &in, bool &out) {
    if (in.IsNull()) {
        out = false;
        return 0;
    }
    if (!in.IsBool()) {
        out = false;
        return -1;
    }
    out = in.GetBool();
    return 0;
}

int FromJSON(const rapidjson::Value &in, int &out) {
    if (in.IsNull()) {
        out = 0;
        return 0;
    }
    if (!in.IsInt()) {
        out = 0;
        return -1;
    }
    out = in.GetInt();
    return 0;
}

int FromJSON(const rapidjson::Value &in, int64_t &out) {
    if (in.IsNull()) {
        out = 0;
        return 0;
    }
    if (!in.IsInt64()) {
        out = 0;
        return -1;
    }
    out = in.GetInt64();
    return 0;
}

int FromJSON(const rapidjson::Value &in, float &out) {
    if (in.IsNull()) {
        out = 0;
        return 0;
    }
    if (!in.IsFloat()) {
        out = 0;
        return -1;
    }
    out = in.GetFloat();
    return 0;
}

int FromJSON(const rapidjson::Value &in, double &out) {
    if (in.IsNull()) {
        out = 0;
        return 0;
    }
    if (!in.IsDouble()) {
        out = 0;
        return -1;
    }
    out = in.GetDouble();
    return 0;
}

int FromJSON(const rapidjson::Value &in, std::string &out) {
    if (in.IsNull()) {
        out.clear();
        return 0;
    }
    if (!in.IsString()) {
        out.clear();
        return -1;
    }
    out = in.GetString();
    return 0;
}
