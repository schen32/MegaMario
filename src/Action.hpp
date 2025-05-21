#pragma once

#include <sstream>
#include <string>

class Action
{
public:
	std::string m_name = "NONE";
	std::string m_type = "NONE";

	Action() = default;
	Action(const std::string& name, const std::string& type)
		: m_name(name), m_type(type) { }
};