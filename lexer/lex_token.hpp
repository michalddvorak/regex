#pragma once
#include <utility> /*std::move*/

enum class lex_token_type
{
	LETTER, PLUS, CONCATENATION, ITERATION, LPAR, RPAR, EOI, ERR
};

struct lex_token
{
	lex_token(lex_token_type type);
	virtual ~lex_token() = default;
	lex_token_type m_type;
};

template <typename T>
struct lex_token_attr : public lex_token
{
	explicit lex_token_attr(lex_token_type type, T attr) : lex_token(type),
														   m_attr(std::move(attr)) { }
	T m_attr;
};