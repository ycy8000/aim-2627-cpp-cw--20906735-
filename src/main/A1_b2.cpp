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

// Assessment 01 B2; see 题面.pdf.
namespace aim::b2 {


// BEGIN IMPLEMENTATION
// 双指针原地稳定压缩：read 顺序扫描，命中 [low,high] 的值写到 write 位置。
// write<=read 始终成立，所以写入只覆盖已经读过的元素，不会破坏未读数据。O(n) 时间、O(1) 空间。
std::size_t compact(int* data, std::size_t n, int low, int high) {
    if (n == 0 || data == nullptr || low > high) {
        return 0;
    }
    std::size_t write = 0;
    for (std::size_t read = 0; read < n; ++read) {
        const int value = data[read];
        if (value >= low && value <= high) {
            data[write] = value;
            ++write;
        }
    }
    return write;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::b2;
int main() {
    try {
        { int a[] = {-1,2,0,9}; std::size_t n=compact(a,4,0,2); CHECK(n==2 && a[0]==2 && a[1]==0); }
        { CHECK(compact(nullptr,0,0,1)==0); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
