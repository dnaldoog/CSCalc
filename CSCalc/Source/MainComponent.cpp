#include "MainComponent.h"

//==============================================================================
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

    // Add text editors for start and length
    alertWindow->addTextEditor("start", "5", "Start Byte Index:");
    alertWindow->addTextEditor("length", "5", "Number of Bytes:");

    alertWindow->addButton("Calculate", 1, juce::KeyPress(juce::KeyPress::returnKey));
    alertWindow->addButton("Cancel", 0, juce::KeyPress(juce::KeyPress::escapeKey));

    // Show the dialog and handle the result
    int result = alertWindow->runModalLoop();

    if (result == 1) // Calculate button pressed
    {
        juce::String sysexString = alertWindow->getTextEditorContents("sysex");
        juce::String startStr = alertWindow->getTextEditorContents("start");
        juce::String lengthStr = alertWindow->getTextEditorContents("length");

        int startByte = startStr.getIntValue();
        int numBytes = lengthStr.getIntValue();

        // Calculate checksum using the Calculator class
        auto result = calculator.calculateChecksum(sysexString.toStdString(), startByte, numBytes);

        // Display result
        juce::String resultText;
        resultText << "SysEx String: " << sysexString << "\n";
        resultText << "Start Byte: " << startByte << "\n";
        resultText << "Length: " << numBytes << "\n";
        resultText << "Calculated Checksum: 0x" << juce::String::toHexString(result.checksum).toUpperCase() << "\n";
        resultText << "Status: " << (result.success ? "Success" : "Error - " + juce::String(result.errorMessage)) << "\n";

        resultDisplay.setText(resultText);
    }
}
