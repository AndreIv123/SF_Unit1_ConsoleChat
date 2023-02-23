#include "Console.h"
#include "Chat.h"

#include <iostream>
#include <string>
#include <memory>

std::shared_ptr<Chat> Console::_chat;
std::unique_ptr<Menu> Console::_menuEntrance;
std::unique_ptr<Menu> Console::_menuChat;


void Console::registraion()
{
    auto login = request(std::string("Login"));

    if ( _chat->usersExists(*login) ) {
        std::cout << "! Login exists" << std::endl;
    } else {
        auto password = request(std::string("Password"));
        _chat->usersRegist(*login, *password);
    };

};


void Console::login()
{
    auto login = request(std::string("Login"));

    if ( _chat->usersExists(*login) ) {

        auto password = request(std::string("Password"));
        _chat->login(*login, *password);

        auto id = _chat->getActiveID();
        if (id) {
            _menuChat->menu();
        } else {
            std::cout << "! Login failed" << std::endl;
        ;}
    } else {
        std::cout << "! Login is not registered" << std::endl;
    };

};



void Console::renameUser()
{
    auto name = request(std::string("New name"));
    _chat->usersRename(*name);
};


void Console::compose()
{
    auto text = request(std::string("Message:"));

    std::unique_ptr<Menu> menu = makeRecipientMenu();
    std::unique_ptr<std::vector<Uniq::ID>> userlist = _chat->usersIDs();

    for (long idx=0; idx<((*userlist).size()); ++idx) {
        Uniq::ID id = ((*userlist)[idx]);
        std::unique_ptr<std::string> name = _chat->usersNameByID(id);
        menu->addOption((*name) + " ID:" + std::to_string(id.value) );
    };



    Uniq::ID idRec = (*userlist)[menu->menu()];

    std::unique_ptr<Uniq::ID> msgID = _chat->msgSend(std::string("message"),idRec);

};





void Console::routine()
{
    std::cout << std::endl << "# CONSOLE CHAT. SkillFactory Unit #1 project " << std::endl;

    _menuEntrance->menu();

};



void printUsersList() {};
void printPromt() {};


void menuEntrance()
{
    std::cout << std::endl << "# Entrance menu ";

};


void menuChat()
{};


void Console::makeEntranceMenu()
{
    if (! _menuEntrance ) {_menuEntrance = std::make_unique<Menu>();};

    _menuEntrance->setFlagZeroOptionLast(true);
    _menuEntrance->setFlagRepeatMenu(true);
    _menuEntrance->setFlagExpectUserInput(true);
    _menuEntrance->setFlagPromtUntilValid(true);

    _menuEntrance->setHeader(std::string("*** Entrance Menu ***"), printChatUsersNum);
    _menuEntrance->setPromt(std::string("---"));

    auto exit_option = _menuEntrance->addOption(std::string("EXIT"));
    _menuEntrance->markExit(exit_option);

    _menuEntrance->addOption(std::string("login (->)"), login);
    _menuEntrance->addOption(std::string("registration"), registraion);



    _menuEntrance->setFooter(std::string("*********************"));
};


void Console::makeChatMenu()
{
    if (! _menuChat ) {_menuChat = std::make_unique<Menu>();};

    _menuChat->setFlagZeroOptionLast(true);
    _menuChat->setFlagRepeatMenu(true);
    _menuChat->setFlagExpectUserInput(true);
    _menuChat->setFlagPromtUntilValid(true);

    _menuChat->setHeader(std::string("*** Chat Menu ***"), printUserStatus);
    _menuChat->setPromt(std::string("---"));

    auto exit_option = _menuChat->addOption(std::string("logout (<-)"));
    _menuChat->markExit(exit_option);

    _menuChat->addOption(std::string("update status"));
    _menuChat->addOption(std::string("read message"));
    _menuChat->addOption(std::string("send message"),compose);
    _menuChat->addOption(std::string("change name"), renameUser);

    _menuChat->setFooter(std::string("*********************"));
};



auto Console::makeRecipientMenu() -> std::unique_ptr<Menu>
{
    auto menu = std::make_unique<Menu>();

    menu->setFlagZeroOptionLast(false);
    menu->setFlagRepeatMenu(false);
    menu->setFlagExpectUserInput(true);
    menu->setFlagPromtUntilValid(true);

    _menuChat->setHeader(std::string("* User"));

    return menu;
};




//

auto Console::request(const std::string &question) -> std::unique_ptr<std::string>
{
    auto answer = std::make_unique<std::string>();
    std::cout << ">> " << question << " : ";
    std::cin >> (*answer);
    return answer;
};

void Console::printChatUsersNum()
{
    std::cout << "* number of chat users: " << _chat->usersNumber() << std::endl;
}

void Console::printUserStatus()
{
    std::unique_ptr<Uniq::ID> id = _chat->getActiveID();

    std::cout << "* user: ID" << id->value
              << " " << _chat->getActiveLogin()
              << " (aka '" << *(_chat->usersNameByID(*id)) << "')"
              << " unread " << _chat->msgUnread()
              << std::endl;
};

