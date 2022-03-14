#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	FILE* file;
	int count = 0;
	char c;
	char fileName[100];
	int nums[100];
	int i, j, min;
	int total = 0;

	/**
	This function takes in no parameters, but returns a pointer to the array we read in from the text file.
	**/
	int* readFile(char fileName[]){
		//Opens file in read mode
		file = fopen(fileName, "r");
		
		///If the file is null, it is not valid and cannot be opened. Return 1.
		if(NULL == file){
			printf("file cannot be opened \n");
		//File is found
		}else{
			printf("file found\n");
		}
		//Reading in file int by int until we reach EOF, or end of file
		while(fscanf(file, "%d", &nums[count])!= EOF){
    		nums[count++];
 		}
 		
 		//Close the file
 		fclose(file);
 		
 		return nums;
	}
	
	/**
	This function takes in an array as its parameter and sorts it using selection sort then returns a pointer to the sorted array.
	**/
	int* sort(int arr [] ){
		//Using selection sort to sort the numbers in an array
 		for (i = 0; i < count; ++i){
      		for (j = i + 1; j < count; ++j){
         		if (arr[i] > arr[j]){
            	min = arr[i];
            	arr[i] = arr[j];
            	arr[j] = min;
         		}
      		}
   		}
   		return arr;
	}
	
	/**
	This function takes in an array, opens a new output file named after the user input in write mode and writes the elements
	of the array line by line. It closes the file at the end and returns 0.
	**/
	int writeFile(char fileName[], int arr[]){
   		
   		//Open new file in write mode with user chosen name
   		FILE* infile = fopen(fileName,"w");
   		//Is file is null, it couldn't be created. Return 1.
 		if(NULL == infile){
 			printf("file cannot be created\n");
 			return 1;
 		//File was able to be created
		}else{
			printf("file successfully created\n");
		}
		
		//Going through the array and printing the number into our new file
		for(i=0; i<count; ++i){
			int num = nums[i];
			fprintf(infile, "%d\n", num);
		}
		//Close the new file.
		fclose(infile);
		return 0;
	}

/**
This is the main method, or what gets ran when you run the program. It has two parameters that take input from the command line.
int argc is 3 if there are two parameters that are passed in. argv[0] is the program name, argv[1] is the input file name,
argv[2] is the output file name. 
**/
int main(int argc, char **argv)
{
	strcpy(nums, sort(readFile(argv[1])));
	
	writeFile(argv[2], nums);
}
	

		
		
		
		
		


