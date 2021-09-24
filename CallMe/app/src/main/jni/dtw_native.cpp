//
// Created by sowmya on 1/7/16.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
#include "com_example_sowmya_callme_DTW_ndk.h"


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

double euclidianDist(double featVecTe[],double featVecTr[],int dim){
    int i;
    double diff = 0;
    for(i=0;i<dim;i++){
        diff = diff + ((featVecTe[i] - featVecTr[i]) * (featVecTe[i] - featVecTr[i]));
    }

    return sqrt(diff);
}

double** featureVectorSet(char * fileName){

    FILE *fileptr;
    int header;
    double n;
    int dimen, noOfFV;
    int i, j;

    fileptr = fopen(fileName, "r");
    if (!(fileptr)) {
        printf("ERROR: Couldn't open %s\n", fileName);
        //exit(1);
    }

    if (fscanf(fileptr, "%d", &header) == 1) {
        dimen = header;
    } else {
        file_format_error();
        //exit(1);
    }

    if (fscanf(fileptr, "%d", &header) == 1) {
        noOfFV = header;
    } else {
        file_format_error();
        //exit(1);
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
               // exit(1);
            }
        }
    }

    fclose(fileptr);
    return features;

}


extern "C"  JNIEXPORT jdouble JNICALL Java_com_example_sowmya_callme_DTW_1ndk_findScore(JNIEnv *env, jobject, jstring test, jstring train){


  FILE *fpTe;
  FILE *fpTr;


  // __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "hi\n");

  double score = 0;
  int header = 0;
  int noOfDimTe = 0;
  int noOfDimTr = 0;
  int noOfVecTe = 0;
  int noOfVecTr = 0;
  int i,j,dim;


  char* testFileName = (char *) env->GetStringUTFChars(test, 0);
  char* trainFileName = (char *) env->GetStringUTFChars(train, 0);

  fpTe = fopen(testFileName,"r");
  /*-------------------test file reading ----------------*/
  if (!(fpTe)) {
    //printf("ERROR: Couldn't open %s\n", testFileName);
    __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "ERROR: Couldn't open %s\n", testFileName);
  }


  if (fscanf(fpTe, "%d", &header) == 1) {
    noOfDimTe = header;
  } else {
    //file_format_error();
    __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "ERROR: Couldn't read header of %s\n",testFileName);
  }

  if (fscanf(fpTe, "%d", &header) == 1) {
    noOfVecTe= header;
  } else {
    //file_format_error();
    __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "ERROR: Couldn't read test header 2");
  }
  fclose(fpTe);

  double** featureVectorSetTe = featureVectorSet(testFileName);


  fpTr = fopen(trainFileName,"r");

  /*--------------------------- train file reading --------------------------*/

  if (!(fpTr)) {
    //  printf("ERROR: Couldn't open %s\n", trainFileName);
    __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "ERROR: Couldn't open %s\n", trainFileName);
  }

  if (fscanf(fpTr, "%d", &header) == 1) {
    noOfDimTr = header;
  } else {
    //file_format_error();
    __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "ERROR: Couldn't read train header 1\n");
  }

  if (fscanf(fpTr, "%d", &header) == 1) {
    noOfVecTr= header;
  } else {
    //file_format_error();
    __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG", "ERROR: Couldn't read train header 2\n");
  }


  fclose(fpTr);

  double** featureVectorSetTr = featureVectorSet(trainFileName);

  /* --------------------- dtw -------------------------*/
  double distances[noOfVecTe][noOfVecTr];
  dim = noOfDimTe;

  for(i = 0;i<noOfVecTe;i++){
    for(j=0;j<noOfVecTr;j++){
      distances[i][j] = 0;
    }
  }

  for(i=0;i<noOfVecTe;i++){
    for(j=0;j<noOfVecTr;j++){
      distances[i][j] = euclidianDist(featureVectorSetTe[i],featureVectorSetTr[j],dim);
    }
  }

  for(j=1;j<noOfVecTr;j++)
    distances[0][j] = distances[0][j] + distances[0][j-1];

  for(i=1;i<noOfVecTe;i++)
    distances[i][0] = distances[i][0] + distances[i-1][0];


  for(i=1;i<noOfVecTe;i++){
    for(j=1;j<noOfVecTr;j++){
      distances [i][j] = distances[i][j] + min(distances[i-1][j],distances[i][j-1],distances[i-1][j-1]);
      // __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG","\n %d,%d - %lf ",i,j,distances[i][j]);
    }
  }
  // __android_log_print(ANDROID_LOG_DEBUG, "LOG_TAG","\n %d ",noOfVecTe);
  score = distances[noOfVecTe-1][noOfVecTr-1]/(noOfVecTe+noOfVecTr);

  env->ReleaseStringUTFChars(test,testFileName);
  env->ReleaseStringUTFChars(train,trainFileName);

  return score;

}