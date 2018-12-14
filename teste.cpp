// C++ program to implement external sorting using 
// merge sort 
#include <bits/stdc++.h>
#include <string>


int main() 
{ 
	
	char input_file[] = "entrada.dat"; 
	

	FILE* in = fopen(input_file, "w"); 
	
	srand(time(NULL));
	for (int i = 0; i < 60; i++) {
		fprintf(in, "%d %s %d\n", rand(), "Clovis", i);
	}
	
	fclose(in);
	
	return 0; 
} 
