#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(){
    FILE* fid = fopen("lists/testList","r");
    FILE* fpt = fopen("lists/testList_cp","w+");
    int i,j,k;
    char fileText[715][50];

    for(i=0;i<715;i++){
        char temp[100]="";
        char rep[50] = "";
        fscanf(fid,"%s\n",temp);
        strncpy(rep,temp+26,strlen(temp)-26);

        strcpy(fileText[i],rep);
        fprintf(fpt,"%s\n",fileText[i]);
        printf("\n %s",fileText[i]);
    }

    fclose(fid);
    fclose(fpt);

}
