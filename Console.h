#pragma once

#include "Chat.h"
#include "Menu.h"


#include <string>
#include <memory>

//! Консоль программы
/*!
Предоставляет интерфейс пользователя посредством текстового меню в терминале.
*/
class Console
{


public:

    Console(std::shared_ptr<Chat> chat) {
        Console::_chat = chat;
        makeEntranceMenu();
        makeChatMenu();
    };

    void routine();



private:
    //Статика для доступа из передаваемых в меню функций
    static std::shared_ptr<Chat> _chat;
    static void registraion();
    static void login();
    static void renameUser();
    static void compose();
    static void receive();
    static auto request(const std::string &question) -> std::unique_ptr<std::string>;
    static void printChatUsersNum();
    static void printUserStatus();
    static void makeChatMenu();
    static void makeEntranceMenu();
    static auto makeRecipientMenu() -> std::unique_ptr<Menu>;

    static std::unique_ptr<Menu> _menuEntrance;
    static std::unique_ptr<Menu> _menuChat;


    void printHeader();
    void printUsersList();
    void printPromt();


};
