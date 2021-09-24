#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double min(double a ,double b, double c){
    if(a<b && a<c)
        return a;
    else if(b<a && b<c)
        return b;
    else
        return c;
}

double norm(double featVecTe[],double featVecTr[],int dim){
    int i =0 ;
    double diff = 0;
         for(i=0;i<dim;i++){
            diff = diff + (featVecTe[i] - featVecTr[i])*(featVecTe[i] - featVecTr[i]);
         }

    return sqrt(diff);
}

void file_format_error() {
	printf("ERROR: The format of the file is incorrect.\n\n");
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

	/*for (i=0; i<noOfFV; i++) {
		for (j=0; j<dimen; j++) {
			printf("%lf ", features[i][j]);
		}
		printf("\n");
	}
    */

	fclose(fileptr);

	return features;

}

double findScore(char* testFile,char*  trainFile){
    FILE *fpTe;
    FILE *fpTr;

    double score = 0;
    double n = 0;
    int header = 0;
    int noOfDimTe = 0;
    int noOfVecTe = 0;
    int noOfDimTr = 0;
    int noOfVecTr = 0;
    int i,j,k,l,m,dim;
     fpTe = fopen(testFile,"r");
    /*-------------------test file reading ----------------*/
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

	fpTr = fopen(trainFile,"r");

/*--------------------------- train file reading --------------------------*/

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

/* --------------------- dtw -------------------------*/
    double distances[noOfVecTe][noOfVecTr];
    double cost[noOfVecTe][noOfVecTr];
    dim = noOfDimTe;

   // memset(distances,0, sizeof(distances)*noOfVecTe*noOfVecTr);
   // memset(cost,0, sizeof(cost)*noOfVecTe*noOfVecTr);

    for(i = 0;i<noOfVecTe;i++){
        for(j=0;j<noOfVecTr;j++){
                distances[i][j] = 0;
                cost[i][j] = 0;
        }
    }

    for(i=0;i<noOfVecTe;i++){
        for(j=0;j<noOfVecTr;j++){
             distances[i][j] = norm(featureVectorSetTe[i],featureVectorSetTr[j],dim);
        }
    }


    cost[0][0] = distances[0][0];

    for(j=1;j<noOfVecTr;j++)
        cost[0][j] = distances[0][j] + cost[0][j-1];

    for(i=1;i<noOfVecTe;i++)
        cost[i][0] = distances[i][0] + cost[i-1][0];


    for(i=1;i<noOfVecTe;i++){
        for(j=1;j<noOfVecTr;j++){
            cost[i][j] = distances[i][j] + min(cost[i-1][j],cost[i][j-1],cost[i-1][j-1]);
        }
    }

   /* for(i=1;i<noOfVecTe;i++){
        for(j=1;j<noOfVecTr;j++){
            printf("%lf ",cost[i][j]);
        }
        printf("\n");
    }
*/

    score = cost[noOfVecTe-1][noOfVecTr-1]/(noOfVecTe+noOfVecTr);

   // printf("%s ",trainFile);
   // printf("\n%e ",score);
    return score;

}

int main(){
   //double score =  findScore("featDir/lg_8a.mfcc","featDir/rf_4b.mfcc");
   //printf("%lf",score);


    int noOfTrainFiles = 4;
    int noOfSpeakers = 0;
    int i,j,k,l,m,n,t;
    int noOfTest = 550;
    char testList[noOfTest][20];
    char temp[20];
    int digitRec[11][noOfTest];
    int actualDigit[11][noOfTest];
    int countOfDigit[11] = {0};
    char* character;

    FILE*  fid = fopen("lists/testList","r");

    for(i=0;i<noOfTest;i++){
        fscanf(fid,"%s",testList[i]);
        //printf("%s ",testList[i]);
    }

    fclose(fid);

    for(t=4;t<=noOfTrainFiles;t++){
        char fileName[16];
        char temp[20];

        sprintf(fileName, "lists/trainList_%d", t);
        FILE * trainFile = fopen(fileName,"r");

        printf("%s",fileName);
        int noOfFiles = 0;

        while(!feof(trainFile)){
            fscanf(trainFile,"%s",temp);
            noOfFiles++;
         }

        noOfFiles--;
        noOfSpeakers = noOfFiles/11;
        printf("\n %d",noOfSpeakers);

        char trainList[noOfFiles][20];
        fseek ( trainFile ,0, SEEK_SET );

        for(i=0;i<noOfFiles;i++){
            fscanf(trainFile,"%s",trainList[i]);
            //printf("%s ",trainList[i]);
        }

        printf("\n");
        fclose(trainFile);


        for(i=0;i<11;i++){
            for(j=0;j<noOfTest;j++){
                digitRec[i][j] = 0;
                actualDigit[i][j] = 0;
            }
        }

        int count = 1;
        for(k=0;k<noOfTest;k++){
            for(i=0;i<11;i++){
                countOfDigit[i] = 0;
            }

            char c = testList[k][11];
            int cInt =  c-'0';

            if(c == 'o')
                actualDigit[9][k] = 1 ;
            else if(c == 'z')
                actualDigit[10][k] = 1;
            else
                actualDigit[cInt-1][k] = 1 ;


            for(i=0;i<noOfSpeakers;i++){
                double score[11];
                for(m=0;m<11;m++)
                    score[m] = 0;

                int digit = 0;
                for(j=i;j<=(i+(10*(noOfSpeakers)));j=j+noOfSpeakers){
                   score[digit] = findScore(testList[k],trainList[j]);
                   //findScore(testList[549],trainList[87]);
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


        char  digitRecFile[14];
        sprintf(digitRecFile, "digitRec_%d.txt", t);
        FILE *FdigitRec = fopen(digitRecFile,"w");

        for(m=0;m<11;m++){
            for(n=0;n<noOfTest;n++){
                fprintf(FdigitRec,"%d ",digitRec[m][n]);
            }
            fprintf(FdigitRec,"\n");
        }
        fclose(FdigitRec);

        char  actualDigitFile[] = "actualDigit.txt";
        FILE *actualDigitFpt = fopen(actualDigitFile,"w");

        for(m=0;m<11;m++){
            for(n=0;n<noOfTest;n++){
                fprintf(actualDigitFpt,"%d ",actualDigit[m][n]);
            }
            fprintf(actualDigitFpt,"\n");
        }

        fclose(actualDigitFpt);



    }


return 0;
}
