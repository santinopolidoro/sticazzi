cmake_minimum_required(VERSION 3.15)
project(LogicReverb VERSION 0.1.0)

# JUCE should be installed separately
list(APPEND CMAKE_PREFIX_PATH $ENV{JUCE_PATH})
find_package(JUCE CONFIG REQUIRED)

juce_add_plugin(LogicReverb
    COMPANY_NAME "Example"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE EXMP
    PLUGIN_CODE LReb
    FORMATS AU VST3
    PRODUCT_NAME "LogicReverb")

juce_generate_juce_header(LogicReverb)

# Sources
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "Source/*.h"
    "Source/*.cpp")

target_sources(LogicReverb PRIVATE ${PROJECT_SOURCES})

target_compile_features(LogicReverb PRIVATE cxx_std_17)

# Use JUCE modules
target_link_libraries(LogicReverb PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_dsp)

