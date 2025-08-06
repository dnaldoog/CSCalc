#pragma once

#include <cstdint>
#include <string>
#include <map>

// Example database for MIDI manufacturer IDs
class MidiManufacturerDatabase
{
public:
    static std::string getManufacturerName(uint32_t id)
    {
        static const std::map<uint32_t, std::string> manufacturers = {
            {0x41, "Roland"},
            {0x43, "Yamaha"},
            {0x44, "Casio"},
            {0x7D, "Non-commercial"},
            // Add more manufacturer IDs as needed
        };

        auto it = manufacturers.find(id);
        if (it != manufacturers.end())
            return it->second;
        return "Unknown";
    }
};
