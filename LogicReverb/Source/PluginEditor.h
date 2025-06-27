#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class LogicReverbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    explicit LogicReverbAudioProcessorEditor(LogicReverbAudioProcessor& p);
    ~LogicReverbAudioProcessorEditor() override = default;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    LogicReverbAudioProcessor& processor;

    juce::Slider delaySlider;
    juce::Slider timeSlider;
    juce::Slider mixSlider;

    juce::Label delayLabel;
    juce::Label timeLabel;
    juce::Label mixLabel;

    juce::AudioProcessorValueTreeState::SliderAttachment delayAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment timeAttachment;
    juce::AudioProcessorValueTreeState::SliderAttachment mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LogicReverbAudioProcessorEditor)
};

