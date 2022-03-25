import csv
import matplotlib.pyplot as plt

dataFile = open("data.csv")
csvReader = csv.reader(dataFile)

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
for row in csvReader:
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
