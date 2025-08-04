/*
  ==============================================================================

    Calculator.cpp
    Created: 4 Aug 2025 11:16:21am
    Author:  zan64

  ==============================================================================
*/

#include "Calculator.h"
#include <sstream>
#include <algorithm>
#include <cctype>

Calculator::~Calculator()
{
}

ChecksumResult Calculator::calculateChecksum(const std::string& hexString, int startByte, int numBytes)
{
    ChecksumResult result;
    result.checksum = 0;
    result.success = false;
    result.errorMessage = "";

    // Parse the hex string into bytes
    std::vector<int> bytes = parseHexString(hexString);

    if (bytes.empty())
    {
        result.errorMessage = "Invalid hex string format";
        return result;
    }

    // Validate parameters
    if (startByte < 0 || startByte >= static_cast<int>(bytes.size()))
    {
        result.errorMessage = "Start byte index out of range";
        return result;
    }

    if (numBytes <= 0 || (startByte + numBytes) > static_cast<int>(bytes.size()))
    {
        result.errorMessage = "Invalid number of bytes or exceeds string length";
        return result;
    }

    // Calculate checksum (sum of bytes)
    int sum = 0;
    for (int i = startByte; i < startByte + numBytes; ++i)
    {
        sum += bytes[i];
    }

    // Roland-style checksum: take lower 7 bits and compute 2's complement
    result.checksum = (128 - (sum % 128)) % 128;
    result.success = true;

    return result;
}

std::vector<int> Calculator::parseHexString(const std::string& hexString)
{
    std::vector<int> bytes;
    std::string cleanHex = hexString;

    // Remove spaces and convert to lowercase
    cleanHex.erase(std::remove_if(cleanHex.begin(), cleanHex.end(), ::isspace), cleanHex.end());
    std::transform(cleanHex.begin(), cleanHex.end(), cleanHex.begin(), ::tolower);

    // Process pairs of hex characters
    for (size_t i = 0; i < cleanHex.length(); i += 2)
    {
        if (i + 1 >= cleanHex.length())
        {
            // Odd number of characters
            return std::vector<int>(); // Return empty vector to indicate error
        }

        char c1 = cleanHex[i];
        char c2 = cleanHex[i + 1];

        if (!isValidHexChar(c1) || !isValidHexChar(c2))
        {
            return std::vector<int>(); // Return empty vector to indicate error
        }

        int byte = (hexCharToInt(c1) << 4) | hexCharToInt(c2);
        bytes.push_back(byte);
    }

    return bytes;
}

bool Calculator::isValidHexChar(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

int Calculator::hexCharToInt(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return 0;
}