/*
  ==============================================================================

    Calculator.h
    Created: 4 Aug 2025 11:16:21am
    Author:  zan64

  ==============================================================================
*/

#pragma once

#include <string>
#include <vector>

struct ChecksumResult
{
    int checksum;
    bool success;
    std::string errorMessage;
};

class Calculator
{
public:
    Calculator();
    ~Calculator();

    // Calculate checksum for a hex string starting at startByte for numBytes
    ChecksumResult calculateChecksum(const std::string& hexString, int startByte, int numBytes);

private:
    // Helper function to parse hex string into bytes
    std::vector<int> parseHexString(const std::string& hexString);

    // Helper function to validate hex character
    bool isValidHexChar(char c);

    // Convert hex character to integer
    int hexCharToInt(char c);
};