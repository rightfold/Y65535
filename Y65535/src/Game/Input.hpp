#pragma once

namespace Y65535 {
    // User input for this frame.
    class Input {
    public:
        bool strafeUp, strafeDown, strafeLeft, strafeRight;
        float lookDx, lookDy;
        bool shoot;
    };
}
