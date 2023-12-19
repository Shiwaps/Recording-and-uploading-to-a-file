#include <iostream>
#include <fstream>
#include <string>

class User {
public:
    std::string _name;
    std::string _login;
    std::string _pass;
};

class Message {
public:
    std::string _text;
    std::string _sender;
    std::string _receiver;
};

int main() {
    User user{"John Doe", "john", "password123"};
    Message message{"Hello, World!", "john", "jane"};

    {
        std::ofstream file("data.dat", std::ios::binary | std::ios::out);
        if (file.is_open()) {
            file.write(reinterpret_cast<const char*>(&user), sizeof(User));
            file.write(reinterpret_cast<const char*>(&message), sizeof(Message));
        } else {
            std::cerr << "Unable to open file for writing." << std::endl;
            return 1;
        }
    }

    User loadedUser;
    Message loadedMessage;

    {
        std::ifstream file("data.dat", std::ios::binary);
        if (file.is_open()) {
            file.read(reinterpret_cast<char*>(&loadedUser), sizeof(User));
            file.read(reinterpret_cast<char*>(&loadedMessage), sizeof(Message));
        } else {
            std::cerr << "Unable to open file for reading." << std::endl;
            return 1;
        }
    }

    return 0;
}