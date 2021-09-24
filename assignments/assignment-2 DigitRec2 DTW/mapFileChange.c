#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(){
    FILE* fid = fopen("mapFile","r");
    FILE* fpt = fopen("mapFile1","w+");
    int i,j,k;
    char fileText[88][56];

    for(i=0;i<88;i++){
        char temp[56]="";
        char sub[]  = "";
        char rep[] = "/database/database/";
        fscanf(fid,"%s\n",temp);
        strncpy(sub,temp+17,38);
        strcat(rep,sub);
        fprintf(fpt,"%s\n",rep);

    }

    fclose(fid);
    fclose(fpt);

}
