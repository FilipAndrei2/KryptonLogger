# **Krypton Logger — Lightweight Logging for C++**
---

Krypton Logger supports multiple logging levels, suitable for both information dumping and debugging.  
It can log to configurable sinks, such as multiple files and the console simultaneously.  
Logging is synchronized using a global mutex, ensuring all operations are thread-safe.

## Usage

By including `kr/logs.hpp`, you gain access to the entire functionality of the library.

In production builds, you can define `KR_DISABLE_LOGGING` before including `kr/logs.hpp` to completely disable logging without modifying your codebase.  
This macro clears the bodies of all public logging functions, allowing the compiler to optimize them away entirely.

You can change the global logger instance for custom sink handling by calling `kr::changeLogger()`.

## Author
**Filip Andrei-Robert**  
Email: [filandrei4@gmail.com](mailto:filandrei4@gmail.com)

## License
You have full permission to use, modify, and distribute this project as you wish.
