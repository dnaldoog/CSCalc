#pragma once

#include <JuceHeader.h>
#include "Calculator.h"
#include "MidiManufacturerDatabase.h"

class MainComponent : public juce::Component, public juce::Button::Listener
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    struct ManufacturerInfo {
        uint32_t id;
        const char* name;
    };

    static const ManufacturerInfo manufacturers[];
    /*juce::String getManufacturerName(uint32_t id);*/
    uint32_t parseManufacturerId(const juce::String& sysexString);
    juce::String MainComponent::getManufacturerName(uint32_t id);
    void showSysExInputDialog();
    void loadSettings();
    void saveSettings();
    void showSettingsDialog();
    void calculateChecksum();
    juce::String insertChecksumAtCorrectPosition(const juce::String& processedString, uint8_t checksum);
    // Keep the original preprocessSysExString method
    juce::String preprocessSysExString(const juce::String& input);
    juce::String correctedSysExString; // Store the corrected string for copying
    //std::unique_ptr<juce::TooltipWindow> tooltipWindow; // Enable tooltips
    std::unique_ptr<juce::TooltipWindow> tooltipWindow; // Enable tooltips
    // UI Components
    juce::TextButton openDialogButton;
    juce::TextButton copyResultButton;
    juce::TextButton clearButton;
    /*************Version 3.0.0 *********************************/
    juce::TextButton settingsButton;
    juce::TextButton calculateButton;
	juce::TextEditor sysexInput;
	juce::Label sysexInputLabel;
    /**********************************************/
    juce::Label resultLabel;
    juce::TextEditor resultDisplay;
    juce::Label checksumLabel;
    juce::Label checksumValueLabel;
    // Calculator
    Calculator calculator;

    // Settings storage
    std::unique_ptr<juce::PropertiesFile> settingsFile;

    // Default values for dialog
    juce::String lastSysExString;
    int lastStartByte;
    int lastParam2;
    int lastRangeType;
    int lastChecksumType;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};