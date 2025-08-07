#include <juce_gui_basics/juce_gui_basics.h>

class CustomSliderComponent : public juce::Component
{
public:
    CustomSliderComponent(int initialStartByte, int initialParam2, bool isEndOffset = true)
        : startByteValue(initialStartByte), param2Value(initialParam2)
    {
        // Setup Start Byte slider
        addAndMakeVisible(startByteSlider);
        startByteSlider.setSliderStyle(juce::Slider::IncDecButtons);
        startByteSlider.setRange(0, 999999, 1); // Adjust range as needed
        startByteSlider.setValue(initialStartByte);
        startByteSlider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 80, 24);
        startByteSlider.onValueChange = [this]() {
            startByteValue = (int)startByteSlider.getValue();
            };

        addAndMakeVisible(startByteLabel);
        startByteLabel.setText("Start Byte Index:", juce::dontSendNotification);
        startByteLabel.attachToComponent(&startByteSlider, false);
        startByteLabel.setJustificationType(juce::Justification::left);

        // Setup Param2 slider
        addAndMakeVisible(param2Slider);
        param2Slider.setSliderStyle(juce::Slider::IncDecButtons);
        param2Slider.setRange(0, 999999, 1); // Adjust range as needed
        param2Slider.setValue(initialParam2);
        param2Slider.setTextBoxStyle(juce::Slider::TextBoxLeft, false, 80, 24);
        param2Slider.onValueChange = [this]() {
            param2Value = (int)param2Slider.getValue();
            };

        addAndMakeVisible(param2Label);
        param2Label.setText(isEndOffset ? "End Offset:" : "Message Length:", juce::dontSendNotification);
        param2Label.attachToComponent(&param2Slider, false);
        param2Label.setJustificationType(juce::Justification::left);
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    }

    void resized() override
    {
        auto bounds = getLocalBounds();
        bounds.removeFromTop(10); // Top padding

        // Start byte slider area
        auto startArea = bounds.removeFromTop(50);
        startArea.removeFromTop(20); // Space for label
        startByteSlider.setBounds(startArea.removeFromTop(30));

        bounds.removeFromTop(10); // Spacing between sliders

        // Param2 slider area  
        auto param2Area = bounds.removeFromTop(50);
        param2Area.removeFromTop(20); // Space for label
        param2Slider.setBounds(param2Area.removeFromTop(30));
    }

    // Getter methods to retrieve values
    int getStartByteValue() const { return startByteValue; }
    int getParam2Value() const { return param2Value; }

    // Method to update param2 label if needed
    void setParam2Label(const juce::String& labelText)
    {
        param2Label.setText(labelText, juce::dontSendNotification);
    }

private:
    juce::Slider startByteSlider;
    juce::Label startByteLabel;
    juce::Slider param2Slider;
    juce::Label param2Label;

    int startByteValue;
    int param2Value;
};