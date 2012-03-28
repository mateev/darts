#ifndef DARTBOARD_H
#define DARTBOARD_H

#include "dartsCore.h"

class Dartboard
{
private:
public:
	Dartboard();
	~Dartboard();

	int HitTarget(int,int);
};

#endif