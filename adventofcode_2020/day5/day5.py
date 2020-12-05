
import re
import sys
 
input_file = open(sys.argv[1], 'r') 

def getRowAndColumn(line): 
    verticalRegionLength = 128
    verticalRegionActual = 0 
    horizontalRegionLength = 8
    horizontalRegionActual = 0
    for char in line: 
        if char == "B" or char == "F": 
            if char == "B":
                verticalRegionActual += verticalRegionLength / 2
            verticalRegionLength /= 2
        else:  
            if char == "R": 
                horizontalRegionActual += horizontalRegionLength / 2
            horizontalRegionLength /= 2
    return int(verticalRegionActual), int(horizontalRegionActual); 
    

seats = [getRowAndColumn(line) for line in input_file.read().splitlines()]
seatIDs = [(seat[0] * 8 + seat[1]) for seat in seats]
seatIDs.sort()

for i in range(0, len(seatIDs) - 1): 
    if seatIDs[i+1]-seatIDs[i] == 2: 
        print (seatIDs[i] + 1)
        break