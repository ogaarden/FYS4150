#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <armadillo>
#include <iomanip>
#include "solver.hpp"
#include "io.cpp"


int main(){

    std::vector<int> N({10, 100, 1000});
    std::vector<std::string> path();
    

    

    double diag = 2;
    double offdiag = -1;
    double start_point = 0;
    double end_point = 1; //From the problem itself

    std::vector<double> X;

    for(int i = 0; i< N.size(); i++){

        std::vector<double> X(N[i],0);
        double dx = (end_point - start_point)/N[i];

        for (int j = 1;j  < X.size(); j++){
            X[j+1] = j*dx;
        }

        std::vector<double> fd = discretizedf(X);
        arma::mat A = tridiagonalMatrix(X, diag, offdiag);
        std::vector<double> u_numerical = thomasAlgorithm(X, fd, A);

        absErr = absoluteError(X, u_numerical, "absolute_error" + std::to_string(N[i]));

    }

    std::vector<double> u_analytical = analyticalSolver(X);


    
}

