#include "DtClock.hpp"

Y65535::DtClock::DtClock()
    : then(Clock::now()) {
}

float Y65535::DtClock::dt() {
    auto now = Clock::now();
    auto dt = now - then;
    then = now;

    namespace C = std::chrono;
    return C::duration_cast<C::nanoseconds>(dt).count() / 1e9f;
}
