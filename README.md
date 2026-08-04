# Terminal ATM Simulator

A small, portable ATM workflow simulator written in C. It demonstrates defensive console input, session-based authentication, balance queries, deposits, withdrawals, and insufficient-funds handling.

> This is an educational simulation. It does not connect to a bank, persist credentials, or provide production-grade authentication.

## Features

- Bounded line input instead of unsafe unbounded scans
- Correct name-and-password authentication
- Strict numeric validation for menus and monetary amounts
- Deposit, withdrawal, balance, and exit workflows
- Portable C11 implementation with no third-party dependencies
- CMake configuration with useful compiler warnings

## Project structure

```text
.
|-- src/
|   `-- main.c
|-- CMakeLists.txt
|-- LICENSE
`-- README.md
```

## Build

Requirements: a C11 compiler and CMake 3.15 or newer.

```bash
cmake -S . -B build
cmake --build build
```

Run the resulting `terminal-atm` executable from the build directory.

## Usage

1. Create a temporary account for the current process.
2. Sign in with the same name and password.
3. Choose a numbered operation and follow the prompts.
4. Select **Exit** to end the session.

All data stays in memory and is discarded when the program exits.

## Security notes

Passwords are visible while typed and stored in process memory as plain text. This is acceptable only for a learning demo. A real financial application would require masked input, secure credential storage, audit logging, decimal-safe money types, authorization controls, and extensive testing.

## Technology

C · C11 · CMake · Console application

## License

Released under the [MIT License](LICENSE).
