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

// Assessment 01 Q2; see 题面.pdf.
namespace aim::q2 {
struct LabelEdit { std::string from; std::string to; };

// BEGIN IMPLEMENTATION
// 在当前文本中查找第一个与 label 完全相等的字段，返回其起始下标；找不到返回 npos。
// 按逗号逐字段比较，因此 "cam" 不会匹配 "cam2"。
std::size_t find_label(const std::string& labels, const std::string& label) {
    if (labels.empty()) {
        return std::string::npos;
    }
    std::size_t start = 0;
    while (true) {
        const std::size_t comma = labels.find(',', start);
        const std::size_t end = (comma == std::string::npos) ? labels.size() : comma;
        if (labels.compare(start, end - start, label) == 0) {
            return start;
        }
        if (comma == std::string::npos) {
            return std::string::npos;
        }
        start = comma + 1;
    }
}

std::string edit_labels(std::string labels, const std::vector<LabelEdit>& edits) {
    for (const LabelEdit& edit : edits) {
        if (edit.from.empty()) {
            // 追加：列表非空时才补逗号；from/to 都为空则什么也不做。
            if (!edit.to.empty()) {
                if (!labels.empty()) {
                    labels += ',';
                }
                labels += edit.to;
            }
            continue;
        }

        // 每次都在上一步的结果上重新查找，不缓存位置。
        const std::size_t pos = find_label(labels, edit.from);
        if (pos == std::string::npos) {
            continue;
        }
        const std::size_t len = edit.from.size();
        if (!edit.to.empty()) {
            labels.replace(pos, len, edit.to);
        } else if (pos + len < labels.size()) {
            labels.erase(pos, len + 1);      // 非最后一个：连同后面的逗号删除
        } else if (pos > 0) {
            labels.erase(pos - 1, len + 1);  // 最后一个：连同前面的逗号删除
        } else {
            labels.clear();                  // 唯一的标签
        }
    }
    return labels;
}
// END IMPLEMENTATION
}

#define CHECK(...) do { if (!(__VA_ARGS__)) throw std::runtime_error("check failed"); } while(false)
#define EXPECT_INVALID(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::invalid_argument&) { caught=true; } CHECK(caught); } while(false)
#define EXPECT_RANGE(...) do { bool caught=false; try { (void)(__VA_ARGS__); } catch(const std::out_of_range&) { caught=true; } CHECK(caught); } while(false)

using namespace aim::q2;
int main() {
    try {
        { CHECK(edit_labels("cam,imu,radar",{{"imu","gyro"},{"cam",""},{"","lidar"}})=="gyro,radar,lidar"); }
        { CHECK(edit_labels("cam,cam2,cam",{{"cam","camera"},{"cam",""}})=="camera,cam2"); }
        std::cout << "PUBLIC 2/2\n";
    } catch(const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}
