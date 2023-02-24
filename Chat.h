#pragma once

#include "User.h"
#include "UniqID.h"
#include "Message.h"

#include <string>
#include <vector>
#include <memory>


//! Чат обмена сообщений между пользователями
/*!
Ведет учет пользователей чата и обеспечивает прием/передачу сообщений между ними.

Чат является посредником между пользователи, 
 и передает пользователям ограниченный набор данных для обмена сообщениями,
 оставляя за собой непосредственный доступ к ним.
*/
class Chat
{

public:

	bool usersExists(const std::string& login);
	void usersRegist(const std::string& login, const std::string& password);
	void usersRename(const std::string& name);

	void login(const std::string& login, const std::string& password);
	void logout();

	long usersNumber();
	auto usersIDs()->std::unique_ptr<std::vector<Uniq::ID>>;
	auto usersNameByID(const Uniq::ID& id)->std::unique_ptr<std::string>;

	auto msgSend(const std::string& msg, const Uniq::ID& idRecep)->std::unique_ptr<Uniq::ID>;
	auto msgSendAll(const std::string& msg)->std::unique_ptr<Uniq::ID>;
	auto msgReceive()->std::shared_ptr<Message>;
	long msgUnread();

	auto getActiveLogin()->std::string;
	auto getActiveID()->std::unique_ptr<Uniq::ID>;

private:

	std::shared_ptr<User> _userActive;
	std::vector<std::shared_ptr<User>> _users;

	long index(const std::string& login);
	auto user(const std::string& login)->std::shared_ptr<User>;
	auto user(const Uniq::ID& id)->std::shared_ptr<User>;

};
