#include "UniqID.h"

long long Uniq::counterGeneratedID{ 0 };

long long Uniq::numberActiveObjectsID{ 0 };


Uniq::Uniq()
{
	_id.value = ++Uniq::counterGeneratedID;
	++Uniq::numberActiveObjectsID;
};


Uniq::~Uniq()
{
	--Uniq::numberActiveObjectsID;
};


auto Uniq::id() -> ID { return _id; };

