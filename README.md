# Garbage Collector C/C++

A custom memory management system in C that helps track and clean up dynamically allocated memory using a stack-based "collector."

## Description

Garbege/Memory Collector ensures that all allocated memory is freed when the program exits, avoiding memory leaks. It replaces standard memory allocation functions with tracked versions, providing automatic cleanup and improved memory safety.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [License](#license)

## Installation

To use Memory Collector in your project, follow these steps:

1. Clone the repository:
   ```sh
   git clone https://github.com/Hari-P-T/Garbage-Collector-C-CPP.git
   ```
2. Navigate to the project directory:
   ```sh
   cd Garbage-Collector-C-CPP
   ```
3. Compile the project:
   ```sh
   gcc -o main Main.c Collector.c
   ```

## Usage

After compilation, run the program:

```sh
./main
```

Example output:
```
Starting cleanup...
Collector emptied: 1
```

To use Memory Collector in your own projects, include `Collector.h` and link with `Collector.c`. Replace standard memory allocation functions with:

- `custom_malloc(size_t size)`
- `custom_calloc(size_t num, size_t size)`
- `custom_realloc(void* ptr, size_t size)`
- `custom_free(void* ptr)` (for manual deallocation)

## Features

- **Custom Memory Management**: Tracked versions of malloc, calloc, and realloc.
- **Automatic Cleanup**: Stack-based collector frees all memory at program exit.
- **Memory Safety**: Prevents leaks and ensures proper management.

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the project
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a pull request

## License

Distributed under the MIT License. See `LICENSE` for more information.

## Contact

Hari PT - [LinkedIn](https://in.linkedin.com/in/hari-p-t-5b585b253) - hariptlinux@gmail.com

Project Link: [https://github.com/Hari-P-T/Garbage-Collector-C-CPP](https://github.com/Hari-P-T/Garbage-Collector-C-CPP)
