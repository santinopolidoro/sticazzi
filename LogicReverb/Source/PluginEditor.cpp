#include "PluginEditor.h"
#include "PluginProcessor.h"

LogicReverbAudioProcessorEditor::LogicReverbAudioProcessorEditor(LogicReverbAudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p),
      delayAttachment(processor.getValueTreeState(), "delay", delaySlider),
      timeAttachment(processor.getValueTreeState(), "time", timeSlider),
      mixAttachment(processor.getValueTreeState(), "mix", mixSlider)
{
    delayLabel.setText("Delay", juce::dontSendNotification);
    timeLabel.setText("Time", juce::dontSendNotification);
    mixLabel.setText("Mix", juce::dontSendNotification);

    addAndMakeVisible(delayLabel);
    addAndMakeVisible(timeLabel);
    addAndMakeVisible(mixLabel);

    addAndMakeVisible(delaySlider);
    addAndMakeVisible(timeSlider);
    addAndMakeVisible(mixSlider);

    delaySlider.setSliderStyle(juce::Slider::Rotary);
    delaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);

    timeSlider.setSliderStyle(juce::Slider::Rotary);
    timeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);

    mixSlider.setSliderStyle(juce::Slider::Rotary);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);

    setSize (300, 200);
}

void LogicReverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkgrey);
}

void LogicReverbAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(10);
    auto sliderWidth = area.getWidth() / 3;

    delayLabel.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(20));
    delaySlider.setBounds(area.removeFromLeft(sliderWidth));

    timeLabel.setBounds(area.removeFromLeft(sliderWidth).removeFromTop(20));
    timeSlider.setBounds(area.removeFromLeft(sliderWidth));

    mixLabel.setBounds(area.removeFromTop(20));
    mixSlider.setBounds(area);
}

