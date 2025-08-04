#include "MainComponent.h"

MainComponent::MainComponent()
{
    // Initialize settings
    juce::PropertiesFile::Options options;
    options.applicationName = "SysExCalculator";
    options.filenameSuffix = ".settings";
    options.osxLibrarySubFolder = "Preferences";
    settingsFile.reset(new juce::PropertiesFile(options));

    loadSettings();

    // Setup the button
    openDialogButton.setButtonText("Enter SysEx Data");
    openDialogButton.addListener(this);
    addAndMakeVisible(openDialogButton);

    // Setup copy button
    copyResultButton.setButtonText("Copy Result");
    copyResultButton.addListener(this);
    copyResultButton.setEnabled(false); // Initially disabled
    addAndMakeVisible(copyResultButton);

    // Setup clear button
    clearButton.setButtonText("Clear All");
    clearButton.addListener(this);
    addAndMakeVisible(clearButton);

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
    saveSettings();
}

void MainComponent::loadSettings()
{
    lastSysExString = settingsFile->getValue("sysexString", "f0 41 10 57 12 03 00 01 10 31 3b f7");
    lastStartByte = settingsFile->getIntValue("startByte", 5);
    lastParam2 = settingsFile->getIntValue("param2", 2);
    lastRangeType = settingsFile->getIntValue("rangeType", 0);
    lastChecksumType = settingsFile->getIntValue("checksumType", 0);
}

void MainComponent::saveSettings()
{
    if (settingsFile != nullptr)
    {
        settingsFile->setValue("sysexString", lastSysExString);
        settingsFile->setValue("startByte", lastStartByte);
        settingsFile->setValue("param2", lastParam2);
        settingsFile->setValue("rangeType", lastRangeType);
        settingsFile->setValue("checksumType", lastChecksumType);
        settingsFile->saveIfNeeded();
    }
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

    // Button area - center aligned
    auto buttonArea = bounds.removeFromTop(40);
    int buttonWidth = 130;
    int buttonSpacing = 10;
    int totalButtonWidth = (buttonWidth * 3) + (buttonSpacing * 2);
    int startX = (buttonArea.getWidth() - totalButtonWidth) / 2;

    openDialogButton.setBounds(startX, buttonArea.getY(), buttonWidth, buttonArea.getHeight());
    copyResultButton.setBounds(startX + buttonWidth + buttonSpacing, buttonArea.getY(), buttonWidth, buttonArea.getHeight());
    clearButton.setBounds(startX + (buttonWidth + buttonSpacing) * 2, buttonArea.getY(), buttonWidth, buttonArea.getHeight());

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
    else if (button == &copyResultButton)
    {
        // Copy the result text to clipboard
        juce::String textToCopy = resultDisplay.getText();
        if (textToCopy.isNotEmpty())
        {
            juce::SystemClipboard::copyTextToClipboard(textToCopy);

            // Provide visual feedback by temporarily changing button text
            copyResultButton.setButtonText("Copied!");
            juce::Timer::callAfterDelay(1500, [this]() {
                copyResultButton.setButtonText("Copy Result");
                });
        }
    }
    else if (button == &clearButton)
    {
        // Reset all stored values to defaults
        lastSysExString = "";
        lastStartByte = 0;
        lastParam2 = 0;
        lastRangeType = 0;
        lastChecksumType = 0;

        // Clear the UI displays
        resultDisplay.setText("");
        checksumValueLabel.setText("--", juce::dontSendNotification);

        // Disable copy button since there are no results
        copyResultButton.setEnabled(false);

        // Provide visual feedback
        clearButton.setButtonText("Cleared!");
        juce::Timer::callAfterDelay(1000, [this]() {
            clearButton.setButtonText("Clear All");
            });
    }
}

void MainComponent::showSysExInputDialog()
{
    // Create a custom AlertWindow with multiple input fields
    auto alertWindow = std::make_unique<juce::AlertWindow>("SysEx Checksum Calculator",
        "Enter the SysEx string and calculation parameters:",
        juce::AlertWindow::NoIcon);

    // Add text editor for SysEx string - use saved value
    alertWindow->addTextEditor("sysex", lastSysExString, "SysEx String (hex bytes):");

    // Add radio buttons for range specification method
    juce::StringArray rangeOptions;
    rangeOptions.add("Start + End (count from end of message)");
    rangeOptions.add("Start + Length (specify number of bytes)");

    alertWindow->addComboBox("rangeType", rangeOptions, "Range Method:");
    alertWindow->getComboBoxComponent("rangeType")->setSelectedItemIndex(lastRangeType);

    // Add text editors for range parameters - use saved values
    alertWindow->addTextEditor("start", juce::String(lastStartByte), "Start Byte Index:");
    alertWindow->addTextEditor("param2", juce::String(lastParam2), "Length / End Offset:");

    // Add radio buttons for checksum type
    juce::StringArray checksumOptions;
    checksumOptions.add("Additive Checksum (Roland/Yamaha style)");
    checksumOptions.add("XOR Checksum");
    alertWindow->addComboBox("checksumType", checksumOptions, "Checksum Type:");
    alertWindow->getComboBoxComponent("checksumType")->setSelectedItemIndex(lastChecksumType);

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

        // Save the current values for next time
        lastSysExString = sysexString;
        lastStartByte = startStr.getIntValue();
        lastParam2 = param2Str.getIntValue();
        lastRangeType = rangeType;
        lastChecksumType = checksumType;

        int startByte = startStr.getIntValue();
        int param2 = param2Str.getIntValue();

        // Calculate checksum using the Calculator class
        Calculator::ChecksumType type = (checksumType == 0) ? Calculator::ChecksumType::Additive : Calculator::ChecksumType::XOR;
        Calculator::RangeType rangeMethod = (rangeType == 0) ? Calculator::RangeType::StartEnd : Calculator::RangeType::StartLength;

        auto calcResult = calculator.calculateChecksum(sysexString.toStdString(), startByte, param2, type, rangeMethod);

        // Display result
        juce::String checksumTypeName = (checksumType == 0) ? "Additive (Roland/Yamaha)" : "XOR";
        juce::String rangeMethodName = (rangeType == 0) ? "Start + End Offset" : "Start + Length";
        juce::String hexChecksum = "0x" + juce::String::toHexString(calcResult.checksum).toUpperCase();
        juce::String intChecksum = juce::String(calcResult.checksum);
        checksumValueLabel.setText(hexChecksum, juce::dontSendNotification);

        juce::MemoryBlock hexData;
        hexData.loadFromHexString(sysexString);

        DBG("Original hex data size: " << hexData.getSize());
        DBG("Start byte: " << startByte << ", Length/End Offset: " << param2);

        // Calculate the actual length based on range type
        int actualLength;
        if (rangeType == 0) // Start + End Offset
        {
            actualLength = hexData.getSize() - startByte - param2;
        }
        else // Start + Length
        {
            actualLength = param2;
        }

        DBG("Calculated actual length: " << actualLength);

        // Direct memory copy approach
        juce::MemoryBlock xr;
        xr.setSize(actualLength);
        memcpy(xr.getData(), static_cast<const uint8_t*>(hexData.getData()) + startByte, actualLength);

        // Convert to hex string with spaces
        juce::String parsedString;
        for (size_t i = 0; i < xr.getSize(); ++i)
        {
            if (i > 0) parsedString += " ";
            parsedString += juce::String::toHexString((int)static_cast<const uint8_t*>(xr.getData())[i]).paddedLeft('0', 2);
        }

        DBG("Extracted data size: " << xr.getSize());
        DBG("Parsed string: " << parsedString);

        juce::String resultText;
        resultText << "SysEx String: " << sysexString << "\n";
        resultText << "Parsed String: " << parsedString << "\n";
        resultText << "Range Method: " << rangeMethodName << "\n";
        resultText << "Start Byte: " << startByte << "\n";
        if (rangeType == 0)
            resultText << "End Offset: " << param2 << " (bytes from end)\n";
        else
            resultText << "Length: " << param2 << "\n";

        resultText << "Bytes Processed: " << calcResult.bytesProcessed << "\n";
        resultText << "Checksum Type: " << checksumTypeName << "\n";
        resultText << "Checksum: " << hexChecksum << " : [" << intChecksum << "]\n";

        resultDisplay.setText(resultText);

        // Enable the copy button now that we have results
        copyResultButton.setEnabled(true);
    }
}