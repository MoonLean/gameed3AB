#ifndef JOGO_ED3
#define JOGO_ED3

// --------------------- DEFINI��O DAS ESTRUTURAS --------------------- //
typedef int tipoChave;

typedef struct tipoNo *apontador;
typedef apontador Arvore;

//este tipoItem tem alguns campos importantes..
typedef struct {
	tipoChave chave;	//chave aqui nada mais � que a posi��o do tabuleiro
	bool acao;			//os n�s que possuem a��es, s�o setados true, isto indica que o movimento do jogador caiu neste n�, e portanto a resposta ao movimento ser� a que est� abaixo
	int resposta;		//resposta aqui � a posi��o do tabuleiro que a maquina deve preencher, exemplo, se o jogador jogou 1 ent�o a resposta aqui pode ser a posi��o 3
	Arvore decisao;		//este apontador conter� a arvore decis�o
} tipoItem;

//declara��o padr�o de um tipoNo
typedef struct tipoNo {
	tipoItem Item;
	struct tipoNo *left, *right;
} tipoNo;
	

// --------------------- ESCOPOS --------------------- //
void criaArvore(Arvore *A);
void criaRaiz(Arvore *A, tipoItem I);
void insere(Arvore *A, tipoItem I);
void pesquisa(Arvore A, tipoChave C, int *jogo);  //pesquisa na verdade recebe o movimento do jogador e realiza a resposta com base no movimento passado C e na estrutura atual do jogo
void preOrder(Arvore A);
void inicializaVetor(int *vetor, int tam); //preenche todos os campos de um vetor com -1
void tabuleiro(int *game); //desenha o tabuleiro
void configuraArvore(Arvore *A); //insere na ordem os numeros dos campos dos tabuleiros
void Responde(Arvore A, int *jogo);
void InsereLocalizado(Arvore *A, Arvore *B, tipoChave C);
int Vitoria(int *jogo); //verifica se alguem ganhou
bool Velha(int *jogo); //verifica se deu velha
int coringa(int *jogo); 
void Intro(); 

void IniciaUM(Arvore *U);
void IniciaDOIS(Arvore *D);
void IniciaTRES(Arvore *T);
void IniciaQUATRO(Arvore *Q);
void IniciaCINCO(Arvore *C);
void IniciaSEIS(Arvore *S);
void IniciaSETE(Arvore *S);
void IniciaOITO(Arvore *O);
void IniciaNOVE(Arvore *N);

#endif
