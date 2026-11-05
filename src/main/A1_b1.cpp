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

// Assessment 01 B1; see 题面.pdf.
namespace aim::b1 {


// BEGIN IMPLEMENTATION
// 语法：可选一个 '+'/'-'，后接至少一位 ASCII 数字，不允许任何其他字符。
// 用非负 magnitude 累加，并在乘加之前检查 magnitude*10+digit<=limit；
// limit 正数为 2147483647，负数为 2147483648（上下界不对称）。失败时不写 output。
bool parse_i32(const std::string& text, int& output) {
    std::size_t i = 0;
    bool negative = false;
    if (i < text.size() && (text[i] == '+' || text[i] == '-')) {
        negative = (text[i] == '-');
        ++i;
    }
    if (i == text.size()) {
        return false;  // 空串或只有符号
    }

    const long long limit = negative ? 2147483648LL : 2147483647LL;
    long long magnitude = 0;
    for (; i < text.size(); ++i) {
        const char c = text[i];
        if (c < '0' || c > '9') {
            return false;
        }
        const int digit = c - '0';
        if (magnitude > (limit - digit) / 10) {
            return false;  // 下一步会超出范围，提前拒绝
        }
        magnitude = magnitude * 10 + digit;
    }

    output = static_cast<int>(negative ? -magnitude : magnitude);
    return true;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::b1;
int main() {
    try {
        { int x=9; CHECK(parse_i32("-12",x) && x==-12); }
        { int x=9; CHECK(!parse_i32("12x",x) && x==9); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
