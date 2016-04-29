#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "noise.c"

#define TWOPI 6.28318530718

int posNeg(int in){
	if(in == 0){
		return -1;
	}
	return 1;
}

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));

	float seed = rand()%1000/100.0;

	int width = 1200;
	int height = 800;

	char path[128];
	path[0] = '\0';
	// strcat(path, directory);
	// strcat(path, filename);
	strcat(path, "homemade.svg");
	FILE *file = fopen(path, "w");
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"");
	fprintf(file, "%d",width);
	fprintf(file, "px\" height=\"");
	fprintf(file, "%d",height);
	fprintf(file, "px\" viewBox=\"0 0 ");
	fprintf(file, "%d ",width);
	fprintf(file, "%d",height);
	fprintf(file, "\" xml:space=\"preserve\">\n");

	// int fputc( int c, FILE *file );
	// char x[10]="ABCDEFGHIJ";
	// fwrite(x, sizeof(x[0]), sizeof(x)/sizeof(x[0]), file);
	fprintf(file, "<g>\n");
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote


	float x, y;

	float COLUMNS = 24;

	for(int i = 0; i < COLUMNS; i++){
		for(float j = 0; j < height; j++){
			int halfI = floor(i*.5);
			int one = 1.5*floor((i+0)*.25);
			int three = 1.5*floor((i+2)*.25);

			float vec[2];
			vec[0] = i*.33;
			vec[1] = j/(float)height*3;
			float waveMag = 15;
			float xShift = 50 * noise2(vec);

			x = 40 + 30*i + 20*one + 20*three + waveMag*sinf(j*.05) * posNeg(halfI%2) + xShift;
			y = j;

			fprintf(file, "%.2f,%.2f ", x, y);
		}
		fprintf(file, "\"/>\n"); // closing quote
		fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote	
	}
	// fprintf(file, "\"/>\n"); // closing quote
	// fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" stroke-miterlimit=\"10\" points=\"");  // hanging open quote

	// float turn = 0;
	// for(int i = 0; i < COLUMNS; i+=2){
	// 	for(float j = 0; j < TWOPI; j += TWOPI/divider){
	// 		x = 0;
	// 		y = 0;
	// 		fprintf(file, "%.2f,%.2f ", x, y);
	// 	}
	// }


	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}