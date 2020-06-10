#include "parser.hpp"


/***
 * Grammar G = ({E, E', T, T', F, F'}, {l, +, ., *, (, )}, P, E), where P contains rules:
 *(1) E -> T E'
 * E'.ires = T.res
 * E.res = E'.res
 *
 *(2) E_1' -> + T E_2'
 * E_2'.ires = E_1'.ires + T.res
 * E_1'.res = E_2'.res
 *
 *(3) E' -> ε
 * E'.res = E'.ires
 *
 *(4) T -> F T'
 * T'.ires = F.res
 * T.res = T'.res
 *
 *(5) T_1' -> . F T_2'
 * T_2'.ires = T_1'.ires . F.res
 * T_1'.res = T_2'.res
 *
 *(6) T_1' -> F T_2'
 * T_2'.ires = T_1'.ires . F.res
 * T_1'.res = T_2'.res
 *
 *(7) T' -> ε
 * T'.res = T'.ires
 *
 *(8) F -> l F'
 * F'.ires = l.val
 * F.res = F'.res
 *
 *(9) F -> ( E ) F'
 * F'.ires = E.res
 * F.res = F'.res
 *
 *(10) F_1' -> * F_2'
 * F_2'.ires = F_1'.ires *
 * F_1'.res = F_2'.res
 *
 *(11) F' -> ε
 *F'.res = F'.ires
 *
 *
 *
 * */

/**
 * Parsing table:
 * 	+-------+-------+-------+-------+-------+-------+-------+-------+
 * 	|		|	l	|	+	|	.	|	*	|	(	|	)	|	e	|
 * 	+-------+-------+-------+-------+-------+-------+-------+-------+
 *	|	E	|	1	|		|		|		|	1	|		|		|
 * 	+-------+-------+-------+-------+-------+-------+-------+-------+
 *	|	E'	|		|	2	|		|		|		|	3	|	3	|
 * 	+-------+-------+-------+-------+-------+-------+-------+-------+
 *	|	T	|	4	|		|		|		|	4	|		|		|
 * 	+-------+-------+-------+-------+-------+-------+-------+-------+
 *	|	T'	|	6	|	7	|	5	|		|	6	|	7	|	7	|
 * 	+-------+-------+-------+-------+-------+-------+-------+-------+
 *	|	F	|	8	|		|		|		|	9	|		|		|
 * 	+-------+-------+-------+-------+-------+-------+-------+-------+
 *	|	F'	|	11	|	11	|	11	|	10	|	11	|	11	|	11	|
 * 	+-------+-------+-------+-------+-------+-------+-------+-------+
 *
 *
 * */


parser::parser(lexer& lex) : m_lex(lex), m_token(m_lex.get_next_token()) { }

bool parser::compare(lex_token_type s)
{
	if(m_token->m_type == s)
	{
		m_token = m_lex.get_next_token();
		return true;
	}
	else
		return false;
}


regex_token* parser::parse_expr()
{
	regex_token* res = nt_e();
	if(m_token->m_type != lex_token_type::EOI)
	{
		delete res;
		return nullptr;
	}
	return res;
}


regex_token* parser::nt_f()
{
	regex_token* res;
	switch(m_token->m_type)
	{
		case lex_token_type::LETTER:
			//Get the value from the token, then compare it and in the end, call the next nonterminal
			res = new regex_token_letter(dynamic_cast<lex_token_attr<char>&>(*m_token).m_attr);
			compare(lex_token_type::LETTER);
			return nt_fp(res);
		case lex_token_type::LPAR:
			compare(lex_token_type::LPAR);
			res = nt_e();
			if(!compare(lex_token_type::RPAR))
			{
				delete res;
				return nullptr;
			}
			return nt_fp(res);
		default:
			return nullptr;
	}
}


regex_token* parser::nt_tp(regex_token* ires)
{
	switch(m_token->m_type)
	{
		case lex_token_type::LETTER:
		case lex_token_type::LPAR:
			return nt_tp(new regex_token_concatenation(ires, nt_f()));
		case lex_token_type::CONCATENATION:
			compare(lex_token_type::CONCATENATION);
			return nt_tp(new regex_token_concatenation(ires, nt_f()));
		case lex_token_type::PLUS:
		case lex_token_type::RPAR:
		case lex_token_type::EOI:
			return ires;
		default:
			delete ires;
			return nullptr;
	}
}


regex_token* parser::nt_t()
{
	switch(m_token->m_type)
	{
		case lex_token_type::LETTER:
		case lex_token_type::LPAR:
			return nt_tp(nt_f());
		default:
			return nullptr;
	}
}


regex_token* parser::nt_ep(regex_token* ires)
{
	switch(m_token->m_type)
	{
		case lex_token_type::PLUS:
			compare(lex_token_type::PLUS);
			return nt_ep(new regex_token_plus(ires, nt_t()));
		case lex_token_type::RPAR:
		case lex_token_type::EOI:
			return ires;
		default:
			delete ires;
			return nullptr;
	}
}

regex_token* parser::nt_e()
{
	switch(m_token->m_type)
	{
		case lex_token_type::LETTER:
		case lex_token_type::LPAR:
			return nt_ep(nt_t());
		default:
			return nullptr;
	}
}

regex_token* parser::nt_fp(regex_token* ires)
{
	switch(m_token->m_type)
	{
		case lex_token_type::ITERATION:
			compare(lex_token_type::ITERATION);
			return nt_fp(new regex_token_iteration(ires));
		case lex_token_type::LETTER:
		case lex_token_type::PLUS:
		case lex_token_type::CONCATENATION:
		case lex_token_type::LPAR:
		case lex_token_type::RPAR:
		case lex_token_type::EOI:
			return ires;
		default:
			delete ires;
			return nullptr;
	}
}



