# KeyboardTranslator Library

A static library for translating keyboard input from AZERTY to QWERTY layout, specifically designed for Qt applications. This library can intercept and translate keyboard events in QLineEdit fields, making it useful for applications that need to handle both keyboard layouts.

## Features

- Translates AZERTY keyboard input to QWERTY
- Handles special characters and numbers
- Easy integration with QLineEdit widgets
- Full test coverage
- Supports both uppercase and lowercase characters

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

3. Run the tests:
```bash
ctest --output-on-failure
```

## Usage

### Basic Integration

```cpp
#include <QApplication>
#include <QLineEdit>
#include "KeyboardTranslator.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLineEdit lineEdit;
    KeyboardTranslator translator;
    translator.installOn(&lineEdit);

    lineEdit.show();
    return app.exec();
}
```

### CMake Integration

Add to your project's CMakeLists.txt:

```cmake
add_subdirectory(path/to/KeyboardTranslator)
target_link_libraries(YourTarget PRIVATE KeyboardTranslator)
```

## Project Structure

```
KeyboardTranslator/
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
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is released under the MIT License. See the LICENSE file for details.