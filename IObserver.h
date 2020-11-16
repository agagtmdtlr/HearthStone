#pragma once

class Card;
enum class EVENT;
class IObserver
{

public:
	virtual ~IObserver(){}
	virtual void onNotify(Card& card, EVENT event) = 0;
	virtual void onNotify(Card* card, EVENT event) = 0;
};

