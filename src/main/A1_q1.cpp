#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

// Assessment 01 Q1; see 题面.pdf.
namespace aim::q1 {


// BEGIN IMPLEMENTATION
// 健康百分比：max_hp<=0 返回 -1（不做除法）；否则先把 hp 截到 [0,max_hp] 再整数截断。
// |hp|<=1e12，hp*100<=1e14，long long 足够，不用浮点。
long long ratio(long long hp, long long max_hp) {
    if (max_hp <= 0) {
        return -1;
    }
    if (hp < 0) {
        hp = 0;
    } else if (hp > max_hp) {
        hp = max_hp;
    }
    return hp * 100 / max_hp;
}

// 电量先截到 [0,100] 再分档：>=60 OK，20..59 WARNING，<20 LOW。
std::string battery_state(int battery) {
    if (battery >= 60) {
        return "OK";
    }
    if (battery >= 20) {
        return "WARNING";
    }
    return "LOW";
}

std::string report(int id, long long hp, long long max_hp, int battery) {
    const long long percent = ratio(hp, max_hp);
    const std::string hp_field = percent < 0 ? "INVALID" : std::to_string(percent);
    const int bat = std::clamp(battery, 0, 100);
    return "ID=" + std::to_string(id) + ";HP=" + hp_field + ";BAT=" + std::to_string(bat) +
           ";STATE=" + battery_state(bat);
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q1;
int main() {
    try {
        { CHECK(ratio(2,3)==66); }
        { CHECK(report(7,2,3,20)=="ID=7;HP=66;BAT=20;STATE=WARNING"); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
