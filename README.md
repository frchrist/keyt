# KeyboardTranslator Library

A static library for translating keyboard input from AZERTY to QWERTY layout, specifically designed for Qt applications. This library can intercept and translate keyboard events in QLineEdit fields, making it useful for applications that need to handle both keyboard layouts.

## Features

- Translates AZERTY keyboard input to QWERTY
- Handles special characters and numbers
- Easy integration with QLineEdit widgets
- Full test coverage
- Supports both uppercase and lowercase characters
- CMake installation support
- CMake package configuration files

### Translation Examples

```
AZERTY Input      -> QWERTY Output
&é"'(-è_çà       -> 1234567890
-&_éààà&éç'_è    -> 6182000129487
çè"àè&é_à"ç(     -> 6973071280395
'è&à_(ààé'&è(    -> 4710850024175
qwertyuiopasd    -> azertyuiopqsd
```

## Prerequisites

- CMake 3.16 or higher
- Qt6
- C++17 compliant compiler

## Installation

### Building from Source

1. Clone the repository:
```bash
git clone [repository-url]
cd keyboard-translator
```

2. Create a build directory and compile:
```bash
mkdir build && cd build
cmake ..
cmake --build .
```

3. Run the tests (optional):
```bash
ctest --output-on-failure
```

4. Install the library:
```bash
# On Unix-like systems (may require sudo)
cmake --install .

# On Windows with custom prefix
cmake --install . --prefix C:/CustomPath
```

### Using as a Dependency in Your Project

#### Method 1: Using find_package

After installing the library, you can use it in your CMake project:

```cmake
find_package(KeyboardTranslator REQUIRED)
target_link_libraries(YourTarget PRIVATE KeyboardTranslator::KeyboardTranslator)
```

#### Method 2: Using add_subdirectory

If you have the library source code as part of your project:

```cmake
add_subdirectory(path/to/KeyboardTranslator)
target_link_libraries(YourTarget PRIVATE KeyboardTranslator::KeyboardTranslator)
```

## Usage

### Basic Integration

```cpp
#include <QApplication>
#include <QLineEdit>
#include <KeyboardTranslator/KeyboardTranslator.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLineEdit lineEdit;
    KeyboardTranslator translator;
    translator.installOn(&lineEdit);

    lineEdit.show();
    return app.exec();
}
```

### CMake Project Configuration

Your project's CMakeLists.txt should look something like this:

```cmake
cmake_minimum_required(VERSION 3.16)
project(YourProject)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(KeyboardTranslator REQUIRED)

add_executable(YourApp main.cpp)
target_link_libraries(YourApp
    PRIVATE
        Qt6::Widgets
        KeyboardTranslator::KeyboardTranslator
)
```

## Project Structure

```
KeyboardTranslator/
├── cmake/
│   └── KeyboardTranslatorConfig.cmake.in
├── include/
│   └── KeyboardTranslator.h
├── src/
│   └── KeyboardTranslator.cpp
├── tests/
│   ├── CMakeLists.txt
│   ├── tst_keyboard_simple.cpp
│   ├── tst_keyboard_complex.cpp
│   └── tst_keyboard_events.cpp
└── CMakeLists.txt
```

## Testing

The library includes three test suites:

1. **Simple Tests** (tst_keyboard_simple):
   - Single character translations
   - Basic string translations
   - Unchanged character verification

2. **Complex Tests** (tst_keyboard_complex):
   - Mixed content translations
   - Case preservation
   - Special cases handling

3. **Event Tests** (tst_keyboard_events):
   - QLineEdit integration
   - Multiple widget handling
   - Event propagation

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/f1`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/f1`)
5. Open a Pull Request

## License

This project is released under the MIT License. See the LICENSE file for details.