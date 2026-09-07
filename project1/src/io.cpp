#include "io.hpp"
#include <fstream>
#include <iomanip>
#include <algorithm>

void saveToFile(const std::vector<Data>& data, const std::string& path, const int precision) {
    std::ofstream file(path);
    if (!file.is_open()) return;

    file << std::fixed << std::setprecision(precision);

    for (size_t i = 0; i < data.size(); ++i) {
        file << data[i].name << (i + 1 < data.size() ? "," : "");
    }
    file << "\n";

    size_t maxRows = 0;
    for (const auto& col : data) {
        maxRows = std::max(maxRows, col.data.size());
    }

    for (size_t r = 0; r < maxRows; ++r) {
        for (size_t c = 0; c < data.size(); ++c) {
            if (r < data[c].data.size()) {
                file << data[c].data[r];
            }
            file << (c + 1 < data.size() ? "," : "");
        }
        file << "\n";
    }

    file.close();
}