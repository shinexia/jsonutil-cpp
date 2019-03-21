// Copyright (c) 2019 Shine Xia <shine.xgh@gmail.com>

#include "jsonutil/jsonutil.hpp"
#include <iostream>
#include <cstdlib>

struct Person {
    int ID;
    std::string Name;
};

struct Room {
    std::shared_ptr<Person> Teacher;
    std::vector<Person> Students;
};

std::string ToJSON(const Person& v) {
    std::ostringstream oss;
    oss << "{"
       << "\"id\":" << ToJSON(v.ID)
       << ", \"name\":" << ToJSON(v.Name)
       << "}";
    return oss.str();
}

int FromJSON(const rapidjson::Value& in, Person& out) {
    int ret = 0;
    ret += FromJSON(in, "id", out.ID);
    ret += FromJSON(in, "name", out.Name);
    return ret;
}

std::string ToJSON(const Room& v) {
    std::ostringstream oss;
    oss << "{"
        << "\"teacher\":" << ToJSON(v.Teacher)
        << ", \"students\":" << ToJSON(v.Students)
        << "}";
    return oss.str();
}

int FromJSON(const rapidjson::Value& in, Room& out) {
    int ret = 0;
    ret += FromJSON(in, "teacher", out.Teacher);
    ret += FromJSON(in, "students", out.Students);
    return ret;
}

int main(int argc, char* argv[]) {
    std::unique_ptr<Room> room(new Room());
    std::shared_ptr<Person> teacher(new Person());
    teacher->ID = 0;
    teacher->Name = "teacher";
    std::vector<Person> students(3);
    for (int i =0; i< students.size(); ++i) {
        auto& student = students[i];
        student.ID = i;
        char buf[40];
        sprintf(buf, "student:%d", i);
        student.Name = buf;
    }
    room->Teacher = std::move(teacher);
    room->Students = std::move(students);

    std::string json = ToPrettyJSON(room);

    std::cout << json << std::endl;

    std::shared_ptr<Room> room2;
    int ret = ParseJSON(json, room2);
    std::cout << "parse, ret=" << ret << std::endl;
    std::cout << "room2:\n" << ToPrettyJSON(room2) << std::endl;
}
