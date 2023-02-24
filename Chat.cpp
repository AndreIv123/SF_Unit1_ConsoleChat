#include "Chat.h"
#include "User.h"

#include <memory>
#include <iostream>

long Chat::usersNumber() {return _users.size(); };

bool Chat::usersExists(const std::string &login) {return (index(login) >= 0);};

void Chat::usersRegist(const std::string &login, const std::string &password)
{
    if ( ! usersExists(login) ) {
        auto userNew = std::make_shared<User>(login, password);
        std::cout << "Capacity" << (userNew->_messages).size() << std::endl;
        userNew->setName(login);
        _users.push_back(userNew);

    };
};


void Chat::usersRename(const std::string &name) {
    if (_userActive) {_userActive->setName(name);};
};

void Chat::login(const std::string &login, const std::string &password)
{
    logout();
    if (usersExists(login)) {
        auto active_user = user(login);
        if (active_user->verify(password)) {
            _userActive=active_user;};
    };
};


void Chat::logout() {_userActive=nullptr;};


long Chat::index(const std::string &login) {

    long idx {0};
    long sz {_users.size()};

    for (; idx<sz; ++idx) { if (login == (_users[idx])->getLogin()) {break;};}

    if (idx >= sz) {idx = -1;};

    return idx;

};


auto Chat::user(const std::string &login) -> std::shared_ptr<User>
{
    long idx {index(login)};
    std::shared_ptr<User> user {nullptr};
    if (idx >= 0) {
        user=(_users[idx]);
    };
    return user;
};


auto Chat::user(const Uniq::ID &id) -> std::shared_ptr<User>
{
    long idx {0};
    long sz {_users.size()};
    std::shared_ptr<User> user;

    for (; idx<sz; ++idx)
    {
        if (id.value == ((_users[idx])->id()).value)
        {
            user = _users[idx];
            break;
        };
    };
    return user;
};


auto Chat::getActiveLogin() -> std::string
{
    std::string login;
    if (_userActive) {login=_userActive->getLogin();};
    return login;
};


auto Chat::getActiveID() -> std::unique_ptr<Uniq::ID>
{
    return  ((_userActive) ? std::make_unique<Uniq::ID>(_userActive->id()) : nullptr);
};


auto Chat::usersNameByID(const Uniq::ID &id) -> std::unique_ptr<std::string>
{
    long idx {0};
    long sz {_users.size()};
    auto name = std::make_unique<std::string>();

    for (; idx<sz; ++idx)
    {
        if (id.value == ((_users[idx])->id()).value)
        {
            (*name) = _users[idx]->getName();
            break;
        };
    };

    return name;
};

long Chat::msgUnread()
{
    return ((_userActive) ? _userActive->getUnread() : -1);
};


auto Chat::msgSend(const std::string &msg, const Uniq::ID &idRecep) -> std::unique_ptr<Uniq::ID>
{
    std::unique_ptr<Uniq::ID> msgID;

    if (_userActive) {
        auto message = std::make_shared<Message>(msg, _userActive->id());
        msgID = std::make_unique<Uniq::ID>(message->id());
        std::shared_ptr<User> recepient = user(idRecep);
        recepient->msgPush(message);
    };

    return msgID;
};

auto Chat::msgSendAll(const std::string &msg) -> std::unique_ptr<Uniq::ID>
{
    std::unique_ptr<Uniq::ID> msgID;

    if (_userActive) {

        auto message = std::make_shared<Message>(msg, _userActive->id());
        msgID = std::make_unique<Uniq::ID>(message->id());

        for (long idx=0; idx<_users.size(); idx++) {
            auto recepient = _users[idx];
            recepient->msgPush(message);
        };
    };

    return msgID;

};

auto Chat::msgReceive() -> std::shared_ptr<Message>
{
    return ( (msgUnread()>0) ? _userActive->msgPull() : nullptr);
};



auto Chat::usersIDs() -> std::unique_ptr<std::vector<Uniq::ID>>
{
    auto userlist = std::make_unique<std::vector<Uniq::ID>>();

    long idx {0};
    long sz {_users.size()};



    for (; idx<sz; ++idx)
    {
        (*userlist).push_back(_users[idx]->id());
    };

    return userlist;
};
