#include "MainComponent.h"

// Add this to your MainComponent.cpp file (after the includes):


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

juce::String MainComponent::getManufacturerName(uint32_t id)
{
    for (int i = 0; manufacturers[i].name != nullptr; ++i)
    {
        if (manufacturers[i].id == id)
        {
            return juce::String(manufacturers[i].name);
        }
    }
    return "Unknown Manufacturer";
}

uint32_t MainComponent::parseManufacturerId(const juce::String& sysexString)
{
    juce::StringArray tokens;
    tokens.addTokens(sysexString, " ", "");

    if (tokens.size() < 2)
        return 0;

    // Skip F0 (first byte), get manufacturer ID
    juce::String secondByte = tokens[1].toLowerCase();
    uint32_t firstId = (uint32_t)secondByte.getHexValue32();

    // If it's 0x00, it's a three-byte manufacturer ID
    if (firstId == 0x00 && tokens.size() >= 4)
    {
        juce::String thirdByte = tokens[2].toLowerCase();
        juce::String fourthByte = tokens[3].toLowerCase();

        uint32_t secondId = (uint32_t)thirdByte.getHexValue32();
        uint32_t thirdId = (uint32_t)fourthByte.getHexValue32();

        return (secondId << 8) | thirdId;
    }

    return firstId;
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
    resultDisplay.setBounds(resultStartX, resultArea.getY() + 25, resultDisplayWidth, resultArea.getHeight() - 25);
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
    auto alertWindow = std::make_unique<juce::AlertWindow>("Calculation Settings",
        "Set the checksum calculation parameters:",
        juce::AlertWindow::NoIcon);

    // Add radio buttons for range specification method
    juce::StringArray rangeOptions;
    rangeOptions.add("Start + End (count from end of message)");
    rangeOptions.add("Start + Length (specify number of bytes)");

    alertWindow->addComboBox("rangeType", rangeOptions, "Range Method:");
    alertWindow->getComboBoxComponent("rangeType")->setSelectedItemIndex(lastRangeType);

    // Add text editors for range parameters
    alertWindow->addTextEditor("start", juce::String(lastStartByte), "Start Byte Index:");

    // Set the param2 label based on range type
    juce::String param2Label = (lastRangeType == 0) ? "End Offset:" : "Message Length:";
    alertWindow->addTextEditor("param2", juce::String(lastParam2), param2Label);

    // Add radio buttons for checksum type
    juce::StringArray checksumOptions;
    checksumOptions.add("Additive Checksum (Roland/Yamaha style)");
    checksumOptions.add("XOR Checksum");
    checksumOptions.add("1's Complement - E-mu,Korg etc");
    alertWindow->addComboBox("checksumType", checksumOptions, "Checksum Type:");
    alertWindow->getComboBoxComponent("checksumType")->setSelectedItemIndex(lastChecksumType);

    // Add callback to update param2 label when range type changes
    alertWindow->getComboBoxComponent("rangeType")->onChange = [&alertWindow]() {
        int selectedRange = alertWindow->getComboBoxComponent("rangeType")->getSelectedItemIndex();
        // Unfortunately, we can't easily change the label text in AlertWindow once it's created
        // This is a limitation of the AlertWindow approach
        };

    alertWindow->addButton("OK", 1, juce::KeyPress(juce::KeyPress::returnKey));
    alertWindow->addButton("Cancel", 0, juce::KeyPress(juce::KeyPress::escapeKey));

    int result = alertWindow->runModalLoop();

    if (result == 1) // OK button pressed
    {
        juce::String startStr = alertWindow->getTextEditorContents("start");
        juce::String param2Str = alertWindow->getTextEditorContents("param2");
        int rangeType = alertWindow->getComboBoxComponent("rangeType")->getSelectedItemIndex();
        int checksumType = alertWindow->getComboBoxComponent("checksumType")->getSelectedItemIndex();

        // Save the settings
        lastStartByte = startStr.getIntValue();
        lastParam2 = param2Str.getIntValue();
        lastRangeType = rangeType;
        lastChecksumType = checksumType;

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
    else
        type = Calculator::ChecksumType::OnesComplement;

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
    else
        checksumTypeName = "One's Complement";

    juce::String rangeMethodName = (lastRangeType == 0) ? "Start + End Offset" : "Start + Length";
    juce::String hexChecksum = "0x" + juce::String::toHexString(calcResult.checksum).toUpperCase();
    juce::String intChecksum = juce::String(calcResult.checksum);
    checksumValueLabel.setText(hexChecksum, juce::dontSendNotification);

    juce::MemoryBlock hexData;
    hexData.loadFromHexString(processedSysExString);

    // Calculate the actual length based on range type
    int actualLength;
    if (lastRangeType == 0) // Start + End Offset
    {
        actualLength = hexData.getSize() - lastStartByte - lastParam2;
    }
    else // Start + Length
    {
        actualLength = lastParam2;
    }

    uint32_t id = parseManufacturerId(sysexString);

    juce::String resultText;
    resultText << "Manufacturer: " << getManufacturerName(id) << "\n";
    resultText << "Original SysEx: " << sysexString << "\n";
    resultText << "Corrected SysEx: " << correctedSysExString << "\n";
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