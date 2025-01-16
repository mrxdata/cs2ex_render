#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>

class Timer {
public:
    Timer() {
        start();
    }

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
        is_running = true;
    }

    void stop() {
        if (is_running) {
            end_time = std::chrono::high_resolution_clock::now();
            is_running = false;
        }
    }

    void restart() {
        start();
    }

    template<typename Duration = std::chrono::milliseconds>
    void print_duration(const std::string& unit = "ms") const {
        auto duration = is_running
            ? std::chrono::high_resolution_clock::now() - start_time
            : end_time - start_time;

        std::cout << std::chrono::duration_cast<Duration>(duration).count()
            << " " << unit << ".\n";
    }

    const char* return_duration(const char* unit = "ms") {
        static char buffer[100];
        auto duration = is_running
            ? std::chrono::high_resolution_clock::now() - start_time
            : end_time - start_time;

        if (std::string(unit) == "ms") {
            snprintf(buffer, sizeof(buffer), "%.3f ms",
                std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() / 1.0);
        }
        else if (std::string(unit) == "s") {
            snprintf(buffer, sizeof(buffer), "%.3f s",
                std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / 1'000'000.0);
        }
        else if (std::string(unit) == "us") {
            snprintf(buffer, sizeof(buffer), "%.3f us",
                std::chrono::duration_cast<std::chrono::microseconds>(duration).count() / 1.0);
        }
        else {
            snprintf(buffer, sizeof(buffer), "Unsupported unit");
        }

        return buffer;
    }


private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    bool is_running = false;
};

#endif // TIMER_H
