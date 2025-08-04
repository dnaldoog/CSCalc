#pragma once

#include <JuceHeader.h>
#include "Calculator.h"

class MainComponent : public juce::Component, public juce::Button::Listener
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;
    juce::String MainComponent::preprocessSysExString(const juce::String& input);
private:
    void showSysExInputDialog();
    void loadSettings();
    void saveSettings();

    // UI Components
    juce::TextButton openDialogButton;
    juce::TextButton copyResultButton;
    juce::TextButton clearButton;
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