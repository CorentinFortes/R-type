//
// Created by erwan on 10/15/23.
//

#ifndef C96F94AE_A938_4661_B473_3EB069770CC8
#define C96F94AE_A938_4661_B473_3EB069770CC8


#include <chrono>
#include <iostream>

class Cooldown {
public:
    Cooldown(std::chrono::milliseconds duration);
    void setDuration(std::chrono::milliseconds duration);
    bool IsReady();
    void Activate();
    void Reset();

private:
    std::chrono::steady_clock::time_point _lastActivation;
    std::chrono::milliseconds _duration;
};


#endif /* C96F94AE_A938_4661_B473_3EB069770CC8 */
