#pragma once

#include <JuceHeader.h>
#include "Calculator.h"
//#include "DemoUtilities.h"
 //==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    enum DialogType
    {
        plainAlertWindow,
        warningAlertWindow,
        infoAlertWindow,
        questionAlertWindow,
        okCancelAlertWindow,
        extraComponentsAlertWindow,
        calloutBoxWindow,
       /* progressWindow,*/
        loadChooser,
        loadWithPreviewChooser,
        directoryChooser,
        //saveChooser,
        //shareText,
        //shareFile,
        //shareImage,
        //numDialogs
    };
    MainComponent()
    {
	setOpaque(true);

    addAndMakeVisible(nativeButton);
    nativeButton.setButtonText("Use Native Windows");
    nativeButton.onClick = [this] { getLookAndFeel().setUsingNativeAlertWindows(nativeButton.getToggleState()); };

    StringArray windowNames{ "Plain Alert Window", "Alert Window With Warning Icon", "Alert Window With Info Icon", "Alert Window With Question Icon",
                              "OK Cancel Alert Window", "Alert Window With Extra Components", "CalloutBox", "Thread With Progress Window",
                              "'Load' File Browser", "'Load' File Browser With Image Preview", "'Choose Directory' File Browser", "'Save' File Browser",
                              "Share Text", "Share Files", "Share Images" };

    // warn in case we add any windows
    jassert(windowNames.size() == numDialogs);

    for (auto windowName : windowNames)
    {
        auto* newButton = new TextButton();

        addAndMakeVisible(windowButtons.add(newButton));
        newButton->setButtonText(windowName);

        auto index = windowNames.indexOf(windowName);
        newButton->onClick = [this, index, newButton] { showWindow(*newButton, static_cast<DialogType> (index)); };
    }
	setSize(600, 400);
	}
   


private:
    //==============================================================================
    // Your private member variables go here...
    ToggleButton nativeButton;
    OwnedArray<TextButton> windowButtons;

    static void alertBoxResultChosen(int result, DialogsDemo*)
    {
        AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "Alert Box",
            "Result code: " + String(result));
    }

    void showWindow(Component& button, DialogType type)
    {
        if (type >= plainAlertWindow && type <= questionAlertWindow)
        {
            AlertWindow::AlertIconType icon = AlertWindow::NoIcon;

            if (type == warningAlertWindow)   icon = AlertWindow::WarningIcon;
            if (type == infoAlertWindow)      icon = AlertWindow::InfoIcon;
            if (type == questionAlertWindow)  icon = AlertWindow::QuestionIcon;

            AlertWindow::showMessageBoxAsync(icon, "This is an AlertWindow",
                "And this is the AlertWindow's message. Blah blah blah blah blah blah blah blah blah blah blah blah blah.",
                "OK");
        }
        else if (type == okCancelAlertWindow)
        {
            AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon, "This is an ok/cancel AlertWindow",
                "And this is the AlertWindow's message. Blah blah blah blah blah blah blah blah blah blah blah blah blah.",
                {}, {}, {},
                ModalCallbackFunction::forComponent(alertBoxResultChosen, this));
        }
        else if (type == calloutBoxWindow)
        {
            auto colourSelector = std::make_unique<ColourSelector>();

            colourSelector->setName("background");
            colourSelector->setCurrentColour(findColour(TextButton::buttonColourId));
            colourSelector->setColour(ColourSelector::backgroundColourId, Colours::transparentBlack);
            colourSelector->setSize(300, 400);

            CallOutBox::launchAsynchronously(std::move(colourSelector), button.getScreenBounds(), nullptr);
        }
        else if (type == extraComponentsAlertWindow)
        {
#if JUCE_MODAL_LOOPS_PERMITTED
            // Modal loops are extremely dangerous. Do not copy the code below unless you are absolutely
            // certain you are aware of all the many complicated things that can go catastrophically
            // wrong. Read the documentation for Component::runModalLoop. If you find you are using code
            // similar to this you should refactor things to remove it.

            AlertWindow w("AlertWindow demo..",
                "This AlertWindow has a couple of extra components added to show how to add drop-down lists and text entry boxes.",
                AlertWindow::QuestionIcon);

            w.addTextEditor("text", "enter some text here", "text field:");
            w.addComboBox("option", { "option 1", "option 2", "option 3", "option 4" }, "some options");
            w.addButton("OK", 1, KeyPress(KeyPress::returnKey, 0, 0));
            w.addButton("Cancel", 0, KeyPress(KeyPress::escapeKey, 0, 0));

            if (w.runModalLoop() != 0) // is they picked 'ok'
            {
                // this is the item they chose in the drop-down list..
                auto optionIndexChosen = w.getComboBoxComponent("option")->getSelectedItemIndex();
                ignoreUnused(optionIndexChosen);

                // this is the text they entered..
                auto text = w.getTextEditorContents("text");
            }
#endif
        }
        else if (type == progressWindow)
        {
            // This will launch our ThreadWithProgressWindow in a modal state. (Our subclass
            // will take care of deleting the object when the task has finished)
            (new DemoBackgroundThread())->launchThread();
        }
        else if (type >= loadChooser && type <= saveChooser)
        {
            auto useNativeVersion = nativeButton.getToggleState();

            if (type == loadChooser)
            {
                fc.reset(new FileChooser("Choose a file to open...", File::getCurrentWorkingDirectory(),
                    "*", useNativeVersion));

                fc->launchAsync(FileBrowserComponent::canSelectMultipleItems | FileBrowserComponent::openMode
                    | FileBrowserComponent::canSelectFiles,
                    [](const FileChooser& chooser)
                    {
                        String chosen;
                        auto results = chooser.getURLResults();

                        for (auto result : results)
                            chosen << (result.isLocalFile() ? result.getLocalFile().getFullPathName()
                                : result.toString(false)) << "\n";

                        AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
                            "File Chooser...",
                            "You picked: " + chosen);
                    });
            }
            else if (type == loadWithPreviewChooser)
            {
                imagePreview.setSize(200, 200);

                fc.reset(new FileChooser("Choose an image to open...", File::getCurrentWorkingDirectory(),
                    "*.jpg;*.jpeg;*.png;*.gif", useNativeVersion));

                fc->launchAsync(FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles
                    | FileBrowserComponent::canSelectMultipleItems,
                    [](const FileChooser& chooser)
                    {
                        String chosen;
                        auto results = chooser.getURLResults();

                        for (auto result : results)
                            chosen << (result.isLocalFile() ? result.getLocalFile().getFullPathName()
                                : result.toString(false)) << "\n";

                        AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
                            "File Chooser...",
                            "You picked: " + chosen);
                    },
                    &imagePreview);
            }
            else if (type == saveChooser)
            {
                auto fileToSave = File::createTempFile("saveChooserDemo");

                if (fileToSave.createDirectory().wasOk())
                {
                    fileToSave = fileToSave.getChildFile("JUCE.png");
                    fileToSave.deleteFile();

                    FileOutputStream outStream(fileToSave);

                    if (outStream.openedOk())
                        if (auto inStream = createAssetInputStream("juce_icon.png"))
                            outStream.writeFromInputStream(*inStream, -1);
                }

                fc.reset(new FileChooser("Choose a file to save...",
                    File::getCurrentWorkingDirectory().getChildFile(fileToSave.getFileName()),
                    "*", useNativeVersion));

                fc->launchAsync(FileBrowserComponent::saveMode | FileBrowserComponent::canSelectFiles,
                    [fileToSave](const FileChooser& chooser)
                    {
                        auto result = chooser.getURLResult();
                        auto name = result.isEmpty() ? String()
                            : (result.isLocalFile() ? result.getLocalFile().getFullPathName()
                                : result.toString(true));

                        // Android and iOS file choosers will create placeholder files for chosen
                        // paths, so we may as well write into those files.
#if JUCE_ANDROID || JUCE_IOS
                        if (!result.isEmpty())
                        {
                            std::unique_ptr<InputStream>  wi(fileToSave.createInputStream());
                            std::unique_ptr<OutputStream> wo(result.createOutputStream());

                            if (wi.get() != nullptr && wo.get() != nullptr)
                            {
                                auto numWritten = wo->writeFromInputStream(*wi, -1);
                                jassert(numWritten > 0);
                                ignoreUnused(numWritten);
                                wo->flush();
                            }
                        }
#endif

                        AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
                            "File Chooser...",
                            "You picked: " + name);
                    });
            }
            else if (type == directoryChooser)
            {
                fc.reset(new FileChooser("Choose a directory...",
                    File::getCurrentWorkingDirectory(),
                    "*",
                    useNativeVersion));

                fc->launchAsync(FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories,
                    [](const FileChooser& chooser)
                    {
                        auto result = chooser.getURLResult();
                        auto name = result.isLocalFile() ? result.getLocalFile().getFullPathName()
                            : result.toString(true);

                        AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
                            "File Chooser...",
                            "You picked: " + name);
                    });
            }
        }
        else if (type == shareText)
        {
            ContentSharer::getInstance()->shareText("I love JUCE!",
                [](bool success, const String& error)
                {
                    auto resultString = success ? String("success") : ("failure\n (error: " + error + ")");

                    AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "Sharing Text Result",
                        "Sharing text finished\nwith " + resultString);
                });
        }
        else if (type == shareFile)
        {
            File fileToSave = File::createTempFile("DialogsDemoSharingTest");

            if (fileToSave.createDirectory().wasOk())
            {
                fileToSave = fileToSave.getChildFile("SharingDemoFile.txt");
                fileToSave.replaceWithText("Make it fast!");

                Array<URL> urls;
                urls.add(URL(fileToSave));

                ContentSharer::getInstance()->shareFiles(urls,
                    [](bool success, const String& error)
                    {
                        auto resultString = success ? String("success") : ("failure\n (error: " + error + ")");

                        AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
                            "Sharing Files Result",
                            "Sharing files finished\nwith " + resultString);
                    });

            }
        }
        else if (type == shareImage)
        {
            auto myImage = getImageFromAssets("juce_icon.png");

            Image myImage2(Image::RGB, 500, 500, true);
            Graphics g(myImage2);
            g.setColour(Colours::green);
            ColourGradient gradient(Colours::yellow, 170, 170, Colours::cyan, 170, 20, true);
            g.setGradientFill(gradient);
            g.fillEllipse(20, 20, 300, 300);

            Array<Image> images{ myImage, myImage2 };

            ContentSharer::getInstance()->shareImages(images,
                [](bool success, const String& error)
                {
                    String resultString = success ? String("success")
                        : ("failure\n (error: " + error + ")");

                    AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, "Sharing Images Result",
                        "Sharing images finished\nwith " + resultString);
                });
        }
    }

    ImagePreviewComponent imagePreview;
    std::unique_ptr<FileChooser> fc;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

