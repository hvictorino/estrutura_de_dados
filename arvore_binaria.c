#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct No{
	int conteudo;
	short altura;
	struct No *esq;
	struct No *dir;
} No;

/*
	Função que cria um novo nó
	valor -> valor a ser inserido no nó
	Retorna: o endereço do nó criado
*/
No *novoNo(int valor){
	No *novo = malloc(sizeof(No));
	if(novo){
		novo->conteudo = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->altura = 0;
	}else
		printf("\nERRO ao alocar nó em novoNo!\n");
	
	return novo;
}

/*
	Retorna o maior dentre dois valores
	a, b -> altura de dois nós da árvore
*/
short maior(short a, short b){
	return a > b ? a : b;
}

/*
	Retorna a altura de um nó ou -1 caso ele seja nulo
*/
short alturaDoNo(No *no){
	if(no == NULL)
		return -1;
	else
		return no->altura;
}

/*
	Calcula e retorna o fator de balanceamento de um nó
*/
short fatorDeBalanceamento(No *no){
	if(no)
		return (alturaDoNo(no->esq) - alturaDoNo(no->dir));
	else
		return 0;
}

/*
	Função para a rotação à esquerda
*/
No *rotacaoEsquerda(No *raiz){
	No *p, *q;
	
	p = raiz->dir;
	q = p->esq;
	
	p->esq = raiz;
	raiz->dir = q;
	
	raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;
	p->altura = maior(alturaDoNo(p->esq), alturaDoNo(p->dir)) + 1;
	
	return p;
}

/*
	Função para a rotação à direita
*/
No *rotacaoDireita(No *raiz){
	No *p, *q;
	
	p = raiz->esq;
	q = p->dir;
	
	p->dir = raiz;
	raiz->esq = q;
	
	raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;
	p->altura = maior(alturaDoNo(p->esq), alturaDoNo(p->dir)) + 1;
	
	return p;
}

/*
	Função para a rotação direita-esquerda
*/
No *rotacaoDireitaEsquerda(No *raiz){
	raiz->dir = rotacaoDireita(raiz->dir);
	return rotacaoEsquerda(raiz);
}

/*
	Função para a rotação esquerda-direita
*/
No *rotacaoEsquerdaDireita(No *raiz){
	raiz->esq = rotacaoEsquerda(raiz->esq);
	return rotacaoDireita(raiz);
}

/*
	Função para realizar o balanceamento da árvore após uma inserção ou remoção
	Recebe o nó que está desbalanceado e retorna a noa raiz após o balanceamento
*/
No *balancear(No *raiz){
	short fb = fatorDeBalanceamento(raiz);
	
	// Rotação à esquerda
	if(fb < -1 && fatorDeBalanceamento(raiz->dir) <= 0)
		raiz = rotacaoEsquerda(raiz);
	
	// Rotação à direita
	else if(fb > 1 && fatorDeBalanceamento(raiz->esq) >= 0)
		raiz = rotacaoDireita(raiz);
	
	// Rotação dupla à esquerda
	else if(fb > 1 && fatorDeBalanceamento(raiz->esq) < 0)
		raiz = rotacaoEsquerdaDireita(raiz);
	
	// Rotação dupla à direita
	else if(fb < -1 && fatorDeBalanceamento(raiz->dir) > 0)
		raiz = rotacaoDireitaEsquerda(raiz);
	
	return raiz;
}

/*
	Insere um novo nó na árvore
	raiz -> raiz da árvore
	valor -> valor a ser inserido
	Retorno: endereço do novo nó ou nova raiz após o balanceamento
*/
No *inserir(No *raiz, int valor){
	if(raiz == NULL) // árvore vazia
		return novoNo(valor);
	else{
		if(valor < raiz->conteudo)
			raiz->esq = inserir(raiz->esq, valor);
		if(valor > raiz->conteudo)
			raiz->dir = inserir(raiz->dir, valor);
		if(valor == raiz->conteudo)
			printf("\nJá existe um elemento de valor %d nesta árvore!\n", valor);
	}
	
	// Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
	raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;
	
	// verifica se é necessário rebalancear a árvore
	raiz = balancear(raiz);
	
	return raiz;
}

/*
	Remove um nó da árvore
	raiz -> raiz da árvore
	valor -> valor a ser removido
*/
No *remover(No *raiz, int valor){
	if(raiz == NULL){
		printf("\nValor não encontrado\n");
		return NULL;
	}else{ // procura o nó a remover
		if(raiz->conteudo == valor){
			// remove nós folhas
			if(raiz->esq == NULL && raiz->dir == NULL){
				free(raiz);
				printf("\nElemento folha removido: %d\n",valor);
				return NULL;
			}else{
				// remover nós que possuem 2 filhos
				if(raiz->esq != NULL && raiz->dir != NULL){
					No *aux = raiz->esq;
					while(aux->dir != NULL)
						aux = aux->dir;
					
					raiz->conteudo = aux->conteudo;
					aux->conteudo = valor;
					printf("\nElemento trocado: %d\n",valor);
					raiz->esq = remover(raiz->esq, valor);
					return raiz;
				}else{
					// remover nós que possuem apenas 1 filho
					No *aux;
					if(raiz->esq != NULL)
						aux = raiz->esq;
					else
						aux = raiz->dir;
					
					free(raiz);
					printf("\nElemento com 1 filho removido: %d\n",valor);
					return aux;
				}
			}
		}else{
			if(valor < raiz->conteudo)
				raiz->esq = remover(raiz->esq, valor);
			if(valor > raiz->conteudo)
				raiz->dir = remover(raiz->dir, valor);
		}
		
		// Recalcula a altura dos nós
		raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir)) + 1;
		
		// Faz o rebalanceamento caso seja necessário
		raiz = balancear(raiz);
		
		return raiz;
	}
}

/*
	Função para imprimir a árvore no console
*/
void imprimir(No *raiz, int nivel){
	int i;
	if(raiz){
		imprimir(raiz->dir, nivel + 1);
		printf("\n\n");
		
		for(i = 0; i < nivel; i++)
			printf("\t");
		
		printf("%d",raiz->conteudo);
		imprimir(raiz->esq, nivel + 1);
	}
}


/*
	Função para imprimir a árvore com base nos percursos
	Em Ordem
	Pré-ordem
	Pós-ordem
*/
void imprimirPercurso(No *raiz, int tipoImp)
{
	if(raiz != NULL){
		switch(tipoImp){
			// EmOrdem
			case 1:
				imprimirPercurso(raiz->esq,tipoImp);
				printf("%d ",raiz->conteudo);
				imprimirPercurso(raiz->dir,tipoImp);
				break;
			// PreOrdem
			case 2:
				printf("%d ",raiz->conteudo);
				imprimirPercurso(raiz->esq,tipoImp);
				imprimirPercurso(raiz->dir,tipoImp);
				break;
			// PosOrdem
			case 3:
				imprimirPercurso(raiz->esq,tipoImp);
				imprimirPercurso(raiz->dir,tipoImp);
				printf("%d ",raiz->conteudo);
				break;
			case 4:
				imprimir(raiz, 1);
				break;
			default:
				printf("\nTipo de impressão inválida.\n");
		}
	}
}

int main(){
	setlocale(LC_ALL,"Portuguese");
	
	int op, valor, tipoImp;
	No *raiz = NULL;
	
	do{
		printf("\n\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\t0 - Sair\n\n");
		scanf("%d",&op);
		
		switch(op){
			case 0:
				printf("\nPrograma encerrado...");
				break;
			case 1:
				printf("\n\tDigite o valor a ser inserido: ");
				scanf("%d",&valor);
				raiz = inserir(raiz, valor);
				imprimir(raiz, 1);
				break;
			case 2:
				printf("\n\tDigite o valor a ser removido: ");
				scanf("%d",&valor);
				raiz = remover(raiz, valor);
				printf("\n");
				imprimir(raiz, 1);
				break;
			case 3:
				printf("\n");
				printf("\n\n\tEscolha um tipo de impressão\n\t1 - InOrdem\n\t2 - PreOrdem\n\t3 - PosOrdem\n\t4 - Árvore\n\n");
				scanf("%d",&tipoImp);
				printf("\n\tImpressão %s\n\t",tipoImp == 1 ? "InOrdem":tipoImp == 2? "PreOrdem":"PosOrdem");
				imprimirPercurso(raiz, tipoImp);
				printf("\n");
				break;
			default:
				printf("\nOpção inválida!\n");
		}
		
	}while(op != 0);
	
	return 0;
}
