#pragma once
#include <iostream>
#include <memory>
#include "lex_token.hpp"

class lexer
{
 public:
	virtual ~lexer() = default;
	virtual std::shared_ptr<lex_token> get_next_token() = 0;
};



class lexer_istream : public lexer
{
 public:
	virtual std::shared_ptr<lex_token> get_next_token() override;
	lexer_istream(std::istream& is);
 private:
	std::istream& m_is;
};


