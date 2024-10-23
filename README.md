# logln.h

A simple C/C++ header-only library for logging messages to a file and console with different log levels.

Ported from the original [logln](https://github.com/zewebdev1337/logln) written in go.

## Usage

```cpp
#include <iostream>
#include <logln.h>

int main() {
    // Initialize the log file with the default filename based on the current date and time (YYYY_MM_DD-HH_mm_SS.log).
    logln::Init()

    // Alternatively:

    //Initialize the log file with the specified file path.
    logln::CustomInit("/path/to/app.log") 

    // Log an info message
    logln::Logln("This is an info message", 0, false);
    // Output: 2006/01/02 15:04:05 INFO This is an info message

    // Log a warning message
    logln::Logln("This is a warning message", 1, false);
    // Output: 2006/01/02 15:04:05 WARNING This is a warning message

    // Log a debug message
    logln::Logln("This is a debug message", 5, false);
    // Output: 2006/01/02 15:04:05 DEBUG This is a debug message

    // Log a debug message (to file only)
    logln::Logln("This is a debug message", 5, true);
    // Output: 2006/01/02 15:04:05 DEBUG This is a debug message (in log file)

    // Log a warning if the condition is false
    bool ok = false;
    logln::PrintWarningOrSuccessIfNotOk(ok, "something is not ok", 0, false);
    // Output: 2006/01/02 15:04:05 WARNING something is not ok.

    // Log an error if the condition is false
    logln::PrintErrorOrSuccessIfNotOk(ok, "something is not ok", 0, false);
    // Output: 2006/01/02 15:04:05 ERROR An error occurred: something is not ok.

    // Log a fatal error if the condition is false and exit
    logln::PrintFatalOrSuccessIfNotOk(ok, "something is fatally not ok", 0, false);
    // Output: 2006/01/02 15:04:05 FATAL Fatal error encountered: something is fatally not ok.

    // Log a panic if the condition is false and throw an exception
    try {
        logln::PrintPanicOrSuccessIfNotOk(ok, "something is not ok", 0, false);
    } catch (const std::runtime_error& error) {
        std::cout << "Caught exception: " << error.what() << std::endl;
    }
    // Output: 2006/01/02 15:04:05 PANIC: something is not ok.

    std::runtime_error error("this is an error");
    // Log an error if the exception is thrown
    try {
        throw error;
    } catch (const std::runtime_error& err) {
        logln::PrintErrorOrSuccess("trying to do something", &err, 0, false);
    }
    // Output: 2006/01/02 15:04:05 ERROR An error occurred trying to do something: this is an error.

    // Log a warning if the exception is thrown
    try {
        throw error;
    } catch (const std::runtime_error& err) {
        logln::PrintWarningOrSuccess("this error triggered this warning", &err, 0, false);
    }
    // Output: 2006/01/02 15:04:05 WARNING this error triggered this warning: this is an error.

    // Log a fatal error if the exception is thrown and exit
    try {
        throw error;
    } catch (const std::runtime_error& error) {
        logln::PrintFatalOrSuccess("reading essential data", &err, 0, false);
    }
    // Output: 2006/01/02 15:04:05 FATAL Fatal error encountered reading essential data: this is an error.

    // Log a panic if the exception is thrown and throw an exception
    try {
        throw error;
    } catch (const std::runtime_error& err) {
        logln::PrintPanicOrSuccess("expecting something different", &err, 0, false);
    }
    // Output: 2006/01/02 15:04:05 PANIC Panic expecting something different: this is an error.

    // Log a success if no exception is thrown
    try {
    // Some code that might throw an exception
    } catch (const std::runtime_error& error) {
    // Handle exception
    }
    logln::PrintErrorOrSuccess("trying to do something", nullptr, 5, false);
    // Output: 2006/01/02 15:04:05 DEBUG Success trying to do something.

    // Close the log file
    logln::Close();

    return 0;
}
```

## Log Levels

The following log levels are available:

- `0`: INFO
- `1`: WARNING
- `2`: ERROR
- `3`: FATAL
- `4`: PANIC
- `5`: DEBUG

## Functions

### `Init()`

Initializes the log file with a default filename based on the current date and time.

### `CustomInit(const std::string& filePath)`

Initializes the log file with the specified file path.

### `Close()`

Closes the log file.

### `Logln(const std::string& line, int level, bool isSilent)`

Logs a message with the given level and message.

- `line`: The message to log.
- `level`: The log level.
- `isSilent`: Whether to suppress the message from the console output.

### `Printf(const std::string& text, int level, bool isSilent)`

Logs a message without appending a newline.

- `text`: The message to log.
- `level`: The log level.
- `isSilent`: Whether to suppress the message from the console output.

### `ManualLogf(const std::string& text, int level, bool isSilent)`

Logs a message without appending a newline and without the date and time prefix.

- `text`: The message to log.
- `level`: The log level.
- `isSilent`: Whether to suppress the message from the console output.

### `PrintWarningOrSuccessIfNotOk(bool ok, const std::string& msg, int successLevel, bool isSuccessSilent)`

Logs a warning message if `ok` is false, otherwise logs a success message.

- `ok`: The condition to check.
- `msg`: The message to log.
- `successLevel`: The log level for the success message.
- `isSuccessSilent`: Whether to suppress the success message from the console output.

### `PrintErrorOrSuccessIfNotOk(bool ok, const std::string& msg, int successLevel, bool isSuccessSilent)`

Logs an error message if `ok` is false, otherwise logs a success message.

- `ok`: The condition to check.
- `msg`: The message to log.
- `successLevel`: The log level for the success message.
- `isSuccessSilent`: Whether to suppress the success message from the console output.

### `PrintFatalOrSuccessIfNotOk(bool ok, const std::string& msg, int successLevel, bool isSuccessSilent)`

Logs a fatal error message if `ok` is false and exits, otherwise logs a success message.

- `ok`: The condition to check.
- `msg`: The message to log.
- `successLevel`: The log level for the success message.
- `isSuccessSilent`: Whether to suppress the success message from the console output.

### `PrintPanicOrSuccessIfNotOk(bool ok, const std::string& msg, int successLevel, bool isSuccessSilent)`

Throws a `std::runtime_error` if `ok` is false, otherwise logs a success message.

- `ok`: The condition to check.
- `msg`: The message to log.
- `successLevel`: The log level for the success message.
- `isSuccessSilent`: Whether to suppress the success message from the console output.

### `PrintWarningOrSuccess(const std::string& msg, const std::exception* err, int successLevel, bool isSuccessSilent)`

Logs a warning message if `err` is not null, otherwise logs a success message.

- `msg`: The message to log.
- `err`: The exception to check.
- `successLevel`: The log level for the success message.
- `isSuccessSilent`: Whether to suppress the success message from the console output.

### `PrintErrorOrSuccess(const std::string& msg, const std::exception* err, int successLevel, bool isSuccessSilent)`

Logs an error message if `err` is not null, otherwise logs a success message.

- `msg`: The message to log.
- `err`: The exception to check.
- `successLevel`: The log level for the success message.
- `isSuccessSilent`: Whether to suppress the success message from the console output.

### `PrintFatalOrSuccess(const std::string& msg, const std::exception* err, int successLevel, bool isSuccessSilent)`

Logs a fatal error message if `err` is not null and exits, otherwise logs a success message.

- `msg`: The message to log.
- `err`: The exception to check.
- `successLevel`: The log level for the success message.
- `isSuccessSilent`: Whether to suppress the success message from the console output.

### `PrintPanicOrSuccess(const std::string& msg, const std::exception* err, int successLevel, bool isSuccessSilent)`

Throws a `std::runtime_error` if `err` is not null, otherwise logs a success message.

- `msg`: The message to log.
- `err`: The exception to check.
- `successLevel`: The log level for the success message.
- `isSuccessSilent`: Whether to suppress the success message from the console output.

## License

This library is licensed under the MIT License.