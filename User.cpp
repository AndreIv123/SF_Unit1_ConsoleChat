#include "User.h"

#include <iostream>
#include <vector>

auto User::getLogin() -> std::string { return _login; };
auto User::getName() -> std::string { return _name; };
void User::setName(const std::string &name) {_name = name;};
long User::getUnread() { return (_messages.size() - _idxLastRead); };


bool User::verify(const std::string &password) {return (_password.compare(password) == 0);};


auto User::msgPull() -> std::shared_ptr<Message>
{
    std::shared_ptr<Message> msg;

    if (getUnread() > 0) {\
        //msg = move(_messages[++_idxLastRead]);
    };

    return msg;
};


void User::msgPush(std::shared_ptr<Message> msg) {
    std::cout  << "push " << (msg->id()).value << std::endl;
    std::cout << "msg : " << msg->getText() << std::endl;
    std::cout  << "size " << _messages.size() << std::endl;
    //_messages.push_back(msg);
};



