#include "Soundex.h"
#include <cctype>
#include <unordered_map>

using namespace std;

class SoundexCodeMap {
private:
    unordered_map<char, char> codeMap;

public:
    SoundexCodeMap() {
        const char* codes[] = {"BFPV", "CGJKQSXZ", "DT", "L", "MN", "R"};
        for (int i = 0; i < 6; ++i) {
            for (const char* code = codes[i]; *code; ++code) {
                codeMap[*code] = '1' + i;
            }
        }
    }

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

std::string getEncodedDigits(const std::string& name) {
    std::string encoded;
    char prevCode = '0';
    for (size_t i = 1; i < name.length() && encoded.length() < 3; ++i) {
        char code = getSoundexCode(name[i]);
        if (code != '0' && code != prevCode) {
            encoded += code;
            prevCode = code;
        }
    }
    return encoded;
}

std::string zeroPad(const std::string& s, size_t length) {
    return s + std::string(std::max(int(length) - int(s.length()), 0), '0');
}

std::string generateSoundex(const std::string& name) {
    return zeroPad(getFirstLetter(name) + getEncodedDigits(name), 4);
}
