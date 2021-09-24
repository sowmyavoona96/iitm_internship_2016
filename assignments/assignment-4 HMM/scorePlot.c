#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(){
    FILE* opFile = fopen("testScores.txt","r");
    int noOfTest = 550;
    int i,j,k,digit;
    char testList[noOfTest][20];
    double testScore[noOfTest][11];
    char c;

    for(i=0;i<noOfTest;i++){
        for(j=0;j<11;j++){
           fscanf(opFile," %lf",&testScore[i][j]);
        }
    }
    fclose(opFile);

    FILE* testFiles = fopen("lists/testList","r");

    for(i=0;i<noOfTest;i++){
        fscanf(testFiles,"%s",testList[i]);
        printf("%s\n",testList[i]);
    }
    fclose(testFiles);

    FILE* tscores = fopen("trueScore.txt","w");
    FILE* fscores = fopen("falseScore.txt","w");

    for(i=0;i<550;i++){
        c = testList[i][11];
        if(c == 'z')
            digit = 10;
        else if(c == 'o')
            digit = 9;
        else
            digit = (c -'0') -1;

        fprintf(tscores,"%lf ",testScore[i][digit]);

        for(j=0;j<11;j++){
            if(j!=digit)
                fprintf(fscores,"%lf ",testScore[i][j]);
        }
    }

    fclose(tscores);
    fclose(fscores);

return 0;
}
