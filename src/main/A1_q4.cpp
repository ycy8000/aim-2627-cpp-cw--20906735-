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

// Assessment 01 Q4; see 题面.pdf.
namespace aim::q4 {
struct CommandResult { long long value; int accepted; int rejected; };

// BEGIN IMPLEMENTATION
const long long kValueLimit = 1000000;

bool in_value_range(long long x) {
    return x >= -kValueLimit && x <= kValueLimit;
}

// 完整校验一条命令；成功时把候选结果写入 candidate 并返回 true，失败返回 false。
// 只计算候选值，不修改累加器，保证事务性。
bool try_command(const std::string& line, long long current, long long& candidate) {
    std::istringstream input(line);
    std::string op;
    if (!(input >> op)) {
        return false;  // 空行或只有空白
    }

    long long next = 0;
    if (op == "RESET") {
        next = 0;
    } else if (op == "ADD" || op == "SET") {
        long long x = 0;
        if (!(input >> x)) {
            return false;  // 缺少参数、非数字或超出 long long
        }
        if (!in_value_range(x)) {
            return false;
        }
        next = (op == "ADD") ? current + x : x;
    } else {
        return false;  // 未知操作（区分大小写）
    }

    std::string extra;
    if (input >> extra) {
        return false;  // 多余字段或 "12x"、"1.5" 这类后缀
    }
    if (!in_value_range(next)) {
        return false;  // 参数合法但结果越界
    }
    candidate = next;
    return true;
}

CommandResult execute(const std::vector<std::string>& lines) {
    CommandResult result{0, 0, 0};
    for (const std::string& line : lines) {
        long long candidate = 0;
        if (try_command(line, result.value, candidate)) {
            result.value = candidate;
            ++result.accepted;
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

using namespace aim::q4;
int main() {
    try {
        { aim::q4::CommandResult r=execute({"ADD 5","SET 8 x","RESET","ADD -2"}); CHECK(r.value==-2 && r.accepted==3 && r.rejected==1); }
        { aim::q4::CommandResult r=execute({}); CHECK(r.value==0 && r.accepted==0 && r.rejected==0); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
