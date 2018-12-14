// https://opendsa-server.cs.vt.edu/ODSA/Books/CS3/html/ExternalSort.html
#include <bits/stdc++.h> 
using namespace std; 

#define MAXNARQS 100
#define MAXMEM 512 //MB LEMBRAR DE NO FINAL MULTIPLICAR POR 1000

#define MAX_REGISTRO_SIZE 1000

struct Registro{
	int chave;
	char nome[21];
	int idade;
};

/*void merge(Registro arr[], int esq, int meio, int dir) {
    int i, j, k; 
	int n1 = m - l + 1; 
	int n2 = r - m;
    
    Registro* ESQ = (Registro*)malloc(n1 * sizeof(Registro));
    
    Registro* DIR = (Registro*)malloc(n2 * sizeof(Registro));
    
    
	
	
	
}*/

void mergeSort(Registro arr[], int esq, int dir) {
    
    if( esq < dir ) {
        int meio = esq + (dir - esq)/2;
        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);
        
        //merge(arr, esq, meio, dir);
    }
    
	
}

FILE* openFile(char* fileName, char* mode) 
{ 
	FILE* fp = fopen(fileName, mode); 
	if (fp == NULL) 
	{ 
		perror("Erro ao abrir o arquivo.\n"); 
		exit(EXIT_FAILURE); 
	} 
	return fp; 
} 

void read(Registro arr[], int n_p, FILE* fp){
   char temp;
   
   //Registro* arr = (Registro*)malloc(run_size * sizeof(Registro));
   
   if(fp==NULL){
       printf("Error\n");
   }
   //fscanf(fp,"%d %s %d\n", reg[n_p].chave, reg[n_p].nome, reg[n_p].idade);
   fscanf(fp,"%d %s %d\n", &arr[n_p].chave, arr[n_p].nome, &arr[n_p].idade);
}

void externalSort(char* input_file, char *output_file, int num_ways, int run_size) 
{

    int i = 0;
    int size;
    
    FILE* out[num_ways]; 
	char fileName[2]; 
	for (int i = 0; i < num_ways; i++) 
	{ 
		snprintf(fileName, sizeof(fileName), "%d", i); 
		out[i] = openFile(fileName, "w"); 
	} 
  
    //Registro reg[MAX_REGISTRO_SIZE];
    Registro* arr = (Registro*)malloc(1000 * sizeof(Registro));
    
    FILE* fp = openFile(input_file, "r"); 
 
    while (!feof(fp)) {
        read(arr, i, fp);
        i++;
    }
    size = i;
    
    for (i = 0; i < size; ++i){
        printf("%d %s %d\n", arr[i].chave, arr[i].nome, arr[i].idade);
    }
    
    
    //##############################################################
    i = 0; 
    bool more_input = true; 
	int next_output_file = 0; 
	
	while (more_input) 
	{ 
		for (int j = 0; j < size; j++) 
			fprintf(out[next_output_file], "%d\n ", arr[j].chave); 

    	next_output_file++; 
	} 

	// close input and output files 
	for (int i = 0; i < num_ways; i++) 
		fclose(out[i]); 
    
    //###############################################################
    
    fclose(fp);
}

int main() 
{ 
	int num_ways = 10;
	int run_size = MAXMEM; 

	char input_file[] = "entrada.dat"; 
	char output_file[] = "saida.dat"; 

	FILE* in = openFile(input_file, "w"); 

	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
	    fprintf(in, "%d ", rand()); 
	    fprintf(in, "%s ", "clovis");
	    fprintf(in, "%d\n", i);
	}
	fclose(in); 
	
    externalSort(input_file, output_file, num_ways, run_size); 
    
	return 0; 
} 