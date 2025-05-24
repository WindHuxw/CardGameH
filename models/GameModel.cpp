#include "GameModel.h"
#include "./views/CardView.h"


bool GameInformation::handPush(CardInformation c)
{
	_handCard.handCardPush(c);
	return true;
}
bool GameInformation::handPop()
{
	_handCard.handCardPop();
	return true;
}
bool GameInformation::deskPush1(CardInformation c)
{
	_desktopCard.deskCardCardPush1(c);
	return true;
}
bool GameInformation::deskPop1()
{
	_desktopCard.deskCardCardPop1();
	return true;
}
bool GameInformation::deskPush2(CardInformation c)
{
	_desktopCard.deskCardCardPush2(c);
	return true;
}
bool GameInformation::deskPop2()
{
	_desktopCard.deskCardCardPop2();
	return true;
}

bool GameInformation::replacementHand()
{
	handPop();
	return true;
}

bool GameInformation::replacementHandByDesk1()
{
	handPop();
	auto tmp = deskTop1();
	handPush(tmp);
	deskPop1();
	return true;
}

bool GameInformation::replacementHandByDesk2()
{
	handPop();
	auto tmp = deskTop2();
	handPush(tmp);
	deskPop2();
	return true;
}


bool GameInformation::undoSave(ActionData a)
{
	_undoModel.stackPush(a);
	return true;
}
ActionData GameInformation::undoGame()
{
		return _undoModel.undo();	
}
CardInformation GameInformation::beforeHandTop()
{
	return _handCard.beforeHandTop();
}

CardInformation GameInformation::handTop()
{
	return _handCard.handTop();
}
CardInformation GameInformation::deskTop1()
{
	return _desktopCard.deskTop1();
}
CardInformation GameInformation::deskTop2()
{
	return _desktopCard.deskTop2();
}

bool GameInformation::judgeWin()
{
	if (_desktopCard.deskSize1() == 0 && _desktopCard.deskSize1() == 0)
	{
		win = true;
		return true;
	}
	else
	{
		win = false;
		return false;
	}
}

bool GameInformation::isWin()
{
	return win;
}