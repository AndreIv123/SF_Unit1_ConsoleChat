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

	if (_chat->usersExists(*login)) {
		std::cout << "! Login exists" << std::endl;
	}
	else {
		auto password = request(std::string("Password"));
		_chat->usersRegist(*login, *password);
	};

};


void Console::login()
{
	auto login = request(std::string("Login"));

	if (_chat->usersExists(*login)) {

		auto password = request(std::string("Password"));
		_chat->login(*login, *password);

		auto id = _chat->getActiveID();
		if (id) {
			_menuChat->menu();
		}
		else {
			std::cout << "! Login failed" << std::endl;
			;
		}
	}
	else {
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
	auto text = request(std::string("Message"));
	auto userlist = _chat->usersIDs();

	auto menu = makeRecipientMenu();
	menu->addOption(std::string("ALL"));
	for (long idx = 0; idx < ((*userlist).size()); ++idx) {
		Uniq::ID id = ((*userlist)[idx]);
		std::unique_ptr<std::string> name = _chat->usersNameByID(id);
		menu->addOption((*name) + " (ID:" + std::to_string(id.value) + ")");
	};

	auto idx = (menu->menu()) - 1;
	if (idx >= 0) {
		auto idRec = std::make_unique<Uniq::ID>((*userlist)[idx]);
		std::unique_ptr<Uniq::ID> msgID = _chat->msgSend(*text, *idRec);
	}
	else {
		_chat->msgSendAll(*text);
	};

};


void Console::receive()
{
	if (_chat->msgUnread() > 0) {
		auto msg = _chat->msgReceive();
		if (msg) {
			auto idMsg = msg->id();
			auto idSender = msg->getSenderID();
			auto nameSender = _chat->usersNameByID(idSender);
			std::cout <<  std::endl << std::endl << "#||||||||||||||||||||#" << std::endl;
			std::cout << "<< MsgID: " << idMsg.value << std::endl;
			std::cout << "<< Sender: '" << *nameSender << "' (ID" << idSender.value << ")" << std::endl;
			std::cout << "<< Text: " << msg->getText() << std::endl;
		};
	}
	else {
		std::cout << "! No unread msgs" << std::endl;
	};

};


void Console::routine()
{
	std::cout << std::endl << "# CONSOLE CHAT. SkillFactory Unit #1 project " << std::endl;
	_menuEntrance->menu();
};


void menuEntrance()
{
	std::cout << std::endl << "# Entrance menu ";

};


void Console::makeEntranceMenu()
{
	if (!_menuEntrance) { _menuEntrance = std::make_unique<Menu>(); };

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
	if (!_menuChat) { _menuChat = std::make_unique<Menu>(); };

	_menuChat->setFlagZeroOptionLast(true);
	_menuChat->setFlagRepeatMenu(true);
	_menuChat->setFlagExpectUserInput(true);
	_menuChat->setFlagPromtUntilValid(true);

	_menuChat->setHeader(std::string("*** Chat Menu ***"), printUserStatus);
	_menuChat->setPromt(std::string("---"));

	auto exit_option = _menuChat->addOption(std::string("logout (<-)"));
	_menuChat->markExit(exit_option);

	_menuChat->addOption(std::string("update status")); //reenter menu
	_menuChat->addOption(std::string("read message"), receive);
	_menuChat->addOption(std::string("send message"), compose);
	_menuChat->addOption(std::string("change name"), renameUser);

	_menuChat->setFooter(std::string("*********************"));
};


auto Console::makeRecipientMenu() -> std::unique_ptr<Menu>
{
	auto menu = std::make_unique<Menu>();

	menu->setFlagZeroOptionLast(true);
	menu->setFlagRepeatMenu(false);
	menu->setFlagExpectUserInput(true);
	menu->setFlagPromtUntilValid(false);

	menu->setHeader(std::string("* Recepients:"));

	return menu;
};


auto Console::request(const std::string& question) -> std::unique_ptr<std::string>
{
	auto answer = std::make_unique<std::string>();
	std::cout << ">> " << question << " : ";

	std::getline(std::cin, *answer);
	//std::cin >> (*answer);
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
