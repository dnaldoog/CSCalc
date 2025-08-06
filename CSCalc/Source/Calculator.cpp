//==============================================================================
// Calculator.cpp
#include "Calculator.h"
#include <sstream>
#include <algorithm>
#include <cctype>

Calculator::Calculator()
{
    // Constructor - nothing specific to initialize for this class
}

Calculator::~Calculator()
{
    // Destructor - nothing specific to clean up
}

ChecksumResult Calculator::calculateChecksum(const std::string& hexString, int startByte, int param2,
    ChecksumType checksumType, RangeType rangeType)
{
    ChecksumResult result;
    result.checksum = 0;
    result.success = false;
    result.errorMessage = "";
    result.bytesProcessed = 0;

    // Parse the hex string into bytes
    std::vector<int> bytes = parseHexString(hexString);

    if (bytes.empty())
    {
        result.errorMessage = "Invalid hex string format";
        return result;
    }

    // Calculate the actual number of bytes to process based on range type
    int numBytes = 0;
    if (rangeType == RangeType::StartLength)
    {
        numBytes = param2; // param2 is the length
    }
    else // RangeType::StartEnd
    {
        // param2 is offset from end - calculate length
        int endIndex = static_cast<int>(bytes.size()) - param2;
        numBytes = endIndex - startByte;
    }

    // Validate parameters
    if (startByte < 0 || startByte >= static_cast<int>(bytes.size()))
    {
        result.errorMessage = "Start byte index out of range";
        return result;
    }

    if (numBytes <= 0)
    {
        if (rangeType == RangeType::StartEnd)
            result.errorMessage = "End offset results in invalid range (check start byte and end offset)";
        else
            result.errorMessage = "Invalid number of bytes";
        return result;
    }

    if ((startByte + numBytes) > static_cast<int>(bytes.size()))
    {
        result.errorMessage = "Range exceeds string length";
        return result;
    }

    result.bytesProcessed = numBytes;

    // Calculate checksum based on type
    if (checksumType == ChecksumType::Additive)
    {
        // Roland-style additive checksum
        int sum = 0;
        for (int i = startByte; i < startByte + numBytes; ++i)
        {
            sum += bytes[i];
        }
        // Roland-style checksum: take lower 7 bits and compute 2's complement
		sum = ~sum & 0x7f; // Keep only lower 7 bits
        result.checksum = ++sum;
        //result.checksum = (128 - (sum % 128)) % 128;
    }
    else if (checksumType == ChecksumType::XOR)
    {
        // XOR checksum
        int xorResult = 0;
        for (int i = startByte; i < startByte + numBytes; ++i)
        {
            xorResult ^= bytes[i];
        }
        result.checksum = xorResult;
    }
    else if (checksumType == ChecksumType::OnesComplement)
    {
        
        int o = 0;
        for (int i = startByte; i < startByte + numBytes; ++i)
        {
            o += bytes[i];
        }
        result.checksum = ~o &0x7f;
    }

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