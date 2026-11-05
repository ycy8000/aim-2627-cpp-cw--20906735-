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

// Assessment 01 Q3; see 题面.pdf.
namespace aim::q3 {


// BEGIN IMPLEMENTATION
// 滑动窗口：维护长度 k 的窗口和，每步加入新值、移出最左值，O(n) 时间、O(1) 额外空间。
// n<=2e5、|value|<=1e9，窗口和最大约 2e14，用 long long。
std::vector<int> alarms(const std::vector<int>& values, int k, long long threshold) {
    std::vector<int> result;
    const std::size_t n = values.size();
    if (k < 1 || static_cast<std::size_t>(k) > n) {
        return result;
    }
    const std::size_t window = static_cast<std::size_t>(k);
    long long sum = 0;
    for (std::size_t i = 0; i < n; ++i) {
        sum += values[i];
        if (i >= window) {
            sum -= values[i - window];
        }
        // i+1>=window 时窗口 [i-k+1, i] 已完整，返回右端下标 i；严格大于才报警。
        if (i + 1 >= window && sum > threshold) {
            result.push_back(static_cast<int>(i));
        }
    }
    return result;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q3;
int main() {
    try {
        { CHECK((alarms({1,2,3,4},2,4)==std::vector<int>{2,3})); }
        { CHECK(alarms({},1,0).empty()); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
