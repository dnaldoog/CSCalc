/*
  ==============================================================================

    CustomSliderComponent.h
    Created: 7 Aug 2025 7:04:02pm
    Author:  zan64

  ==============================================================================
*/
#pragma once
#include <juce_gui_basics/juce_gui_basics.h>

class CustomSliderComponent : public juce::Component
{
public:
    CustomSliderComponent(int initialStartByte, int initialParam2, bool isEndOffset = true);

    void paint(juce::Graphics& g) override;
    void resized() override;

    int getStartByteValue() const;
    int getParam2Value() const;
    void setParam2Label(const juce::String& labelText);

private:
    juce::Slider startByteSlider;
    juce::Label startByteLabel;
    juce::Slider param2Slider;
    juce::Label param2Label;

    int startByteValue;
    int param2Value;
};

