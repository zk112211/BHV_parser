# BVH Parser

A C++ implementation of a BVH (Biovision Hierarchy) file parser that converts motion capture data to JSON format.

## Overview

This project implements a parser for BVH files, which are commonly used in motion capture and computer animation. The parser reads BVH files containing skeletal hierarchy and motion data, then converts them to a structured JSON format for further processing or analysis.

## Features

- **BVH File Parsing**: Reads and parses standard BVH format files
- **Skeletal Hierarchy**: Extracts joint structure, offsets, and channel information
- **Motion Data**: Processes frame-by-frame motion data
- **JSON Output**: Converts parsed data to JSON format
- **Stack-based Implementation**: Uses custom stack data structure for parsing
- **C++11 Compatible**: Built with modern C++ standards

## Project Structure

```
├── bvh_parser.h          # Header file with joint and META structures
├── bvh_parser.cpp        # Main parser implementation
├── json.cpp              # JSON output functionality
├── stack.h               # Custom stack template class
├── Makefile              # Build configuration
├── sample.bvh            # Sample BVH input file
├── output.json           # Generated JSON output
└── DSProject/            # Additional project files
    ├── bvh_parser.cpp    # Extended parser implementation
    ├── stack.h           # Stack implementation
    └── base              # Compiled executable
```

## Data Structures

### Joint Structure
```cpp
struct joint {
    string name;                    // Joint name
    double offset_x, offset_y, offset_z;  // 3D offset coordinates
    vector<joint*> children;        // Child joints
    vector<string> channels;        // Motion channels (e.g., Xrotation, Yposition)
    vector<vector<double>> motion;  // Frame-by-frame motion data
    string joint_type;              // Type (ROOT, JOINT, END)
};
```

### Metadata Structure
```cpp
struct META {
    int frame;                      // Number of frames
    double frame_time;              // Time per frame
};
```

## Build Instructions

### Prerequisites
- C++11 compatible compiler (g++, clang++)
- Make utility

### Building
```bash
# Build the base version
make base

# Build the bonus version
make bonus

# Clean build artifacts
make clean
```

### Usage
```bash
# Run the parser with a BVH file
./base sample.bvh

# Or use the bonus version
./bonus sample.bvh
```

## BVH File Format

The parser supports standard BVH format with the following sections:

1. **HIERARCHY**: Defines the skeletal structure
   - `ROOT`: Root joint definition
   - `JOINT`: Regular joint definition
   - `OFFSET`: 3D position offset
   - `CHANNELS`: Motion channels for the joint
   - `End Site`: End effector definition

2. **MOTION**: Contains frame-by-frame motion data
   - Frame count and frame time
   - Motion values for each channel in each frame

## Implementation Details

### Parsing Algorithm
The parser uses a stack-based approach to handle the hierarchical structure:
1. Read the hierarchy section token by token
2. Use a stack to maintain the current joint context
3. Parse joint properties (name, offset, channels)
4. Handle nested joint structures
5. Process motion data frame by frame

### Stack Implementation
Custom template stack class with:
- Dynamic resizing (increment by 50)
- Push, Pop, and Top operations
- Memory management for overflow handling

### JSON Output
The `jsonify` function converts the parsed data to JSON format:
- Metadata (frame count, frame time)
- Joint hierarchy with properties
- Motion data arrays

## Sample Output

The parser generates JSON output in the following format:
```json
{
    "frame": 1668183408,
    "frame_time": 4.92969e+204,
    "joint": {
        "type": "",
        "name": "",
        "offset": [0, 0, 0],
        "channels": [],
        "motion": [],
        "children": []
    }
}
```

## Limitations

- Basic error handling
- Limited validation of BVH file format
- JSON output structure is partially implemented
- No support for advanced BVH features (e.g., multiple motion clips)

## Future Improvements

- Enhanced error handling and validation
- Complete JSON output implementation
- Support for more BVH file variations
- Performance optimizations
- Better memory management
- Unit tests and documentation

## License

This project is part of a Data Structures course assignment.

## Author

Student ID: 21307130123
Course: Data Structures
Institution: Fudan University
