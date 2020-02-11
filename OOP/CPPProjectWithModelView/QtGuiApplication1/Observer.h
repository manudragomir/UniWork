#pragma once
class Observer
{
private:
	
public:
	Observer() {};
	virtual void update() = 0;
	~Observer() {};
};

