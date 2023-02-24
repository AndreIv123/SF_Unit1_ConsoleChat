#pragma once

#include "Message.h"
#include "UniqID.h"

#include <string>
#include <vector>
#include <memory>


//! Пользователь чата
/*!
Хранит данные аккаунта и (указатели на) получаемые сообщения. 

При отправке сообщения пользователю в его хранилище сообщенией 
добавляется разделяемый указатель на сообщения.

При прочтении сообщения пользователем разделяемый указатель 
на сообщение удаляется из хранилища. 
Сообщение считается доставленным и более не отслеживается пользователем.

*/
class User : public Uniq
{
public:

	User(const std::string& login, const std::string& password)
		: _login(login), _password(password) {};

	void setName(const std::string& name);

	auto getLogin()->std::string;
	auto getName()->std::string;
	long getUnread();
	
	bool verify(const std::string& password);

	auto msgPull()->std::shared_ptr<Message>;
	void msgPush(std::shared_ptr<Message> msg);

	std::vector<std::shared_ptr<Message>> _messages;

private:

	const std::string _login;
	std::string _password;
	std::string _name;

	long _idxLastRead{ -1 };

};
