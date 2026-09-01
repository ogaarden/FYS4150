#pragma once

#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>

void saveToFile(const std::vector<double>& X, const std::vector<double>& u, const std::string& path){

    std::ofstream file(path);

    file << std::fixed << std::setprecision(10);
    file << "X,u," << X.size() << "\n";

    for (int i = 0; i < X.size(); i++){
        file << X[i] << "," << u[i] << "\n";
    }

    file.close();
}