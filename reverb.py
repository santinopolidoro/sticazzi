import argparse
import wave
import struct


def apply_reverb(samples, sample_rate, delay_ms=50, reverb_time=2.0, dry_wet=0.5):
    delay_samples = int(delay_ms * sample_rate / 1000)
    if delay_samples <= 0:
        raise ValueError("Delay must be positive")
    # Feedback coefficient to reach -60 dB after reverb_time seconds
    if reverb_time <= 0:
        raise ValueError("Reverb time must be positive")
    feedback = 10 ** (-3 * delay_ms / (reverb_time * 1000))
    buffer = [0] * delay_samples
    out = []
    buf_index = 0
    max_amp = 2 ** 15 - 1
    min_amp = -2 ** 15
    for sample in samples:
        wet_sample = sample + int(buffer[buf_index] * feedback)
        buffer[buf_index] = wet_sample
        buf_index = (buf_index + 1) % delay_samples
        mixed = int((1 - dry_wet) * sample + dry_wet * wet_sample)
        mixed = max(min_amp, min(max_amp, mixed))
        out.append(mixed)
    return out


def read_wav(filename):
    with wave.open(filename, 'rb') as wf:
        if wf.getsampwidth() != 2:
            raise ValueError('Only 16-bit PCM WAV files are supported')
        n_channels = wf.getnchannels()
        sample_rate = wf.getframerate()
        frames = wf.getnframes()
        raw = wf.readframes(frames)
        fmt = '<' + 'h' * (len(raw) // 2)
        samples = list(struct.unpack(fmt, raw))
        if n_channels == 2:
            # convert to mono by averaging
            samples = [(samples[i] + samples[i + 1]) // 2 for i in range(0, len(samples), 2)]
    return samples, sample_rate


def write_wav(filename, samples, sample_rate):
    with wave.open(filename, 'wb') as wf:
        wf.setnchannels(1)
        wf.setsampwidth(2)
        wf.setframerate(sample_rate)
        fmt = '<' + 'h' * len(samples)
        data = struct.pack(fmt, *samples)
        wf.writeframes(data)


def main():
    parser = argparse.ArgumentParser(description='Apply simple reverb to a WAV file.')
    parser.add_argument('input', help='Input WAV file')
    parser.add_argument('output', help='Output WAV file')
    parser.add_argument('--delay', type=float, default=50, help='Delay in ms between echoes')
    parser.add_argument('--time', type=float, default=2.0, help='Reverb time (s) until -60dB decay')
    parser.add_argument('--mix', type=float, default=0.5, help='Dry/Wet mix (0-1)')
    args = parser.parse_args()

    samples, sr = read_wav(args.input)
    processed = apply_reverb(samples, sr, delay_ms=args.delay, reverb_time=args.time, dry_wet=args.mix)
    write_wav(args.output, processed, sr)
    print(f"Output written to {args.output}")


if __name__ == '__main__':
    main()
