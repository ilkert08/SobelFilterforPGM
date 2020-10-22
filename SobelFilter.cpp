#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>



int getIndex(int x, int y, int width){
	int value;
	value = x * width + y;
	return value;
}

int normalize(int max, int min, int value){
	float newValue =(float) (value - min) / (max-min);
	//printf("New: %f", newValue);
	return newValue *255;
}



//TODO: tek boyutlu array icin get(i,j) tipi fonksiyon yaz. 


int main() {

  int yMatrix[3][3] = {
    {  1,  2,  1 },
    {  0,  0,  0 },
    { -1, -2, -1 }
  };
  int xMatrix[3][3] = {
    { -1, 0, 1 },
    { -2, 0, 2 },
    { -1, 0, 1 }
  };





    /*
    //Tek boyutlu arrayde 2 boyutlu erisim icin indexler. 
    //X: islem yappilan index
    //Y: genislik(width)
        x-y-1     x-y    x-y+1
        x-1         x      x+1
        x+y-1     x+y    x+y+1      
    */
    /*
    for(i=0; i< 640*480; i++){
    	int arr[9] = {(i - width - 1), (i - width), (i - width + 1), (i-1),  (i), (i + 1), (i + width - 1), (i+ width), (i + width + 1});
    	
	}*/
	
	
   int i, j, k;
   int width;
   int height;
    //printf("selam: %d", imgMatrix[400][350]);
  
   char firstLines[4][200]; // header bilgilerini tutan matris.
   char buffer[200];
   
   FILE * fp;
   int lineCount = 0;
   fp = fopen("bird.pgm", "rb");
   printf("Opening the file test.c in read mode\n");

   if (fp == NULL) {
     printf("Could not open file test.c");
     return 1;
   }
   printf("Reading the file test.c\n");
   //printf("Atoi: %d", atoi(" "));   
   
   
   i = 0;
    while(fgets(buffer, 200, fp)) { //Header bilgilerini alan dongu.
	    int limit = 2;	
    	printf("%s", buffer);
    	strcpy(firstLines[i], buffer);
    	i++;
    	if(buffer[0] == '#'){
    		printf("Yorum var!");
    		limit++;
		}
    	if(i>limit){
    		break;
		}
  	}
	  if(firstLines[1][0] == '#'){
   		char str[20];
   		strcpy(str, firstLines[2]);
   		const char s[2] = " ";
  		char *token;
 		  token = strtok(str, s);
   		  width = atoi(token); //genisligin alinmasi
   		  printf("%s", token);
		  token = strtok(NULL, s);
		  printf("%s", token);
		  height = atoi(token); //yuksekligin alinmasi
  		 }
	 else{	
		  char str[20];
		  strcpy(firstLines[3], "#");
   		  strcpy(str, firstLines[1]);
   	      const char s[2] = " ";
  		  char *token;
 		  token = strtok(str, s);
   		  width = atoi(token); //genisligin alinmasi
   		  printf("%s", token);
		  token = strtok(NULL, s);
		  printf("%s", token);
		  height = atoi(token); //yuksekligin alinmasi			  		 	
		   }
		   
	for(i=0; i<4; i++){
		printf("i: %d %s\n", i, firstLines[i]);
	}	   
	  	
	  	
  //int mat[width][height] = {0};
  int *mat = (int *)malloc((width)*(height) * sizeof(int));

  unsigned char buffer2[80];
  int buff;
  
  j = 0;
  while(fread(&buffer2 ,sizeof(buffer2),1,fp) > 0){
  	  for(i=0; i< 80; i++){
	  	//printf(":%d: ", buffer2[i]); // prints a series of bytes
	  	int tmp = getIndex((j / width),(j % width), width);
	  	mat[tmp] = buffer2[i];
	  	j++;
  		}
  }
  
  //ySobel(width, height);
  
  
  int sum = 0;
  //Y padding
  
  for(i=1; i<height-1; i++){
  	for(j=1; j< width-1; j++){  
	    int tmp = getIndex((i-1),(j-1), width);	    
	    sum+= mat[tmp] * yMatrix[0][0];
	    tmp = getIndex((i-1),(j), width);
	    sum+= mat[tmp]  * yMatrix[0][1];
	    tmp = getIndex((i+1),(j-1), width);
	    sum+= mat[tmp] * yMatrix[0][2];
	    tmp = getIndex((i),(j-1), width);
	    sum+= mat[tmp]  * yMatrix[1][0];
	    tmp = getIndex((i),(j), width);
	    sum+= mat[tmp]     * yMatrix[1][1];
	    tmp = getIndex((i),(j+1), width);
	    sum+= mat[tmp]   * yMatrix[1][2];
	    tmp = getIndex((i+1),(j-1), width);
	    sum+= mat[tmp] * yMatrix[2][0];
	    tmp = getIndex((i+1),(j), width);
	    sum+= mat[tmp]   * yMatrix[2][1];
	    tmp = getIndex((i+1),(j+1), width);
	    sum+= mat[tmp] * yMatrix[2][2];
	    mat[tmp] = sum;
	  }
  }  
  
  //Min Max normalization
  
  int max = 0;
  for(i=1; i<width*height; i++){
  	if(mat[i] > mat[max]){
  		max = i;
	  }
  }
  int min = 0;
  for(i=1; i<width*height; i++){
  	if(mat[i] < mat[min]){
  		min = i;
	  }
  }  
  
  for(i=0; i< width*height; i++){
  	mat[i] = normalize(mat[max], mat[min], mat[i]);
  }
  
  
  fclose(fp);
  
  
  
  
  
  
  
  
  
  
  
  //TODO:  dosyaya yazma islemini hallet!
  ///////////////
  
  printf("\nKendi Dosyamiz\n");
  FILE *fp2;
  fp2 = fopen("ilkPgm2.pgm","w+");
  
  for(i=0; i<4; i++){
  	if(firstLines[i][0]=='#'){
  		continue;
	  }	  
	fprintf(fp2,firstLines[i]);  
	//fwrite (firstLines[i] , sizeof(firstLines[i]), sizeof(firstLines[i, fp2);
	}	
	fclose(fp2);


  
  //unsigned char iBuffer[20] = "selam ilker\n";
  fp2 = fopen("ilkPgm2.pgm", "ab");
  
  for(i=0; i< width*height; i++){
	  fwrite (&mat[i] , sizeof(unsigned char), 1, fp2); 
  	
  }

 /* for(i=0; i<height; i++){
  	int iBuffer[width];
	for(j=0; j<width; j++){
		int tmp = getIndex((i),(j), width);
		iBuffer[j] = mat[tmp];
	}	 
	fwrite (iBuffer , sizeof(iBuffer), sizeof(iBuffer), fp2); 
  } */



  
  fclose (fp2);


	
   fp = fopen("ilkPgm2.pgm", "rb");
   printf("Opening the file test.c in read mode\n");

   if (fp == NULL) {
     printf("Could not open file test.c");
     return 1;
   }
   printf("Reading the file test.c\n");
   
    i = 0;
    while(fgets(buffer, 80, fp)) { //Header bilgilerini alan dongu.
	    int limit = 2;	
    	printf("%s", buffer);
    	i++;
    	if(buffer[0] == '#'){
    		printf("Yorum var!");
    		limit++;
		}
    	if(i>limit){
    		break;
		}
	}

	
  unsigned char buffer3[80];
  
  j = 0;
  while(fread(&buffer3 ,sizeof(buffer3),1,fp) > 0){
  	  for(i=0; i< 80; i++){
	  	//printf(":%d: ", buffer3[i]); // prints a series of bytes
	  	j++;
  		}
  		if(j>3){
  			//break;
		  }
  } 
  
  fclose(fp);
  
  
   
	
    

	return 0; 
}
