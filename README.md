# hash-cracker-cplusplus

A hash cracking tool written in C++ and compiled to WebAssembly with Emscripten, allowing it to run directly in the browser with no backend required.

## Live Demo

Try it live at [malachivalenzuela.com](https://malachivalenzuela.com) — no installation needed.

## Overview

This project started as a terminal-based hash cracker and was refactored into a browser-embeddable WASM module. The cracking logic is written entirely in C++ and compiled to WebAssembly, where JavaScript handles the UI and calls into the C++ functions directly.

## Features

- **Dictionary attack** using a curated wordlist derived from the rockyou.txt dataset
- **Brute force attack** supporting alphanumeric character sets up to a configurable max length
- **MD5** and **SHA-256** support in the web version
- **MD5**, **SHA-1**, and **SHA-256** support in the terminal version
- No external dependencies — hashing handled by picosha2 and a standalone MD5 implementation
- Compiled to WASM with Emscripten for zero-backend browser deployment

## Project Structure
```
hash-cracker-cplusplus/
├── main.cpp          # Entry point, exports crackHash() for WASM
├── hasher.h          # Hashing function declarations
├── hasher.cpp        # MD5, SHA-1, SHA-256 implementations
├── cracker.h         # Cracker function declarations
├── cracker.cpp       # Dictionary and brute force logic
├── md5.h / md5.c     # Standalone MD5 implementation (B-Con)
├── picosha2.h        # Header-only SHA-256 implementation
├── rockyou_mini.txt  # Top 10,000 passwords from rockyou.txt
├── hashcracker.js    # Emscripten-generated WASM bootstrap
└── hashcracker.wasm  # Compiled WebAssembly binary
```

## Building

### Terminal Version
Requires GCC and OpenSSL.
```bash
g++ main.cpp hasher.cpp cracker.cpp md5.c -o hashcracker -lssl -lcrypto
./hashcracker
```

### WASM Version
Requires [Emscripten](https://emscripten.org).
```bash
emcc main.cpp hasher.cpp cracker.cpp md5.c -o hashcracker.js \
  -s WASM=1 \
  -s EXPORTED_FUNCTIONS='["_crackHash"]' \
  -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
  --embed-file rockyou_mini.txt \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s NO_EXIT_RUNTIME=1
```

## How It Works

Hashing is a one-way function — you can't reverse it mathematically. The cracker works by hashing thousands of candidate strings and comparing each result to the target hash. If they match, the original input has been found.

- **Dictionary attack** reads candidates from rockyou_mini.txt, a wordlist of the 10,000 most common real-world passwords sourced from the 2009 RockYou data breach
- **Brute force** generates every alphanumeric combination up to a given length, effectively counting in base 36

This is why long, random passwords are secure — the search space grows exponentially with length, making brute force computationally infeasible beyond ~6 characters on consumer hardware.

## Tech Stack

- **C++** — core cracking and hashing logic
- **Emscripten** — compiles C++ to WebAssembly
- **picosha2** — header-only SHA-256
- **B-Con's crypto-algorithms** — standalone MD5
- **JavaScript** — UI layer, calls into WASM via cwrap

## Disclaimer

This tool is built for educational purposes and portfolio demonstration. Only use it against hashes you own or have explicit permission to test.