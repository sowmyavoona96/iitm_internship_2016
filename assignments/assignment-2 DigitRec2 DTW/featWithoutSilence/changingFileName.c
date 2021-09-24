#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(){
    FILE* fid = fopen("trainList","r");
    FILE* fpt = fopen("trainList1","w+");
    int i,j,k;
    char fileText[88][23];

    for(i=0;i<88;i++){
        char temp[23]="";
        char rep[24] = "featDirTrain1/";
        fscanf(fid,"%s\n",temp);
        strcat(rep,temp+13,9);
        fprintf(fpt,"%s\n",rep);
    }

    fclose(fid);
    fclose(fpt);

}
