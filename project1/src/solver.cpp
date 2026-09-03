#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <armadillo>
#include <iomanip>


double f(double x){
    return 100 * exp(-10*x);
}

double u(double x){
    return 1 - 1* (1 - exp(-10)) * x - exp(-10*x);
}

std::vector<double> analyticalSolver(const std::vector<double>& X){

    int N = X.size();

    std::vector<double> u_(N, 0);


    for(int i = 0; i < N; i++){
        u_[i] = u(X[i]);
    }
    return u_;
}

std::vector<double> discretizedf(const std::vector<double>& X){
    std::vector<double>fd (X.size());
    double h = X[1] - X[0];
    for(int i = 0; i < X.size(); i++){
        fd[i] = f(X[i])*h*h;
    }

    return fd;
}

arma::mat tridiagonalMatrix(const std::vector<double>& X, double& diag, double& offdiag){
    int n = X.size();
    arma::mat A = arma::mat(n,n).fill(0.);
    
    A.diag(0).fill(diag);
    A.diag(-1).fill(offdiag);
    A.diag(1).fill(offdiag);

    return A;
}

std::vector<double> thomasAlgorithm(
    const std::vector<double>& X,
    std::vector<double> fd,
    arma::mat& A
){
    int n = X.size();
    std::vector<double> v(n);

    for(int i = 1; i < n; i++){
        double m = A(i, i-1) / A(i-1, i-1);
        A(i,i) -= m * A(i-1,i);
        fd[i] -= m * fd[i-1];
    }

    v[n-1] = fd[n-1] / A(n-1,n-1);

    for (int i = n-2; i>=0; i--){
        v[i] = fd[i] - (A(i,i+1) * v[i+1] / A(i,i));
    }

    return v;
}


std::vector<double> absoluteError(
    const std::vector<double>& X,
    const std::vector<double> & u_numerical,
    const std::string& path
){

    std::vector<double> absErr(X.size(),0);

    for(int i = 1; i < X.size()-1; i++){
        absErr[i] = log10(abs(u(X[i]) - u_numerical[X[i]]));
    }

    return absErr;
}


// UNFINISHED 
std::vector<double> relativeError(
    const std::vector<double>& X,
    const std::vector<double> & u_numerical,
    const std::string& path
){

    std::vector<double> relErr(X.size(), 0);

    for(int i = 1; i < X.size()-1; i++){
        relErr[i] = i;
    }
}