"""
Minimal quick start for the mybowed_py Python module.

Renders ~2.1 seconds of a G3 note to quick_start.wav using MyBowed.

Prereqs:
- Build the C++ Python extension target `mybowed_py` so it exists in this folder.

Run:
  python quick_start.py
"""

import os
import sys
import wave
import numpy as np

# Ensure local module resolution if running from another directory
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
# Also search ../lib for the built extension
# LIB_DIR = os.path.abspath(os.path.join(SCRIPT_DIR, "lib"))
# if LIB_DIR not in sys.path:
#     sys.path.insert(0, LIB_DIR)

from bowed_simulator import MyBowed

SAMPLE_RATE = 44100
OUTPUT_WAV = os.path.join(SCRIPT_DIR, "quick_start.wav")


def write_wav_int16(path: str, samples: np.ndarray, sample_rate: int) -> None:
    """Write mono float32 samples (-1..1) to 16-bit PCM WAV."""
    # Hard clip to [-1, 1] then scale
    s = np.asarray(samples, dtype=np.float32)
    s = np.clip(s, -1.0, 1.0)
    s_i16 = (s * 32767.0).astype(np.int16)
    with wave.open(path, "wb") as wf:
        wf.setnchannels(1)
        wf.setsampwidth(2)  # 16-bit
        wf.setframerate(sample_rate)
        wf.writeframes(s_i16.tobytes())


def main() -> int:
    # Create instrument
    violin = MyBowed(20.0)
    violin.set_sample_rate(SAMPLE_RATE)

    # Basic controls
    violin.set_frequency(196.0)        # G3
    violin.control_change(4, 32.0)     # __SK_BowPosition_
    violin.control_change(2, 64.0)     # __SK_BowPressure_
    violin.control_change(92, 40.0)    # reverb mix ~30%
    violin.start_bowing(0.5, 0.1)

    # Render 2.0s sustain + 0.1s release
    sustain = violin.render(int(2.0 * SAMPLE_RATE))
    violin.stop_bowing(0.01)
    release = violin.render(int(0.1 * SAMPLE_RATE))

    audio = np.concatenate([sustain, release])
    write_wav_int16(OUTPUT_WAV, audio, SAMPLE_RATE)
    print(f"Wrote {OUTPUT_WAV} ({len(audio)/SAMPLE_RATE:.2f}s)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
