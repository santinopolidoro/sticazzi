# sticazzi

This repository provides a simple command line tool to apply a basic reverb effect to a WAV audio file.

## Usage

```
python3 reverb.py INPUT.wav OUTPUT.wav [--delay MS] [--time SECONDS] [--mix RATIO]
```

- `--delay` sets the delay in milliseconds between echoes (default: 50).
- `--time` controls how long it takes for the reverb to decay by 60 dB (default: 2 seconds).
- `--mix` sets the dry/wet mix ratio where `0` is completely dry and `1` is fully wet (default: 0.5).

The script outputs a new mono WAV file with the reverb applied.

## Logic Pro Plugin

A basic Audio Unit plugin is provided in `LogicReverb/` using the JUCE framework. It exposes delay, reverb time, and mix parameters with a simple rotary control interface.

To build the plugin you need JUCE installed and CMake available. Set the environment variable `JUCE_PATH` to the location of your JUCE installation and run:

```bash
cmake -B build -S LogicReverb
cmake --build build --config Release
```

The resulting AU component can be loaded in Logic Pro after it is signed and validated.
