# Bowed String Simulator (mybowed)

This program demonstrates how to use the STK `Bowed` class to simulate a bowed string instrument with hardcoded control parameters.

## Features

The simulator controls four key parameters of bowed string playing with **dynamic parameter changes**:

1. **Frequency** (Hz): The pitch of the note
   - Determines which note is played
   - **Array**: `{440.0, 523.25, 659.25, 392.0, 554.37}` (A4, C5, E5, G4, C#5)

2. **Bow Pressure** (0-128): How hard the bow presses on the string
   - Lower values = heavier pressure (more force)
   - Higher values = lighter pressure
   - **Array**: `{64.0, 80.0, 40.0, 100.0, 20.0}` (5 segments)

3. **Bow Position** (0-128): Where the bow touches the string
   - 0 = at the bridge (bright, focused sound)
   - 128 = at the nut/fingerboard (darker, more mellow sound)
   - **Array**: `{16.0, 32.0, 8.0, 64.0, 4.0}` (5 segments)

4. **Bow Speed** (0-1): How fast the bow moves
   - Controls the amplitude/velocity of bowing
   - **Array**: `{0.7, 0.5, 0.9, 0.3, 0.8}` (5 segments)

### Dynamic Parameter Changes

The simulation is divided into **5 segments** (1 second each for 5-second duration). Each segment uses different parameters from the predefined arrays, creating a dynamic melodic performance that demonstrates various bowing techniques:

- **Segment 1**: A4 (440Hz), medium pressure, near bridge, moderate speed
- **Segment 2**: C5 (523Hz), light pressure, middle position, slow speed  
- **Segment 3**: E5 (659Hz), heavy pressure, very near bridge, fast speed
- **Segment 4**: G4 (392Hz), very light pressure, middle position, slow speed
- **Segment 5**: C#5 (554Hz), very heavy pressure, very near bridge, fast speed

## Usage

```bash
# Build the program (from STK root directory)
mkdir -p build && cd build
cmake ..
make mybowed

# Run with default parameters
./projects/examples/mybowed

# Run with custom output filename
./projects/examples/mybowed my_custom_output.wav
```

## Output

- Generates a 5-second WAV file (44.1 kHz, 16-bit, mono)
- Default filename: `bowed_output.wav`
- Custom filename can be specified as command-line argument

## Technical Details

The program uses the STK digital waveguide model based on:
- Smith (1986) bowed string model
- McIntyre, Schumacher, Woodhouse (1983) physical model

Key STK classes used:
- `Bowed`: Main bowed string instrument
- `FileWvOut`: Audio file output
- `BowTable`: Non-linear bow-string friction model

## Modifying Parameters

To experiment with different sounds, edit the arrays and constants in `mybowed.cpp`:

```cpp
// Basic parameters
const StkFloat DURATION = 5.0;        // Change length

// Dynamic parameter arrays (must have same length)
const StkFloat FREQUENCIES[] = {440.0, 523.25, 659.25, 392.0, 554.37};  // Hz
const StkFloat BOW_PRESSURES[] = {64.0, 80.0, 40.0, 100.0, 20.0};       // 0-128
const StkFloat BOW_POSITIONS[] = {16.0, 32.0, 8.0, 64.0, 4.0};          // 0-128  
const StkFloat BOW_SPEEDS[] = {0.7, 0.5, 0.9, 0.3, 0.8};                // 0-1
```

**Note**: All four arrays must have the same length. The program automatically calculates `NUM_SEGMENTS` based on the array size.

## Example Parameter Combinations

- **Bright violin sound**: `BOW_POSITION = 8, BOW_PRESSURE = 40`
- **Mellow cello sound**: `BOW_POSITION = 64, BOW_PRESSURE = 80`
- **Heavy bowing**: `BOW_PRESSURE = 20, BOW_SPEED = 0.9`
- **Light bowing**: `BOW_PRESSURE = 100, BOW_SPEED = 0.3`
