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

void saveToFile(const std::vector<double>& X, const std::vector<double>& u, const std::string& path){

    std::ofstream file(path);

    file << std::fixed << std::setprecision(10);
    file << "X,u," << X.size() << "\n";

    for (int i = 0; i < X.size(); i++){
        file << X[i] << "," << u[i] << "\n";
    }

    file.close();
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

void relativeError(
    const std::vector<double>& X,
    const std::vector<double> & u_numerical,
    const std::string& path
){

    std::vector<double> rel_err(X.size(),0);

    for(int i = 1; i < X.size()-1; i++){
        rel_err[i] = log10(abs(u(X[i]) - u_numerical[X[i]]));
    }

    saveToFile(X, rel_err, path);
}


int main(){

    std::vector<int> N({10, 100, 1000});
    double L = 1.0;

    double diag = 2;
    double offdiag = -1;

    std::vector<double>X_analytical;

    for(int i = 0; i < N.size(); i++){
        std::vector<double> X(N[i],0);
        double dx = L/N[i];

        for (int j = 0; j < N[i]; j++){
            X[j] = j*dx;
        }

        arma::mat A = tridiagonalMatrix(X, diag, offdiag);
        std::vector<double> fd = discretizedf(X);
        std::vector<double>u_numerical = thomasAlgorithm(X, fd, A);

        saveToFile(X, u_numerical, "data/data_numerical" + std::to_string(N[i]) + ".csv");
        relativeError(X, u_numerical, "data/rel_error" + std::to_string(N[i]) + ".csv");

        if (i == N.size()-1){
            X_analytical = X;
        }
    }

    std::vector<double>u_analytic = analyticalSolver(X_analytical);
    saveToFile(X_analytical, u_analytic, "data_exact.csv");


    return 0;
}

