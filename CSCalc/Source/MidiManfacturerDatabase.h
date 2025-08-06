#pragma once
#include <juce_core/juce_core.h>

class MidiManufacturerDatabase
{
public:
    /**
     * @brief Structure to hold manufacturer ID and name.
     */
    struct ManufacturerInfo {
        uint32_t id;
        const char* name;
    };

    /**
     * @brief Gets the manufacturer name for a given ID.
     * @param id The manufacturer ID.
     * @return A juce::String containing the manufacturer's name.
     */
    static juce::String getManufacturerName(uint32_t id);

private:
    // Static constant array to hold the manufacturer data.
    static const ManufacturerInfo manufacturers[];

    // This class is not meant to be instantiated.
    MidiManufacturerDatabase() = delete;
};