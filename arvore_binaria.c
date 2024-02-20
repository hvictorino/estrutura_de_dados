#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct No{
	int conteudo;
	struct No *esq;
	struct No *dir;
} No;

No *inserir(No *pRaiz, int numero){
	if(pRaiz == NULL){
		No *novo = (No*)malloc(sizeof(No));
		novo->conteudo = numero;
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
	}else{
		if(numero < pRaiz->conteudo)
			pRaiz->esq = inserir(pRaiz->esq, numero);
		if(numero > pRaiz->conteudo)
			pRaiz->dir = inserir(pRaiz->dir, numero);
		return pRaiz;
	}
}

void imprimir(No *pRaiz, int tipoImp){
	if(pRaiz != NULL){
		switch(tipoImp){
			// EmOrdem
			case 1:
				imprimir(pRaiz->esq,tipoImp);
				printf("%d ",pRaiz->conteudo);
				imprimir(pRaiz->dir,tipoImp);
				break;
			// PreOrdem
			case 2:
				printf("%d ",pRaiz->conteudo);
				imprimir(pRaiz->esq,tipoImp);
				imprimir(pRaiz->dir,tipoImp);
				break;
			// PosOrdem
			case 3:
				imprimir(pRaiz->esq,tipoImp);
				imprimir(pRaiz->dir,tipoImp);
				printf("%d ",pRaiz->conteudo);
				break;
			default:
				printf("\nTipo de impressão inválida.\n");
				
		}
	}
}

No *remover(No *pRaiz, int valor){
	if(pRaiz == NULL){
		printf("Valor não encontrado!\n");
		return NULL;
	}else{
		if(pRaiz->conteudo == valor){
			
			int esquerda = pRaiz->esq != NULL;
			int direita = pRaiz->dir != NULL;
			
			// remove nós folhas
			if(!esquerda && !direita)
			{
				free(pRaiz);
				return NULL;
			}else{
				// remove nós que têm apenas um filho
				if(!esquerda || !direita){
					No *aux;
					if(esquerda && !direita)
						aux = pRaiz->esq;
					if(!esquerda && direita)
						aux = pRaiz->dir;
					
					free(pRaiz);
					return aux;
				}else{
					// remove nós que têm dois filhos
					No *aux = pRaiz->esq;
					while(aux->dir != NULL)
						aux = aux->dir;
					
					pRaiz->conteudo = aux->conteudo;
					aux->conteudo = valor;
					
					pRaiz->esq = remover(pRaiz->esq, chave);
					
					return pRaiz;
				}
			}
		}else{
			if(valor < pRaiz->conteudo)
				pRaiz->esq = remover(pRaiz->esq, valor);
			if(valor > pRaiz->conteudo)
				pRaiz->dir = remover(pRaiz->dir, valor);
			return pRaiz;
		}
	}
}

int main()
{
	setlocale(LC_ALL,"Portuguese");
	No *pRaiz = NULL;
	int op, numero;
	
	do{
		printf("\n0 - Sair\n1 - Inserir\n2 - Imprimir\n3 - Remover\n");
		scanf("%d",&op);
		
		switch(op){
			case 0:
				printf("\nPrograma encerrado...");
				break;
			case 1:
				/*
				printf("Digite o valor a ser inserido: ");
				scanf("%d",&numero);
				pRaiz = inserir(pRaiz, numero);
				*/
				pRaiz = inserir(pRaiz,34);
				pRaiz = inserir(pRaiz,80);
				pRaiz = inserir(pRaiz,55);
				pRaiz = inserir(pRaiz,40);
				pRaiz = inserir(pRaiz,43);
				pRaiz = inserir(pRaiz,5);
				pRaiz = inserir(pRaiz,13);
				pRaiz = inserir(pRaiz,75);
				pRaiz = inserir(pRaiz,1);
				pRaiz = inserir(pRaiz,17);
				pRaiz = inserir(pRaiz,26);
				pRaiz = inserir(pRaiz,90);
				break;
			case 2:
				printf("\n");
				imprimir(pRaiz, 1);
				printf("\n");
				imprimir(pRaiz, 2);
				printf("\n");
				imprimir(pRaiz, 3);
				printf("\n");
				break;
			case 3:
				printf("Digite o valor a ser inserido: ");
				scanf("%d",&numero);
				pRaiz = remover(pRaiz, numero);
				break;
			default:
				printf("\nOpção inválida.\n");
			
		}
	}while(op != 0);
		
	return 0;
}
