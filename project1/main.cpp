#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <armadillo>
#include <iomanip>
#include "solver.hpp"
#include "io.hpp"

void analyticalSolution(){

    int N = 1000;
    std::vector<double>X(N+1,0);

    double h = 1.0/N; // IN our problem, we have x in [0,1]

    for(int i = 1; i < N+1; i++){
        X[i] = h*i;
    }

    std::vector<double> u_analytical = analyticalSolver(X);

    saveToFile({
        {"X" , X}, 
        {"u" , u_analytical},
    }, "data/analytical_solution.csv", 5);
}



int main(){

    //For problem 2
    analyticalSolution();

    std::vector<int> N({10, 100, 1000});
    
    std::string data_path = "data/";
    
    double diag = 2;
    double offdiag = -1;
    double start_point = 0;
    double end_point = 1; //From the problem itself

    std::vector<double> X;

    for(int i = 0; i < N.size(); i++){

        std::vector<double> X(N[i],0);
        double h = (end_point - start_point)/N[i];

        for (int j = 1;j  < N[i]+1; j++){
            X[j] = j*h;
        }

        std::vector<double> fd = discretizedf(X);

        arma::mat A = tridiagonalMatrix(X, diag, offdiag);
        std::vector<double> u_numerical = thomasAlgorithm(X, fd, A);


        saveToFile({
            {"X" , X},
            {"U", u_numerical}
        }, data_path + "numerical_solotion" + std::to_string(N[i]) + ".csv", 4);

        std::vector<double> absErr = absoluteError(X, u_numerical);
        saveToFile({
            {"X" , X},
            { "absolute_error" , absErr}
        }, data_path + "absolute_error" + std::to_string(N[i]) + ".csv", 4);

        std::vector<double> relErr = relativeError(X, u_numerical);
        saveToFile({
            {"X", X},
            {"relative_error", relErr}
        }, data_path + "relative_error" + std::to_string(N[i]) + ".csv", 4);
    }   

    

    return 0;
    
}

