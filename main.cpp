
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class Point{

public:
	int Xcoord;
	int Ycoord;
	int Label;
	double Distance; //the distance to its own cluster centroid

	Point(){
		this->Xcoord=0;
		this->Ycoord=0;
		this->Label=0;
		this->Distance=9999.0;  //initial
	}

	Point(int xc, int yc, int l, double d){
		this->Xcoord=xc;
		this->Ycoord=yc;
		this->Label=l;
		this->Distance=d;
	}

};

class xyCoord{

public:
     int Xcoord;
     int Ycoord;
     int Label;

     xyCoord(){
    	 this->Xcoord=0;
    	 this->Ycoord=0;
    	 this->Label=0;
     }


}; //end classXYcord


class Kmean{
public:
	      int K;
	     int numPts;  //initialize to 0
	     Point* pointSet;  //1d array of point class to be dynamacally allocated
	     int numRows;
	     int numCols;
	     int minVal;
	     int maxVal;
	     xyCoord* Kcentroids;
	     int** imgAry;
	     int change;


	Kmean(int k, int nr, int nc, int minVal, int maxVal){

		this->K=k;
		this->numRows=nr;
		this->numCols=nc;
		this->minVal=minVal;
		this->maxVal=maxVal;

		this->numPts=0;  //we will initialize to 0
		this->change=0;

		this->pointSet= new Point[this->numPts];   //point set to 0 at first
		this->Kcentroids= new xyCoord[this->K+1]; //we dont want to consider the 0

		//initialize the imgArr
		this->imgAry= new int*[this->numRows];
		for(int i=0; i<nr; i++){
			this->imgAry[i]= new int[nc];
		}//end for




	}//end constructor

int extractPts(ofstream& outFile1){

	this->numPts=0;

	for(int i=0; i<this->numRows; i++){
		 for(int j=0; j<this->numCols; j++){
		   if(this->imgAry[i][j]>0){
			   this->numPts++;      //number of points that are greater then 0
			   outFile1<<i<<" "<<j<<endl;
		   }//end if
		 }
	}


	this->pointSet= new Point[this->numPts];  //initialize pointset with updated numPts

return this->numPts;

}//end extractPoints

void loadPointSet (ifstream& outFile1){

	//read, and store in the pointset array, and assign a label
	  //begin from 1
	int xCord;
	int yCord;

	int i=0;
	while(outFile1>>xCord>>yCord && i<this->numPts){

		this->pointSet[i].Xcoord=xCord;
		this->pointSet[i].Ycoord=yCord;
		this->pointSet[i].Label=0;
		this->pointSet[i].Distance=9999.0;

		i++;
	}//end while

}

void assignLabel(){
	 int front=0;
     int back=numPts-1;
	 int label=1;
	while(front<=back){
		if(label>K){
				label=1;
		}
		this->pointSet[front].Label=label;
			front++;
			label++;
			if(label>K){
					label=1;
			}
		pointSet[back].Label=label;
			back--;
		label++;

			}

}


void writePtSet(ofstream& outFile3){

	outFile3<<this->numPts<<endl;
	outFile3<<this->numRows<<" "<<this->numCols<<endl;

	for(int i=0; i<this->numPts; i++){
		outFile3<<pointSet[i].Xcoord<<" "<<pointSet[i].Ycoord<<" "<<pointSet[i].Label<<endl;

	}//end for

}

void Point2Image(){
		for(int i=0;i<this->numPts;i++){
			imgAry[pointSet[i].Xcoord][pointSet[i].Ycoord] = pointSet[i].Label;
		}
	}//end Point2Image

void printImage (ofstream& outFile2, int it){
		outFile2 << "*** Result of iteration " <<it<< " ***"<<endl;

		for(int i=0;i<this->numRows;i++){
			for(int j=0;j<numCols;j++){
				if(this->imgAry[i][j]>0){
					outFile2<<this->imgAry[i][j]<<" ";  //display its label
				}
				else{
					outFile2 <<"  ";  //display with a blank
				}
			}
			outFile2<<endl;
		}
		outFile2<<endl<<endl;
	}//end printImage
//
double computeDist(Point p1, xyCoord Kcentroids){  //distance between point p1, and a sentroid
		double distance = sqrt(pow((p1.Xcoord - Kcentroids.Xcoord),2) + pow((p1.Ycoord-Kcentroids.Ycoord),2));
		return distance;
	}

void computeCentroids(){

	    int sumX[this->K+1] = {0};
		int sumY[this->K+1] = {0};
		int totalPt[this->K+1] = {0};
		int label;
		int index = 0; //begin from the first
		while(index<this->numPts){
			label = pointSet[index].Label;     //get label of the pointset
			sumX[label]+=pointSet[index].Xcoord;     //add the x cordinates with that lable
			sumY[label]+= pointSet[index].Ycoord;    //add the Y cordinates with that lable
			totalPt[label]++;    //total number of points for that lable
			index++;
		}

		label = 1;
		while(label<=K){  //get the centroid for each lable
			if(totalPt[label]>0){

			Kcentroids[label].Xcoord = (int)(sumX[label]/totalPt[label]);
			Kcentroids[label].Ycoord = (int)(sumY[label]/totalPt[label]);
			}
			label++;
		}//end while
	}

void DistanceMinLabel(int index){
		// compute the distance from a point p to each of the K centroids.
		// check to see if p’s label need to be change or not.
	//step 0
	double minDistance=99999;
	int minLabel=0;
		int label = 1;

		double dist=0.0;
		while(label<=K){
			dist = computeDist(this->pointSet[index], Kcentroids[label]);  //al the K centroids

			if(dist<minDistance){
				minLabel=label;
				minDistance=dist;

			}//end if
			label++;

		}//end while

		if(minDistance < this->pointSet[index].Distance){
			this->pointSet[index].Distance=minDistance;
			this->pointSet[index].Label=minLabel;
			this->change++;
		}


}

void kMeansClustering(ofstream& outFile2){

	      int it = 0;
	      this->assignLabel();
		  this->change = 0;
			do{
				this->Point2Image();
				this->printImage(outFile2, it);
				this->change = 0;
				this->computeCentroids();  //compute centriods of each
				int index=0;
				while(index<this->numPts){
					DistanceMinLabel(index);
					index++;
				}//end while

				it++;
			} while (change!=0);

}//end KmeanClustering


};


int main(int argc, char**argv) {


	      //step1
	     ifstream inFile1;
	     ofstream outFile1;
	     ofstream outFile2;
	     ofstream outFile3;

	     inFile1.open(argv[1]);

	     outFile1.open(argv[2]);
	     outFile2.open(argv[3]);
	     outFile3.open(argv[4]);

	     int numRows;
	     int numCols;
	     int minVal;
	     int maxVal;
	     int k;

	     Kmean* theKmean;


	     if(inFile1.is_open()){

	    	 inFile1>>numRows;
	    	 inFile1>>numCols;
	    	 inFile1>>minVal;
	    	 inFile1>>maxVal;

	    	 cout<<"Enter Number of klusters K"<<endl;
	    	 cin>>k;

	    	 cout<<endl;
	    	 theKmean= new Kmean(k, numRows, numCols, minVal, maxVal);

	    	 //imgAry Dynamically allocate a 2-D arrays, size numRows X numCols.
	    		 for(int i=0; i<numRows; i++){
	    			 for(int j=0; j<numCols; j++){
	    				 inFile1>>theKmean->imgAry[i][j];
	    			 }
	    		 }

	    		 //Step 1: numPts  extractPts (inFile, outFile_1) // see algorithm below.
	    		 // pointSet  Dynamically allocate the pointSet array, size of numPts

	    		int numPts=theKmean->extractPts(outFile1);

	    	  //step2-close outFile, and open it again
	    		outFile1.close();
	    		ifstream myFile;
	    		myFile.open(argv[2]);  //has the outFile1

	    		//STEP 3:loadPointSet, and assign label
	    		theKmean->loadPointSet(myFile);

	    		//step4
	    		theKmean->kMeansClustering(outFile2);

	    		//step5
	    	    theKmean->writePtSet(outFile3);

	    	 inFile1.close();
	    	 outFile1.close();
	    	 outFile2.close();
	    	 outFile3.close();


	     }else{
	    	 cerr<<"Can not open the file!";
	     }


	return 0;
}
