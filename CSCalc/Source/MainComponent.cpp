#include "MainComponent.h"

MainComponent::MainComponent()
{
    // Setup the button
    openDialogButton.setButtonText("Enter SysEx Data");
    openDialogButton.addListener(this);
    addAndMakeVisible(openDialogButton);

    // Setup result display
    resultLabel.setText("Calculation Details:", juce::dontSendNotification);
    resultLabel.attachToComponent(&resultDisplay, true);
    addAndMakeVisible(resultLabel);

    resultDisplay.setMultiLine(true);
    resultDisplay.setReadOnly(true);
    resultDisplay.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    resultDisplay.setColour(juce::TextEditor::backgroundColourId, juce::Colour::fromString("ff99ccff"));
    addAndMakeVisible(resultDisplay);

    // Setup checksum display
    checksumLabel.setText("Checksum (Hex):", juce::dontSendNotification);
    checksumLabel.attachToComponent(&checksumValueLabel, true);
    addAndMakeVisible(checksumLabel);

    checksumValueLabel.setText("--", juce::dontSendNotification);
    checksumValueLabel.setFont(juce::Font(24.0f, juce::Font::bold));
    checksumValueLabel.setColour(juce::Label::textColourId, juce::Colours::darkgreen);
    checksumValueLabel.setColour(juce::Label::backgroundColourId, juce::Colours::white);
    checksumValueLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(checksumValueLabel);

    setSize(600, 450);
}
MainComponent::~MainComponent()
{
}
void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("MIDI SysEx Checksum Calculator", getLocalBounds().removeFromTop(50),
        juce::Justification::centred, true);
}

void MainComponent::resized()
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop(60); // Space for title
    bounds.reduce(20, 20);

    openDialogButton.setBounds(bounds.removeFromTop(40));
    bounds.removeFromTop(20); // Spacing

    // Checksum display area
    auto checksumArea = bounds.removeFromTop(60);
    checksumArea.removeFromLeft(150); // Space for label
    checksumValueLabel.setBounds(checksumArea);
    bounds.removeFromTop(10); // Spacing

    // Result details area
    auto resultArea = bounds.removeFromTop(200);
    resultArea.removeFromLeft(150); // Space for label
    resultDisplay.setBounds(resultArea);
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &openDialogButton)
    {
        showSysExInputDialog();
    }
}

void MainComponent::showSysExInputDialog()
{
    // Create a custom AlertWindow with multiple input fields
    auto alertWindow = std::make_unique<juce::AlertWindow>("SysEx Checksum Calculator",
        "Enter the SysEx string and calculation parameters:",
        juce::AlertWindow::NoIcon);

    // Add text editor for SysEx string
    alertWindow->addTextEditor("sysex", "f0 41 10 57 12 03 00 01 10 31 3b f7", "SysEx String (hex bytes):");

    // Add radio buttons for range specification method
    juce::StringArray rangeOptions;
    rangeOptions.add("Start + End (count from end of message)");
    rangeOptions.add("Start + Length (specify number of bytes)");

    alertWindow->addComboBox("rangeType", rangeOptions, "Range Method:");
    alertWindow->getComboBoxComponent("rangeType")->setSelectedItemIndex(0); // Default to start+length

    // Add text editors for range parameters
    alertWindow->addTextEditor("start", "5", "Start Byte Index:");
    alertWindow->addTextEditor("param2", "2", "Length / End Offset:");

    // Add radio buttons for checksum type
    juce::StringArray checksumOptions;
    checksumOptions.add("Additive Checksum (Roland/Yamaha style)");
    checksumOptions.add("XOR Checksum");
    alertWindow->addComboBox("checksumType", checksumOptions, "Checksum Type:");
    alertWindow->getComboBoxComponent("checksumType")->setSelectedItemIndex(0); // Default to additive

    alertWindow->addButton("Calculate", 1, juce::KeyPress(juce::KeyPress::returnKey));
    alertWindow->addButton("Cancel", 0, juce::KeyPress(juce::KeyPress::escapeKey));

    // Show the dialog and handle the result
    int result = alertWindow->runModalLoop();

    if (result == 1) // Calculate button pressed
    {
        juce::String sysexString = alertWindow->getTextEditorContents("sysex");
        juce::String startStr = alertWindow->getTextEditorContents("start");
        juce::String param2Str = alertWindow->getTextEditorContents("param2");
        int rangeType = alertWindow->getComboBoxComponent("rangeType")->getSelectedItemIndex();
        int checksumType = alertWindow->getComboBoxComponent("checksumType")->getSelectedItemIndex();

        int startByte = startStr.getIntValue();
        int param2 = param2Str.getIntValue();

        // Calculate checksum using the Calculator class
        Calculator::ChecksumType type = (checksumType == 0) ? Calculator::ChecksumType::Additive : Calculator::ChecksumType::XOR;
        Calculator::RangeType rangeMethod = (rangeType == 0) ? Calculator::RangeType::StartEnd : Calculator::RangeType::StartLength;

        auto result = calculator.calculateChecksum(sysexString.toStdString(), startByte, param2, type, rangeMethod);

        // Display result
        juce::String checksumTypeName = (checksumType == 0) ? "Additive (Roland/Yamaha)" : "XOR";
        juce::String rangeMethodName = (rangeType == 0) ? "Start + End Offset" : "Start + Length" ;
        juce::String hexChecksum = "0x" + juce::String::toHexString(result.checksum).toUpperCase();
        juce::MemoryBlock hexData;
        hexData.loadFromHexString(sysexString);

        // Create new MemoryBlock and copy the range
        juce::MemoryBlock extractedRange;
        extractedRange.copyFrom(static_cast<const uint8_t*>(hexData.getData()) + startByte, 0, param2);

        // Convert to hex string manually
        juce::String extractedText;
        for (size_t i = 0; i < extractedRange.getSize(); ++i)
        {
            if (i > 0) extractedText += " ";
            extractedText += juce::String::toHexString((int)static_cast<const uint8_t*>(extractedRange.getData())[i]).paddedLeft('0', 2);
        }
        
        // Update detailed results
        juce::String resultText;
        resultText << "SysEx String: " << sysexString << "\n";
        resultText << "Parsed String: " << extractedRange.toHexString(1) << "\n";
        resultText << "Range Method: " << rangeMethodName << "\n";
        resultText << "Start Byte: " << startByte << "\n";
        if (rangeType == 0)
            resultText << "End Offset: " << param2 << " (bytes from end)\n";
        else
            resultText << "Length: " << param2 << "\n";

        resultText << "Bytes Processed: " << result.bytesProcessed << "\n";
        resultText << "Checksum Type: " << checksumTypeName << "\n";
        resultText << "Status: " << (result.success ? "Success" : "Error - " + juce::String(result.errorMessage)) << "\n";

        resultDisplay.setText(resultText);
    }
}
