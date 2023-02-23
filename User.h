#pragma once

#include "Message.h"
#include "UniqID.h"


#include <string>
#include <vector>
#include <memory>



//! Пользователь чата
/*!

*/
class User : public Uniq
{
public:

    User(const std::string &login, const std::string &password)
    : _login(login), _password(password) {};

    auto getLogin() -> std::string;
    auto getName() -> std::string;
    void setName(const std::string &name);
    long getUnread();

    bool verify(const std::string &password);

    auto msgPull() -> std::shared_ptr<Message>;
    void msgPush(std::shared_ptr<Message> msg);


    std::vector<std::shared_ptr<Message>> _messages;


private:

    const std::string _login;
    std::string _password;
    std::string _name;
    long _numUnread {0};

    long _idxLastRead {-1};

};
