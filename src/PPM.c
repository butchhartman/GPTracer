#include "PPM.h"

void ppm_writePPM(char** PPMdata) {
	FILE *fptr;

	fptr = fopen("image.ppm", "w");

	if (fptr == NULL) {
		printf("Failed to open file.\n");
		exit(1);
	}

	fprintf(fptr, PPMdata[0]);
	fprintf(fptr, PPMdata[1]);
	fprintf(fptr, PPMdata[2]);
	fprintf(fptr, PPMdata[3]);


	fclose(fptr);

	free(PPMdata[0]);
	free(PPMdata[1]);
	free(PPMdata[2]);
	free(PPMdata[3]);
	free(PPMdata);
}
