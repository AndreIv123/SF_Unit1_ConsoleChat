#pragma once

#include "UniqID.h"

#include <string>
#include <vector>

//! Контейнер сообщения чата
/*!
Хранение и доступ к тексту сообщения и приписываемым свойствам.
*/
class Message : public Uniq
{
public:

    Message(const std::string &msg, Uniq::ID sender);
    Message() = default;
    ~Message();

    auto getText() -> std::string;
    auto getSenderID() -> Uniq::ID;

private:
    const std::string _text;
    const Uniq::ID _sender;
};
