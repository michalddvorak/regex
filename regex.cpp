#include "regex.hpp"
#include "parser/parser.hpp"
#include <sstream>
#include <stdexcept>

regex::regex(const char* str)
{
	std::stringstream ss(str);
	lexer_istream lex(ss);
	parser p(lex);
	m_root = p.parse_expr();
	if(m_root == nullptr)
		throw std::invalid_argument("Invalid regular expression");
}
regex::~regex()
{
	delete m_root;
}

std::ostream& operator <<(std::ostream& os, const regex& x)
{
	x.m_root->print(os);
	return os;
}