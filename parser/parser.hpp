#pragma once

#include "../lexer/lexer.hpp"
#include "../regex_ast/regex_tokens.hpp"


/***
 * Grammar G = ({E, E', T, T', F, F'}, {l, +, ., *, (, )}, P, E)
 * */

class parser
{
 public:
	regex_token* parse_expr();
	parser(lexer& lex);
 private:
	regex_token* nt_e();
	regex_token* nt_ep(regex_token* ires);
	regex_token* nt_t();
	regex_token* nt_tp(regex_token* ires);
	regex_token* nt_f();
	regex_token* nt_fp(regex_token* ires);
	bool compare(lex_token_type tk);
	lexer& m_lex;
	std::shared_ptr<lex_token> m_token;
};



