#pragma once
#include <iostream>
#include <string>
#include "DebugObjectContext.h"

class Debug
{
private:
	typedef const char* string;
	static int indentLevel;
	Debug() {};
	Debug(const Debug&) {};

public:

	static void increaseIndent() { indentLevel++; };
	static void decreaseIndent() { indentLevel--; };

	static std::string outputIndent() { return std::string(indentLevel * 2, ' '); };

	static void log(const char* content) { std::cout << outputIndent().c_str() << content << std::endl;};
	static void warning(const char* content) { std::cout << outputIndent().c_str() << "Warning: " << content << std::endl; };
	static void error(const char* content) { std::cout << outputIndent().c_str() << "ERROR: " << content << std::endl; };

	static void log(std::string content) { log(content.c_str()); };
	static void warning(std::string content) { warning(content.c_str()); };
	static void error(std::string content) { error(content.c_str()); };

	static void log(DebugObjectContext content) { log(content.log()); };

	static void titleLog(std::string title) { log("<>----" + title + "----<>"); };
	static void sectionBegin(std::string title) { titleLog(title); increaseIndent(); };
	static void sectionEnd(std::string title) { decreaseIndent(); titleLog(std::string(title.length(), '-')); };

	const std::string LINE = "--------------";
};