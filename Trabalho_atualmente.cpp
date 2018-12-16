 
#include <bits/stdc++.h>
#define MAXNARQS 10
#define MAXMEM 520 * 1024 * 1024
using namespace std; 




struct Registro{
	int chave;
	char nome[21];
	int idade;
};
 
struct MenorNo { 
	 
	Registro RegistroInformacoesArquivo; 

	int i; }; 

 
class ArvoreMenor { 

	MenorNo* harr;  
	int TamanhoArvore;	 

public:ArvoreMenor(MenorNo a[], int size); 
	 
	
  void MenorIndiceArvore(int); 
  int noDireito(int i) { 
   return (2 * i + 2);} 
  MenorNo menorIndice() {
   return harr[0];}
 
  int noEsquerdo(int i) {
   return (2 * i + 1); } 
 
 
	 
	void trocaIndiceDoNo(MenorNo x) { 
       harr[0] = x;MenorIndiceArvore(0); } }; 


   ArvoreMenor::ArvoreMenor(MenorNo a[], int size){ 
  TamanhoArvore=size;harr=a;
 
   int i = (TamanhoArvore - 1) / 2; 

	 for(i;i>=0;i--)
      MenorIndiceArvore(i);} 






  void TrocaNos(MenorNo* x, MenorNo* y);
  
  
  
  
  void ArvoreMenor::MenorIndiceArvore(int i) { 
  int l = noEsquerdo(i); int r = noDireito(i); int menorElemento = i; 
	if (l < TamanhoArvore && harr[l].RegistroInformacoesArquivo.chave < harr[i].RegistroInformacoesArquivo.chave) { 
       menorElemento = l; }
	if (menorElemento != i) { 
	  TrocaNos(&harr[i], &harr[menorElemento]); 
          MenorIndiceArvore(menorElemento);}
   if (r < TamanhoArvore && harr[r].RegistroInformacoesArquivo.chave < harr[menorElemento].RegistroInformacoesArquivo.chave) {
		menorElemento = r; }} 







  void TrocaNos(MenorNo* x, MenorNo* y) { 
	MenorNo temp=*x; 
		*x=*y;*y=temp;} 



	void merge(Registro MemoriaRuns[], int Esq, int Meio, int Dir) { 
	
      int LadoEsquerdo = Meio - Esq + 1;int LadoDireito = Dir - Meio; 
	
     Registro VetorAuxiliarEsquerdo[LadoEsquerdo];Registro VetorAuxiliarDireito[LadoDireito]; 
	
     int i=0;
   while(i<LadoEsquerdo){
	VetorAuxiliarEsquerdo[i] = MemoriaRuns[Esq + i];
 i++;}int j = 0; 
  while(j < LadoDireito) {
   VetorAuxiliarDireito[j] = MemoriaRuns[Meio + 1 + j]; 
    j++;}

	
	i = 0; j = 0 ; 
    
	int Auxiliar = Esq; 
 while (i < LadoEsquerdo && j < LadoDireito){ 
  if (VetorAuxiliarEsquerdo[i].chave <= VetorAuxiliarDireito[j].chave) {
  	MemoriaRuns[Auxiliar++] = VetorAuxiliarEsquerdo[i++];}
   else{
	MemoriaRuns[Auxiliar++] = VetorAuxiliarDireito[j++];}} 

	
 while (i < LadoEsquerdo){
	MemoriaRuns[Auxiliar++] = VetorAuxiliarEsquerdo[i++];}
	
  while(j < LadoDireito) {
	MemoriaRuns[Auxiliar++] = VetorAuxiliarDireito[j++]; }
} 





 void mergeSort(Registro MemoriaRuns[], int Esq, int Dir) {
  if (Esq < Dir) { 
		
   int Meio = Esq + (Dir - Esq) / 2; 
		
	 mergeSort(MemoriaRuns, Esq, Meio); 
	 mergeSort(MemoriaRuns, Meio + 1, Dir); 
	 merge(MemoriaRuns,Esq, Meio, Dir); }} 
 




 void CriandoArquivoFinal(char *ArquivoSaida, int Memoria, int NumeroArquivos){ 
  FILE* vetorEntrada[NumeroArquivos];int i = 0;
 while (i < NumeroArquivos) { 
	 char IndiceRuns[20]; 
		
	 snprintf(IndiceRuns, sizeof(IndiceRuns), "%d", i); 
		
	 vetorEntrada[i] = fopen(IndiceRuns, "r");
	  i++;} 
	
 FILE *vetorSaida = fopen(ArquivoSaida, "w");
	 
 MenorNo* VetorArvore = new MenorNo[NumeroArquivos]; i=0;
 while (i < NumeroArquivos) { 
		
	 if (fread(&VetorArvore[i].RegistroInformacoesArquivo, 1, sizeof(Registro), vetorEntrada[i]) == 0 )
		 break; 
	 VetorArvore[i].i = i;  
	 i++;
	} 
   ArvoreMenor RaizNo(VetorArvore, i); 
  int count = 0; 
	 
	while (count != i) { 
		
		MenorNo IndiceMenorNo = RaizNo.menorIndice(); 
		fprintf(vetorSaida, "%d %s %d\n", IndiceMenorNo.RegistroInformacoesArquivo.chave, IndiceMenorNo.RegistroInformacoesArquivo.nome, IndiceMenorNo.RegistroInformacoesArquivo.idade); 

		 
		if (fread(&IndiceMenorNo.RegistroInformacoesArquivo, 1, sizeof(Registro), vetorEntrada[IndiceMenorNo.i]) == 0 ) { 
			IndiceMenorNo.RegistroInformacoesArquivo.chave = INT_MAX; 
			count++; } 
		 
		RaizNo.trocaIndiceDoNo(IndiceMenorNo);} 
	
	for (int i = 0; i < NumeroArquivos; i++) { 
		fclose(vetorEntrada[i]);}
	fclose(vetorSaida);} 
Registro* LerRegistro(Registro* registro, FILE* in){
	fread(&registro, 1, sizeof(Registro), in);
	return registro;}






/*  void CriandoRuns(char *ArquivoEntrada,int Memoria,int NumeroArquivos) {
	bool ProximoArquivo = true;int IndiceArquivoSaida = 0;int i;
    Registro* MemoriaRuns = (Registro*)malloc(Memoria * sizeof(Registro));
	 
  FILE *ArquivoCompleto = fopen(ArquivoEntrada, "r");
	 
  FILE* ArquivosRuns[NumeroArquivos];
  char IndiceRuns[20]; 
  for (int i = 0; i < NumeroArquivos; i++) { 
		 
	snprintf(IndiceRuns, sizeof(IndiceRuns), "%d", i); 
		
	ArquivosRuns[i] = fopen(IndiceRuns, "w");} 
	 
  while (ProximoArquivo) { 
	 
	for (i = 0; i < Memoria; i++) {
		if (fread(&MemoriaRuns[i], 1, sizeof(Registro), ArquivoCompleto) == 0) { 
			ProximoArquivo = false; 
		break; }} 
		
	
	
	
	
	mergeSort(MemoriaRuns, 0, i - 1); 
		
	for (int j = 0; j < i; j++) {  
		fwrite(&MemoriaRuns[j], sizeof(Registro), 1, ArquivosRuns[IndiceArquivoSaida]);}
		IndiceArquivoSaida++;} 
	
for (int i = 0; i < NumeroArquivos; i++) { 
		fclose(ArquivosRuns[i]); }
	fclose(ArquivoCompleto);} 

*/

/*void OrdernacaoExterna(char* ArquivoEntrada, char *ArquivoSaida, int NumeroArquivos, int Memoria) { 
	
	CriandoRuns(ArquivoEntrada, Memoria, NumeroArquivos); 
	
	CriandoArquivoFinal(ArquivoSaida, Memoria, NumeroArquivos);} 
*/



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
				 remove (fileName);}}}}





int main() { 
	
  int NumeroArquivos = MAXNARQS;
	
   int Memoria = MAXMEM/sizeof(Registro); 
  char ArquivoEntrada[] = "input.txt"; 
 char ArquivoSaida[] = "saida.dat"; 
	
   FILE* Entrada1 = fopen(ArquivoEntrada, "w"); FILE* Entrada2 = fopen("entrada.dat", "r+");
    Registro registro;
	 while(fscanf(Entrada2, "%d %s %d", &registro.chave, registro.nome, &registro.idade) == 3){
		fwrite(&registro, sizeof(Registro), 1, Entrada1);}
	fclose(Entrada1);fclose(Entrada2);
	 //OrdernacaoExterna(ArquivoEntrada, ArquivoSaida, NumeroArquivos, Memoria);
	 
	 bool ProximoArquivo = true;int IndiceArquivoSaida = 0;int i;
    Registro* MemoriaRuns = (Registro*)malloc(Memoria * sizeof(Registro));
	 
  FILE *ArquivoCompleto = fopen(ArquivoEntrada, "r");
	 
  FILE* ArquivosRuns[NumeroArquivos];
  char IndiceRuns[20]; 
  for (int i = 0; i < NumeroArquivos; i++) { 
		 
	snprintf(IndiceRuns, sizeof(IndiceRuns), "%d", i); 
		
	ArquivosRuns[i] = fopen(IndiceRuns, "w");} 
	 
  while (ProximoArquivo) { 
	 
	for (i = 0; i < Memoria; i++) {
		if (fread(&MemoriaRuns[i], 1, sizeof(Registro), ArquivoCompleto) == 0) { 
			ProximoArquivo = false; 
		break; }} 
		
	
	
	
	
	mergeSort(MemoriaRuns, 0, i - 1); 
		
	for (int j = 0; j < i; j++) {  
		fwrite(&MemoriaRuns[j], sizeof(Registro), 1, ArquivosRuns[IndiceArquivoSaida]);}
		IndiceArquivoSaida++;} 
	
for (int i = 0; i < NumeroArquivos; i++) { 
		fclose(ArquivosRuns[i]); }
	fclose(ArquivoCompleto);
	 
	 
	 CriandoArquivoFinal(ArquivoSaida, Memoria, NumeroArquivos);
	 
	 
	//ExcluirArquivosVazios CASO SEJA TRUE EXCLUI ARQUIVOS QUE ESTÃO VAZIOS,
	//E NÃO FORAM NECESSARIOS DURANTE A EXECUÇÃO DO PROGRAMA.
	  bool ExcluirArquivosVazios = true;//MUDAR PARA FALSE CASO QUEIRA SE MANTENHA ARQUIVOS VAZIOS
	    removerArquivo(ExcluirArquivosVazios, NumeroArquivos);
	  return 0;} 