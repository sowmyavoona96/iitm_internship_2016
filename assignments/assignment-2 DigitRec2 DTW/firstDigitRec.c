#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void file_format_error() {
	printf("ERROR: The format of the file is incorrect.\n\n");
}

double min(double a ,double b, double c){
    if(a<b && a<c)
        return a;
    else if(b<a && b<c)
        return b;
    else
        return c;
}

double minOfArr(double* arr,int length){
    int i,index=0;
    double minimum = arr[0];
    for(i=0;i<length;i++){
        if(arr[i]<minimum)
            minimum = arr[i];
            index = i;
    }
    return minimum;
}

double norm(double featVecTe[],double featVecTr[],int dim){
    int i =0 ;
    double diff = 0;
         for(i=0;i<dim;i++){
            diff = diff + (featVecTe[i] - featVecTr[i])*(featVecTe[i] - featVecTr[i]);
         }
    return sqrt(diff);
}

double** featureVectorSet(char * fileName){
    FILE *fileptr;
    int header;
	double n;
	int dimen, noOfFV;
	int i, j, k;

	fileptr = fopen(fileName, "r");
	if (!(fileptr)) {
		printf("ERROR: Couldn't open %s\n", fileName);
		exit(1);
	}

	if (fscanf(fileptr, "%d", &header) == 1) {
		dimen = header;
	} else {
		file_format_error();
		exit(1);
	}

	if (fscanf(fileptr, "%d", &header) == 1) {
		noOfFV = header;
	} else {
		file_format_error();
		exit(1);
	}
    double **features = (double **)malloc(noOfFV * sizeof(double *));
    int row;

    // for each row allocate Cols ints
    for (row = 0; row < noOfFV; row++) {
        features[row] = (double *)malloc(dimen * sizeof(double));
    }


	for (i=0; i<noOfFV; i++) {
		for (j=0; j<dimen; j++) {
			if (fscanf(fileptr, "%lf", &n) == 1) {
				features[i][j] = n;
			} else {
				file_format_error();
				exit(1);
			}
		}
	}


/*	for (i=0; i<noOfFV; i++) {
		for (j=0; j<dimen; j++) {
			printf("%lf ", features[i][j]);
		}
		printf("\n");
	}
*/

	fclose(fileptr);
	return features;

}

double findMinScore(char* testFile, char* trainFile){
    FILE *fpTe,*fpTr;
    int noOfDimTe,noOfDimTr,noOfVecTe,noOfVecTr,header,dim;
    int i,j,k,l,m,n;
    double minScore;

    /*-------------------test file reading ----------------*/
    fpTe = fopen(testFile,"r");
    if (!(fpTe)) {
		printf("ERROR: Couldn't open %s\n", testFile);
		return 1;
	}

	if (fscanf(fpTe, "%d", &header) == 1) {
		noOfDimTe = header;
	} else {
		file_format_error();
		return 1;
	}

	if (fscanf(fpTe, "%d", &header) == 1) {
		noOfVecTe= header;
	} else {
		file_format_error();
		return 1;
	}


    double** featureVectorSetTe = featureVectorSet(testFile);
	fclose(fpTe);

/*--------------------------- train file reading --------------------------*/
    fpTr = fopen(trainFile,"r");

    if (!(fpTr)) {
		printf("ERROR: Couldn't open %s\n", trainFile);
		return 1;
	}

	if (fscanf(fpTr, "%d", &header) == 1) {
		noOfDimTr = header;
	} else {
		file_format_error();
		return 1;
	}

	if (fscanf(fpTr, "%d", &header) == 1) {
		noOfVecTr= header;
	} else {
		file_format_error();
		return 1;
	}

    double** featureVectorSetTr = featureVectorSet(trainFile);
    fclose(fpTr);

    int lowerLimit = 1;
    int upperLimit = noOfVecTr;
    int range = upperLimit - lowerLimit;
    double score[range];

    double distances[upperLimit][noOfVecTr];
    double cost[upperLimit][noOfVecTr];
    dim = noOfDimTe;

    if(noOfVecTe<upperLimit)
        upperLimit = noOfVecTe;
    if(noOfVecTe<lowerLimit)
        lowerLimit = noOfVecTe;

    for(i = 0;i<upperLimit;i++){
        for(j=0;j<noOfVecTr;j++){
            distances[i][j] = 0;
            cost[i][j] = 0;
        }
    }

    for(i=0;i<upperLimit;i++){
        for(j=0;j<noOfVecTr;j++){
             distances[i][j] = norm(featureVectorSetTe[i],featureVectorSetTr[j],dim);
        }
    }

    cost[0][0] = distances[0][0];

    for(j=1;j<noOfVecTr;j++)
        cost[0][j] = distances[0][j] + cost[0][j-1];

    for(i=1;i<upperLimit;i++)
        cost[i][0] = distances[i][0] + cost[i-1][0];

    for(i=1;i<upperLimit;i++){
        for(j=1;j<noOfVecTr;j++){
            cost[i][j] = distances[i][j] + min(cost[i-1][j],cost[i][j-1],cost[i-1][j-1]);
        }
    }
/*
   for(i=1;i<upperLimit;i++){
        for(j=1;j<noOfVecTr;j++){
            printf(" (%d,%d):%e",i,j,cost[i][j]);
        }
        printf("\n");
    }
*/
    for(j=0;j<range;j++){
        score[j] = cost[j+lowerLimit-1][noOfVecTr-1]/(j+lowerLimit+noOfVecTr);
    }

    minScore = minOfArr(score,range);
    return minScore;
}

int main(){
   // printf("%lf",findMinScore("featDir/966381za.mfcc","featDirTrain/st_ob.mfcc"));

          int i,j,k,l,m,n,count=1;
    int noOfSpeakers = 0,noOfFiles =0,noOfTest = 1;
    int countOfDigit[11] = {0};
    int digitRec[11][noOfTest];
    int actualDigit[11][noOfTest];
    char temp[30];

    FILE* trainFile = fopen("lists/trainList","r");
    FILE* testFile = fopen("lists/testList","r");
    while(!feof(trainFile)){
        fscanf(trainFile,"%s",temp);
        noOfFiles++;
    }

    noOfSpeakers = noOfFiles/11;
    char trainList[noOfFiles][50];
    fseek(trainFile,0,SEEK_SET);

    for(i=0;i<noOfFiles;i++){
        fscanf(trainFile,"%s",trainList[i]);
    }
    fclose(trainFile);

    for(i=0;i<11;i++){
        for(j=0;j<noOfTest;j++){
           digitRec[i][j] = 0;
           actualDigit[i][j] = 0;
        }
    }

    char testList[noOfTest][50];
    char c;
    int cInt;
    for(i=0;i<noOfTest;i++){
        fscanf(testFile,"%s\n",testList[i]);
        c = testList[i][8];
        cInt = c-'0';

        if(c=='o')
            actualDigit[9][i] = 1;
        else if(c=='z')
            actualDigit[10][i] = 1;
        else
            actualDigit[cInt-1][i] = 1;
    }
    fclose(testFile);

    strcpy(testList[0] ,"featDir/17za.mfcc");

    char  actualDigitFile[] = "actualDigit2.txt";
    FILE *actualDigitFpt = fopen(actualDigitFile,"w");

    for(m=0;m<11;m++){
        for(n=0;n<noOfTest;n++){
            fprintf(actualDigitFpt,"%d ",actualDigit[m][n]);
        }
        fprintf(actualDigitFpt,"\n");
    }
    fclose(actualDigitFpt);

    for(k=0;k<noOfTest;k++){
        for(i=0;i<11;i++){
            countOfDigit[i] = 0;
        }
        for(i=0;i<noOfSpeakers;i++){
            double score[11];
            for(m=0;m<11;m++)
                score[m] = 0;

            int digit = 0;
            for(j=i;j<=(i+(10*(noOfSpeakers)));j=j+noOfSpeakers){
                score[digit] = findMinScore(testList[k],trainList[j]);
                printf("\n%d %s %s %e \n",count,testList[k],trainList[j],score[digit]);
                digit = digit + 1;
                count++;
            }

            int index =0;
            int ind;
            for(ind = 0;ind<11;ind++){
                if(score[index]>score[ind])
                    index = ind;
            }
            countOfDigit[index] = countOfDigit[index]+1;
        }

        int mainIndex = 1;
        int mainInd;
        for(mainInd=0;mainInd<11;mainInd++){
            if(countOfDigit[mainInd]>countOfDigit[mainIndex])
                mainIndex = mainInd;
        }
        digitRec[mainIndex][k] = 1;
    }

    char  digitRecFile[] = "digitRecTest.txt";
    FILE *FdigitRec = fopen(digitRecFile,"w");

    for(m=0;m<11;m++){
        for(n=0;n<noOfTest;n++){
            fprintf(FdigitRec,"%d ",digitRec[m][n]);
        }
        fprintf(FdigitRec,"\n");
    }
    fclose(FdigitRec);

    for(i=0;i<11;i++){
        printf("%d ",countOfDigit[i]);
    }

    return 0;
}
