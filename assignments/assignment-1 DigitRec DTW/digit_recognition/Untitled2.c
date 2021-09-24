/* ----------------------------reading test file ------------------------------------*/
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

    printf("%d\n%d", noOfDimTe,noOfVecTe);

    double featureVectorSetTe[noOfVecTe][noOfDimTe];

	for (i=0; i<noOfVecTe; i++) {
		for (j=0; j<noOfDimTe; j++) {
			if (fscanf(fpTe, "%lf", &n) == 1) {
				featureVectorSetTe[i][j] = n;
			} else {
				file_format_error();
				return 1;
			}
		}
	}


/*	for (i=0; i<noOfVecTe; i++) {
		for (j=0; j<noOfDimTe; j++) {
			printf("%e ", featureVectorSetTe[i][j]);
		}
        printf("\n");
	}
*/
	fclose(fpTe);

/*-----------------------------------------------------reading train file---------------------------------*/

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

    //printf("\n %d %d", noOfDimTr,noOfVecTr);

    double featureVectorSetTr[noOfVecTr][noOfDimTr];

	for (i=0; i<noOfVecTr; i++) {
		for (j=0; j<noOfDimTr; j++) {
			if (fscanf(fpTr, "%lf", &n) == 1) {
				featureVectorSetTr[i][j] = n;
			} else {
				file_format_error();
				return 1;
			}
		}
	}


/*	for (i=0; i<noOfVecTr; i++) {
		for (j=0; j<noOfDimTr; j++) {
			printf("%e ", featureVectorSetTr[i][j]);
		}
        printf("\n");
	}
*/
	fclose(fpTr);
