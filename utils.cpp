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

uint32_t uchars_to_uint32(unsigned char* chars){
    int num = 1;
    uint32_t result = 0;
    for(int i = 0; i < 4; i++){
        // std::cout << (uint) chars[i] << "x" << num << std::endl;
        result += chars[i] * num;
        num = num * 256;
    }

    return result;
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


