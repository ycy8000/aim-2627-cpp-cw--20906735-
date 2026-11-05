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

// Assessment 01 Q6; see 题面.pdf.
namespace aim::q6 {
struct Target { int id; int x; int y; int hp; bool visible; };

// BEGIN IMPLEMENTATION
// 坐标绝对值 <=1e6，平方和 <=2e12，必须用 long long。
long long squared_distance(const Target& t) {
    const long long x = t.x;
    const long long y = t.y;
    return x * x + y * y;
}

// 字典序优先级：hp 小优先，其次距离平方小，最后 id 小。
bool better_target(const Target& a, long long a_dist, const Target& b, long long b_dist) {
    if (a.hp != b.hp) {
        return a.hp < b.hp;
    }
    if (a_dist != b_dist) {
        return a_dist < b_dist;
    }
    return a.id < b.id;
}

int select_target(const std::vector<Target>& targets, int max_range) {
    if (max_range < 0) {
        return -1;
    }
    const long long range = max_range;
    const long long range_sq = range * range;

    const Target* best = nullptr;
    long long best_dist = 0;
    for (const Target& t : targets) {
        if (!t.visible || t.hp <= 0) {
            continue;
        }
        const long long dist = squared_distance(t);
        if (dist > range_sq) {
            continue;  // 边界 dist==range_sq 合格
        }
        if (best == nullptr || better_target(t, dist, *best, best_dist)) {
            best = &t;
            best_dist = dist;
        }
    }
    return best == nullptr ? -1 : best->id;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q6;
int main() {
    try {
        { CHECK(select_target({{7,3,4,20,true},{2,0,5,20,true}},5)==2); }
        { CHECK(select_target({},5)==-1); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
