#pragma once

#include <JuceHeader.h>
#include "Calculator.h"
#include "MidiManufacturer.h"
#include "CustomSliderComponent.h"

class MainComponent : public juce::Component,
    private juce::Button::Listener
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void buttonClicked(juce::Button* button) override;
    void showSettingsDialog();
    void calculateChecksum();

    // Helper methods
    juce::String preprocessSysExString(const juce::String& input);
    juce::String insertChecksumAtCorrectPosition(const juce::String& processedString, uint8_t checksum);

    // Settings management
    void loadSettings();
    void saveSettings();

    // UI Components
    juce::TextButton settingsButton;
    juce::TextButton calculateButton;
    juce::TextButton copyResultButton;
    juce::TextButton clearButton;

    juce::Label sysexInputLabel;
    juce::TextEditor sysexInput;

    juce::Label resultLabel;
    juce::TextEditor resultDisplay;

    juce::Label checksumLabel;
    juce::Label checksumValueLabel;
    juce::Label versionLabel;

    // Calculator and settings
    Calculator calculator;
    std::unique_ptr<juce::PropertiesFile> settingsFile;
    std::unique_ptr<juce::TooltipWindow> tooltipWindow;

    // Stored settings
    juce::String lastSysExString;
    int lastStartByte = 5;
    int lastParam2 = 2;
    int lastRangeType = 0;
    int lastChecksumType = 0;
    // Store the corrected SysEx string for copying
    juce::String correctedSysExString;

    std::unique_ptr<juce::MidiOutput> midiOutput;
    juce::String selectedMidiOutputDevice;
    juce::TextButton sendMidiButton;

    // MIDI methods
    void showMidiSettingsDialog();
    void sendSysExMessage();
    juce::MidiMessage createSysExFromString(const juce::String& hexString);

    // Settings keys for MIDI
    void loadMidiSettings();
    void saveMidiSettings();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};