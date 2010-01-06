#!/usr/bin/env python
import math
import numpy
import sys

nameList = [
#    ["whootIPHighNoise1.txt", "whootIPHighNoise2.txt", "whootIPHighNoise3.txt"],
#    ["ipSR_30N_5A_CR.out", "ipSR_30N_5A_CR2.out"]    
#    ["ip_30N_10A_8R.dat"]
    ["ip_5A_30N.out"], ["ip_10A_30N.out"], ["ip_20A_30N.out"]
    ]

def grokFiles(fileNames, xIndex, yIndex):
    data = {}
    
    for fileName in fileNames:
        #print fileName
        file = open(fileName, 'r')
        lines = file.readlines()
        file.close()
        for line in lines:
            line = line.strip()
            if len(line) > 0:
                tokens = line.split()
                x = eval(tokens[xIndex])
                y = eval(tokens[yIndex])
                #print "x, y:", x, y
                data[x] = data.get(x, []) + [y]
                #print data[x]
    
    dataKeys = data.keys()
    dataKeys.sort()
    
    bounds = {}
    for key in dataKeys:
        #If there is only one sample, cant compute bounds
        #Assumes (probably incorrectly) that the distribution of Y is gaussian
        #Hardcoded to compute the 0.95 CI
        if len(data[key]) > 1:
            Ys = numpy.array(data[key])
            mean = numpy.mean(Ys)
            stdDev = numpy.std(Ys)
            sqrtN = math.sqrt(len(Ys))
            bound = 1.96 * stdDev / sqrtN
            bounds[key]= (mean - bound, mean, mean + bound)
    
    boundKeys = bounds.keys()
    boundKeys.sort()
    
    outFileName = fileNames[0][:fileNames[0].index(".")] + "Bounds" + fileNames[0][fileNames[0].index("."):]    
    file = open(outFileName, 'w') #open(sys.argv[4], 'w')
    
    for key in boundKeys:
        string = str(key) +"\t"+ str(bounds[key][0]) +"\t"+ str(bounds[key][1]) +"\t"+ str(bounds[key][2])
        file.write(string + "\n")
        #print string
            
    file.close()
    
if __name__ == "__main__":
    for fileNames in nameList:
        grokFiles(fileNames, 0, 2)
        
    
#if __name__ == "__main__":
#    print sys.argv
#    
#    #File with the names of all the log files
#    fileNamesFile = sys.argv[1]
#    #What will be the x-axis/left column of the graph
#    xIndex = int(sys.argv[2])
#    #What will be the y-axis/right column of the graph
#    yIndex = int(sys.argv[3])
#    
#    if len(sys.argv) < 5:
#        raise Exception("Too few command line params")
#    
#    print len(sys.argv), sys.argv
#    file = open(fileNamesFile, 'r')
#    lines = file.readlines()
#    file.close()
#    fileNames = []
#    for line in lines:
#        fileNames.append(line.strip())
#    
#    print "File names:", fileNames
#    grokFiles(fileNames, xIndex, yIndex)
