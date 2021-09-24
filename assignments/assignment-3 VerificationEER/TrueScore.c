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
    int noOfSpeakers = 0;
    int i,j,k,l,m,n,t;
    int noOfTest = 550;
    char testList[noOfTest][20];
    int digitRec[11][noOfTest];
    int actualDigit[11][noOfTest];
    int countOfDigit[11] = {0};
    char* character;
    double score;
    int tcount=0,fcount = 0;

    FILE*  fid = fopen("lists/testList","r");
    FILE* tscores = fopen("Tscores.txt","w");
    FILE* fscores = fopen("Fscores.txt","w");

    for(i=0;i<noOfTest;i++){
        fscanf(fid,"%s",testList[i]);
        //printf("%s ",testList[i]);
    }

    fclose(fid);

        char fileName[] =  "lists/trainList_3";
        char temp[20];

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

        double scores[noOfTest][noOfFiles];

        for(i=0;i<noOfFiles;i++){
            fscanf(trainFile,"%s",trainList[i]);
            //printf("%s ",trainList[i]);
        }

        fclose(trainFile);

        /* -------------------read actualDigit ------------------------*/
        FILE* actual = fopen("actualDigit.txt","r");
        for(i=0;i<11;i++)
            for(j=0;j<noOfTest;j++)
                fscanf(actual,"%d",actualDigit[i][j]);
        /* -------------------read DigitRec ------------------------*/
        FILE* digitR = fopen("digitRec.txt","r");
        for(i=0;i<11;i++)
            for(j=0;j<noOfTest;j++)
                fscanf(digitR,"%d",digitRec[i][j]);


        int count = 1;
        for(k=0;k<noOfTest;k++){
            for(i=0;i<noOfFiles;i++){
                    score  = findScore(testList[k],trainList[i]);
                    int cd = 0;
                    for(m=0;m<11;m++){
                        if(actualDigit[m][k] == digitRec[m][k])
                            cd++;
                    }

                    if (cd == 11)
                        fprintf(tscores," %lf",score);
                    else
                        fprintf(fscores," %lf",score);
                }
        }

return 0;
}
