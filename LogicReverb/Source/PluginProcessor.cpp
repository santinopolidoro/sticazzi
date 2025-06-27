#include "PluginProcessor.h"
#include "PluginEditor.h"

LogicReverbAudioProcessor::LogicReverbAudioProcessor()
    : parameters(*this, nullptr, juce::Identifier("Params"),
                 {
                     std::make_unique<juce::AudioParameterFloat>("delay", "Delay", juce::NormalisableRange<float>(1.0f, 500.0f), 50.0f),
                     std::make_unique<juce::AudioParameterFloat>("time", "Time", juce::NormalisableRange<float>(0.1f, 5.0f), 2.0f),
                     std::make_unique<juce::AudioParameterFloat>("mix", "Mix", juce::NormalisableRange<float>(0.0f, 1.0f), 0.5f)
                 })
{
}

void LogicReverbAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    const int maxDelaySamples = static_cast<int>(sampleRate * 0.5f); // 500ms max
    delayBuffer.setSize(2, maxDelaySamples);
    delayBuffer.clear();
    delayWritePosition = 0;
}

void LogicReverbAudioProcessor::releaseResources()
{
}

bool LogicReverbAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void LogicReverbAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi)
{
    const int numSamples = buffer.getNumSamples();
    const float delayMs = *parameters.getRawParameterValue("delay");
    const float time = *parameters.getRawParameterValue("time");
    const float mix = *parameters.getRawParameterValue("mix");

    const double sampleRate = getSampleRate();
    const int delaySamples = static_cast<int>(delayMs * 0.001 * sampleRate);
    const float feedback = std::pow(10.0f, -3.0f * (delayMs / 1000.0f) / time);

    if (delayBuffer.getNumSamples() < delaySamples + numSamples)
        delayBuffer.setSize(2, delaySamples + numSamples, true, true, true);

    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);
        float* delayData = delayBuffer.getWritePointer(channel);

        for (int i = 0; i < numSamples; ++i)
        {
            const float in = channelData[i];
            const float delayed = delayData[(delayWritePosition + i) % delayBuffer.getNumSamples()];
            delayData[(delayWritePosition + i) % delayBuffer.getNumSamples()] = in + delayed * feedback;
            channelData[i] = in * (1.0f - mix) + delayed * mix;
        }
    }

    delayWritePosition += numSamples;
    delayWritePosition %= delayBuffer.getNumSamples();
}

juce::AudioProcessorEditor* LogicReverbAudioProcessor::createEditor()
{
    return new LogicReverbAudioProcessorEditor(*this);
}

void LogicReverbAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = parameters.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void LogicReverbAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml.get() != nullptr)
        parameters.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LogicReverbAudioProcessor();
}
