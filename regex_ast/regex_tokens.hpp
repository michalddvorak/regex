#pragma once

#include <array>
#include <iostream>
#include <map>

enum class regex_token_type
{
	PLUS, CONCATENATION, ITERATION, LETTER
};

struct regex_token
{
	regex_token(regex_token_type type);
	virtual ~regex_token() = default;
	virtual void print(std::ostream& os = std::cout) const = 0;
	const regex_token_type m_type;
};

template <typename T>
struct regex_token_val : public regex_token
{
	regex_token_val(regex_token_type type, const T& val) : regex_token(type),
														   m_val(val) { }
	T m_val;
	void print(std::ostream& os = std::cout) const override
	{
		os << m_val;
	}
};


struct regex_token_binary_op : public regex_token
{
	regex_token_binary_op(regex_token_type type,
						  regex_token* left,
						  regex_token* right);
	regex_token * m_left;
	regex_token * m_right;
};

struct regex_token_unary_op : public regex_token
{
	regex_token_unary_op(regex_token_type type,
						 regex_token* arg);
	regex_token * m_arg;
};

struct regex_token_iteration : public regex_token_unary_op
{
	regex_token_iteration(regex_token* arg);
	void print(std::ostream& os = std::cout) const override;
};

struct regex_token_concatenation : public regex_token_binary_op
{
	regex_token_concatenation(regex_token* left, regex_token* right);
	void print(std::ostream& os = std::cout) const override;
};

struct regex_token_plus : public regex_token_binary_op
{
	regex_token_plus(regex_token* left, regex_token* right);
	void print(std::ostream& os = std::cout) const override;
};
struct regex_token_letter : public regex_token_val<char>
{
	regex_token_letter(char c);
};
