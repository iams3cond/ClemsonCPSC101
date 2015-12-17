//
//  instagram.c
//  
//
//  Created by Andrew Marion Hunter on 4/6/15.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "instagram.h"


int subscript(int r, int c, int width){
        return r * width + c;
}

int randomNumber(int lowest, int highest){
    int range = highest - lowest + 1;
    return rand() % range + lowest;
}

void writeHeader(FILE * file, int width, int height){
    fprintf(file,"P6\n %d %d 255\n",width,height);
}


void writePixel(FILE * file, pixel p){
    fprintf(file,"%c%c%c",(unsigned char)p.r,(unsigned char)p.g, (unsigned char)p.b);
}


void writePPMFile(char * filename, pixel * picture, int width, int height){
    FILE * writeFile = fopen(filename,"w");
    writeHeader(writeFile,width,height);
    

    int r, c;
    for (r = 0; r < height; r++){
        for (c = 0; c < width; c++){
            writePixel(writeFile,picture[subscript(r,c,width)]);
        }
    }
    fclose(writeFile);
}


void readHeader(FILE * file, int * width, int * height){
    fscanf(file,"P6\n %d %d 255\n",width,height);
}


void readPixel(FILE * file, pixel * p){
    unsigned char r, g, b;
    fscanf(file,"%c%c%c",&r,&g,&b);
    p->r = r;
    p->g = g;
    p->b = b;
}


pixel * readPPMFile(char * filename, int * width, int * height){
    FILE * readFile = fopen(filename,"r");
        readHeader(readFile,width,height);
    
    pixel * image = malloc(sizeof(pixel)*(*width)*(*height));
    
    int r, c;
    for (r = 0; r < *height; r++){
        for (c = 0; c < *width; c++){
            readPixel(readFile,&image[subscript(r,c,*width)]);
        }
    }
    
    fclose(readFile);
    return image;
}

void contrast(pixel * image, int width, int height){
    int value;
    
    printf("Please enter an integer between 0 and 255");
    scanf("%d",&value);
    
    int r, c;
    for (r = 0; r < height; r++){
        for (c = 0; c < width; c++){
		pixel pix = image[subscript(r,c,width)];
            
            if(pix.r < value || pix.g < value || pix.b < value){
                pix.r = 255;
                pix.g = 255;
                pix.b = 255;
            }
            else{
                pix.r = 0;
                pix.g = 0;
                pix.b = 0;
            }
		image[subscript(r,c,width)] = pix;
        }
    }
}

void normalize(pixel * image, int width, int height){
    int value;
    int rMinimumValue = 255;
    int gMinimumValue = 255;
    int bMinimumValue = 255;
    int rMaximumValue = 0;
    int gMaximumValue = 0;
    int bMaximumValue = 0;
    
    int r, c;
    for (r = 0; r < height; r++){
        for (c = 0; c < width; c++){
            pixel pix = image[subscript(r,c,width)];
            
            if(pix.r < rMinimumValue){
                rMinimumValue = pix.r;
            }
            if(pix.r > rMaximumValue){
                rMaximumValue = pix.r;
            }
            if(pix.g < gMinimumValue){
                gMinimumValue = pix.g;
            }
            if(pix.g > gMaximumValue){
                gMaximumValue = pix.g;
            }
            if(pix.b < bMinimumValue){
                bMinimumValue = pix.b;
            }
            if(pix.b > bMaximumValue){
                bMaximumValue = pix.b;
            }

            image[subscript(r,c,width)] = pix;
        }
    }
    for (r = 0; r < height; r++){
        for (c = 0; c < width; c++){
            pixel pix = image[subscript(r,c,width)];
            
            pix.r = (pix.r - rMinimumValue) * (rMaximumValue - rMinimumValue) / 255.0 + rMinimumValue;
            pix.g = (pix.g - gMinimumValue) * (gMaximumValue - gMinimumValue) / 255.0 + gMinimumValue;
            pix.b = (pix.b - bMinimumValue) * (bMaximumValue - bMinimumValue) / 255.0 + bMinimumValue;

            
            image[subscript(r,c,width)] = pix;
        }
    }
}


void shaky(pixel * image, int width, int height){
    srand(time(NULL));
    
    int r, c;
    int randomR, randomC;
    for (r = 1; r < height-2; r++){
        for (c = 1; c < width-2; c++){
            pixel pix = image[subscript(r,c,width)];
            
            randomR = randomNumber(r-1, r+1);
            randomC = randomNumber(c-1, c+1);
            
            pixel rando = image[subscript(randomR,randomC,width)];
            
            pix.r = rando.r;
            pix.g = rando.g;
            pix.b = rando.b;
            
            image[subscript(r,c,width)] = pix;
        }
    }

}








