#pragma once

#include <JuceHeader.h>
#include "Calculator.h"

class MainComponent : public juce::Component,
    public juce::Button::Listener
{
public:
    MainComponent();
    ~MainComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;

private:
    void showSysExInputDialog();

    juce::TextButton openDialogButton;
    juce::TextEditor resultDisplay;
    juce::Label resultLabel;
    juce::Label checksumLabel;
    juce::Label checksumValueLabel;

    Calculator calculator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};