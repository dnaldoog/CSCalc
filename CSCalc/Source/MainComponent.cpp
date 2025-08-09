#include "MainComponent.h"

MainComponent::MainComponent()
{
    // Initialize settings
    juce::PropertiesFile::Options options;
    options.applicationName = "SysExCalculator";
    options.filenameSuffix = ".settings";
    options.osxLibrarySubFolder = "Preferences";
    settingsFile.reset(new juce::PropertiesFile(options));
    tooltipWindow.reset(new juce::TooltipWindow(this, 700));
    loadSettings();

    // Setup the buttons
    settingsButton.setButtonText("Settings");
    settingsButton.addListener(this);
    addAndMakeVisible(settingsButton);

    calculateButton.setButtonText("Calculate");
    calculateButton.addListener(this);
    addAndMakeVisible(calculateButton);

    copyResultButton.setButtonText("Copy Result");
    copyResultButton.addListener(this);
    copyResultButton.setEnabled(false);
    copyResultButton.setTooltip("Click to copy full result\nCtrl+Click to copy SysEx only");
    addAndMakeVisible(copyResultButton);

    clearButton.setButtonText("Clear All");
    clearButton.addListener(this);
    addAndMakeVisible(clearButton);

    // Setup SysEx input
    sysexInputLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    sysexInputLabel.setText("SysEx Data (hex bytes):", juce::dontSendNotification);
    sysexInputLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(sysexInputLabel);

    sysexInput.setMultiLine(true);
    sysexInput.setReturnKeyStartsNewLine(false);
    sysexInput.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    sysexInput.setColour(juce::TextEditor::backgroundColourId, juce::Colour::fromString("fff0f8ff"));
    sysexInput.setText(lastSysExString);
    sysexInput.setTextToShowWhenEmpty("Enter SysEx data here (e.g., F0 41 10 42 xx xx F7)", juce::Colours::grey);
    addAndMakeVisible(sysexInput);

    // Setup result display
	resultLabel.setColour(juce::Label::textColourId,juce::Colours::black);
    resultLabel.setText("Calculation Results:", juce::dontSendNotification);
    resultLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(resultLabel);

    resultDisplay.setMultiLine(true);
    resultDisplay.setReadOnly(true);
    resultDisplay.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    resultDisplay.setColour(juce::TextEditor::backgroundColourId, juce::Colour::fromString("ff99ccff"));
    addAndMakeVisible(resultDisplay);

    // Setup checksum display

    checksumLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    checksumLabel.setText("Checksum (Hex):", juce::dontSendNotification);
    checksumLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(checksumLabel);

    checksumValueLabel.setText("--", juce::dontSendNotification);
    checksumValueLabel.setFont(juce::Font(24.0f, juce::Font::bold));
    checksumValueLabel.setColour(juce::Label::textColourId, juce::Colours::darkgreen);
    checksumValueLabel.setColour(juce::Label::backgroundColourId, juce::Colours::white);
    checksumValueLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(checksumValueLabel);

    DBG("Actual window size: " + juce::String(getWidth()) + " x " + juce::String(getHeight()));
    centreWithSize(650, 700); // Alternative that might work better
}

MainComponent::~MainComponent()
{
    saveSettings();
}


void MainComponent::loadSettings()
{
    lastSysExString = settingsFile->getValue("sysexString", "");
    lastStartByte = settingsFile->getIntValue("startByte", 5);
    lastParam2 = settingsFile->getIntValue("param2", 2);
    lastRangeType = settingsFile->getIntValue("rangeType", 0);
    lastChecksumType = settingsFile->getIntValue("checksumType", 0);
}

void MainComponent::saveSettings()
{
    if (settingsFile != nullptr)
    {
        settingsFile->setValue("sysexString", sysexInput.getText());
        settingsFile->setValue("startByte", lastStartByte);
        settingsFile->setValue("param2", lastParam2);
        settingsFile->setValue("rangeType", lastRangeType);
        settingsFile->setValue("checksumType", lastChecksumType);
        settingsFile->saveIfNeeded();
    }
}

juce::String MainComponent::insertChecksumAtCorrectPosition(const juce::String& processedString, uint8_t checksum)
{
    juce::StringArray tokens;
    tokens.addTokens(processedString, " ", "");

    if (tokens.size() < 2)
        return processedString;

    // Find the last F7 (EOX) byte
    int eoxPosition = -1;
    for (int i = tokens.size() - 1; i >= 0; --i)
    {
        if (tokens[i].toLowerCase() == "f7")
        {
            eoxPosition = i;
            break;
        }
    }

    // If we found F7, the checksum goes in the position before it
    int checksumPosition = -1;
    if (eoxPosition > 0)
    {
        checksumPosition = eoxPosition - 1;
    }

    // Build the result string
    juce::String result;
    for (int i = 0; i < tokens.size(); ++i)
    {
        if (i > 0) result += " ";

        // If this is the checksum position, insert the calculated checksum
        if (i == checksumPosition)
        {
            result += juce::String::toHexString((int)checksum).paddedLeft('0', 2).toLowerCase();
        }
        else
        {
            result += tokens[i];
        }
    }

    return result;
}

juce::String MainComponent::preprocessSysExString(const juce::String& input)
{
    juce::StringArray tokens;
    tokens.addTokens(input, " ", "");

    juce::String processed;

    for (int i = 0; i < tokens.size(); ++i)
    {
        if (i > 0) processed += " ";

        juce::String token = tokens[i].trim().toLowerCase();

        // Check if token is valid hex (1-2 characters, only 0-9, a-f)
        bool isValidHex = true;
        if (token.length() == 0 || token.length() > 2)
        {
            isValidHex = false;
        }
        else
        {
            for (int j = 0; j < token.length(); ++j)
            {
                char c = token[j];
                if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')))
                {
                    isValidHex = false;
                    break;
                }
            }
        }

        if (isValidHex)
        {
            // Valid hex token - pad to 2 characters if needed
            processed += token.paddedLeft('0', 2);
        }
        else
        {
            // Non-hex token (like xx, e14, etc.) - replace with 00
            processed += "00";
        }
    }

    return processed;
}

void MainComponent::paint(juce::Graphics& g)
{
    //g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::lightgrey);  // Or lightgrey, aliceblue, etc.
    g.setColour(juce::Colours::darkgrey);
    g.setFont(26.0f);
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
    int buttonWidth = 110;
    int buttonSpacing = 10;
    int totalButtonWidth = (buttonWidth * 4) + (buttonSpacing * 3);
    int startX = (buttonArea.getWidth() - totalButtonWidth) / 2;

    settingsButton.setBounds(startX, buttonArea.getY(), buttonWidth, buttonArea.getHeight());
    calculateButton.setBounds(startX + buttonWidth + buttonSpacing, buttonArea.getY(), buttonWidth, buttonArea.getHeight());
    copyResultButton.setBounds(startX + (buttonWidth + buttonSpacing) * 2, buttonArea.getY(), buttonWidth, buttonArea.getHeight());
    clearButton.setBounds(startX + (buttonWidth + buttonSpacing) * 3, buttonArea.getY(), buttonWidth, buttonArea.getHeight());

    bounds.removeFromTop(20); // Spacing

    // SysEx input area
    auto sysexArea = bounds.removeFromTop(100);
    int sysexInputWidth = 400;
    int sysexStartX = (sysexArea.getWidth() - sysexInputWidth) / 2;

    sysexInputLabel.setBounds(sysexStartX, sysexArea.getY(), sysexInputWidth, 20);
    sysexInput.setBounds(sysexStartX, sysexArea.getY() + 25, sysexInputWidth, 70);

    bounds.removeFromTop(20); // Spacing

    // Checksum display area - center aligned
    auto checksumArea = bounds.removeFromTop(80);
    int checksumValueWidth = 200;
    int checksumStartX = (checksumArea.getWidth() - checksumValueWidth) / 2;

    checksumLabel.setBounds(checksumStartX, checksumArea.getY(), checksumValueWidth, 20);
    checksumValueLabel.setBounds(checksumStartX, checksumArea.getY() + 25, checksumValueWidth, 50);

    bounds.removeFromTop(10); // Spacing

    // Result details area - center aligned
    auto resultArea = bounds;
    int resultDisplayWidth = 400;
    int resultStartX = (resultArea.getWidth() - resultDisplayWidth) / 2;

    resultLabel.setBounds(resultStartX, resultArea.getY(), resultDisplayWidth, 20);
    resultDisplay.setBounds(resultStartX, resultArea.getY() + 25, resultDisplayWidth, resultArea.getHeight() - 15);
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &settingsButton)
    {
        showSettingsDialog();
    }
    else if (button == &calculateButton)
    {
        calculateChecksum();
    }
    else if (button == &copyResultButton)
    {
        // Check if Ctrl key is held down
        bool ctrlPressed = juce::ModifierKeys::getCurrentModifiers().isCtrlDown();

        if (ctrlPressed && correctedSysExString.isNotEmpty())
        {
            // Ctrl+Click: Copy only the corrected SysEx string
            juce::SystemClipboard::copyTextToClipboard(correctedSysExString);

            // Provide visual feedback
            copyResultButton.setButtonText("SysEx Copied!");
            juce::Timer::callAfterDelay(1500, [this]() {
                copyResultButton.setButtonText("Copy Result");
                });
        }
        else
        {
            // Normal click: Copy the full result text
            juce::String textToCopy = resultDisplay.getText();
            if (textToCopy.isNotEmpty())
            {
                juce::SystemClipboard::copyTextToClipboard(textToCopy);

                // Provide visual feedback
                copyResultButton.setButtonText("Copied!");
                juce::Timer::callAfterDelay(1500, [this]() {
                    copyResultButton.setButtonText("Copy Result");
                    });
            }
        }
    }
    else if (button == &clearButton)
    {
        // Reset all stored values to defaults
        lastSysExString = "";
        lastStartByte = 5;
        lastParam2 = 2;
        lastRangeType = 0;
        lastChecksumType = 0;
        correctedSysExString = "";

        // Clear the UI displays
        sysexInput.setText("");
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

void MainComponent::showSettingsDialog()
{
    juce::AlertWindow alert("Calculation Settings",
        "Set the checksum calculation parameters:",
        juce::AlertWindow::NoIcon);

    // Create custom component with initial values
    auto* sliderComponent = new CustomSliderComponent(lastStartByte, lastParam2, lastRangeType == 0);
    sliderComponent->setSize(300, 120);
    alert.addCustomComponent(sliderComponent);

    // Add combo box for range specification method
    juce::StringArray rangeOptions;
    rangeOptions.add("Start + End (count from end of message)");
    rangeOptions.add("Start + Length (specify number of bytes)");
    alert.addComboBox("rangeType", rangeOptions, "Range Method:");
    alert.getComboBoxComponent("rangeType")->setSelectedItemIndex(lastRangeType);

    // Add combo box for checksum type
    juce::StringArray checksumOptions;
    checksumOptions.add("Additive Checksum (Roland/Yamaha style)");
    checksumOptions.add("XOR Checksum");
    checksumOptions.add("1's Complement - E-mu,Korg etc");
    checksumOptions.add("Simple Sum + mask");
    checksumOptions.add("SONY MSB");
    //checksumOptions.add("Kawai K5");
    alert.addComboBox("checksumType", checksumOptions, "Checksum Type:");
    alert.getComboBoxComponent("checksumType")->setSelectedItemIndex(lastChecksumType);

    alert.addButton("OK", 1, juce::KeyPress(juce::KeyPress::returnKey));
    alert.addButton("Cancel", 0, juce::KeyPress(juce::KeyPress::escapeKey));

    int result = alert.runModalLoop();

    if (result == 1) // OK button pressed
    {
        // Get values from the custom slider component
        int newStartByte = sliderComponent->getStartByteValue();
        int newParam2 = sliderComponent->getParam2Value();

        // Get values from combo boxes
        int rangeType = alert.getComboBoxComponent("rangeType")->getSelectedItemIndex();
        int checksumType = alert.getComboBoxComponent("checksumType")->getSelectedItemIndex();

        // Save the settings
        lastStartByte = newStartByte;
        lastParam2 = newParam2;
        lastRangeType = rangeType;
        lastChecksumType = checksumType;

        // Update the slider component's param2 label if range type changed
        if (rangeType != lastRangeType)
        {
            sliderComponent->setParam2Label(rangeType == 0 ? "End Offset:" : "Message Length:");
        }

        // Provide visual feedback
        settingsButton.setButtonText("Saved!");
        juce::Timer::callAfterDelay(1000, [this]() {
            settingsButton.setButtonText("Settings");
            });
    }
}

void MainComponent::calculateChecksum()
{
    juce::String sysexString = sysexInput.getText();

    if (sysexString.trim().isEmpty())
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
            "Input Required", "Please enter SysEx data before calculating.");
        return;
    }

    // Save the current SysEx string
    lastSysExString = sysexString;

    // Preprocess the SysEx string to handle tokens (convert non-hex to 00)
    juce::String processedSysExString = preprocessSysExString(sysexString);

    // Calculate checksum using the Calculator class
    Calculator::ChecksumType type;
    if (lastChecksumType == 0)
        type = Calculator::ChecksumType::Additive;
    else if (lastChecksumType == 1)
        type = Calculator::ChecksumType::XOR;
    else if (lastChecksumType == 2)
        type = Calculator::ChecksumType::OnesComplement;
    else if (lastChecksumType == 3)
        type = Calculator::ChecksumType::SimpleSumming;
    else if (lastChecksumType == 4)
        type = Calculator::ChecksumType::Sony;
    else
        type = Calculator::ChecksumType::KawaiK5;

    Calculator::RangeType rangeMethod = (lastRangeType == 0) ?
    Calculator::RangeType::StartEnd : Calculator::RangeType::StartLength;

    auto calcResult = calculator.calculateChecksum(processedSysExString.toStdString(),
        lastStartByte, lastParam2, type, rangeMethod);

    correctedSysExString = insertChecksumAtCorrectPosition(processedSysExString, calcResult.checksum);

    // Display result
    juce::String checksumTypeName;
    if (lastChecksumType == 0)
        checksumTypeName = "Additive (Roland/Yamaha)";
    else if (lastChecksumType == 1)
        checksumTypeName = "XOR";
    else if (lastChecksumType == 2)
        checksumTypeName = "One's Complement";
    else  if (lastChecksumType == 3)
        checksumTypeName = "Simple Sum AND 0x7F";
	else if (lastChecksumType == 4)
        checksumTypeName = "SONY MSB";
	else if (lastChecksumType == 5)
        checksumTypeName = "Kawai K5";
    else
		checksumTypeName = "Unknown";

    juce::String rangeMethodName = (lastRangeType == 0) ? "Start + End Offset" : "Start + Length";
    juce::String hexChecksum = "0x" + juce::String::toHexString(calcResult.checksum).toUpperCase();
    juce::String intChecksum = juce::String(calcResult.checksum);
    checksumValueLabel.setText(hexChecksum, juce::dontSendNotification);

    juce::MemoryBlock hexData;
    juce::MemoryBlock dataCalc;
    hexData.loadFromHexString(processedSysExString);

    int actualLength;
    if (lastRangeType == 0) // Start + End Offset
    {
        actualLength = hexData.getSize() - lastStartByte - lastParam2;
    }
    else // Start + Length
    {
        actualLength = lastParam2;
    }
    juce::String parsedDataHex;
    if (hexData.getSize() > 0 && lastStartByte >= 0 && actualLength > 0 &&
        (lastStartByte + actualLength) <= static_cast<int>(hexData.getSize()))
    {
        const uint8_t* data = static_cast<const uint8_t*>(hexData.getData());
        for (int i = 0; i < actualLength; ++i)
        {
            if (i > 0) parsedDataHex += " ";
            parsedDataHex += juce::String::toHexString(data[lastStartByte + i]).paddedLeft('0', 2).toUpperCase();
        }
    }
    else
    {
        parsedDataHex = "(Invalid range or no data)";
    }


    uint32_t id = MidiManufacturer::parseManufacturerId(sysexString);

    juce::String resultText;
    resultText << "Manufacturer: " << MidiManufacturer::getManufacturerName(id) << "\n";
    resultText << "Original SysEx: " << sysexString << "\n";
    resultText << "Corrected SysEx: " << correctedSysExString << "\n";
    resultText << "Parsed Data: " << parsedDataHex << "\n";
    resultText << "Range Method: " << rangeMethodName << "\n";
    resultText << "Start Byte: " << lastStartByte << "\n";
    if (lastRangeType == 0)
        resultText << "End Offset: " << lastParam2 << " (bytes from end)\n";
    else
        resultText << "Length: " << lastParam2 << "\n";

    resultText << "Bytes Processed: " << calcResult.bytesProcessed << "\n";
    resultText << "Checksum Type: " << checksumTypeName << "\n";
    resultText << "Checksum: " << hexChecksum << " : [" << intChecksum << "]\n";

    resultDisplay.setText(resultText);
    copyResultButton.setEnabled(true);

    // Provide visual feedback
    calculateButton.setButtonText("Calculated!");
    juce::Timer::callAfterDelay(1000, [this]() {
        calculateButton.setButtonText("Calculate");
        });
}