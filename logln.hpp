#ifndef LOGLN_H
#define LOGLN_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <stdexcept>

namespace logln
{
    void Init();
    void CustomInit(const std::string &filePath);
    void Close();
    std::string getDateStringLogFmt();
    std::string getDateStringFileFmt();
    std::string levelStr(int level);
    void PrintWarningOrSuccessIfNotOk(bool ok, const std::string &msg, int successLevel, bool isSuccessSilent);
    void PrintErrorOrSuccessIfNotOk(bool ok, const std::string &msg, int successLevel, bool isSuccessSilent);
    void PrintFatalOrSuccessIfNotOk(bool ok, const std::string &msg, int successLevel, bool isSuccessSilent);
    void PrintPanicOrSuccessIfNotOk(bool ok, const std::string &msg, int successLevel, bool isSuccessSilent);
    void PrintWarningOrSuccess(const std::string &msg, const std::exception *err, int successLevel, bool isSuccessSilent);
    void PrintErrorOrSuccess(const std::string &msg, const std::exception *err, int successLevel, bool isSuccessSilent);
    void PrintPanicOrSuccess(const std::string &msg, const std::exception *err, int successLevel, bool isSuccessSilent);
    void PrintFatalOrSuccess(const std::string &msg, const std::exception *err, int successLevel, bool isSuccessSilent);
    void errorIfNotOk(bool ok, const std::string &msg);
    void warnIfNotOk(bool ok, const std::string &msg);
    void fatalIfNotOk(bool ok, const std::string &msg);
    void panicIfNotOk(bool ok, const std::string &msg);
    void warningWithError(const std::string &msg, const std::exception *err);
    void warning(const std::string &msg, const std::exception *err);
    void printError(const std::string &msg, const std::exception *err);
    void fatalError(const std::string &msg, const std::exception *err);
    void panicError(const std::string &msg, const std::exception *err);
    void errorIfNotFalse(bool b, const std::string &msg);
    void warnIfNotFalse(bool b, const std::string &msg);
    void fatalIfNotFalse(bool b, const std::string &msg);
    void panicIfNotFalse(bool b, const std::string &msg);
    void printSuccess(const std::string &msg, int successLevel, bool isSilent);
    void ManualLogf(const std::string &text, int level, bool isSilent);
    void StartManualLogf(const std::string &text, int level, bool isSilent);
    void Printf(const std::string &text, int level, bool isSilent);
    void Logln(const std::string &line, int level, bool isSilent);

    // defaultLogFileName  is initialized with the current date and time in the format YYYY_MM_DD-HH_mm_SS.log
    inline std::string defaultLogFileName()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y_%m_%d-%H_%M_%S.log");
        return ss.str();
    }

    static std::string defaultLogFileName_ = defaultLogFileName();

    // logFile is a pointer to the log file. It is initialized to nil and is set to the opened log file in the Init function.
    static std::ofstream *logFile_ = nullptr;

    // Init initializes the log file by creating and opening defaultLogFileName
    inline void Init()
    {
        CustomInit(defaultLogFileName_);
    }

    // CustomInit initializes the log file by opening the file at provided path. If the file does not exist, it is created.
    inline void CustomInit(const std::string &filePath)
    {
        logFile_ = new std::ofstream(filePath, std::ios::app);
        if (!logFile_->is_open())
        {
            std::cerr << "Error opening log file: " << filePath << std::endl;
            exit(1);
        }
    }

    // Close closes the log file
    inline void Close()
    {
        if (logFile_ != nullptr)
        {
            logFile_->close();
            delete logFile_;
            logFile_ = nullptr;
        }
    }

    // getDateStringLogFmt returns the current date and time in the format YYYY/MM/DD HH:mm:SS
    inline std::string getDateStringLogFmt()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y/%m/%d %H:%M:%S");
        return ss.str();
    }

    // getDateStringFileFmt returns the current date and time in the format YYYY_MM_DD-HH_mm_SS
    inline std::string getDateStringFileFmt()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y_%m_%d-%H_%M_%S");
        return ss.str();
    }

    // levelStr returns a string representation of the log level based on the provided integer.
    // It takes an integer 'level' as input and returns a string representing the log level.
    // The function uses a switch statement to map the integer values to their corresponding string representations.
    // If the input integer does not match any of the cases, an empty string is returned.
    inline std::string levelStr(int level)
    {
        switch (level)
        {
        case 0:
            return "INFO"; // If the level is 0, return "INFO"
        case 1:
            return "WARNING"; // If the level is 1, return "WARNING"
        case 2:
            return "ERROR"; // If the level is 2, return "ERROR"
        case 3:
            return "FATAL"; // If the level is 3, return "FATAL"
        case 4:
            return "PANIC"; // If the level is 4, return "PANIC"
        case 5:
            return "DEBUG"; // If the level is 5, return "DEBUG"
        default:
            return ""; // If the level does not match any case, return an empty string
        }
    }

    // PrintWarningOrSuccessIfNotOk logs an error message if the 'ok' parameter is false,
    // otherwise logs a success message.
    inline void PrintWarningOrSuccessIfNotOk(bool ok, const std::string &msg, int successLevel, bool isSuccessSilent)
    {
        if (!ok)
        {
            warnIfNotOk(ok, msg);
        }
        else
        {
            printSuccess(msg, successLevel, isSuccessSilent);
        }
    }

    // PrintErrorOrSuccessIfNotOk logs an error message if the 'ok' parameter is false,
    // otherwise logs a success message.
    inline void PrintErrorOrSuccessIfNotOk(bool ok, const std::string &msg, int successLevel, bool isSuccessSilent)
    {
        if (!ok)
        {
            errorIfNotFalse(ok, msg);
        }
        else
        {
            printSuccess(msg, successLevel, isSuccessSilent);
        }
    }

    // PrintFatalOrSuccessIfNotOk logs a fatal error message if the 'ok' parameter is false,
    // otherwise logs a success message. If a fatal error is logged, the program will exit with status code 1.
    inline void PrintFatalOrSuccessIfNotOk(bool ok, const std::string &msg, int successLevel, bool isSuccessSilent)
    {
        if (!ok)
        {
            fatalIfNotFalse(ok, msg);
        }
        else
        {
            printSuccess(msg, successLevel, isSuccessSilent);
        }
    }

    // PrintPanicOrSuccessIfNotOk logs a panic message if the 'ok' parameter is false,
    // otherwise logs a success message. If a panic is logged, the program will crash.
    inline void PrintPanicOrSuccessIfNotOk(bool ok, const std::string &msg, int successLevel, bool isSuccessSilent)
    {
        if (!ok)
        {
            panicIfNotFalse(ok, msg);
        }
        else
        {
            printSuccess(msg, successLevel, isSuccessSilent);
        }
    }

    // PrintWarningOrSuccess logs a warning message if the 'err' parameter is not nil,
    // otherwise logs a success message.
    inline void PrintWarningOrSuccess(const std::string &msg, const std::exception *err, int successLevel, bool isSuccessSilent)
    {
        if (err != nullptr)
        {
            warningWithError(msg, err);
        }
        else
        {
            printSuccess(msg, successLevel, isSuccessSilent);
        }
    }

    // PrintErrorOrSuccess logs an error message if the 'err' parameter is not nil,
    // otherwise logs a success message.
    inline void PrintErrorOrSuccess(const std::string &msg, const std::exception *err, int successLevel, bool isSuccessSilent)
    {
        if (err != nullptr)
        {
            printError(msg, err);
        }
        else
        {
            printSuccess(msg, successLevel, isSuccessSilent);
        }
    }

    // PrintPanicOrSuccess logs a panic message if the 'err' parameter is not nil,
    // otherwise logs a success message. If a panic is logged, the program will crash.
    inline void PrintPanicOrSuccess(const std::string &msg, const std::exception *err, int successLevel, bool isSuccessSilent)
    {
        if (err != nullptr)
        {
            panicError(msg, err);
        }
        else
        {
            printSuccess(msg, successLevel, isSuccessSilent);
        }
    }

    // PrintFatalOrSuccess logs a fatal error message if the 'err' parameter is not nil,
    // otherwise logs a success message. If a fatal error is logged, the program will exit with status code 1.
    inline void PrintFatalOrSuccess(const std::string &msg, const std::exception *err, int successLevel, bool isSuccessSilent)
    {
        if (err != nullptr)
        {
            fatalError(msg, err);
        }
        else
        {
            printSuccess(msg, successLevel, isSuccessSilent);
        }
    }

    // errorIfNotOk logs an error message if the 'ok' parameter is false.
    inline void errorIfNotOk(bool ok, const std::string &msg)
    {
        errorIfNotFalse(ok, msg);
    }

    // warnIfNotOk logs a warning message if the 'ok' parameter is false.
    inline void warnIfNotOk(bool ok, const std::string &msg)
    {
        warnIfNotFalse(ok, msg);
    }

    // fatalIfNotOk logs a fatal error message if the 'ok' parameter is false.
    // The program will exit with status code 1.
    inline void fatalIfNotOk(bool ok, const std::string &msg)
    {
        fatalIfNotFalse(ok, msg);
    }

    // panicIfNotOk logs a panic message if the 'ok' parameter is false.
    // The program will then panic
    inline void panicIfNotOk(bool ok, const std::string &msg)
    {
        panicIfNotFalse(ok, msg);
    }

    // warningWithError logs a warning message with the given message and error.
    inline void warningWithError(const std::string &msg, const std::exception *err)
    {
        Logln(msg + ": " + err->what(), 1, false);
    }

    // warning logs a simple warning message with the given message.
    inline void warning(const std::string &msg, const std::exception *err)
    {
        Logln(msg + ": " + err->what(), 1, false);
    }

    // printError logs an error message with the given message and error.
    inline void printError(const std::string &msg, const std::exception *err)
    {
        Logln("Error occurred " + msg + ": " + err->what(), 2, false);
    }

    // fatalError logs a fatal error message with the given message and error,
    // then exits the program with status code 1.
    inline void fatalError(const std::string &msg, const std::exception *err)
    {
        Logln("Fatal error encountered " + msg + ": " + err->what(), 3, false);
        exit(1);
    }

    // panicError logs a panic message with the given message and error.
    // The program will crash.
    inline void panicError(const std::string &msg, const std::exception *err)
    {
        Logln("Panic " + msg + ": " + err->what(), 4, false);
        throw std::runtime_error("Panic " + msg + ": " + err->what());
    }

    // errorIfNotFalse logs an error message if the 'b' parameter is false.
    inline void errorIfNotFalse(bool b, const std::string &msg)
    {
        if (!b)
        {
            Logln("Error occurred " + msg + ": " + (b ? "true" : "false"), 2, false);
        }
    }

    // warnIfNotFalse logs a warning message if the 'b' parameter is false.
    inline void warnIfNotFalse(bool b, const std::string &msg)
    {
        if (!b)
        {
            Logln(msg + ": " + (b ? "true" : "false"), 1, false);
        }
    }

    // fatalIfNotFalse logs a fatal error message if the 'b' parameter is false.
    // The program will exit with status code 1.
    inline void fatalIfNotFalse(bool b, const std::string &msg)
    {
        if (!b)
        {
            Logln("Fatal error occurred " + msg + ": " + (b ? "true" : "false"), 3, false);
            exit(1);
        }
    }

    // panicIfNotFalse logs a panic message if the 'b' parameter is false.
    // The program will crash.
    inline void panicIfNotFalse(bool b, const std::string &msg)
    {
        if (!b)
        {
            Logln("Panic " + msg + ": " + (b ? "true" : "false"), 4, false);
            throw std::runtime_error("Panic " + msg + ": " + (b ? "true" : "false"));
        }
    }

    // printSuccess logs a success message with the given message, level, and silent flag.
    inline void printSuccess(const std::string &msg, int successLevel, bool isSilent)
    {
        Logln("Success " + msg + ".", successLevel, isSilent);
    }

    // ManualLogf writes the given text to the console and appends it to the log file. It doesn't append a newline to the provided string.
    inline void ManualLogf(const std::string &text, int level, bool isSilent)
    {
        if (!isSilent)
        {
            std::cout << text;
        }
        if (logFile_ != nullptr)
        {
            *logFile_ << text;
        }
    }

    // StartManualLogf writes the given text to the console and appends it to the log file with the current date and time. It doesn't append a newline to the provided string.
    inline void StartManualLogf(const std::string &text, int level, bool isSilent)
    {
        std::string levelStr_ = levelStr(level);

        std::string date = getDateStringLogFmt();
        std::string msg = "";
        if (!levelStr_.empty())
        {
            msg = date + " " + levelStr_ + " " + text;
        }
        else
        {
            msg = date + " " + text;
        }

        if (!isSilent)
        {
            std::cout << msg;
        }
        if (logFile_ != nullptr)
        {
            *logFile_ << msg;
        }
    }

    // Printf writes the given text to the console and appends it to the log file. It doesn't append a newline to the provided string.
    inline void Printf(const std::string &text, int level, bool isSilent)
    {
        if (!isSilent)
        {
            std::cout << text;
        }
        if (logFile_ != nullptr)
        {
            *logFile_ << text;
        }
    }

    // Logln writes the given line to the console and appends it to the log file with the current date and time. It appends a newline to the provided string.
    inline void Logln(const std::string &line, int level, bool isSilent)
    {
        // Get the level string based on the level integer
        std::string levelStr_ = levelStr(level);
        // Get the current date and time in the format YYYY/MM/DD HH:mm:SS
        std::string date = getDateStringLogFmt();
        // Initialize an empty string for the message
        std::string msg = "";

        // If the level string is not empty, include it in the message
        if (!levelStr_.empty())
        {
            msg = date + " " + levelStr_ + " " + line;
        }
        else
        {
            // If the level string is empty, do not include it in the message
            msg = date + " " + line;
        }

        // If the log is not silent
        if (!isSilent)
        {
            // Print the line to the console
            std::cout << msg << std::endl;
        }

        // If the log file is not nil
        if (logFile_ != nullptr)
        {
            // Write the message to the log file, appending a newline
            *logFile_ << msg << std::endl;
        }
    }
}
#endif // LOGLN_H
