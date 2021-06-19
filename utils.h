#pragma once
#include <string>
#include <iostream>

char* hexToASCII(std::string c);
char* uint32_to_chars(uint32_t num, char* chars);
// unsigned char[] chars_to_uchars(char* chars, int len);
uint32_t uchars_to_uint32(unsigned char* chars);
std::string uint32_to_string(uint32_t num);