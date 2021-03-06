#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define TWOPI 6.28318530718

// output
char filename[128] = "001-dual-sine-wave.svg\0";
char path[128] = "out/\0";

// document
int width = 800;
int height = 800;

// shape
int REVOLUTIONS = 2;//15.0;//18.0;
float SPACING = 70.0f;
float wobbleFreq = 10.0;
float wobbleMag = 0.1;
float ROTATE_2ND = .5; // angle of the second spiral against the first (percent of 2pi)
// ROTATE_2ND = .3;  // 90 degree offset

int main(int argc, char **argv){
	time_t t;
	srand((unsigned) time(&t));

	strcat(path, filename);
	FILE *file = fopen(path, "w");
	// HEADER
	fprintf(file, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
	fprintf(file, "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\" ");
	fprintf(file, "x=\"0px\" y=\"0px\" width=\"%dpx\" height=\"%dpx\" ", width, height);
	fprintf(file, "viewBox=\"0 0 %d %d\">\n", width, height);
	// BODY
	fprintf(file, "<g>\n");
	fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open polyline
	
	float divider = 5 * 60;

	// spiral in toward the center
	for(int i = REVOLUTIONS-1; i >= 0; i--){
		for(float a = TWOPI; a >= 0; a -= TWOPI/divider){
			float revolution = a/TWOPI;
			float radius = 2*(i+revolution) + sin(a*wobbleFreq) * wobbleMag * 2*(i+revolution);
			float x = width*.5  + cos(a) * radius * SPACING;
			float y = height*.5 + sin(a) * radius * SPACING;
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}

	// // OPTIONAL: pick up the pen when it gets to the middle
	// fprintf(file, "\"/>\n"); // closing quote
	// fprintf(file, "<polyline fill=\"none\" stroke=\"#000000\" points=\"");  // hanging open quote
	
	// spiral out from the center
	for(int i = 0; i < REVOLUTIONS; i++){
		for(float a = 0; a <= TWOPI; a += TWOPI/divider){
			float revolution = a/TWOPI;
			float radius = 2*(i+revolution) + sin(a*wobbleFreq) * wobbleMag * 2*(i+revolution);
			float x = width*.5  + cos(a-TWOPI*ROTATE_2ND) * radius * SPACING;
			float y = height*.5 + sin(a-TWOPI*ROTATE_2ND) * radius * SPACING;
			fprintf(file, "%.2f,%.2f ", x, y);
		}
	}
	fprintf(file, "\"/>\n"); // closing quote

	fprintf(file, "</g>\n");
	fprintf(file, "</svg>");
	fclose(file);
	return 0;
}