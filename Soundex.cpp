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
std::string encodeChar(char code, char prevCode) {
    if (code == '0') {
        return "";
    }
    if (code == prevCode) {
        return "";
    }
    return std::string(1, code);
}

std::string getEncodedDigits(const std::string& name) {
    std::string encoded;
    char prevCode = '0';

    for (size_t i = 1; i < name.length(); ++i) {
        if (encoded.length() >= 3) {
            break;
        }
        char code = getSoundexCode(name[i]);
        std::string encodedChar = encodeChar(code, prevCode);
        if (!encodedChar.empty()) {
            encoded += encodedChar;
        }
        prevCode = code;
    }
    return encoded;
}

std::string zeroPad(const std::string& s, size_t length) {
    return s + std::string(std::max(int(length) - int(s.length()), 0), '0');
}

std::string generateSoundex(const std::string& name) {
    return zeroPad(getFirstLetter(name) + getEncodedDigits(name), 4);
}
