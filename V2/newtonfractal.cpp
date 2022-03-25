#include <complex>
#include <iostream>
#include <fstream>
#include <list>
using namespace std;
using namespace std::complex_literals;

typedef complex<double> cpx;
double INF = 1e9;
double dx = 1e-9;

cpx a = 1.0 + 0.0i;
list<cpx> roots = {1.0 + 0.0i, 0.5 + sqrt(3) / 2, 0.5 - sqrt(3) / 2};

// The main polynomial P(z)
cpx p(cpx z) {
    cpx val = a;
    for (cpx root : roots) {
        val *= (z - root);
    }
    return val;
}

// Derivative of P(z)
cpx pPrime(cpx z) {
    return (p(z + dx) - p(z)) / dx;
}

// Returns a Newton Approximation for the roots after a specified number of iterations
cpx newtonApprox(cpx a0, int numIterations) {
    if (p(a0) == cpx(0, 0)) return a0;

    cpx ai = a0;
    for (int i = 1; i <= numIterations; i++) {
        if (pPrime(ai) == cpx(0, 0)) return ai;
        ai = ai - p(ai) / pPrime(ai);
    }

    return ai;
}

// Finds index of closest root to any complex number z
int closestRoot(cpx z) {
    int index = 0, bestRoot = 0;
    double best = INF;
    for (cpx root : roots) {
        double dist = sqrt(pow(z.real() - root.real(), 2) + pow(z.imag() - root.imag(), 2));
        if (dist < best) {
            best = dist;
            bestRoot = index;
        }
        index++;
    }

    return bestRoot;
}

// Main loop to calculate set sized image array
void calculateImgPlot(int radius, int pixels, int numIterations) {
    double interval = 2 * radius / pixels;
    list<list<int>> image;
    list<double> x, y;
    list<int> line;

    for (double i = 1; i <= pixels; i++) {
        x.push_back(interval * i);
        y.push_back(interval * i);
    }

    for (double b : y) {
        for (double a : x) {
            cpx z(a, b);
            line.push_back(closestRoot(newtonApprox(z, numIterations)));
        }
        image.push_back(line);
        line.clear();
    }

    ofstream dataFile;
    dataFile.open("data.csv")
}

int main() {
    cout << closestRoot(newtonApprox(cpx(1, 2), 5));
}