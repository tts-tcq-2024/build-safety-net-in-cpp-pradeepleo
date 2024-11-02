#include <gtest/gtest.h>
#include <string>
#include "Soundex.h" // Assuming the Soundex implementation is in Soundex.h

// Test for an empty string input
TEST(SoundexTest, HandlesEmptyString) {
    EXPECT_EQ(generateSoundex(""), "0000");
}

// Test for a string with a single letter
TEST(SoundexTest, HandlesSingleLetter) {
    EXPECT_EQ(generateSoundex("A"), "A000");
}

// Test for typical names
TEST(SoundexTest, HandlesTypicalNames) {
    EXPECT_EQ(generateSoundex("Robert"), "R163");
    EXPECT_EQ(generateSoundex("Rupert"), "R163");
    EXPECT_EQ(generateSoundex("Ashcraft"), "A261");
}

// Test for the first letter as a number
TEST(SoundexTest, HandlesFirstLetterAsNumber) {
    EXPECT_EQ(generateSoundex("3rd"), "R300");
    EXPECT_EQ(generateSoundex("9th"), "T000");
}

// Test for names with mixed case
TEST(SoundexTest, HandlesMixedCase) {
    EXPECT_EQ(generateSoundex("Jackson"), "J250");
    EXPECT_EQ(generateSoundex("JACKsoN"), "J250");
}

// Test for names with spaces
TEST(SoundexTest, HandlesNamesWithSpaces) {
    EXPECT_EQ(generateSoundex("Da Vinci"), "D152");
    EXPECT_EQ(generateSoundex("Mary Ann"), "M650");
}

// Test for names with hyphens
TEST(SoundexTest, HandlesNamesWithHyphens) {
    EXPECT_EQ(generateSoundex("Smith-Jones"), "S532");
}

// Test for names with silent consonants
TEST(SoundexTest, HandlesSilentConsonants) {
    EXPECT_EQ(generateSoundex("Knight"), "K523");  // Silent "K"
    EXPECT_EQ(generateSoundex("Wright"), "W623");  // Silent "W"
}

// Test for non-phonetic consonants
TEST(SoundexTest, HandlesNonPhoneticConsonants) {
    EXPECT_EQ(generateSoundex("Phone"), "P500");   // 'P' and 'H' combined as 'F'
}

// Test for names with special characters
TEST(SoundexTest, HandlesSpecialCharacters) {
    EXPECT_EQ(generateSoundex("J4ck$on"), "J250");  // Numbers and special characters ignored
}

// Test for names with numbers in non-first position
TEST(SoundexTest, HandlesNumbersAfterFirstLetter) {
    EXPECT_EQ(generateSoundex("J4ckson"), "J250");
    EXPECT_EQ(generateSoundex("M4ry4"), "M600");
}

// Test for names with only special characters or numbers
TEST(SoundexTest, HandlesNamesWithOnlySpecialCharsOrNumbers) {
    EXPECT_EQ(generateSoundex("123"), "0000");  // No valid letters
    EXPECT_EQ(generateSoundex("@#$"), "0000");  // Only special characters
}

// Test for name with a vowel-only name (should pad zeros)
TEST(SoundexTest, HandlesVowelOnlyName) {
    EXPECT_EQ(generateSoundex("Aeia"), "A000");  // No consonants to encode
}

// Test for names with multiple consonants forming combinations (silent consonants and phonetic groupings)
TEST(SoundexTest, HandlesConsonantCombinations) {
    EXPECT_EQ(generateSoundex("Shawn"), "S500");  // 'SH' sounds like S
    EXPECT_EQ(generateSoundex("Pfaff"), "P100");  // 'P' is silent
}

// Test for very long names
TEST(SoundexTest, HandlesLongNames) {
    EXPECT_EQ(generateSoundex("abcdefghijklmnopqrstuvwxyz"), "A123");
}

// Test for zero-padding for names shorter than 4 Soundex characters
TEST(SoundexTest, HandlesZeroPadding) {
    EXPECT_EQ(generateSoundex("Jo"), "J000");
    EXPECT_EQ(generateSoundex("Ray"), "R000");
}
