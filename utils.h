#pragma once
#include <string>
#include <iostream>

char* hexToASCII(std::string c);
char* uint32_to_chars(uint32_t num, char* chars);
std::string uint32_to_string(uint32_t num);
void error(std::string str);