#include "utils.h"

char* hexToASCII(std::string c)
{
	int length = c.length();
	std::string newString;
	for (int i = 0; i < length; i+=2)
	{
		std::string byte = c.substr(i, 2);
		char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
		newString.push_back(chr);
	}
	return (char*) newString.c_str();
}

char* uint32_to_chars(uint32_t num, char* chars){
    for(int i = 3; i >= 0; i--){
        int least = num % 256;
        chars[i] = least;
        num = num / 256;
    }
    return chars;
} 

std::string uint32_to_string(uint32_t num){
    std::string str;
    for(int i = 3; i >= 0; i--){
        int least = num % 256;
        char ch = least;
        str += ch;
        num = num / 256;
    }
    return str;
} 

void error(std::string str)
{
    perror(str);
    exit(EXIT_FAILURE);
}
