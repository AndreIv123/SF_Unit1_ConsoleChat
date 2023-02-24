#pragma once

//! Уникальный идентификатор
/*!
Присваивается объекту при создании.

Позволяет ссылаться на объект не указывая сам объект.
*/
class Uniq
{

public:

	//! Идентификатор
	struct ID { long long value; }; 

	Uniq();
	~Uniq();

	auto id()->ID;

private:
	ID _id;
	static long long counterGeneratedID;
	static long long numberActiveObjectsID;
};

