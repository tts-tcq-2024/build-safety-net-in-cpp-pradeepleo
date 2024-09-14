#include "Soundex.h"
#include <cctype>
#include <unordered_map>

using namespace std;

class SoundexCodeMap {
private:
    unordered_map<char, char> codeMap;

public:
    SoundexCodeMap() : codeMap{
        {'B', '1'}, {'F', '1'}, {'P', '1'}, {'V', '1'},
        {'C', '2'}, {'G', '2'}, {'J', '2'}, {'K', '2'},
        {'Q', '2'}, {'S', '2'}, {'X', '2'}, {'Z', '2'},
        {'D', '3'}, {'T', '3'},
        {'L', '4'},
        {'M', '5'}, {'N', '5'},
        {'R', '6'}
    } {}

    char getCode(char c) const {
        auto it = codeMap.find(toupper(c));
        return it != codeMap.end() ? it->second : '0';
    }
};

const SoundexCodeMap soundexMap;

char getSoundexCode(char c) {
    return soundexMap.getCode(c);
}
std::string getFirstLetter(const std::string& name) {
    return name.empty() ? "" : std::string(1, std::toupper(name[0]));
}
char encodeChar(char code, char prevCode) {
    if (code == '0' || code == prevCode) {
        return '\0';  // Return null char if same as previous or '0'
    }
    return code;
}

std::string getEncodedDigits(const std::string& name) {
    std::string encoded;
    char prevCode = '0';  // Initialize previous code

    size_t i = 1;
    while (i < name.length() && encoded.length() < 3) {  // 1 decision point from loop
        char code = getSoundexCode(name[i]);
        char encodedChar = encodeChar(code, prevCode);
        if (encodedChar != '\0') {  // 1 decision point
            encoded += encodedChar;  // Append encoded character
        }
        prevCode = code;  // Update previous code
        ++i;
    }

    return encoded;
}


std::string zeroPad(const std::string& s, size_t length) {
    return s + std::string(std::max(int(length) - int(s.length()), 0), '0');
}

std::string generateSoundex(const std::string& name) {
    return zeroPad(getFirstLetter(name) + getEncodedDigits(name), 4);
}
