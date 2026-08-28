#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <armadillo>

std::vector<double> analyticalSolver(const std::vector<double>& X){

    int N = X.size();

    std::vector<double> u(N, 0);


    for(int i = 0; i < N; i++){
        u[i] = 1 - 1* (1 - exp(-10)) * X[i] - exp(-10*X[i]);
    }

    return u;
}


// u(n) = (u(n+1) - 2 u(n) - u(n-1)) / (2 * dx)
// 

double f(double x){
    return 100 * exp(-10*x);
}

std::vector<double> numericalSolution(const std::vector<double>& X, const float & dt){
    int N = X.size();

    std::vector<double> u(N, 0);
    u[0] = 0;
    u[u.size()-1] = 0;
    float dx = X[1] - X[0];
    // 2*dt f_i + 2 u(n) - u(n-1) = u(n+1)
    for(int i = 1; i < N; i++){
        u[i+1] = 2*u[i]  - u[i-1] -dx*dx*f(X[i]);
    }

    return u;
}

void saveToFile(const std::vector<double>& X, const std::vector<double>& u, const std::string& filename){

    std::ofstream file(filename);

    file << "X,u\n";

    for (int i = 0; i < X.size(); i++){
        file << X[i] << "," << u[i] << "\n";
    }

    file.close();
}

arma::mat matrix(const std::vector<double>& X){
    int n = X.size();
    arma::mat A = arma::mat(n,n).fill(0.);
    
    A.diag(0).fill(-2.0);
    A.diag(-1).fill(1.0);
    A.diag(1).fill(1.0);


    return A;
}

int main(){

    int N = 1000;
    int T = 1;
    std::vector<double> X(N, 0);

    double dt = static_cast<double>(T) / N;

    for(int i = 0; i < N+1; i++){
        X[i] = i*dt;
    }

    std::vector<double>u_analytic = analyticalSolver(X);
    std::vector<double>u_numerical = numericalSolution(X, dt);


    saveToFile(X, u_analytic, "data_exact.csv");
    saveToFile(X, u_numerical, "data_numerical.csv");


    return 0;
}