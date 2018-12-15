// C++ program to implement external sorting using 
// merge sort 
#include <bits/stdc++.h>
#define MAXNARQS 10
#define MAXMEM 520 * 1024 * 1024
using namespace std; 

struct Registro{
	int chave;
	char nome[21];
	int idade;
};

struct MenorNo 
{ 
	// The RegistroInformacoesArquivo to be stored 
	Registro RegistroInformacoesArquivo; 

	// index of the array from which the RegistroInformacoesArquivo is taken 
	int i; 
}; 

// Prototype of a utility function to swap two min heap nodes 
void swap(MenorNo* x, MenorNo* y); 

// A class for Min Heap 
class ArvoreMenor 
{ 
	MenorNo* harr; // pointer to array of RegistroInformacoesArquivos in heap 
	int TamanhoArvore;	 // size of min heap 

public: 
	// Constructor: creates a min heap of given size 
	ArvoreMenor(MenorNo a[], int size); 

	// to heapify a subtree with IndiceMenorNo at given index 
	void MenorIndiceArvore(int); 

	// to get index of left child of node at index i 
	int left(int i) { return (2 * i + 1); } 

	// to get index of right child of node at index i 
	int right(int i) { return (2 * i + 2); } 

	// to get the IndiceMenorNo 
	MenorNo getMin() { return harr[0]; } 

	// to replace IndiceMenorNo with new node x and heapify() 
	// new IndiceMenorNo 
	void replaceMin(MenorNo x) 
	{ 
		harr[0] = x; 
		MenorIndiceArvore(0); 
	} 
}; 

// Constructor: Builds a heap from a given array a[] 
// of given size 
ArvoreMenor::ArvoreMenor(MenorNo a[], int size) 
{ 
	TamanhoArvore = size; 
	harr = a; // store address of array 
	int i = (TamanhoArvore - 1) / 2; 
	while (i >= 0) 
	{ 
		MenorIndiceArvore(i); 
		i--; 
	} 
} 

// A recursive method to heapify a subtree with IndiceMenorNo 
// at given index. This method assumes that the 
// subtrees are already heapified 
void ArvoreMenor::MenorIndiceArvore(int i) 
{ 
	int l = left(i); 
	int r = right(i); 
	int smallest = i; 
	if (l < TamanhoArvore && harr[l].RegistroInformacoesArquivo.chave < harr[i].RegistroInformacoesArquivo.chave) 
		smallest = l; 
	if (r < TamanhoArvore && harr[r].RegistroInformacoesArquivo.chave < harr[smallest].RegistroInformacoesArquivo.chave) 
		smallest = r; 
	if (smallest != i) 
	{ 
		swap(&harr[i], &harr[smallest]); 
		MenorIndiceArvore(smallest); 
	} 
} 

// A utility function to swap two RegistroInformacoesArquivos 
void swap(MenorNo* x, MenorNo* y) 
{ 
	MenorNo temp = *x; 
	*x = *y; 
	*y = temp; 
} 

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(Registro MemoriaRuns[], int Esq, int Meio, int Dir) 
{ 
	//int i, j, k; 
	int LadoEsquerdo = Meio - Esq + 1; 
	int LadoDireito = Dir - Meio; 

	/* create temp arrays */
	Registro VetorAuxiliarEsquerdo[LadoEsquerdo];
	Registro VetorAuxiliarDireito[LadoDireito]; 

	/* Copy data to temp arrays L[] and R[] */
	for(int i = 0; i < LadoEsquerdo; i++) {
		VetorAuxiliarEsquerdo[i] = MemoriaRuns[Esq + i];
	} 
	for(int j = 0; j < LadoDireito; j++) {
		VetorAuxiliarDireito[j] = MemoriaRuns[Meio + 1 + j]; 
	}

	/* Merge the temp arrays back into arr[l..r]*/
	int i = 0; // Initial index of first subarray 
	int j = 0; // Initial index of second subarray 
	int Auxiliar = Esq; // Initial index of merged subarray 
	while (i < LadoEsquerdo && j < LadoDireito)
	{ 
		if (VetorAuxiliarEsquerdo[i].chave <= VetorAuxiliarDireito[j].chave) {
			MemoriaRuns[Auxiliar++] = VetorAuxiliarEsquerdo[i++]; }
		else{
			MemoriaRuns[Auxiliar++] = VetorAuxiliarDireito[j++]; }
	} 

	/* Copy the remaining RegistroInformacoesArquivos of L[], if there 
	are any */
	while (i < LadoEsquerdo) {
		MemoriaRuns[Auxiliar++] = VetorAuxiliarEsquerdo[i++]; }

	/* Copy the remaining RegistroInformacoesArquivos of R[], if there 
	are any */
	while(j < LadoDireito) {
		MemoriaRuns[Auxiliar++] = VetorAuxiliarDireito[j++]; }
} 

/* l is for left index and r is right index of the 
sub-array of arr to be sorted */
void mergeSort(Registro MemoriaRuns[], int Esq, int Dir) 
{
	if (Esq < Dir) 
	{ 
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int Meio = Esq + (Dir - Esq) / 2; 

		// Sort first and second halves 
		mergeSort(MemoriaRuns, Esq, Meio); 
		mergeSort(MemoriaRuns, Meio + 1, Dir); 

		merge(MemoriaRuns,Esq, Meio, Dir); 
	} 
} 

// Merges k sorted files. Names of files are assumed 
// to be 1, 2, 3, ... k 
void CriandoArquivoFinal(char *ArquivoSaida, int Memoria, int NumeroArquivos) 
{ 
	FILE* vetorEntrada[NumeroArquivos]; 
	for (int i = 0; i < NumeroArquivos; i++) 
	{ 
		char IndiceRuns[20]; 

		// convert i to string 
		snprintf(IndiceRuns, sizeof(IndiceRuns), "%d", i); 

		// Open output files in read mode. 
		//in[i] = openFile(fileName, "r"); 
		vetorEntrada[i] = fopen(IndiceRuns, "r");
	} 

	// FINAL OUTPUT FILE 
	//FILE *out = openFile(ArquivoSaida, "w"); 
	FILE *vetorSaida = fopen(ArquivoSaida, "w");

	// Create a min heap with k heap nodes. Every heap node 
	// has first RegistroInformacoesArquivo of scratch output file 
	MenorNo* VetorArvore = new MenorNo[NumeroArquivos]; 
	int i; 
	for (i = 0; i < NumeroArquivos; i++) 
	{ 
		// break if no output file is empty and 
		// index i will be no. of input files 
		if (fread(&VetorArvore[i].RegistroInformacoesArquivo, 1, sizeof(Registro), vetorEntrada[i]) == 0 )
			break; 

		VetorArvore[i].i = i; // Index of scratch output file 
	} 
	ArvoreMenor RaizNo(VetorArvore, i); // Create the heap 

	int count = 0; 

	// Now one by one get the minimum RegistroInformacoesArquivo from min 
	// heap and replace it with next RegistroInformacoesArquivo. 
	// run till all filled input files reach EOF 
	while (count != i) 
	{ 
		// Get the minimum RegistroInformacoesArquivo and store it in output file 
		MenorNo IndiceMenorNo = RaizNo.getMin(); 
		fprintf(vetorSaida, "%d %s %d\n", IndiceMenorNo.RegistroInformacoesArquivo.chave, IndiceMenorNo.RegistroInformacoesArquivo.nome, IndiceMenorNo.RegistroInformacoesArquivo.idade); 

		// Find the next RegistroInformacoesArquivo that will replace current 
		// IndiceMenorNo of heap. The next RegistroInformacoesArquivo belongs to same 
		// input file as the current min RegistroInformacoesArquivo. 
		if (fread(&IndiceMenorNo.RegistroInformacoesArquivo, 1, sizeof(Registro), vetorEntrada[IndiceMenorNo.i]) == 0 )
		{ 
			IndiceMenorNo.RegistroInformacoesArquivo.chave = INT_MAX; 
			count++; 
		} 

		// Replace IndiceMenorNo with next RegistroInformacoesArquivo of input file 
		RaizNo.replaceMin(IndiceMenorNo); 
	} 

	// close input and output files 
	for (int i = 0; i < NumeroArquivos; i++) 
		fclose(vetorEntrada[i]); 

	fclose(vetorSaida); 
} 


Registro* LerRegistro(Registro* registro, FILE* in){
	fread(&registro, 1, sizeof(Registro), in);
	return registro;
	
}

// Using a merge-sort algorithm, create the initial runs 
// and divide them evenly among the output files 
void CriandoRuns(char *ArquivoEntrada,int Memoria,int NumeroArquivos) 
{ 
	bool ProximoArquivo = true; 
	int IndiceArquivoSaida = 0; 
	int i;
	
    Registro* MemoriaRuns = (Registro*)malloc(Memoria * sizeof(Registro));
	// For big input file 
	//FILE *in = openFile(ArquivoEntrada, "r"); 
    FILE *ArquivoCompleto = fopen(ArquivoEntrada, "r");
	// output scratch files 
	//FILE* out[NumeroArquivos]; 
    FILE* ArquivosRuns[NumeroArquivos];
	char IndiceRuns[20]; 
	for (int i = 0; i < NumeroArquivos; i++) 
	{ 
		// convert i to string 
		snprintf(IndiceRuns, sizeof(IndiceRuns), "%d", i); 

		// Open output files in write mode. 
		ArquivosRuns[i] = fopen(IndiceRuns, "w"); 
	} 

	// allocate a dynamic array large enough 
	// to accommodate runs of size Memoria 
	 
	while (ProximoArquivo) 
	{ 
		// write Memoria RegistroInformacoesArquivos into arr from input file 
		for (i = 0; i < Memoria; i++) 
		{
			if (fread(&MemoriaRuns[i], 1, sizeof(Registro), ArquivoCompleto) == 0) 
			{ 
				ProximoArquivo = false; 
				break; 
			}
			
		} 

		// sort array using merge sort 
		mergeSort(MemoriaRuns, 0, i - 1); 

		// write the records to the appropriate scratch output file 
		// can't assume that the loop runs to Memoria 
		// since the last run's length may be less than Memoria 
		for (int j = 0; j < i; j++)  
			fwrite(&MemoriaRuns[j], sizeof(Registro), 1, ArquivosRuns[IndiceArquivoSaida]);

		IndiceArquivoSaida++; 
	} 

	// close input and output files 
	for (int i = 0; i < NumeroArquivos; i++) 
		fclose(ArquivosRuns[i]); 

	fclose(ArquivoCompleto); 
} 

// For sorting data stored on disk 
void OrdernacaoExterna(char* ArquivoEntrada, char *ArquivoSaida, int NumeroArquivos, int Memoria) 
{ 
	// read the input file, create the initial runs, 
	// and assign the runs to the scratch output files 
	CriandoRuns(ArquivoEntrada, Memoria, NumeroArquivos); 

	// Merge the runs using the K-way merging 

	CriandoArquivoFinal(ArquivoSaida, Memoria, NumeroArquivos); 
} 


void removerArquivo(bool ExcluirArquivosVazios, int NumeroArquivos) {
		remove ("input.txt");
		if(ExcluirArquivosVazios) {
			FILE *arquivo; 
			long tamanho;
			for (int i = 0; i < NumeroArquivos; i++) { 
				char fileName[20]; 
				snprintf(fileName, sizeof(fileName), "%d", i); 
				arquivo = fopen(fileName, "r");
				fseek(arquivo, 0, SEEK_END);
				tamanho = ftell(arquivo);
	        	if(tamanho == 0){
					remove (fileName);
				}
			}
		}
	}


// Driver program to test above 
int main() 
{ 
	// No. of Partitions of input file. 
	 
    int NumeroArquivos = MAXNARQS;
	// The size of each partition 
	
    int Memoria = MAXMEM/sizeof(Registro); 

	char ArquivoEntrada[] = "input.txt"; 
	char ArquivoSaida[] = "saida.dat"; 

	/*FILE* in = openFile(ArquivoEntrada, "w"); 
	FILE* in2 = openFile("entrada.dat", "r+");*/
    FILE* Entrada1 = fopen(ArquivoEntrada, "w");
    FILE* Entrada2 = fopen("entrada.dat", "r+");

	Registro registro;
	
	srand(time(NULL));
	
	while(fscanf(Entrada2, "%d %s %d", &registro.chave, registro.nome, &registro.idade) == 3){
		
		fwrite(&registro, sizeof(Registro), 1, Entrada1);
	}
	fclose(Entrada1);
	fclose(Entrada2);
	
	OrdernacaoExterna(ArquivoEntrada, ArquivoSaida, NumeroArquivos, Memoria); 
	
	//ExcluirArquivosVazios CASO SEJA TRUE EXCLUI ARQUIVOS QUE ESTÃO VAZIOS,
	//E NÃO FORAM NECESSARIOS DURANTE A EXECUÇÃO DO PROGRAMA.
	bool ExcluirArquivosVazios = true;//MUDAR PARA FALSE CASO QUEIRA SE MANTENHA ARQUIVOS VAZIOS
	removerArquivo(ExcluirArquivosVazios, NumeroArquivos);
	
	return 0; 
} 