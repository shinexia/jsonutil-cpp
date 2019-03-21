# jsonutil-cpp

`json`解析的辅助类, 这里是基于`rapidjson`实现的, 使用`boost::property_tree`等也是同理的


### 示列：

[example/simple_test.cpp](example/simple_test.cpp)

### 类定义

```cpp

class Person {
public:
    int ID;
    std::string Name;
};

class Room {
public:
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

```

### 序列化

```
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
```

### 输出

```json
{
    "teacher": {
        "id": 0,
        "name": "teacher"
    },
    "students": [
        {
            "id": 0,
            "name": "student:0"
        },
        {
            "id": 1,
            "name": "student:1"
        },
        {
            "id": 2,
            "name": "student:2"
        }
    ]
}
```

### 反序列化

```bash
std::shared_ptr<Room> room2;
int ret = ParseJSON(json, room2);
```


