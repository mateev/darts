#ifndef DARTBOARD_H
#define DARTBOARD_H

#include "dartsCore.h"

class Dartboard
{
public:
	Dartboard();
	~Dartboard();

	int HitTarget(int,int);
};

#endif