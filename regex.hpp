#pragma once
#include "regex_ast/regex_tokens.hpp"

class regex
{
 public:
	regex(const char * str);
	~regex();
	friend std::ostream& operator << (std::ostream& os, const regex& x);
 private:
	regex_token * m_root;
};




