#include <string>
#include <cctype>
#include <unordered_map>
#include <algorithm>

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

// Instantiate the SoundexCodeMap
const SoundexCodeMap soundexMap;

// Function to get the Soundex code for a character
char getSoundexCode(char c) {
    return soundexMap.getCode(c);
}

// Function to get the first letter in UPPERCASE
std::string getFirstLetter(const std::string& name) {
    return name.empty() ? "" : std::string(1, std::toupper(name[0]));
}

// Helper function to process and add encoded character
void processAndAdd(char code, char& prevCode, std::string& encoded) {
    if (code != '0' && code != prevCode) {
        encoded += code;
        prevCode = code;
    }
}

// function to get encoded digits
std::string getEncodedDigits(const std::string& name) {
    std::string encoded;
    char prevCode = '0';

    for (size_t i = 1; i < name.length(); ++i) {
        if (encoded.length() >= 3) {
            break; // Exit early if we already have 3 encoded digits
        }
        char code = getSoundexCode(name[i]);
        processAndAdd(code, prevCode, encoded);
    }

    return encoded;
}

// Function to zero-pad a string to required length
std::string zeroPad(const std::string& s, size_t length) {
    size_t zerosToAdd = length > s.length() ? length - s.length() : 0;
    return s + std::string(zerosToAdd, '0');
}

std::string FindFirstLetter(std::string name) {
    while(isdigit(name[0])){
        name = name.substr(1);
    }
    return name.empty()?"":name;
    
}

// Function to generate the full Soundex code for a name
std::string generateSoundex(std::string name) {
    if (name.empty()) {
        return "";  // Handle empty string input by returning "0000"
    }

    name = FindFirstLetter(name);
    if(name.empty()){
        return "";
    }
    std::string firstLetter = getFirstLetter(name);
    std::string encodedDigits = getEncodedDigits(name);
    return zeroPad(firstLetter + encodedDigits, 4);

}
