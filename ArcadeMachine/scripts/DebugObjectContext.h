#pragma once
#include <iostream>
#include <string>

class DebugObjectContext
{
public:
	virtual std::string log() { return ""; };
	virtual std::string fullLog() { return log(); };
};

