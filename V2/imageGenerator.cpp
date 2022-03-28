#include <complex>
#include <fstream>
#include <iostream>
#include <list>
#include "include/progressbar.hpp"
using namespace std;
using namespace std::complex_literals;

typedef complex<double> cpx;
double INF = 1e9;
double dx = 1e-9;

cpx a = cpx(1, 0);
list<cpx> roots = {cpx(1, 0), cpx(-0.5, (sqrt(3) / 2)),
                   cpx(-0.5, -(sqrt(3) / 2))};

// The main polynomial P(z)
cpx p(cpx z) {
  cpx val = a;
  for (cpx root : roots) {
    val *= (z - root);
  }
  return val;
}

// Derivative of P(z)
cpx pPrime(cpx z) { return (p(z + dx) - p(z)) / dx; }

// Returns a Newton Approximation for the roots after a specified number of
// iterations
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
    double dist =
        pow(z.real() - root.real(), 2) + pow(z.imag() - root.imag(), 2);
    if (dist < best) {
      best = dist;
      bestRoot = index;
    }
    index++;
  }

  return bestRoot;
}

// Main loop to calculate set sized image array
void calculateImgPlot(int radius, int pixels, int numIterations,
                      string fileName) {
  double interval = 2 * double(radius) / double(pixels);

  list<double> x, y;
  for (double i = -radius; i <= radius; i += interval) {
    x.push_back(interval * i);
    y.push_back(interval * i);
  }

  ofstream dataFile;
  dataFile.open(fileName, ofstream::out | ofstream::trunc);
  dataFile << radius << ',';
  dataFile << pixels << ',';
  dataFile << numIterations << '\n';
  for (cpx root : roots) dataFile << root.real() << ',' << root.imag() << ',';
  dataFile << '\n';

  int counter = 1;
  progressbar bar(pixels);
  for (double b : y) {
    bar.update();
    for (double a : x) {
      cpx z(a, b);
      dataFile << closestRoot(newtonApprox(z, numIterations)) << ',';
    }
    dataFile << '\n';

    //if (counter % 100 == 0) cout << counter << " Rows Done...\n";
    counter++;
  }

  dataFile.close();
}

int main() {
<<<<<<< HEAD
  int radius, pixels, numIterations;
  string fileName;
  cout << "Radius: ";
  cin >> radius;
  cout << "\nPixels: ";
  cin >> pixels;
  cout << "\nIterations: ";
  cin >> numIterations;
  cout << "\nFile name to write to: ";
  cin >> fileName;
  cout << '\n';
  calculateImgPlot(radius, pixels, numIterations, fileName);
  cout << "\nRender complete!";
}
=======
    int radius, pixels, numIterations;
    string fileName;
    cout << "Radius: ";
    cin >> radius;
    cout << "\nPixels: ";
    cin >> pixels;
    cout << "\nIterations: ";
    cin >> numIterations;
    cout << "\nFile name to write to (MUST END WITH .csv): ";
    cin >> fileName;
    cout << '\n';
    calculateImgPlot(radius, pixels, numIterations, fileName);
    cout << "\nRender complete!";
}
>>>>>>> d410ffdcc8197784d5d97a74b30bd750390f74f6
