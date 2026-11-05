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

// Assessment 01 Q7; see 题面.pdf.
namespace aim::q7 {
struct FireResult { int shots; int rejected; int ammo; int heat; };

// BEGIN IMPLEMENTATION
// 每帧顺序：先冷却，再处理请求。0 只冷却；1 在有弹且冷却后热量+shot_heat<=100 时开火。
// 拒绝只增加 rejected，不消耗弹药、不加热量。
FireResult simulate(int ammo, int heat, int cool, int shot_heat, const std::vector<int>& requests) {
    FireResult result{0, 0, ammo, heat};
    for (int request : requests) {
        result.heat = std::max(0, result.heat - cool);
        if (request != 1) {
            continue;
        }
        if (result.ammo > 0 && result.heat + shot_heat <= 100) {
            --result.ammo;
            result.heat += shot_heat;
            ++result.shots;
        } else {
            ++result.rejected;
        }
    }
    return result;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q7;
int main() {
    try {
        { aim::q7::FireResult r=simulate(2,90,10,20,{1,1,1}); CHECK(r.shots==2 && r.rejected==1 && r.ammo==0 && r.heat==100); }
        { aim::q7::FireResult r=simulate(3,100,20,10,{0}); CHECK(r.heat==80 && r.rejected==0 && r.ammo==3); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
