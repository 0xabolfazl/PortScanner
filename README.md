# Port Scanner

## Overview
A multi-threaded TCP port scanner written in C for Windows systems that detects open ports and identifies common services.

## Features
* Multi-threaded scanning (50 concurrent threads max)
* Custom port range scanning
* Service detection (HTTP, SSH, FTP, etc.)
* Configurable connection timeout (2000ms default)
* Simple command-line interface

## Installation
1. Ensure you have MinGW or Visual Studio installed
2. Compile with:
```bash
gcc port_scanner.c -o port_scanner.exe -lws2_32
```
 
## Usage
1. Run port scanner with:
```bash
port_scanner.exe
```
2. Then enter:
-Target IP address (e.g., 127.0.0.1)
-Starting port number
-Ending port number

## Customization
To Modify:
Thread limit: Change #define MAX_THREADS

Timeout: Adjust #define TIMEOUT_MS

Add services: Extend get_service_name()