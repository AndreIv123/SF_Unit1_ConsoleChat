#include "User.h"

#include <iostream>
#include <vector>

auto User::getLogin() -> std::string { return _login; };
auto User::getName() -> std::string { return _name; };
void User::setName(const std::string &name) {_name = name;};
long User::getUnread() { return (_messages.size() - _idxLastRead - 1); };


bool User::verify(const std::string &password) {return (_password.compare(password) == 0);};


auto User::msgPull() -> std::shared_ptr<Message>
{
    std::shared_ptr<Message> msg;

    if (getUnread() > 0) {\
        msg = (_messages[++_idxLastRead]);
        _messages[_idxLastRead] = nullptr;
    };

    return msg;
};


void User::msgPush(std::shared_ptr<Message> msg) {
    _messages.push_back(msg);
};



