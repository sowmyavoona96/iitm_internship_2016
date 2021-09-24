
    /*------------------------------malloc terms--------------------------------------*/
    /*--------------------------------------------------------------------------------/

    /*while(fscanf(fpTe,"%lf",&x)){
        printf("%e",x);
    }
    */
    /*for(i=0;i<noOfVecTe;i++){
        for(j=0;j<noOfDimTe;j++){
            if(fscanf(fpTe,"%lf",&x)){
                printf("%e",x);
            }

        }
        printf("\n");
    }
*/

/*
    fpTr = fopen(trainFile,"r");
    fscanf(fpTr,"%d %d",&noOfDimTr,&noOfVecTr);
    printf("%d %d",noOfDimTr,noOfVecTr);

     for(i=0;i<noOfVecTr;i++){
        for(j=0;j<noOfDimTr;j++){
            //printf("%e ",x);
            //fscanf(fpTr,"%lf",&featureVectorSetTr);
        }
        //printf("\n");
    }


    fclose(trainFile);
*/

/*--------------------------------------------dtw --------------------------------------------*/
 /*   int dim = 38;
    memset(distances,0, sizeof(distances)*noOfVecTe*noOfVecTr);
    memset(cost,0, sizeof(cost)*noOfVecTe*noOfVecTr);

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
*/
