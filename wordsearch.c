#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);

void altlow( char *p, int length) {
	
	//printf("This is result: %s\n", result);
	for( int i =0; i < length; i++){
/* Fill-in ‘A’ = 65, ‘a’ = 97, ‘Z’ = 90, ‘z’ = 122 */
		//printf("P is : %c\n",*p);
		if (*p >= 'A' && *p <= 'Z'){
		*p +=  'a'- 'A';
		//printf("P is now : %c\n",*p);
		}
		p = p +1;
	}

}


char* lowCase(char* str) {
	char* p;
	char* result;
	result = (char*) malloc((1+strlen(str)));
	strcpy(result, str);
	//printf("This is result: %s\n", result);
	for( p=result; *p !='\0'; p++){
/* Fill-in ‘A’ = 65, ‘a’ = 97, ‘Z’ = 90, ‘z’ = 122 */
		//printf("P is : %c\n",*p);
		if (*p >= 'A' && *p <= 'Z'){
		*p +=  'a'- 'A';
		//printf("P is now : %c\n",*p);
		}
	}
return result;
}

char* changeCase(char* str) {
	char* p;
	char* result;
	result = (char*) malloc((1+strlen(str)));
	strcpy(result, str);
	//printf("This is result: %s\n", result);
	for( p=result; *p !='\0'; p++){
/* Fill-in ‘A’ = 65, ‘a’ = 97, ‘Z’ = 90, ‘z’ = 122 */
		//printf("P is : %c\n",*p);
		if (*p >= 'a' && *p <= 'z'){
		*p += 'A' - 'a';
		//printf("P is now : %c\n",*p);
		}
	}
return result;
}

/*void LtRSearch(char** block, int bSize, char** list, int listSize){
	
}*/


// Main function, DO NOT MODIFY!!!	
int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i=0; i<bSize; i++){
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i=0; i<50; i++){
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i=0; i<49; i++){
		*(*(words+i) + strlen(*(words+i))-2) = '\0';	
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i=0; i<50; i++){
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}

void printPuzzle(char** block, int bSize){
	// This function will print out the complete puzzle grid (arr)
	
	for(int i=0; i<bSize; i++){
       

        printf( "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", **(block+i), *(*(block+i)+1), *(*(block+i)+2), *(*(block+i)+3), *(*(block+i)+4), *(*(block+i)+5), *(*(block+i)+6), *(*(block+i)+7), *(*(block+i)+8), *(*(block+i)+9), *(*(block+i)+10), *(*(block+i)+11), *(*(block+i)+12), *(*(block+i)+13), *(*(block+i)+14) );
    }

}

void searchPuzzle(char** block, int bSize, char** list, int listSize){
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	
	//first task: take in first word on list and save substring consisting of first character.
	
	for(int i=0; i<listSize; i++){
		
		char *CWord = (char*) malloc(strlen(*(list +i)));
		char *CWordlow = (char*) malloc(strlen(*(list +i)));
		  
		  strcpy(CWord, *(list+i));
		 
	
		 // printf("Current String is : %s\n",CWord); // I need to uppercase this somehow
		  
		  CWord = changeCase(CWord);
		//  printf("Upcase String is : %s\n",CWord); 
		  
		  CWordlow = lowCase(CWord);
		//  printf(" lowcase String is : %s\n",CWordlow); 
	
		char Fletter = *(*(list+i));
	//	printf( "First Letter is: %c\n", Fletter);
		
	
	//2nd task: save whole row of wordsearch, use string library function to see if word appears. (covers left to right)
	// this needs to be a nested for loop. 
	
	for(int j=0; j < bSize; j++){
		
	char *CRow = (char*) malloc(strlen(*(block +j)));
	
	
	strcpy(CRow, *(block+j));
	//printf("This is the copy being stored '%s'\n",CRow);
	
	 *(block +j) = changeCase(*(block +j));
	
	//printf("Current Row is : %s\n",CRow);
	
	char *p;
	p	= strstr(*(block +j), CWord);
	
	if (p) { 
        printf("Word found: %s\n", *(list+i)); 
       // printf("First occurrence of string '%s' in '%s' is '%s'\n",CWord, *(block +j), p);
		strcpy(*(block +j), CRow);
		//printf("Reloaded *(block +j)is '%s' and p now is '%s'\n",*(block +j), p);
		altlow( p , strlen(CWord));
		//printf("After calling altlow, *(block +j) is '%s' and p now is '%s'\n",*(block +j), p);
		
		} 
	else {
		strcpy(*(block +j), CRow);
		//printf("Reloaded *(block +j)is '%s' and p now is '%s'\n",*(block +j), p);
	}
	
		
	}
	//printPuzzle(block, bSize);
	
	// 3rd task: save whole column of word search , use string library function to see if word appears
	
	for(int m=0; m < bSize; m++){
		
	char *CCol = (char*) malloc(strlen(*(block +m)));
	char *copy = (char*) malloc(strlen(*(block +m)));
	
	for (int k =0; k < bSize; k++){
//	*(CRow +i) = *(*(list + i));// this highkey might be the key behind diagonal
	*(CCol +k) = *(*(block+k)+m);
	}
	
	strcpy(copy, CCol);
	CCol = changeCase(CCol);
	
	
	//printf("Current Column is : %s\n",CCol);
	
	char *p;
	p	= strstr(CCol, CWord);
	
	if (p) { 
        printf("Word found: %s\n", *(list+i)); 
        //printf("First occurrence of string '%s' in '%s' is '%s'\n",CWord, CCol, p); 
		strcpy(CCol, copy);
		altlow( p , strlen(CWord));
		} 
		else{
		strcpy(CCol, copy);}
		for (int k =0; k < bSize; k++){
	 *(*(block+k)+m) = *(CCol +k);
	}
	
	}
	
	// 4th task: same as 3rd but rows are now in reverse
	
	for(int m=0; m < bSize; m++){
		
	char *CCol2 = (char*) malloc(strlen(*(block +m)));
	char *copy = (char*) malloc(strlen(*(block +m)));
	
	int r = 0;
	for (int k = bSize -1; k >= 0; k--){
//	*(CRow +i) = *(*(list + i));// this highkey might be the key behind diagonal
	*(CCol2+ r) = *(*(block+k)+m);
	r= r+1;
	}
	
	strcpy(copy, CCol2);
	CCol2 = changeCase(CCol2);
	
	
	//printf("Current Column is : %s\n",CCol);
	
	char *p;
	p	= strstr(CCol2, CWord);
	
	if (p) { 
        printf("Word found: %s\n", *(list+i)); 
        //printf("First occurrence of string '%s' in '%s' is '%s'\n",CWord, CCol2, p); 
		strcpy( CCol2, copy);
		altlow( p , strlen(CWord));
		} 
	else{
		strcpy(CCol2, copy);}
		
		r=0;
		for (int k = bSize -1; k >= 0; k--){
//	*(CRow +i) = *(*(list + i));// this highkey might be the key behind diagonal
	 *(*(block+k)+m) = *(CCol2+ r);
	r= r+1;
	}
	}
	
	//5th task: implement searching from low left : high right diagonal (/) 1st half = 4 to 15
	for(int s=4; s < 15; s++){ 
	
	char *CLDiag = (char*) malloc(sizeof(char)*s);
	char *copy = (char*) malloc(sizeof(char)*s);
	
	int u =0;
	for(int t=s-1; t >= 0; t--){
		*(CLDiag+ u) = *(*(block+t)+u);
		u = u +1;
	}
	
	stpcpy(copy,CLDiag);
	CLDiag = changeCase(CLDiag);
	
	//printf("Current Diagonal is : %s\n",CLDiag);
	char *p;
	p	= strstr(CLDiag, CWord);
	
	if (p) { 
        printf("Word found: %s\n", *(list+i)); 
        //printf("First occurrence of string '%s' in '%s' is '%s'\n",CWord, CLDiag, p); 
		strcpy( CLDiag, copy);
		altlow( p , strlen(CWord));
		} 
	else{
		strcpy(CLDiag, copy);}
		
		u=0;
		for(int t=s-1; t >= 0; t--){
		*(*(block+t)+u) = *(CLDiag+ u);
		u = u +1;
	}
	 }
	 
	
	//To do list : lower half of CLDiag & both halves of CRDiag. Also need to figure out how to update crosswoard and still be okay with finding words
	
	//6th task: implement searching from low left : high right diagonal (/) 2nd half = 15 to 4
	int u = 1;
	int v = 1;
	for(int s=14; s >= 4; s--){ // need to iterate 11 times
	
	char *CLDiag2 = (char*) malloc(sizeof(char)*s);
	char *copy = (char*) malloc(sizeof(char)*s);
	
	int m=0;
	int z = u; 
	for(int t=0; t < s; t++){
		*(CLDiag2+ m) = *(*(block+(14-t))+z);
		z= z+1;
		m=m+1;
	}
	u= u +1;
	
	strcpy(copy , CLDiag2);
	CLDiag2 = changeCase(CLDiag2);
	
	//printf("Current Diagonal is : %s\n",CLDiag2);
	char *p;
	p	= strstr(CLDiag2, CWord);
	
	if (p) { 
        printf("Word found: %s\n", *(list+i)); 
        //printf("First occurrence of string '%s' in '%s' is '%s'\n",CWord, CLDiag2, p); 
		strcpy(CLDiag2,copy);
		altlow( p , strlen(CWord));
		} 
	else {
		strcpy(CLDiag2,copy);
	}
	int r = 0;
	int y = v;
		for(int t=0; t < s; t++){
		*(*(block+(14-t))+y) = *(CLDiag2+ r);
		y= y+1;
		r=r+1;
		}
	v= v +1;
		
		
	 }
	 
	 //7th task: implement searching from low right : high left (\) 1st half = 14 to 4
	
	for(int s=4; s <= 15; s++){ 
	
	char *CRDiag = (char*) malloc(sizeof(char)*s);
	char *copy = (char*) malloc(sizeof(char)*s);
	
	int u =0;
	
	for(int t=s-1; t >= 0; t--){
		*(CRDiag+ u) = *(*(block+u)+(15-s)+u);
		u = u +1;
	}
	
	strcpy(copy, CRDiag);
	CRDiag = changeCase(CRDiag);
	//printf("Current Diagonal is : %s\n",CRDiag);
	char *p;
	p	= strstr(CRDiag, CWord);
	
	if (p) { 
        printf("Word found: %s\n", *(list+i)); 
        //printf("First occurrence of string '%s' in '%s' is '%s'\n",CWord, CRDiag, p); 
		strcpy(CRDiag,copy);
		altlow( p , strlen(CWord));
		} 
	else {
	strcpy(CRDiag,copy);
	}	
	
	u = 0;
	
	for(int t=s-1; t >= 0; t--){
		*(*(block+u)+(15-s)+u) = *(CRDiag+ u);
		u = u +1;
	}
		
	 }
	 
	 //8th task: implement searching from low right : high left (\) 2nd half = 14 to 4
	
	int y = 14;
	
	for(int s=1; s <= 11; s++){ // need to iterate 11 times
	
	char *CRDiag2 = (char*) malloc(sizeof(char)*y);
	char *copy = (char*) malloc(sizeof(char)*y);
	
	int m=0;
	int r=0;
	 
	for(int t=s; t < 15; t++){
		*(CRDiag2+ m) = *(*(block+t)+m);
		m=m+1;
	}
	y= y -1;
	
	strcpy(copy , CRDiag2);
	CRDiag2 = changeCase(CRDiag2);
	
	//printf("Current Diagonal is : %s\n",CRDiag2);
	
	char *p;
	p	= strstr(CRDiag2, CWord);
	
	if (p) { 
	
        printf("Word found: %s\n", *(list+i)); 
        //printf("First occurrence of string '%s' in '%s' is '%s'\n",CWord, CRDiag2, p); 
		strcpy(CRDiag2,copy);
		altlow( p , strlen(CWord));
		} 
	else{
		strcpy(CRDiag2,copy);
	}
	
		for(int t=s; t < 15; t++){
		*(*(block+t)+r) = *(CRDiag2+ r);
		r=r+1;
	}
	
	
	
	 }
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	}// big for loop end
	
/*
	for(int i=0; i<listSize; i++){
		for(int j=0; j < strlen(*(list+i)); j++){ 
	 printf( "%c", *(*(list+i)+j));
	 }
	 printf("\n");
	 } */
}
