# K-means-Clustering-Problem
k-means clustering is a method of vector quantization, originally from signal processing, that is popular for cluster analysis in data mining. k-means clustering aims to partition n observations into k clusters in which each observation belongs to the cluster with the nearest mean, serving as a prototype of the cluster. This results in a partitioning of the data space into Voronoi cells.

Algorithm Steps for Computing:
main (..)
Step 0:  
inFile  Open the input file argv[]
numRows, numCols, minVal, maxVal get from inFile.
imgAry  Dynamically allocate a 2-D arrays, size numRows X numCols.
outFile_1, outFile_2, outFile_3  open from argv[], argv[], argv[] 
K  ask user from console
Kcentroids[K]  Dynamically allocate centroids struct, size of K+1

Step 1: numPts  extractPts (inFile, outFile_1) // see algorithm below.
  pointSet  Dynamically allocate the pointSet array, size of numPts  	 
 	
Step 2: close outFile_1
   outFile_1  reopen outFile_1

Step 3: loadPointSet (outFile_1, pointSet)
Step 4: kMeansClustering (pointSet, K)
Step 5: writePtSet (pointSet, outFile_3)
Step 6: close all files

int extractPts(inFile, outFile_1)
Step 0: numPts  0
	Step 1: read inFile from left to right and top to bottom
		  Use i, j as index for rows and cols bounded by numRows and numCols
    
Step 2: if p(i, j) > 0
			numPts++
                write i and j to outFile1
Step 3: repeat step 1 and step 2 until EOF inFile
	Step 4: return numPts

kMeansClustering (pointSet, K)

Step 0: iteration  0
Step 1: assignLable (pointSet, K)

Step 2: Point2Image (pointSet, imgAry) 
   printImage (imgAry, outFile_2, iteration) 

Step 3: change  0
Step 4: computeCentroids (pointSet, Kcentroids) // see algorithm below
Step 5: index  0
Step 6: DistanceMinLable(pointSet[index], Kcentroids) // see algorithm below
Step 7: index ++ 
Step 8: repeat step 6 to step 7 while index < numPts
Step 9: iteration++
Step 10: repeat step 2 to step 9 until no more changes


computeCentroids (pointSet, Kcentroids ) 

Step 0: sumX[K]  dynamically allocate 1-D array, size of K
   sumY[K]  dynamically allocate 1-D array, size of K
   totalPt[K]  dynamically allocate 1-D array, size of K

		// initialize the above 3 1D arrays to 0
 
Step 1: index  0
Step 2: label  pointSet[index].label // get the point’s cluster label
	sumX[label] += pointSet[index].Xcoord
  	sumY[label] += pointSet[index].Ycoord
	totalPt[label] ++
Step 3: index++
Step 4: repeat step 2 to step 3 while index < numPts

step 5: label  1
step 6: Kcentroids[label].Xcoord  (sumX[label]/ totalPt[label]) 
	   Kcentroids[label].Ycoord  (sumY[label]/ totalPt[label])

Step 7: label ++
Step 8: repeat step 6 to step 7 while label <= K

DistanceMinLable (p, Kcentroids)
Step 1: label  1

Step 2: dist  computeDist(p, Kcentroids[label]) // 
	   if p’s Distance > dist
		p’s label  label
		change++
Step 3: label ++
Step 4: repeat step 2 to step 3 while label <= K

assignLabel (pointSet, K)
Step 0: front <-- 0
           back <-- numPts - 1
           label <-- 1
Step 1: if label >= K
          Label <-- 1
Step 2:  pointSet[front]'s label <-- label
            front ++
            label++
Step 3:  pointSet[back]'s label <-- label
            back --
            label++
Step 4: repeat step 1 to step 3 while front <= back
