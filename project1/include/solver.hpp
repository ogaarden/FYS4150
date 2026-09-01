#pragma once

#include <vector>
#include <armadillo>

double f(double x);
double u(double x);

std::vector<double> analyticalSolver(
    const std::vector<double>& X
);

std::vector<double> discretizedf(
    const std::vector<double>& X
);

arma::mat tridiagonalMatrix(
    const std::vector<double>& X,
    double diag,
    double offdiag
);

std::vector<double> thomasAlgorithm(
    const std::vector<double>& X,
    std::vector<double> fd,
    arma::mat& A
);

std::vector<double> relativeError(
    const std::vector<double>& X,
    const std::vector<double>& u_numerical
);