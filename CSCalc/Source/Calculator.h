#pragma once

#include <string>
#include <vector>

struct ChecksumResult
{
    int checksum;
    bool success;
    std::string errorMessage;
    int bytesProcessed; // Number of bytes actually processed
};
class Calculator
{
public:
    enum class ChecksumType
    {
        Additive,
        XOR,
		OnesComplement  // One's complement checksum
    };

    enum class RangeType
    {
        StartLength,  // Start byte + number of bytes
        StartEnd      // Start byte + offset from end
    };

    Calculator();
    ~Calculator();

    // Calculate checksum for a hex string starting at startByte for numBytes
    ChecksumResult calculateChecksum(const std::string& hexString, int startByte, int param2,
        ChecksumType checksumType = ChecksumType::Additive,
        RangeType rangeType = RangeType::StartLength);

private:
    // Helper function to parse hex string into bytes
    std::vector<int> parseHexString(const std::string& hexString);

    // Helper function to validate hex character
    bool isValidHexChar(char c);

    // Convert hex character to integer
    int hexCharToInt(char c);
};
