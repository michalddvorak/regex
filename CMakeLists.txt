cmake_minimum_required(VERSION 3.16)
project(regex)

set(CMAKE_CXX_STANDARD 17)

add_executable(regex main.cpp parser/parser.cpp parser/parser.hpp lexer/lexer.cpp lexer/lexer.hpp regex_ast/regex_defines.hpp regex_ast/regex_tokens.cpp regex_ast/regex_tokens.hpp lexer/lex_token.cpp lexer/lex_token.hpp regex.cpp regex.hpp)