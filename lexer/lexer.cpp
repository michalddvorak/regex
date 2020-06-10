#include "lexer.hpp"
#include "../regex_ast/regex_defines.hpp"

lexer_istream::lexer_istream(std::istream& is) : m_is(is) { }


std::shared_ptr<lex_token> lexer_istream::get_next_token()
{
	char c;
	m_is >> c;
	if(m_is.eof())
		return std::make_shared<lex_token>(lex_token_type::EOI);
	else if(c == '+')
		return std::make_shared<lex_token>(lex_token_type::PLUS);
	else if(c == '.')
		return std::make_shared<lex_token>(lex_token_type::CONCATENATION);
	else if(c == '(')
		return std::make_shared<lex_token>(lex_token_type::LPAR);
	else if(c == ')')
		return std::make_shared<lex_token>(lex_token_type::RPAR);
	else if(c == '*')
		return std::make_shared<lex_token>(lex_token_type::ITERATION);
	else if(isalnum(c) || c == EPSILON || c == NULLCHAR)
		return std::make_shared<lex_token_attr<char>>(lex_token_type::LETTER, c);
	else
		return std::make_shared<lex_token>(lex_token_type::ERR);
}