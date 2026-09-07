#pragma once

#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>

struct Data{
    std::string name;
    std::vector<double> data;
};

void saveToFile(
    const std::vector<Data>&data,
    const std::string& path,
    const int precision
);
