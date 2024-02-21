#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct No{
	int conteudo;
	struct No *esq;
	struct No *dir;
	int balanco;
	int altura;
} No;

No *inserir(No *pRaiz, int valor){
	if(pRaiz == NULL){
		No *novo = (No*)malloc(sizeof(No));
		novo->conteudo = valor;
		novo->esq = NULL;
		novo->dir = NULL;
		
		
		return novo;
	}else{
		if(valor < pRaiz->conteudo)
		{
			pRaiz->esq = inserir(pRaiz->esq, valor);
		}
			
		if(valor > pRaiz->conteudo)
		{
			pRaiz->dir = inserir(pRaiz->dir, valor);
		}
		
		return pRaiz;
	}
}

int buscar(No *pRaiz, int valor){
	if(pRaiz == NULL)
		return 0;
	else{
		if(pRaiz->conteudo == valor)
			return 1;
		else{
			if(valor < pRaiz->conteudo)
				return buscar(pRaiz->esq, valor);
			if(valor > pRaiz->conteudo)
				return buscar(pRaiz->dir, valor);
		}
	}
}

No *buscarNo(No *pRaiz, int valor){
	if(pRaiz == NULL)
		return NULL;
	else{
		if(pRaiz->conteudo == valor)
			return pRaiz;
		else{
			if(valor < pRaiz->conteudo)
				return buscarNo(pRaiz->esq, valor);
			if(valor > pRaiz->conteudo)
				return buscarNo(pRaiz->dir, valor);
		}
	}
}

int alturaArv(No *pRaiz){
	if(pRaiz == NULL || pRaiz->esq &&pRaiz->dir == NULL)
		return 0;
	else{
		int esq = 1 + alturaArv(pRaiz->esq);
		int dir = 1 + alturaArv(pRaiz->dir);
		
		if(esq > dir)
			return esq;
		else
			return dir;
	}
}

int alturaSubArv(No *pRaiz, int valor){
	No *no = buscarNo(pRaiz, valor);
	if(no)
		return alturaArv(no);
	else
		return -1;
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
					
					pRaiz->esq = remover(pRaiz->esq, valor);
					
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

void balanceamento(){
	printf("mais um teste de commit de nova branch");
}

int main()
{
	setlocale(LC_ALL,"Portuguese");
	No *pRaiz = NULL;
	int op, valor;
	int tipoImp;
	
	do{
		printf("\n0 - Sair\n1 - Inserir\n2 - Imprimir\n3 - Remover\n4 - Buscar\n5 - Altura\n6 - Altura da Sub-árvore\n");
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
				printf("\nEscolha um tipo de impressão\n1 - InOrdem\n2 - PreOrdem\n3 - PosOrdem\n");
				scanf("%d",&tipoImp);
				printf("\nImpressão %s\n",tipoImp == 1 ? "InOrdem":tipoImp == 2? "PreOrdem":"PosOrdem");
				imprimir(pRaiz, tipoImp);
				printf("\n");
				break;
			case 3:
				printf("Digite o valor a ser removido: ");
				scanf("%d",&valor);
				pRaiz = remover(pRaiz, valor);
				break;
			case 4:
				printf("\nDigite o valor a buscar: ");
				scanf("%d",&valor);
				if(buscar(pRaiz, valor))
					printf("\nValor encontrado!\n");
				else
					printf("\nValor não encontrado!\n");
				break;
			case 5:
				printf("\nAltura da árvore: %d",alturaArv(pRaiz));
				break;
			case 6:
				printf("\nDigite o valor do nó que quer saber a altura: ");
				scanf("%d",&valor);
				printf("\nAltura da sub-árvore desse nó é: %d\n",alturaSubArv(pRaiz, valor));
				break;
			default:
				printf("\nOpção inválida.\n");
			
		}
	}while(op != 0);
		
	return 0;
}
