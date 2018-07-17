#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "JOGO_ED3.h"

// --------------------- I M P L E M E N T A C O E S --------------------- //

//criação padrão de uma arvore em uma AB
void criaArvore(Arvore *A){
	*A = NULL;
}

//esta função como o nome sugere, configura a arvore, assim como se instala um programa num pc esta função "instala"
//toda a logica do jogo na arvore passada
void configuraArvore(Arvore *A){
	//ordem de inserção das posições
	int padrao[] = {5, 3, 2, 4, 1, 7, 6, 8, 9};
	tipoItem I;
	
	//criação da arvore de posições
	for(int i = 0; i < 9; i++){
		I.chave = padrao[i];
		I.acao = false;
		I.resposta = -1;
		I.decisao = NULL;
		insere(&(*A), I);
	}
	
}

//todo vetor no jogo é inicializado com suas posições preenchidas com -1
void inicializaVetor(int *vetor, int tam){
	for(int i = 0; i < tam; i++)
		vetor[i] = -1;
}

//verifica se deu velha
bool Velha(int *jogo){
	int contador = 0;
	for (int i = 0; i < 9; i++){
		if (jogo[i] == -1) contador++;
	}
	if(contador != 0) return false;
	else return true;
}

//simplesmente uma funcao que realiza uma introducao a forma de jogar
void Intro(){
	int r = 0;
	printf("OLA, VAMOS AS INSTRUCOES INCIAIS...\n");
	printf("ESTE JOGO E UM JOGO DA VELHA COMO QUALQUER OUTRO, COMO TODO BOM ANFITRIAO, AQUI VOCE COMECA! :D\n");
	
		printf("\t|	|\n");
	printf("   1    |   2   |   3\n");
		printf("\t|	|\n");
		printf("  ----------------------\n");
		printf("\t|	|\n");
		
	printf("   4    |   5   |   6\n");
	
		printf("\t|	|\n");
		printf("  ----------------------\n");
		printf("\t|	|\n");
	printf("   7    |   8   |   9\n");
		printf("\t|	|\n");
	
	printf("ESTE E O NOSSO TABULEIRO, E OS NUMEROS NELE INDICAM A TECLA QUE VOCE DEVE APERTA* PARA COLOCAR SUA BOLINHA(SIM, VOCE E A BOLINHA)\n");
	printf("* apos apertar a tecla numerica correspondente a casa do tabuleiro pressione enter...");
	printf("\nUMA PEQUENA DEMONSTRACAO:\n");
	
	printf("\t|	|\n");
	printf("   X    |       |\n");
		printf("\t|	|\n");
		printf("  ----------------------\n");
		printf("\t|	|\n");
		
	printf("\t|       |\n");
	
		printf("\t|	|\n");
		printf("  ----------------------\n");
		printf("\t|	|\n");
	printf("\t|       |   X\n");
		printf("\t|	|\n");
		
	printf("que numero voce deve jogar para impedir que eu ganhe?\nR: ");
	scanf("%d", &r);
	
	if(r == 5){
		printf("PARABENS, PARECE QUE VOCE ENTENDEU!!! VAMOS JOGAR VALENDO ENTAO...");
		Sleep(3000);
	} 
	else{
		printf("ERROU FEIO! ERA 5, CINCO, C I N C O, PELAMOR, BASTA IMAGINAR O TABULEIRO COMO UM TECLADO TELEFONICO >:(  \n");
		printf("PELO VISTO TEREMOS PROBLEMAS FUTUROS AQUI... VAMOS JOGAR VALENDO");
		Sleep(6000);
	}
	
	system("cls");
}

//criação de uma raiz padrão em um AB
void criaRaiz(Arvore *A, tipoItem I){
	*A = (Arvore) malloc(sizeof(tipoNo));
	(*A)->Item = I;
	(*A)->left = NULL;
	(*A)->right = NULL;
}

//inserção padrão em uma AB
void insere(Arvore *A, tipoItem I){
	if(!(*A)){
		criaRaiz(&(*A), I);
		return;
	}
		
	// verifica chave duplicada
	if((*A)->Item.chave == I.chave){
		printf("CHAVE DUPLICADA!\n");
		return;
	}
	
	if(I.chave < (*A)->Item.chave){
		insere(&(*A)->left, I);
	}
	else {
		insere(&(*A)->right, I);
	}
}

//está função aplica as arvores de decisão criadas aos respectivos casos
//o caso um guarda um comportamento específico, o caso dois outro, e assim sucessivamente
void InsereLocalizado(Arvore *A, Arvore *B, tipoChave C){
	if((*A)->Item.chave == C){
		
		(*A)->Item.decisao = *B;
		
		return ;
	}
	if(C < (*A)->Item.chave) InsereLocalizado(&(*A)->left, &(*B), C);
	else InsereLocalizado(&(*A)->right, &(*B), C);
}

//quando o usuario seleciona o campo 1 do tabuleiro, então a maquina procurará na arvore o 
//nó de chave 1, e dentro deste nó, tem os procedimentos(arvore de decisão) que serão seguidos para responder ao movimento do jogador
void pesquisa(Arvore A, tipoChave C, int *jogo){
	//printf("\nCHEGOU ATE A FN PESQUISA\n");	
	apontador P = A;
	
	while(P != NULL){
		if(P->Item.chave == C){
			//printf("\nESTA PASSANDO A ARVORE E O VETOR JOGO PARA A FN RESPONDE\n");
			Responde(P->Item.decisao, jogo);
			return;
		}
		if(C < P->Item.chave) P = P->left;
		else P = P->right;
	}
	
	printf("CHAVE NÃO ENCONTRADA\n");
}

int coringa(int *jogo){
	for(int i = 0; i < 9; i++){
		if(jogo[i] == -1)
			return i;
	}
}

//esta função percorre a arvore de decisão passada e aplica a resposta contida no nó
void Responde(Arvore A, int *jogo){
	//printf("\nCHEGOU ATE A FN RESPONDE\n");
	apontador P = A;
	
	//printf("\nIMPRIMINDO A ARVORE DE DECISAO PARA VERIFICACAO\n");
	//preOrder(A);
	
	while(P != NULL){
		//veja só, quando um nó guarda uma ação, ele entra nesta condicional
		if(P->Item.acao){
			//em seguida é aplicada a resposta contida no nó
			//printf("\nCHEGOU ATE A RESPOSTA AO MOVIMENTO\n");
			jogo[P->Item.resposta - 1] = 5;
			
			return ;
		}
		else if(jogo[P->Item.chave - 1] != -1)
			P = P->right;
		else
			P = P->left;
	}
}

//aqui sera o tabuleiro, ele é montado de acordo com o vetor "game" passado pada ele
void tabuleiro(int *game){
	
	//system("cls");
	printf("\n");
	
	char maq[] = {"   O   "};	// 0
	char gam[] = {"   X   "}; 	// 1
	char nada[] = {"       "};	// 2	
	
		printf("\t|	|\n");
		
	
	for(int i = 0; i < 3; i++){
		if(i==0){
			if(game[i]== -1) printf("%s ",&nada);
			if(game[i]== 5) printf("%s ",&gam);
			if(game[i]== 0) printf("%s ",&maq);
		}
		
		else if(i==1){
			if(game[i]== -1) printf("|%s|",&nada);
			if(game[i]== 5) printf("|%s|",&gam);
			if(game[i]== 0) printf("|%s|",&maq);
		}
		
		else if(i==2){
			if(game[i]== -1) printf(" %s\n",&nada);
			if(game[i]== 5) printf(" %s\n",&gam);
			if(game[i]== 0) printf(" %s\n",&maq);
		}
	}
	
		printf("\t|	|\n");
		printf("  ----------------------\n");
		printf("\t|	|\n");
		
	for(int i = 3; i < 6; i++){
		if(i==3){
			if(game[i]== -1) printf("%s ",&nada);
			if(game[i]== 5) printf("%s ",&gam);
			if(game[i]== 0) printf("%s ",&maq);
		}
		
		else if(i==4){
			if(game[i]== -1) printf("|%s|",&nada);
			if(game[i]== 5) printf("|%s|",&gam);
			if(game[i]== 0) printf("|%s|",&maq);
		}
		
		else if(i==5){
			if(game[i]== -1) printf(" %s\n",&nada);
			if(game[i]== 5) printf(" %s\n",&gam);
			if(game[i]== 0) printf(" %s\n",&maq);
		}
	}
	
		printf("\t|	|\n");
		printf("  ----------------------\n");
		printf("\t|	|\n");
	
	for(int i = 6; i < 9; i++){
		if(i==6){
			if(game[i]== -1) printf("%s ",&nada);
			if(game[i]== 5) printf("%s ",&gam);
			if(game[i]== 0) printf("%s ",&maq);
		}		
		else if(i==7){
			if(game[i]== -1) printf("|%s|",&nada);
			if(game[i]== 5) printf("|%s|",&gam);
			if(game[i]== 0) printf("|%s|",&maq);
		}
		
		else if(i==8){
			if(game[i]== -1) printf(" %s\n",&nada);
			if(game[i]== 5) printf(" %s\n",&gam);
			if(game[i]== 0) printf(" %s\n",&maq);
		}
	}
		printf("\t|	|\n");
	
}

//verifica de houve alguma combinação vitoriosa e retorna quem ganhou
int Vitoria(int *jogo){
	int match[9][4]; // 8 linhas 3 colunas
	int soma = 0;
	
	match[0][0] = 1;
	match[0][1] = 2;
	match[0][2] = 3;
	
	match[1][0] = 1;
	match[1][1] = 4;
	match[1][2] = 7;
	
	match[2][0] = 1;
	match[2][1] = 5;
	match[2][2] = 9;
	
	match[3][0] = 2;
	match[3][1] = 5;
	match[3][2] = 8;
	
	match[4][0] = 3;
	match[4][1] = 6;
	match[4][2] = 9;
	
	match[5][0] = 4;
	match[5][1] = 5;
	match[5][2] = 6;
	
	match[6][0] = 7;
	match[6][1] = 8;
	match[6][2] = 9;
	
	match[7][0] = 3;
	match[7][1] = 5;
	match[7][2] = 7;
	
	for(int i = 0; i < 8; i++){
		soma = 0;
		for(int j = 0; j < 3; j++)
			soma += jogo[match[i][j]-1];
		if(soma == 0) return 2;
		if(soma == 15) return 1;
	}
	
	//se chegou ate aqui significa que nao houve ganhador ainda
	return 0;
}

//a seguir seguem as arvores de decisoes..

// a arvore de decisão UM tem esta configuração
void IniciaUM(Arvore *UM){
	
	//a declaração é feita de forma manual
	//primeiro declaramos um item "I"
	tipoItem I;
	
	//em seguida o preenchemos
	I.acao = false;
	I.chave = 2;
	I.decisao = NULL;
	I.resposta = -1;
	
	//então a arvore passada tem seu primeiro item(raiz) criada
	criaRaiz(&(*UM), I);
	
	//a partir dai criaremos os demais nos da arvore...
	//acontece que reaproveitaremos o item "I" criado em todos os nós, alterando somente algumas propriedades específicas
	//não é preciso alterar TODAS as propriedades, pois elas não tem mais importancia depois do nó raiz...
	
	//veja aqui.. alteramos a chave de dois para 3 e criamos dois nós com a mesma chave, numa inserção dinamica isto não seria possivel
	//por isso, e outros motivos, a criação da arvore esta sendo feita de forma manual.
	I.chave = 3;
		criaRaiz(&(*UM)->left, I);
		criaRaiz(&(*UM)->right, I);
	
	I.acao = true;
	I.resposta = 2;	
		criaRaiz(&(*UM)->left->right, I);
	
	I.acao = true;
	I.resposta = 3;
		criaRaiz(&(*UM)->right->left, I);
	
	I.acao = false;
	I.chave = 4;	
		criaRaiz(&(*UM)->left->left, I);
		
	
	I.acao = false;
	I.chave = 7;
		criaRaiz(&(*UM)->left->left->left, I);
		criaRaiz(&(*UM)->left->left->right, I);
		
	I.acao = true;
	I.resposta = 4;	
		criaRaiz(&(*UM)->left->left->left->right, I);
		
	I.resposta = 7;	
		criaRaiz(&(*UM)->left->left->right->left, I);
		
	I.acao = false;
	I.chave = 5;
		criaRaiz(&(*UM)->left->left->left->left, I);
	
	I.chave = 9;
		criaRaiz(&(*UM)->left->left->left->left->left, I);
		criaRaiz(&(*UM)->left->left->left->left->right, I);
		
	I.acao = true;
	I.resposta = 5;
		criaRaiz(&(*UM)->left->left->left->left->left->left, I);
		criaRaiz(&(*UM)->left->left->left->left->left->right, I);
	
	I.resposta = 9;
		criaRaiz(&(*UM)->left->left->left->left->right->left, I);
		criaRaiz(&(*UM)->left->left->left->left->right->right, I);
		
	(*UM)->right->right = (*UM)->left->left;
	(*UM)->left->left->right->right = (*UM)->left->left->left->left;
}

void IniciaDOIS(Arvore *D){
	tipoItem I;
	
	//em seguida o preenchemos
	I.acao = false;
	I.chave = 1;
	I.decisao = NULL;
	I.resposta = -1;
	
		//então a arvore passada tem seu primeiro item(raiz) criada
		criaRaiz(&(*D), I);
	
	I.chave = 3;
		criaRaiz(&(*D)->right,I);
		criaRaiz(&(*D)->left,I);
	
	I.acao = true;
	I.resposta = 3;
		criaRaiz(&(*D)->right->left,I);
	
	I.resposta = 1;
		criaRaiz(&(*D)->left->right,I);
		
	I.acao = false;
	I.chave = 5;
		criaRaiz(&(*D)->left->left,I);
		
	I.chave = 8;
		criaRaiz(&(*D)->left->left->left,I);
		criaRaiz(&(*D)->left->left->right,I);
		
	I.acao = true;
	
	I.resposta = 3; //CORINGA AQUI
	
		criaRaiz(&(*D)->left->left->right->right,I);
	
	I.resposta = 8;
		criaRaiz(&(*D)->left->left->right->left,I);
		
	I.resposta = 1;
		criaRaiz(&(*D)->left->left->left->right,I);
		
	I.resposta = 8;
		criaRaiz(&(*D)->left->left->left->left,I);
		
	(*D)->right->right = (*D)->left->left;
	
}

void IniciaTRES(Arvore *T){
	tipoItem I;
	
	I.acao = false;
	I.chave = 1;
	I.decisao = NULL;
	I.resposta = -1;
	
		criaRaiz(&(*T), I);
	
	I.chave = 2;
		criaRaiz(&(*T)->right,I);
		criaRaiz(&(*T)->left,I);
		
	I.acao = true;
	I.resposta = 2;
		criaRaiz(&(*T)->right->left,I); 
	
	I.resposta = 1;
		criaRaiz(&(*T)->left->right,I);
		
	I.acao = false;
	I.chave = 6;
		criaRaiz(&(*T)->left->left,I);
	
	I.chave = 9;
		criaRaiz(&(*T)->left->left->left,I);
		criaRaiz(&(*T)->left->left->right,I);
	
	I.acao = true;
	I.resposta = 9;
		criaRaiz(&(*T)->left->left->right->left,I); 
	
	I.resposta = 6;	
		criaRaiz(&(*T)->left->left->left->right,I);
	
	I.acao = false;
	I.chave = 5;
		criaRaiz(&(*T)->left->left->left->left,I);
	
	I.chave = 7;
		criaRaiz(&(*T)->left->left->left->left->left,I);
		criaRaiz(&(*T)->left->left->left->left->right,I);
		
	I.acao = true;
	I.resposta = 5;
		criaRaiz(&(*T)->left->left->left->left->left->left,I);
		criaRaiz(&(*T)->left->left->left->left->left->right,I);
	
	I.resposta = 7;
		criaRaiz(&(*T)->left->left->left->left->right->left,I);
	
	I.resposta = 7; //CORINGA AQUI;
		criaRaiz(&(*T)->left->left->left->left->right->right,I);
		
	(*T)->left->left->right->right = (*T)->left->left->left->left;
	(*T)->right->right = (*T)->left->left;
		
}

void IniciaQUATRO(Arvore *Q){
	tipoItem I;
	
	I.acao = false;
	I.chave = 1;
	I.decisao = NULL;
	I.resposta = -1;
	
		criaRaiz(&(*Q), I);
	
	I.chave = 7;
		criaRaiz(&(*Q)->right,I);
		criaRaiz(&(*Q)->left,I);
	
	I.acao = true;
	I.resposta = 7;
		criaRaiz(&(*Q)->right->left,I);
		
	I.resposta = 1;
		criaRaiz(&(*Q)->left->right,I);
		
	I.acao = false;
	I.chave = 5;
		criaRaiz(&(*Q)->left->left,I);
	
	I.chave = 6;
		criaRaiz(&(*Q)->left->left->left,I);
		criaRaiz(&(*Q)->left->left->right,I);
	
	I.acao = true;
	I.resposta = 5;
		criaRaiz(&(*Q)->left->left->left->left,I);
		criaRaiz(&(*Q)->left->left->left->right,I);
		
	I.resposta = 6;
		criaRaiz(&(*Q)->left->left->right->left,I);
	
	
	I.resposta = 7; // CORINGA AQUI
	
		criaRaiz(&(*Q)->left->left->right->right,I);
		
	(*Q)->right->right = (*Q)->left->left;
}


void IniciaCINCO(Arvore *C){
	tipoItem I;
	
	I.acao = false;
	I.chave = 1;
	I.decisao = NULL;
	I.resposta = -1;
	
		criaRaiz(&(*C), I);
	
	I.chave = 9;
		criaRaiz(&(*C)->right,I);
		criaRaiz(&(*C)->left,I);
		
	I.acao = true;
	I.resposta = 9;
		criaRaiz(&(*C)->right->left,I); 
	
	I.resposta = 1;
		criaRaiz(&(*C)->left->right,I);
		
	I.acao = false;
	I.chave = 2;
		criaRaiz(&(*C)->left->left,I);
	
	I.chave = 8;
		criaRaiz(&(*C)->left->left->left,I);
		criaRaiz(&(*C)->left->left->right,I);
	
	I.acao = true;
	I.resposta = 8;
		criaRaiz(&(*C)->left->left->right->left,I); 
	
	I.resposta = 2;	
		criaRaiz(&(*C)->left->left->left->right,I);
	
	I.acao = false;
	I.chave = 3;
		criaRaiz(&(*C)->left->left->left->left,I);
	
	I.chave = 7;
		criaRaiz(&(*C)->left->left->left->left->left,I);
		criaRaiz(&(*C)->left->left->left->left->right,I);
		
	I.acao = true;
	I.resposta = 3;
		criaRaiz(&(*C)->left->left->left->left->left->right,I);
	
	I.resposta = 7;
		criaRaiz(&(*C)->left->left->left->left->right->left,I);
	
	I.acao = false;
	I.chave = 6;	
		criaRaiz(&(*C)->left->left->left->left->left->left,I);
		
	I.chave = 4;
		criaRaiz(&(*C)->left->left->left->left->left->left->left,I);
		criaRaiz(&(*C)->left->left->left->left->left->left->right,I);
		
	I.acao = true;
	I.resposta = 6;
		criaRaiz(&(*C)->left->left->left->left->left->left->left->left,I);
		criaRaiz(&(*C)->left->left->left->left->left->left->left->right,I);
	
	I.resposta = 4;
		criaRaiz(&(*C)->left->left->left->left->left->left->right->left,I);
		
	I.resposta = 7; //CORINGA AQUI;
		criaRaiz(&(*C)->left->left->left->left->left->left->right->right,I);
	
	(*C)->left->left->left->left->right->right = (*C)->left->left->left->left->left->left;
	(*C)->left->left->right->right = (*C)->left->left->left->left;
	(*C)->right->right = (*C)->left->left;
}

void IniciaSEIS(Arvore *S){
	tipoItem I;
	
	I.acao = false;
	I.chave = 4;
	I.decisao = NULL;
	I.resposta = -1;
	
		criaRaiz(&(*S), I);
	
	I.chave = 5;
		criaRaiz(&(*S)->right,I);
		criaRaiz(&(*S)->left,I);
	
	I.acao = true;
	I.resposta = 5;
		criaRaiz(&(*S)->right->left,I);
		
	I.resposta = 4;
		criaRaiz(&(*S)->left->right,I);
		
	I.acao = false;
	I.chave = 3;
		criaRaiz(&(*S)->left->left,I);
	
	I.chave = 9;
		criaRaiz(&(*S)->left->left->left,I);
		criaRaiz(&(*S)->left->left->right,I);
	
	I.acao = true;
	I.resposta = 3;
		criaRaiz(&(*S)->left->left->left->left,I);
		criaRaiz(&(*S)->left->left->left->right,I);
		
	I.resposta = 9;
		criaRaiz(&(*S)->left->left->right->left,I);
	
	
	I.resposta = 5; // CORINGA AQUI
	
		criaRaiz(&(*S)->left->left->right->right,I);
		
	(*S)->right->right = (*S)->left->left;
}

void IniciaSETE(Arvore *S){
	tipoItem I;
	
	I.acao = false;
	I.chave = 1;
	I.decisao = NULL;
	I.resposta = -1;
	
		criaRaiz(&(*S), I);
	
	I.chave = 4;
		criaRaiz(&(*S)->right,I);
		criaRaiz(&(*S)->left,I);
		
	I.acao = true;
	I.resposta = 4;
		criaRaiz(&(*S)->right->left,I); 
	
	I.resposta = 1;
		criaRaiz(&(*S)->left->right,I);
		
	I.acao = false;
	I.chave = 3;
		criaRaiz(&(*S)->left->left,I);
	
	I.chave = 5;
		criaRaiz(&(*S)->left->left->left,I);
		criaRaiz(&(*S)->left->left->right,I);
	
	I.acao = true;
	I.resposta = 5;
		criaRaiz(&(*S)->left->left->right->left,I); 
	
	I.resposta = 3;	
		criaRaiz(&(*S)->left->left->left->right,I);
	
	I.acao = false;
	I.chave = 9;
		criaRaiz(&(*S)->left->left->left->left,I);
	
	I.chave = 8;
		criaRaiz(&(*S)->left->left->left->left->left,I);
		criaRaiz(&(*S)->left->left->left->left->right,I);
		
	I.acao = true;
	I.resposta = 9;
		criaRaiz(&(*S)->left->left->left->left->left->left,I);
		criaRaiz(&(*S)->left->left->left->left->left->right,I);
	
	I.resposta = 8;
		criaRaiz(&(*S)->left->left->left->left->right->left,I);
	
	I.resposta = 5; //CORINGA AQUI;
		criaRaiz(&(*S)->left->left->left->left->right->right,I);
		
	(*S)->left->left->right->right = (*S)->left->left->left->left;
	(*S)->right->right = (*S)->left->left;
}

void IniciaOITO(Arvore *O){
	tipoItem I;
	
	I.acao = false;
	I.chave = 2;
	I.decisao = NULL;
	I.resposta = -1;
	
		criaRaiz(&(*O), I);
	
	I.chave = 5;
		criaRaiz(&(*O)->right,I);
		criaRaiz(&(*O)->left,I);
	
	I.acao = true;
	I.resposta = 5;
		criaRaiz(&(*O)->right->left,I);
		
	I.resposta = 2;
		criaRaiz(&(*O)->left->right,I);
		
	I.acao = false;
	I.chave = 7;
		criaRaiz(&(*O)->left->left,I);
	
	I.chave = 9;
		criaRaiz(&(*O)->left->left->left,I);
		criaRaiz(&(*O)->left->left->right,I);
	
	I.acao = true;
	I.resposta = 7;
		criaRaiz(&(*O)->left->left->left->left,I);
		criaRaiz(&(*O)->left->left->left->right,I);
		
	I.resposta = 9;
		criaRaiz(&(*O)->left->left->right->left,I);
	
	
	I.resposta = 5; // CORINGA AQUI
	
		criaRaiz(&(*O)->left->left->right->right,I);
		
	(*O)->right->right = (*O)->left->left;
}

void IniciaNOVE(Arvore *N){
	tipoItem I;
	
	I.acao = false;
	I.chave = 1;
	I.decisao = NULL;
	I.resposta = -1;
	
		criaRaiz(&(*N), I);
	
	I.chave = 5;
		criaRaiz(&(*N)->right,I);
		criaRaiz(&(*N)->left,I);
		
	I.acao = true;
	I.resposta = 5;
		criaRaiz(&(*N)->right->left,I); 
	
	I.resposta = 1;
		criaRaiz(&(*N)->left->right,I);
		
	I.acao = false;
	I.chave = 3;
		criaRaiz(&(*N)->left->left,I);
	
	I.chave = 6;
		criaRaiz(&(*N)->left->left->left,I);
		criaRaiz(&(*N)->left->left->right,I);
	
	I.acao = true;
	I.resposta = 6;
		criaRaiz(&(*N)->left->left->right->left,I); 
	
	I.resposta = 3;	
		criaRaiz(&(*N)->left->left->left->right,I);
	
	I.acao = false;
	I.chave = 7;
		criaRaiz(&(*N)->left->left->left->left,I);
	
	I.chave = 8;
		criaRaiz(&(*N)->left->left->left->left->left,I);
		criaRaiz(&(*N)->left->left->left->left->right,I);
		
	I.acao = true;
	I.resposta = 7;
		criaRaiz(&(*N)->left->left->left->left->left->left,I);
		criaRaiz(&(*N)->left->left->left->left->left->right,I);
	
	I.resposta = 8;
		criaRaiz(&(*N)->left->left->left->left->right->left,I);
	
	I.resposta = 6; //CORINGA AQUI;
		criaRaiz(&(*N)->left->left->left->left->right->right,I);
		
	(*N)->left->left->right->right = (*N)->left->left->left->left;
	(*N)->right->right = (*N)->left->left;
}


