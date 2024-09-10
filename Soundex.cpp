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
string generateSoundex(const string& name) {
    if (name.empty()) return "";

    string soundex(1, toupper(name[0]));
    char prevCode = getSoundexCode(name[0]);

    for (size_t i = 1; i < name.length() && soundex.length() < 4; ++i) {
        char code = getSoundexCode(name[i]);
        if (code != '0' && code != prevCode) {
            soundex += code;
            prevCode = code;
        }
    }

    while (soundex.length() < 4) {
        soundex += '0';
    }

    return soundex;
}
