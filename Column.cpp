#include "Column.h"

/// @author Alexander Pinkerton

Column::Column()
	:length(0)
{
}

Column::Column(std::string & name)
	:name(name)
{
}


Column::~Column()
{
}

void Column::addEntry(const float & newEntry)
{
	entries.push_back(newEntry);
	length++;
}

float & Column::operator[](int && index)
{
	return entries.at(index);
}

float & Column::operator[](int & index)
{
	return entries.at(index);
}

