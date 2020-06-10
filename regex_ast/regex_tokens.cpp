#include "regex_tokens.hpp"

regex_token::regex_token(regex_token_type type) : m_type(type) { }


regex_token_binary_op::regex_token_binary_op(regex_token_type type,
											 regex_token* left,
											 regex_token* right) : regex_token(type), m_left(left), m_right(right) { }

regex_token_unary_op::regex_token_unary_op(regex_token_type type,
										   regex_token* arg) : regex_token(type), m_arg(arg) { }


regex_token_iteration::regex_token_iteration(regex_token* arg) : regex_token_unary_op(regex_token_type::ITERATION, arg) { }

regex_token_concatenation::regex_token_concatenation(regex_token* left,
													 regex_token* right) : regex_token_binary_op(regex_token_type::CONCATENATION, left, right) { }


regex_token_plus::regex_token_plus(regex_token* left,
								   regex_token* right) : regex_token_binary_op(regex_token_type::PLUS, left, right) { }

regex_token_letter::regex_token_letter(char c) : regex_token_val<char>(regex_token_type::LETTER, c) { }



const std::map<regex_token_type, int> print_priority = {{regex_token_type::LETTER,        6},
														{regex_token_type::ITERATION,     5},
														{regex_token_type::CONCATENATION, 4},
														{regex_token_type::PLUS,          3}};

void regex_token_iteration::print(std::ostream& os) const
{
	if(print_priority.at(m_arg->m_type) < print_priority.at(m_type))
	{
		os << '(';
		m_arg->print(os);
		os << ')';
	}
	else
	{
		m_arg->print(os);
	}
	os << '*';
}

void regex_token_plus::print(std::ostream& os) const
{
	if(print_priority.at(m_left->m_type) < print_priority.at(m_type))
	{
		os << '(';
		m_left->print(os);
		os << ')';
	}
	else
		m_left->print(os);
	
	os << '+';
	
	if(print_priority.at(m_right->m_type) < print_priority.at(m_type))
	{
		os << '(';
		m_right->print(os);
		os << ')';
	}
	else
		m_right->print(os);
}

void regex_token_concatenation::print(std::ostream& os) const
{
	
	if(print_priority.at(m_left->m_type) < print_priority.at(m_type))
	{
		os << '(';
		m_left->print(os);
		os << ')';
	}
	else
		m_left->print(os);
	
	if(print_priority.at(m_right->m_type) < print_priority.at(m_type))
	{
		os << '(';
		m_right->print(os);
		os << ')';
	}
	else
		m_right->print(os);
}