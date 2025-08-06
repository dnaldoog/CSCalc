/*
  ==============================================================================

    MidiManufacturer.h
    Created: 7 Aug 2025 8:14:13am
    Author:  zan64

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <cstdint>

class MidiManufacturer
{
public:
    // Get manufacturer name from ID
    static juce::String getManufacturerName(uint32_t id);

    // Parse manufacturer ID from SysEx string
    static uint32_t parseManufacturerId(const juce::String& sysexString);

private:
    struct ManufacturerInfo
    {
        uint32_t id;
        const char* name;
    };

    static const ManufacturerInfo manufacturers[];
};