#pragma once
#include <string>
#include <vector>
#include <cstdint>

class Calculator
{
public:
    enum class ChecksumType
    {
        Additive,
        XOR,
        OnesComplement,  // One's complement checksum
        SimpleSumming,
        Sony,
        KawaiK5  // Kawai K5 checksum
    };

    enum class RangeType
    {
        StartLength,  // Start byte + number of bytes
        StartEnd      // Start byte + offset from end
    };

    struct ChecksumResult
    {
        uint8_t checksum;           // For 8-bit checksums
        uint16_t checksum16;        // For 16-bit checksums (Kawai K5)
        int bytesProcessed;
        bool is16Bit;               // Flag to indicate if this is a 16-bit checksum
        bool success;               // Keep this from your original
        std::string errorMessage;   // Keep this from your original

        ChecksumResult() : checksum(0), checksum16(0), bytesProcessed(0), is16Bit(false), success(false) {}
    };

    Calculator();
    ~Calculator();

    // Calculate checksum for a hex string starting at startByte for param2
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