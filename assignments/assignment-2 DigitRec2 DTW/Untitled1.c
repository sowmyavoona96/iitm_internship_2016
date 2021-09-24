 for(i=0;i<11;i++)
        for(j=0;j<noOfTest;j++)
            digitRec[i][j] = 0;

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
                //digit = digit + 1;
               // printf("\n%d ",j);
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

    for(i=0;i<11;i++){
         for(j=0;j<noOfTest;j++)
            printf("%d ",digitRec[i][j]);
        printf("\n");
    }


