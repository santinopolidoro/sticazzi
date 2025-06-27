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
