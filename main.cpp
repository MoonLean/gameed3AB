#include <stdio.h>
#include <stdlib.h>
#include "JOGO_ED3.h"
#include <windows.h>
#define numPosicoes 9+1

// MACHINE X chis
// PLAYER O little ball

// --------------------- M A I N --------------------- //	
int main(){
	system("cls");
	Arvore A;
		criaArvore(&A); 	//pointer tree created and set up as NULL
		configuraArvore(&A);
	Arvore d1, d2, d3, d4, d5, d6, d7, d8, d9;
		criaArvore(&d1);
		criaArvore(&d2);
		criaArvore(&d3);
		criaArvore(&d5);
		criaArvore(&d6);
		criaArvore(&d7);
		criaArvore(&d8);
		criaArvore(&d9);
	
	IniciaUM(&d1);
		InsereLocalizado(&A, &d1, 1);
	
	IniciaDOIS(&d2);
		InsereLocalizado(&A, &d2, 2);
		
	IniciaTRES(&d3);
		InsereLocalizado(&A, &d3, 3);
	
	IniciaQUATRO(&d4);
		InsereLocalizado(&A, &d4, 4);

	IniciaCINCO(&d5);
		InsereLocalizado(&A, &d5, 5);
		
	IniciaSEIS(&d6);
		InsereLocalizado(&A, &d6, 6);
		
	IniciaSETE(&d7);
		InsereLocalizado(&A, &d7, 7);
		
	IniciaOITO(&d8);
		InsereLocalizado(&A, &d8, 8);
		
	IniciaNOVE(&d9);
		InsereLocalizado(&A, &d9, 9);
		
	Intro();
		
	int VetorJogo[numPosicoes];
		inicializaVetor(VetorJogo, numPosicoes-1);
	
	bool onGame = true;
	int jogador = 0;
	
	tabuleiro(VetorJogo);
	
	//este e o loop do jogo
	while(onGame){
		if(Vitoria(VetorJogo) != 0){
				system("cls");
				tabuleiro(VetorJogo);
				//procedimento para o ganhador
			if(Vitoria(VetorJogo) == 1){
				//vitoria da maquina
				printf("\nMAIS SORTE DA PROXIMA VEZ!!!\n");
			}
			else {
				//vitoria do jogador
			printf("\n:/ DEVE TER SIDO SORTE DE PRINCIPIANTE u.u \n");
			}
			onGame = false;
			break;
		}
		if (Velha(VetorJogo)){
				system("cls");
				tabuleiro(VetorJogo);
				printf("\nPARECE QUE EMPATAMOS!!!\n");
				onGame = false;
				break;
		}
		else {

			printf("\nSUA VEZ DE JOGAR, VOCE (O); EU (X)..\n");
			scanf("%d", &jogador);
		
			if(VetorJogo[jogador-1] != -1 || 8 < jogador-1 < 0){
				printf("\nMOVIMENTO IRREGULAR  :/  TENTE NOVAMENTE\n");
			} else {
				VetorJogo[jogador-1] = 0;
								
				system("cls");
				
				tabuleiro(VetorJogo);
				
				printf("BOA JOGADA... AGORA APRENDA!\n");
				Sleep(1000);
				
				pesquisa(A, jogador, VetorJogo);
				system("cls");
				tabuleiro(VetorJogo);
				
			}
		}	
	}
	system("PAUSE");
	return 0;
}

