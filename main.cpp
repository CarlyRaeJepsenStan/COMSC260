#include <assert.h>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using std::cout;
using std::pow;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
/**
 * Description: This function checks if a string represents a binary number by
 * checking if every character is either a 0 or a 1.  It returns true or false.
 *
 * Author name: Aaron Shey
 *
 * Author email: ashey142@dvc.edu
 *
 * Last modified date: Monday, Feb. 5th, 2024
 *
 * Creation date: Sunday, Feb. 4th, 2024
 *
 **/
bool isBinary(string input) {
  for (char c : input) {
    if (c != '0' && c != '1') {
      return false;
      break;
    } else {
      return true;
    }
  }
}

/**
 * Description: This function checks if a string represents a hexadecimal number
 * by comparing each character against a prewritten unordered set of allowed
 * characters.  This allows the hexadecimal number to be case insensitive (id
 * est, ff00ff and FF00FF will both return true.)
 * Author name: Aaron Shey
 *
 * Author email: ashey142@dvc.edu
 *
 * Last modified date: Monday, Feb. 5th, 2024
 *
 * Creation date: Sunday, Feb. 4th, 2024
 **/
bool isHexadecimal(string input, unordered_set<char> allowedHexChar) {
  bool out;
  for (char c : input) {
    if (allowedHexChar.find(c) == allowedHexChar.end()) {
      out = false;
      break;
    } else {
      out = true;
    }
  }
  return out;
}

/**
 * Description: This function converts a 16-bit binary number to a decimal
 * number.  If the number is either not 16 bit or non-binary, -1 is returned.
 * The function works by iterating through the string from right to left
 * (assuming the binary number is little-endian), adding 2 to a power to the
 * final result, then incrementing both the index and power
 *
 * Author email: ashey142@dvc.edu
 *
 * Author name: Aaron Shey
 *
 * Last modified date: Monday, Feb. 5th, 2024
 *
 * Creation date: Sunday, Feb. 4th, 2024
 *
 **/
int convertUnsigned16BitBinarytoDecimal(string input) {
  if (input.size() > 16 || !isBinary(input)) {
    return -1;
  } else {
    int result = 0;
    int power = 0;
    for (int i = input.size() - 1; i >= 0; i--) {
      if (input[i] == '1') {
        result += pow(2, power);
      }
      power++;
    }
    return result;
  }
}

/**
 * Description: This function converts an unsigned 32 bit (8 digit) hexdecimal
 * number into a decimal number.  It works by accepting an unordered set of
 * allowed hexadecimal characters (0-9 and A-F, case insensitive) to ensure the
 * input is hexadecimal, along with an unordered map of each hexadecimal digit
 * to its base-10 equivalent (also case insensitive).  It then loops through
 * each character in the input string, converts it into its base-10 equivalent
 * using a hardcoded unordered map, multiplies it by the appropiate power of 16,
 * and adds it to the result.
 *
 * Author email: ashey142@dvc.edu
 *
 * Author name: Aaron Shey
 *
 * Last modified date: Monday, Feb. 5th, 2024
 *
 * Creation date: Sunday, Feb. 5th, 2024
 *
 **/
int convertUnsigned32BitHexadecimaltoDecimal(
    string input, unordered_set<char> allowedHexChar,
    unordered_map<char, int> hexCharTable) {
  if (input.size() > 8 || !isHexadecimal(input, allowedHexChar)) {
    return -1;
  } else {
    int result = 0;
    int power = 0;
    for (int i = input.size() - 1; i >= 0; i--) {
      result += (hexCharTable[input[i]] * pow(16, power));
      power++;
    }
    return result;
  }
}

/**
 * Description: This function converts an unsigned decimal integer to its binary
 * representation using bit shift operators.  First, it extracts the least
 * significant digit using the right-shift operator >>.  Then, it compares the
 * last digit against two using the binary singular ampersand operator, which is
 * analogous to division modulo two.  Depending on the result, it then appends 1
 * or 0 to the output string using a ternary operator.
 *
 * Author email: ashey142@dvc.edu
 *
 * Author name: Aaron Shey
 *
 * Last modified date: Monday, Feb. 5th, 2024
 *
 * Creation date: Sunday, Feb. 4th, 2024
 *
 **/
string convertUnsignedIntegerto8BitBinary(int input) {
  string result;

  if (input < 0 || input > 255) {
    result = "Error: input was out of bounds";
  } else {
    for (int i = 7; i >= 0; i--) {
      (input >> i) & 1 ? result += "1" : result += "0";
    }
  }
  return result;
}

/**
 * Description: This function converts an unsigned decimal integer to its
 * hexadecimal representation using bit shift operators and a reversed form of
 * the previously used unordered map.  It works by dividing the given integer
 * into nibbles, or sets of 4 bytes, then using the bitwise AND operator against
 * 0xF, which is analogous to divison modulo 15 (0xF).  It then uses the given
 * unordered map to convert the number into its hexadecimal form.  Only capital
 * letters are used.
 *
 * Author email: ashey142@dvc.edu
 *
 * Author name: Aaron Shey
 *
 * Last modified date: Monday, Feb. 5th, 2024
 *
 * Creation date: Sunday, Feb. 4th, 2024
 *
 **/

string convertUnsignedIntegerto32BitHexadecimal(
    int input, unordered_map<int, char> reversedHexCharTable) {
  if (input < 0) {
    return "Error: input was out of bounds";
  } else {
    string result;
    for (int i = 28; i >= 0; i -= 4) {
      result += reversedHexCharTable[((input >> i) & 0xF)];
    }
    return result;
  }
}
int main() {
  unordered_set<char> allowedHexChar = {'A', 'B', 'C', 'D', 'E', 'F', 'a', 'b',
                                        'c', 'd', 'e', 'f', '0', '1', '2', '3',
                                        '4', '5', '6', '7', '8', '9'};

  unordered_map<char, int> hexCharTable = {
      {'0', 0},  {'1', 1},  {'2', 2},  {'3', 3},  {'4', 4},  {'5', 5},
      {'6', 6},  {'7', 7},  {'8', 8},  {'9', 9},  {'A', 10}, {'B', 11},
      {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15}, {'a', 10}, {'b', 11},
      {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15}};

  unordered_map<int, char> reversedHexCharTable = {
      {0, '0'},  {1, '1'},  {2, '2'},  {3, '3'},  {4, '4'},  {5, '5'},
      {6, '6'},  {10, 'a'}, {7, '7'},  {8, '8'},  {9, '9'},  {10, 'A'},
      {11, 'B'}, {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'F'},
  };

  assert(isBinary("10") == true);
  assert(isBinary("20") == false);
  assert(isBinary("02") == true);

  assert(isHexadecimal("1F", allowedHexChar) == true);
  assert(isHexadecimal("1f", allowedHexChar) == true);
  assert(isHexadecimal("1z", allowedHexChar) == false);

  assert(convertUnsigned16BitBinarytoDecimal("100") == 4);
  assert(convertUnsigned16BitBinarytoDecimal("1000000000000000") == 32768);
  assert(convertUnsigned16BitBinarytoDecimal("10000000000000000") == -1);

  assert(convertUnsigned32BitHexadecimaltoDecimal("000000AF", allowedHexChar,
                                                  hexCharTable) == 175);
  assert(convertUnsigned32BitHexadecimaltoDecimal("000000AG", allowedHexChar,
                                                  hexCharTable) == -1);

  assert(convertUnsignedIntegerto8BitBinary(2) == "00000010");
  assert(convertUnsignedIntegerto8BitBinary(255) == "11111111");
  assert(convertUnsignedIntegerto8BitBinary(-1) ==
         "Error: input was out of bounds");

  assert(convertUnsignedIntegerto32BitHexadecimal(255, reversedHexCharTable) ==
         "000000FF");
  assert(convertUnsignedIntegerto32BitHexadecimal(-1, reversedHexCharTable) ==
         "Error: input was out of bounds");

  return 0;
}