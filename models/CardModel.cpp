#include "CardModel.h"

bool HandCard::handCardPush(CardInformation c)
{
	//CardInformation tmp = c;
	_handCardPairs.push_back(c);
	return true;
}
bool HandCard::handCardPop()
{
	if (!_handCardPairs.empty())
	{
		_handCardPairs.pop_back();
		return true;
	}
	else
	{
		return false;
	}
	
}
CardInformation HandCard::handTop()
{
	if (!_handCardPairs.empty())
	{
		return _handCardPairs.back();
	}
	else
	{
		CardInformation a;
		a._pointer = nullptr;
		a._CFTtype = CFT_NONE;
		a._CSTtype = CST_NONE;
		a._x = -1000;
		a._y = -1000;
		return a;
	}
}

CardInformation HandCard::beforeHandTop()
{
	if (_handCardPairs.size() >= 2)
	{
		return _handCardPairs[_handCardPairs.size()-2];
	}
	else
	{
		CardInformation a;
		a._pointer = nullptr;
		a._CFTtype = CFT_NONE;
		a._CSTtype = CST_NONE;
		a._x = -1000;
		a._y = -1000;
		return a;
	}
	
}


bool DesktopCard::deskCardCardPush1(CardInformation c)
{
	_deskCardPairs1.push_back(c);
	return true;
}
bool DesktopCard::deskCardCardPop1()
{
	_deskCardPairs1.pop_back();
	return true;
}
bool DesktopCard::deskCardCardPush2(CardInformation c)
{
	_deskCardPairs2.push_back(c);
	return true;
}
bool DesktopCard::deskCardCardPop2()
{
	_deskCardPairs2.pop_back();
	return true;
}
CardInformation DesktopCard::deskTop1()
{

	if (!_deskCardPairs1.empty())
	{
		return _deskCardPairs1.back();
	}
	else
	{
	CardInformation a;
	a._pointer = nullptr;
	a._CFTtype = CFT_NONE;
	a._CSTtype = CST_NONE;
	a._x = -1000;
	a._y = -1000;
	return a;
	}
}
CardInformation DesktopCard::deskTop2()
{
	if (!_deskCardPairs2.empty())
	{
		return _deskCardPairs2.back();
	}
	else
	{
		CardInformation a;
		a._pointer = nullptr;
		a._CFTtype = CFT_NONE;
		a._CSTtype = CST_NONE;
		a._x = -1000;
		a._y = -1000;
		return a;
	}
	
}

int HandCard::handSize()
{
	return  _handCardPairs.size();
}

int DesktopCard::deskSize1()
{
	return _deskCardPairs1.size();
}

int DesktopCard::deskSize2()
{
	return _deskCardPairs2.size();
}