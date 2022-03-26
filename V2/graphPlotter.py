import csv
import matplotlib.pyplot as plt
from tqdm import tqdm
import tkinter as tk
from tkinter.filedialog import askopenfilename

tk.Tk().withdraw()

fileName = askopenfilename(
    title='Open a file', initialdir='')

dataFile = open(fileName)
csvReader = csv.reader(dataFile)
print(f"\nReading from {fileName}\n")

header = next(csvReader)
radius = int(header[0])
pixels = int(header[1])
numIterations = int(header[2])

rootsRaw = next(csvReader)
roots = []
isOdd = True
a = b = 0

for i in rootsRaw:
    if i == '':
        break

    if isOdd:
        a = float(i)
        isOdd = False
    else:
        b = float(i)
        roots.append(complex(a, b))
        isOdd = True

image = []
for row in tqdm(csvReader, total=pixels):
    for i in range(len(row)):
        try:
            row[i] = float(row[i])
        except:
            row.remove(row[i])
    image.append(row)

dataFile.close()

extent = [-radius, radius, -radius, radius]
plt.imshow(image, extent=extent)

rootX = [i.real for i in roots]
rootY = [i.imag for i in roots]
plt.scatter(rootX, rootY, c='#ff0000', marker='.')

plt.title(f"Iterations: {numIterations}")
plt.show()
