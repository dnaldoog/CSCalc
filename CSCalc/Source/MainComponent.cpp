#include "MainComponent.h"



// Add this to your MainComponent.cpp file (after the includes):

const MainComponent::ManufacturerInfo MainComponent::manufacturers[] = {
    // Single byte manufacturer IDs (0x01-0x7F)
    {0x01, "Sequential Circuits"},
    {0x02, "Big Briar"},
    {0x03, "Octave / Plateau"},
    {0x04, "Moog"},
    {0x05, "Passport Designs"},
    {0x06, "Lexicon"},
    {0x07, "Kurzweil"},
    {0x08, "Fender"},
    {0x09, "Gulbransen"},
    {0x0A, "Delta Labs"},
    {0x0B, "Sound Comp."},
    {0x0C, "General Electro"},
    {0x0D, "Techmar"},
    {0x0E, "Matthews Research"},
    {0x10, "Oberheim"},
    {0x11, "PAIA"},
    {0x12, "Simmons"},
    {0x13, "DigiDesign"},
    {0x14, "Fairlight"},
    {0x15, "JL Cooper"},
    {0x16, "Lowery"},
    {0x17, "Lin"},
    {0x18, "Emu"},
    {0x1B, "Peavey"},
    {0x20, "Bon Tempi"},
    {0x21, "S.I.E.L."},
    {0x23, "SyntheAxe"},
    {0x24, "Hohner"},
    {0x25, "Crumar"},
    {0x26, "Solton"},
    {0x27, "Jellinghaus Ms"},
    {0x28, "CTS"},
    {0x29, "PPG"},
    {0x2F, "Elka"},
    {0x36, "Cheetah"},
    {0x3E, "Waldorf"},
    {0x40, "Kawai"},
    {0x41, "Roland"},
    {0x42, "Korg"},
    {0x43, "Yamaha"},
    {0x44, "Casio"},
    {0x45, "Akai"},
    {0x46, "Kamiya Studio Co. Ltd"},
    {0x47, "Akai Electric Co. Ltd."},
    {0x48, "Victor Company of Japan, Ltd."},
    {0x4B, "Fujitsu Limited"},
    {0x4C, "Sony Corporation"},
    {0x4E, "Teac Corporation"},
    {0x50, "Matsushita Electric Industrial Co. , Ltd"},
    {0x51, "Fostex Corporation"},
    {0x52, "Zoom Corporation"},
    {0x54, "Matsushita Communication Industrial Co., Ltd."},
    {0x55, "Suzuki Musical Instruments MFG. Co., Ltd."},
    {0x56, "Fuji Sound Corporation Ltd."},
    {0x57, "Acoustic Technical Laboratory, Inc."},
    {0x59, "Faith, Inc."},
    {0x5A, "Internet Corporation"},
    {0x5C, "Seekers Co. Ltd."},
    {0x5F, "SD Card Association"},

    // Three-byte manufacturer IDs (0x00 + 2 bytes)
    {0x000074, "Ta Horng Musical Instrument"},
    {0x000075, "e-Tek Labs (Forte Tech)"},
    {0x000076, "Electro-Voice"},
    {0x000077, "Midisoft Corporation"},
    {0x000078, "QSound Labs"},
    {0x000079, "Westrex"},
    {0x00007A, "Nvidia"},
    {0x00007B, "ESS Technology"},
    {0x00007C, "Media Trix Peripherals"},
    {0x00007D, "Brooktree Corp"},
    {0x00007E, "Otari Corp"},
    {0x00007F, "Key Electronics"},
    {0x000100, "Shure incorporated"},
    {0x000101, "AuraSound"},
    {0x000102, "Crystal Semiconductor"},
    {0x000103, "Conexant (Rockwell)"},
    {0x000104, "Silicon Graphics"},
    {0x000105, "M-Audio (Midiman)"},
    {0x000106, "PreSonus"},
    {0x000108, "Topaz Enterprises"},
    {0x000109, "Cast Lighting"},
    {0x00010A, "Microsoft"},
    {0x00010B, "Sonic Foundry"},
    {0x00010C, "Line 6 (Fast Forward)"},
    {0x00010D, "Beatnik Inc"},
    {0x00010E, "Van Koevering Company"},
    {0x00010F, "Altech Systems"},
    {0x000110, "S & S Research"},
    {0x000111, "VLSI Technology"},
    {0x000112, "Chromatic Research"},
    {0x000113, "Sapphire"},
    {0x000114, "IDRC"},
    {0x000115, "Justonic Tuning"},
    {0x000116, "TorComp Research Inc."},
    {0x000117, "Newtek Inc."},
    {0x000118, "Sound Sculpture"},
    {0x000119, "Walker Technical"},
    {0x00011A, "Digital Harmony (PAVO)"},
    {0x00011B, "InVision Interactive"},
    {0x00011C, "T-Square Design"},
    {0x00011D, "Nemesys Music Technology"},
    {0x00011E, "DBX Professional (Harman Intl)"},
    {0x00011F, "Syndyne Corporation"},
    {0x000120, "Bitheadz"},
    {0x000121, "Cakewalk Music Software"},
    {0x000122, "Analog Devices"},
    {0x000123, "National Semiconductor"},
    {0x000124, "Boom Theory / Adinolfi Alternative Percussion"},
    {0x000125, "Virtual DSP Corporation"},
    {0x000126, "Antares Systems"},
    {0x000127, "Angel Software"},
    {0x000128, "St Louis Music"},
    {0x000129, "Lyrrus dba G-VOX"},
    {0x00012A, "Ashley Audio Inc."},
    {0x00012B, "Vari-Lite Inc."},
    {0x00012C, "Summit Audio Inc."},
    {0x00012D, "Aureal Semiconductor Inc."},
    {0x00012E, "SeaSound LLC"},
    {0x00012F, "U.S. Robotics"},
    {0x000130, "Aurisis Research"},
    {0x000131, "Nearfield Research"},
    {0x000132, "FM7 Inc"},
    {0x000133, "Swivel Systems"},
    {0x000134, "Hyperactive Audio Systems"},
    {0x000135, "MidiLite (Castle Studios Productions)"},
    {0x000136, "Radikal Technologies"},
    {0x000137, "Roger Linn Design"},
    {0x000138, "TC-Helicon Vocal Technologies"},
    {0x000139, "Event Electronics"},
    {0x00013A, "Sonic Network Inc"},
    {0x00013B, "Realtime Music Solutions"},
    {0x00013C, "Apogee Digital"},
    {0x00013D, "Classical Organs"},
    {0x00013E, "Microtools Inc."},
    {0x00013F, "Numark Industries"},
    {0x000140, "Frontier Design Group"},
    {0x000141, "Recordare LLC"},
    {0x000142, "Starr Labs"},
    {0x000143, "Voyager Sound Inc."},
    {0x000144, "Manifold Labs"},
    {0x000145, "Aviom Inc."},
    {0x000146, "Mixmeister Technology"},
    {0x000147, "Notation Software"},
    {0x000148, "Mercurial Communications"},
    {0x000149, "Wave Arts"},
    {0x00014A, "Logic Sequencing Devices"},
    {0x00014B, "Axess Electronics"},
    {0x00014C, "Muse Research"},
    {0x00014D, "Open Labs"},
    {0x00014E, "Guillemot R&D Inc"},
    {0x00014F, "Samson Technologies"},
    {0x000150, "Electronic Theatre Controls"},
    {0x000151, "Blackberry (RIM)"},
    {0x000152, "Mobileer"},
    {0x000153, "Synthogy"},
    {0x000154, "Lynx Studio Technology Inc."},
    {0x000155, "Damage Control Engineering LLC"},
    {0x000156, "Yost Engineering"},
    {0x000157, "Brooks & Forsman Designs LLC / DrumLite"},
    {0x000158, "Infinite Response"},
    {0x000159, "Garritan Corp"},
    {0x00015A, "Plogue Art et Technologie"},
    {0x00015B, "RJM Music Technology"},
    {0x00015C, " Custom Solutions Software"},
    {0x00015D, "Sonarcana LLC"},
    {0x00015E, "Centrance"},
    {0x00015F, "Kesumo LLC"},
    {0x000160, "Stanton (Gibson)"},
    {0x000161, "Livid Instruments"},
    {0x000162, "First Act / 745 Media"},
    {0x000163, "Pygraphics"},
    {0x000164, "Panadigm Innovations Ltd"},
    {0x000165, "Avedis Zildjian Co"},
    {0x000166, "Auvital Music Corp"},
    {0x000167, "Inspired Instruments Inc"},
    {0x000168, "Chris Grigg Designs"},
    {0x000169, "Slate Digital LLC"},
    {0x00016A, "Mixware"},
    {0x00016B, "Social Entropy"},
    {0x00016C, "Source Audio LLC"},
    {0x00016D, "Ernie Ball / Music Man"},
    {0x00016E, "Fishman Transducers"},
    {0x00016F, "Custom Audio Electronics"},
    {0x000170, "American Audio/DJ"},
    {0x000171, "Mega Control Systems"},
    {0x000172, "Kilpatrick Audio"},
    {0x000173, "iConnectivity"},
    {0x000174, "Fractal Audio"},
    {0x000175, "NetLogic Microsystems"},
    {0x000176, "Music Computing"},
    {0x000177, "Nektar Technology Inc"},
    {0x000178, "Zenph Sound Innovations"},
    {0x000179, "DJTechTools.com"},
    {0x00017A, "Rezonance Labs"},
    {0x00017B, "Decibel Eleven"},
    {0x002029, "Focusrite/Novation"},
    {0x00202A, "Samkyung Mechatronics"},
    {0x00202B, "Medeli Electronics Co."},
    {0x00202C, "Charlie Lab SRL"},
    {0x00202D, "Blue Chip Music Technology"},
    {0x00202E, "BEE OH Corp"},
    {0x00202F, "LG Semicon America"},
    {0x002030, "TESI"},
    {0x002031, "EMAGIC"},
    {0x002032, "Behringer GmbH"},
    {0x002033, "Access Music Electronics"},
    {0x002034, "Synoptic"},
    {0x002035, "Hanmesoft"},
    {0x002036, "Terratec Electronic GmbH"},
    {0x002037, "Proel SpA"},
    {0x002038, "IBK MIDI"},
    {0x002039, "IRCAM"},
    {0x00203A, "Propellerhead Software"},
    {0x00203B, "Red Sound Systems Ltd"},
    {0x00203C, "Elektron ESI AB"},
    {0x00203D, "Sintefex Audio"},
    {0x00203E, "MAM (Music and More)"},
    {0x00203F, "Amsaro GmbH"},
    {0x002040, "CDS Advanced Technology BV"},
    {0x002041, "Touched By Sound GmbH"},
    {0x002042, "DSP Arts"},
    {0x002043, "Phil Rees Music Tech"},
    {0x002044, "Stamer Musikanlagen GmbH"},
    {0x002045, "Musical Muntaner S.A. dba Soundart"},
    {0x002046, "C-Mexx Software"},
    {0x002047, "Klavis Technologies"},
    {0x002048, "Noteheads AB"},
    {0x002049, "Algorithmix"},
    {0x00204A, "Skrydstrup R&D"},
    {0x00204B, "Professional Audio Company"},
    {0x00204C, "NewWave Labs (MadWaves)"},
    {0x00204D, "Vermona"},
    {0x00204E, "Nokia"},
    {0x00204F, "Wave Idea"},
    {0x002050, "Hartmann GmbH"},
    {0x002051, "Lion's Tracs"},
    {0x002052, "Analogue Systems"},
    {0x002053, "Focal-JMlab"},
    {0x002054, "Ringway Electronics (Chang-Zhou) Co Ltd"},
    {0x002055, "Faith Technologies (Digiplug)"},
    {0x002056, "Showworks"},
    {0x002057, "Manikin Electronic"},
    {0x002058, "1 Come Tech"},
    {0x002059, "Phonic Corp"},
    {0x00205A, "Dolby Australia (Lake)"},
    {0x00205B, "Silansys Technologies"},
    {0x00205C, "Winbond Electronics"},
    {0x00205D, "Cinetix Medien und Interface GmbH"},
    {0x00205E, "A&G Soluzioni Digitali"},
    {0x00205F, "Sequentix Music Systems"},
    {0x002060, "Oram Pro Audio"},
    {0x002061, "Be4 Ltd"},
    {0x002062, "Infection Music"},
    {0x002063, "Central Music Co. (CME)"},
    {0x002064, "genoQs Machines GmbH"},
    {0x002065, "Medialon"},
    {0x002066, "Waves Audio Ltd"},
    {0x002067, "Jerash Labs"},
    {0x002068, "Da Fact"},
    {0x002069, "Elby Designs"},
    {0x00206A, "Spectral Audio"},
    {0x00206B, "Arturia"},
    {0x00206C, "Vixid"},
    {0x00206D, "C-Thru Music"},
    {0x00206E, "Ya Horng Electronic Co LTD"},
    {0x00206F, "SM Pro Audio"},
    {0x002070, "OTO MACHINES"},
    {0x002071, "ELZAB S.A."},
    {0x002072, "Blackstar Amplification Ltd"},
    {0x002073, "M3i Technologies GmbH"},
    {0x002074, "Gemalto (from Xiring)"},
    {0x002075, "Prostage SL"},
    {0x002076, "Teenage Engineering"},
    {0x002077, "Tobias Erichsen Consulting"},
    {0x002078, "Nixer Ltd"},
    {0x002079, "Hanpin Electron Co Ltd"},
    {0x00207A, "MIDI-hardware R.Sowa"},
    {0x00207B, "Beyond Music Industrial Ltd"},
    {0x00207C, "Kiss Box B.V."},
    {0x00207D, "Misa Digital Technologies Ltd"},
    {0x00207E, "AI Musics Technology Inc"},
    {0x00207F, "Serato Inc LP"},
    {0x002100, "Limex Music Handles GmbH"},
    {0x002101, "Kyodday/Tokai"},
    {0x002102, "Mutable Instruments"},
    {0x002103, "PreSonus Software Ltd"},
    {0x002104, "Xiring"},
    {0x002105, "Fairlight Instruments Pty Ltd"},
    {0x002106, "Musicom Lab"},
    {0x002107, "VacoLoco"},
    {0x002108, "RWA (Hong Kong) Limited"},
    {0x002109, "Native Instruments"},
    {0x00210A, "Naonext"},
    {0x00210B, "MFB"},
    {0x00210C, "Teknel Research"},
    {0x00210D, "Ploytec GmbH"},
    {0x00210E, "Surfin Kangaroo Studio"},
    {0x004000, "Crimson Technology Inc."},
    {0x004001, "Softbank Mobile Corp"},
    {0x004003, "D&M Holdings Inc."},

    // End marker
    {0, nullptr}
};

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

    // Setup the button
    openDialogButton.setButtonText("Enter SysEx Data");
    openDialogButton.addListener(this);
    addAndMakeVisible(openDialogButton);

    // Setup copy button
    copyResultButton.setButtonText("Copy Result");
    copyResultButton.addListener(this);
    copyResultButton.setEnabled(false);
    copyResultButton.setTooltip("Click to copy full result\nCtrl+Click to copy SysEx only");
    addAndMakeVisible(copyResultButton);

    // Setup clear button
    clearButton.setButtonText("Clear All");
    clearButton.addListener(this);
    addAndMakeVisible(clearButton);

    // Setup result display
    resultLabel.setText("Calculation Details:", juce::dontSendNotification);
    resultLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(resultLabel);

    resultDisplay.setMultiLine(true);
    resultDisplay.setReadOnly(true);
    resultDisplay.setColour(juce::TextEditor::textColourId, juce::Colours::black);
    resultDisplay.setColour(juce::TextEditor::backgroundColourId, juce::Colour::fromString("ff99ccff"));
    addAndMakeVisible(resultDisplay);

    // Setup checksum display
    checksumLabel.setText("Checksum (Hex):", juce::dontSendNotification);
    checksumLabel.setJustificationType(juce::Justification::centred);
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
        settingsFile->setValue("sysexString", lastSysExString);
        settingsFile->setValue("startByte", lastStartByte);
        settingsFile->setValue("param2", lastParam2);
        settingsFile->setValue("rangeType", lastRangeType);
        settingsFile->setValue("checksumType", lastChecksumType);
        settingsFile->saveIfNeeded();
    }
}
// Method to insert checksum at the correct position (before EOX/F7)
juce::String MainComponent::insertChecksumAtCorrectPosition(const juce::String& processedString, uint8_t checksum)
{
    juce::StringArray tokens;
    tokens.addTokens(processedString, " ", "");

    if (tokens.size() < 2)
        return processedString; // Not enough tokens to have a checksum position

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
    int buttonWidth = 130;
    int buttonSpacing = 10;
    int totalButtonWidth = (buttonWidth * 3) + (buttonSpacing * 2);
    int startX = (buttonArea.getWidth() - totalButtonWidth) / 2;

    openDialogButton.setBounds(startX, buttonArea.getY(), buttonWidth, buttonArea.getHeight());
    copyResultButton.setBounds(startX + buttonWidth + buttonSpacing, buttonArea.getY(), buttonWidth, buttonArea.getHeight());
    clearButton.setBounds(startX + (buttonWidth + buttonSpacing) * 2, buttonArea.getY(), buttonWidth, buttonArea.getHeight());

    bounds.removeFromTop(20); // Spacing

    // Checksum display area - center aligned vertically
    auto checksumArea = bounds.removeFromTop(80);
    int checksumValueWidth = 200;
    int checksumStartX = (checksumArea.getWidth() - checksumValueWidth) / 2;

    // Label directly above the value
    checksumLabel.setBounds(checksumStartX, checksumArea.getY(), checksumValueWidth, 20);
    checksumValueLabel.setBounds(checksumStartX, checksumArea.getY() + 25, checksumValueWidth, 50);

    bounds.removeFromTop(10); // Spacing

    // Result details area - center aligned vertically
    auto resultArea = bounds;
    int resultDisplayWidth = 400;
    int resultStartX = (resultArea.getWidth() - resultDisplayWidth) / 2;

    // Label directly above the text editor
    resultLabel.setBounds(resultStartX, resultArea.getY(), resultDisplayWidth, 20);
    resultDisplay.setBounds(resultStartX, resultArea.getY() + 25, resultDisplayWidth, resultArea.getHeight() - 25);
}

void MainComponent::buttonClicked(juce::Button* button)
{
    if (button == &openDialogButton)
    {
        showSysExInputDialog();
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
        lastStartByte = 0;
        lastParam2 = 0;
        lastRangeType = 0;
        lastChecksumType = 0;
        correctedSysExString = ""; // Clear the stored corrected string

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

    // Set the param2 label based on whether we have saved state
    juce::String param2Label;
    if (lastSysExString.isEmpty()) // First time or after clear - no saved state
    {
        param2Label = "Length / End Offset:";
    }
    else // Have saved state - use specific label based on range type
    {
        param2Label = (lastRangeType == 0) ? "End Offset:" : "Message Length:";
    }
    alertWindow->addTextEditor("param2", juce::String(lastParam2), param2Label);

    // Add radio buttons for checksum type
    juce::StringArray checksumOptions;
    checksumOptions.add("Additive Checksum (Roland/Yamaha style)");
    checksumOptions.add("XOR Checksum");
    checksumOptions.add("1's Complement - E-mu,Korg etc");
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

        // Save the current values for next time (save original with tokens)
        lastSysExString = sysexString;
        lastStartByte = startStr.getIntValue();
        lastParam2 = param2Str.getIntValue();
        lastRangeType = rangeType;
        lastChecksumType = checksumType;

        // Preprocess the SysEx string to handle tokens (convert non-hex to 00)
        juce::String processedSysExString = preprocessSysExString(sysexString);
        int startByte = startStr.getIntValue();
        int param2 = param2Str.getIntValue();
        // Calculate checksum using the Calculator class with processed string
        Calculator::ChecksumType type;

        if (checksumType == 0)
        {
            type = Calculator::ChecksumType::Additive;
        }
        else if (checksumType == 1)
        {
            type = Calculator::ChecksumType::XOR;
        }
        else
        {
            type = Calculator::ChecksumType::OnesComplement;
        }
        Calculator::RangeType rangeMethod = (rangeType == 0) ? Calculator::RangeType::StartEnd : Calculator::RangeType::StartLength;

        auto calcResult = calculator.calculateChecksum(processedSysExString.toStdString(), startByte, param2, type, rangeMethod);
        correctedSysExString = insertChecksumAtCorrectPosition(processedSysExString, calcResult.checksum);


        // Display result
        juce::String checksumTypeName;

        if (checksumType == 0)
        {
            checksumTypeName = "Additive (Roland/Yamaha)";
        }
        else if (checksumType == 1)
        {
            checksumTypeName = "XOR";
        }
        else
        {
            checksumTypeName = "One's Complement";
        }
        juce::String rangeMethodName = (rangeType == 0) ? "Start + End Offset" : "Start + Length";
        juce::String hexChecksum = "0x" + juce::String::toHexString(calcResult.checksum).toUpperCase();
        juce::String intChecksum = juce::String(calcResult.checksum);
        checksumValueLabel.setText(hexChecksum, juce::dontSendNotification);

        juce::MemoryBlock hexData;
        hexData.loadFromHexString(processedSysExString);

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
        uint32_t id = parseManufacturerId(sysexString);

        juce::String resultText;
        resultText << "Manufacturer: " << MainComponent::getManufacturerName(id) << "\n";
        resultText << "Original SysEx: " << sysexString << "\n";
        resultText << "Corrected SysEx: " << correctedSysExString << "\n";  // Always show corrected version with proper checksum
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
        copyResultButton.setEnabled(true);
    }
}