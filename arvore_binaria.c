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
		novo->alura = 0;
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
	
	raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir) + 1;
	p->altura = maior(alturaDoNo(p->esq), alturaDoNo(p->dir) + 1;
	
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
	
	raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir) + 1;
	p->altura = maior(alturaDoNo(p->esq), alturaDoNo(p->dir) + 1;
	
	return p;
}

/*
	Função para a rotação direita-esquerda
*/
No *rotacaoDireitaEsquerda(No *raiz){
	raiz->dir = rotacaoDireita(r->dir);
	return rotacaoEsquerda(raiz);
}

/*
	Função para a rotação esquerda-direita
*/
No *rotacaoEsquerdaDireita(No *raiz){
	raiz->esq = rotacaoEsquerda(r->esq);
	return rotacaoDireita(raiz);
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
		if(valor < raiz->valor)
			raiz->esq = inserir(raiz->esq, valor);
		if(valor > raiz-> valor)
			raiz->dir = inserir(raiz->dir, valor);
		if(valor == raiz->valor)
			printf("\nJá existe um elemento de valor %d nesta árvore!\n", valor);
	}
	
	// Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
	raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir) + 1;
	
	// verifica se é necessário rebalancear a árvore
	raiz = balancear(raiz);
	
	return raiz;
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
	else if(fb > 1 && fatorDeBalanceamento(raiz->esq >= 0)
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
	Remove um nó da árvore
	raiz -> raiz da árvore
	valor -> valor a ser removido
*/
No *remover(No *raiz, int valor){
	if(raiz == NULL){
		printf("Valor não encontrado\n");
		return NULL;
	}else{ // procura o nó a remover
		if(raiz->conteudo == valor){
			// remove nós folhas
			if(raiz->esq == NULL && raiz->dir == NULL){
				free(raiz);
				printf("Elemento folha removido: %d\n",valor);
				return NULL;
			}else{
				// remover nós que possuem 2 filhos
				if(raiz->esq != NULL && raiz->dir != NULL){
					No *aux = raiz->esq;
					while(aux->dir != NULL)
						aux = aux->dir;
					
					raiz->conteudo = aux->conteudo;
					aux->conteudo = valor;
					printf("Elemento trocado: %d\n",valor);
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
					printf("Elemento com 1 filho removido: %d\n",valor);
					return aux;
				}
			}
		}else{
			if(chave < raiz->conteudo)
				raiz->esq = remover(raiz->esq, valor);
			if(chave > raiz->conteudo)
				raiz->dir = remover(raiz->dir, valor);
		}
		
		// Recalcula a altura dos nós
		raiz->altura = maior(alturaDoNo(raiz->esq), alturaDoNo(raiz->dir) + 1;
		
		// Faz o rebalanceamento caso seja necessário
		raiz = balancear(raiz);
		
		return raiz;
	}
}


int main(){
	setlocale(LC_ALL,"Portuguese");
	
	No *raiz = NULL;
	
	
	return 0;
}
