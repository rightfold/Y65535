#pragma once

#include <chrono>

namespace Y65535 {
    // Device for measuring time difference. The time difference is used all
    // over the game as a variable named dt.
    class DtClock {
    public:
        // Initialize the clock.
        DtClock();

        // Get the time difference since construction or the last call to dt,
        // whichever came latest. The time difference is in seconds.
        float dt();

    private:
        using Clock = std::chrono::high_resolution_clock;

        // The previously measured time.
        Clock::time_point then;
    };
}
