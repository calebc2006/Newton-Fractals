import numpy as np
import matplotlib.pyplot as plt
import math
from tqdm import tqdm

a = complex(1, 0)
roots = [complex(1, 0), complex(-1/2, math.sqrt(3)/2),
         complex(-1/2, -math.sqrt(3)/2)]
INF = 1e9
DX = 1e-9


def roundComplex(z: complex, precision):
    # real = round(z.real, precision)
    # imag = round(z.imag, precision)
    # return complex(real, imag)
    return z


def p(z: complex):  # of the form a(z-r1)(z-r2)...
    val = a
    for i in range(len(roots)):
        val *= (z - roots[i])
    return roundComplex(val, 8)


def pPrime(z: complex):
    dz = complex(DX, DX)
    return roundComplex((p(z + dz) - p(z)) / dz, 8)


def newtonApproximation(a0: complex, numIterations):
    if (p(a0) == 0):
        return a0
    ai = a0
    for i in range(1, numIterations + 1):
        if (pPrime(ai) == 0):
            return ai
        ai = ai - p(ai) / pPrime(ai)
    return roundComplex(ai, 7)


def closestRootTo(z: complex):
    best = INF
    rootNum = 0
    for i in range(len(roots)):
        root = roots[i]
        dist = math.sqrt((z.real - root.real)**2 + (z.imag - root.imag)**2)
        if dist < best:
            best = dist
            rootNum = i
    return rootNum


def calculateImgPlot(radius, pixels, numIterations):
    x = y = np.linspace(-radius, radius, pixels)
    image = []

    for b in tqdm(y):
        line = []
        for a in x:
            z = complex(a, b)
            line.append(closestRootTo(newtonApproximation(z, numIterations)))

        image.append(line)

    return image


def main():
    radius = int(input("Radius: "))
    pixels = int(input("Pixels: "))
    numIterations = int(input("Iterations: "))
    image = calculateImgPlot(
        radius=radius, pixels=pixels, numIterations=numIterations)
    extent = [-radius, radius, -radius, radius]
    plt.imshow(image, extent=extent)

    rootX = [i.real for i in roots]
    rootY = [i.imag for i in roots]
    plt.scatter(rootX, rootY, c='#ff0000', marker='.')

    plt.title(f"Iterations: {numIterations}")
    plt.show()


if __name__ == "__main__":
    main()
