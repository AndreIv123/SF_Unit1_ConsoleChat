#pragma once

#include "Message.h"
#include "UniqID.h"

#include <string>
#include <iostream>


Message::Message(const std::string &msg, Uniq::ID sender)
: _text(msg), _sender(sender)
{ std::cout << "#MSG# create " << (id()).value << std::endl; };

Message::~Message()
{ std::cout << "#MSG# delete " << (id()).value << std::endl; };


auto Message::getText() -> std::string
{return _text;};


auto Message::getSenderID() -> Uniq::ID
{return _sender;};


