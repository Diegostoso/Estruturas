#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <locale.h>

typedef struct sAluno{
	int matricula;
	char nome[50];
	float p1, p2, p3, total;
}Aluno;


typedef struct sCELULA{
	Aluno info;
	struct sCELULA *prox;
}CELULA;

// funções básicas: inicializar, criar nó, verificar se a lista está vazia

void inicializar(CELULA **lista){
	*lista = NULL;
}

CELULA* cria_no(){
	return (CELULA*)malloc(sizeof(CELULA));
}

int lista_vazia(CELULA* lista){
	if(lista == NULL){
		printf("\n  ---- Ops! Não há alunos na lista! ----\n\n");
		return 1;
	}
	return 0;
}

// calcula a soma total das notas de cada aluno
void calcula_total(CELULA **no){
	(*no)->info.total = (*no)->info.p1 + (*no)->info.p2 + (*no)->info.p3;
}

// insere cada aluno com suas respectivas notas
void insere(CELULA **lista, Aluno x){
	CELULA *q;
	CELULA *aux;
	
	q = cria_no();

	if(q == NULL){
		printf("!!! ERRO !!! \n Houve um problema na alocaçãoo do nó! \n\n");
		exit(1);
	} else {
		q->info.matricula = x.matricula;
		strcpy(q->info.nome, x.nome);
		q->info.p1 = x.p1;
		q->info.p2 = x.p2;
		q->info.p3 = x.p3;
		calcula_total(&q);

		q->prox = NULL;
		
		if(*lista == NULL){
			*lista = q;
		} else{
			aux = *lista;
			
			while (aux->prox != NULL){
				aux = aux->prox;
			}
			aux->prox = q;
		}
	printf("\n ---- Aluno(a) inserido(a) com sucesso! ----\n");
	}
}

//imprime todos os dados dos alunos
void imprimir(CELULA *lista){ 
	CELULA *aux;
	aux = lista;
	
	printf("\n");

	if(lista_vazia(lista)){
		return;
	}else{
		while(aux != NULL){
			printf("==============================================\n");
			printf("	Matrícula: %d \n", aux->info.matricula);
			printf("	Nome: %s \n", aux->info.nome);
			printf("	Notas: ( P1 ) %.2f \n", aux->info.p1);
			printf("	       ( P2 ) %.2f \n", aux->info.p2);
			printf("	       ( P3 ) %.2f \n", aux->info.p3);
			printf("	Total: %.2f \n", aux->info.total);
			printf("\n");
			aux = aux->prox;
		}
	}
	printf("\n");
}

//remove aluno de acordo com a matrícula informada
void remove_elem(CELULA **lista, int matricula){
	CELULA *aux;
	CELULA *ant;
	
	aux = *lista;
	ant = *lista;

	if(lista_vazia(*lista)){
  		return;
  	}else{
		while(aux->info.matricula != matricula || aux == NULL){
			ant = aux;
			aux = aux->prox;
   		}

		if(aux->info.matricula == matricula){
   			if((*lista) == aux){
   				*lista = aux->prox;
   			} else {
   				ant->prox = aux->prox;
   			}
   			printf("\n\n  ---- Aluno removido com sucesso! ----\n");
      	}else{
  			printf("  !!! ERRO !!! \n Aluno não encontrado! \n\n");
      	}

  	}
  	free(aux);
}



void maiorNota(CELULA *lista){
	CELULA *maior = lista;
	CELULA *aux = lista;

	if (lista_vazia(lista))
		return;

	while (aux != NULL)
	{
		if (aux->info.total > maior->info.total)
		{
			maior = aux;
		}
		aux=aux->prox;
	}
	printf("==============================================\n");
	printf("	O aluno de maior nota é: \n");
	printf("	Matrícula: %d \n", maior->info.matricula);
	printf("	Nome:      %s \n", maior->info.nome);
	printf("	Total:     %.2f \n", maior->info.total);

}

void menorNota(CELULA *lista){
	CELULA *menor = lista;
	CELULA *aux = lista;

	if (lista_vazia(lista))
		return;

	while (aux != NULL)
	{
		if (aux->info.total < menor->info.total)
		{
			menor = aux;
		}
		aux=aux->prox;
	}
	printf("==============================================\n");
	printf("	O aluno de menor nota é: \n");
	printf("	Matricula: %d \n", menor->info.matricula);
	printf("	Nome:      %s \n", menor->info.nome);
	printf("	Total:     %.2f\n", menor->info.total);

}

void situacaoAluno(CELULA *lista){
	CELULA *aux;
	aux = lista;

	if(lista_vazia(lista)){
		return;
	}else{
		while(aux != NULL){
			printf("==============================================\n");
			printf("  Matricula: %d \n", aux->info.matricula);
			printf("  Nome: %s \n", aux->info.nome);

			if(aux->info.total > 60){
				printf("  O(a) aluno(a) foi aprovado!\n\n");
			}else{
				printf("  O(a) aluno(a) foi reprovado!\n\n");
			}
			aux = aux->prox;
		}
	}
}

/*
CELULA* FindMenorAnt(CELULA **lista){ 
    
	CELULA *aux = *lista;
	CELULA *menor = *lista;
	CELULA *ant = NULL;
	CELULA *antMenor = *lista;

	while(aux!=NULL){
    	if(aux->info.total < menor->info.total){
    		menor = aux;
    		antMenor = &ant->prox;
   		}
	    ant = aux;
    	aux = aux->prox;
    }

	//printf("o ant menor é: %s %f\n", antMenor->info.nome, antMenor->info.total);
	return *antMenor;
}

//nessa função utilizei o metodo de mover pra frente para 
//facilitar o metodo de ordenação do código
void moverPraFrente(CELULA **lista){
	CELULA *aux = *lista;
	CELULA **antmenortotal = FindMenorAnt(lista);
	printf("sadby\n");
	//printf("o menor é: %s %d\n", antmenortotal->prox->info.nome, antmenortotal->prox->info->total);

	CELULA *menortotal = *antmenortotal;
	CELULA *menor = NULL;
	CELULA *antmenor = NULL;
		
	//primeira movimentação
	*antmenortotal = menortotal->prox;
 	menortotal->prox = *lista;
  	*lista = menortotal;
	
	while(menortotal->prox != NULL){
		printf("teste2\n");
		antmenor = FindMenorAnt(&menortotal->prox);
		printf("teste3\n");
		imprimir(*lista);
		menor = antmenor->prox;
		antmenor->prox = menor->prox;
		menor->prox = *lista;
		*lista = menor;
	}
	
}

*/

void moverPraFrente(CELULA **lista, CELULA *ant){

	CELULA *menor = ant->prox;
	ant->prox = menor->prox;
	menor->prox = *lista;
	*lista = menor;

}

void ordena(CELULA **lista){

	CELULA *aux = *lista;
	CELULA *menortotal = *lista;
	CELULA *ant = NULL;
	CELULA *antMenor = *lista;
	CELULA *menor;

	while(aux!=NULL){
    	if(aux->info.total < menortotal->info.total){
    		menortotal = aux;
    		antMenor = ant;
   		}
	    ant = aux;
    	aux = aux->prox;
    }

	if(antMenor != *lista)
		moverPraFrente(lista, antMenor);

	while(menortotal->prox != NULL)
	{
		aux = menortotal->prox;
		menor = aux;
		while(aux != NULL)
		{
			if(aux->info.total < menor->info.total)
			{
				menor = aux;
				antMenor = ant;
   			}
			ant = aux;
			aux = aux->prox;
		}
		if (menor = menortotal->prox)
			antMenor = menortotal;
		moverPraFrente(lista, antMenor);
	}

}


int main(){
	setlocale(LC_ALL, "Portuguese"); //Faz alterar a linguagem para portugues

	CELULA *ptrlista;	
	ptrlista = cria_no();	
	inicializar(&ptrlista);
	
	int opcao=-1;
	int mat;
	Aluno elem;

	// Aluno teste1;
	// teste1.matricula = 123;
	// strcpy(teste1.nome, "Ana");
	// teste1.p1 = 14;
	// teste1.p2 = 25;
	// teste1.p3 = 18;

	// Aluno teste2;
	// teste2.matricula = 124;
	// strcpy(teste2.nome, "João");
	// teste2.p1 = 17;
	// teste2.p2 = 26;
	// teste2.p3 = 34;

    // Aluno teste3;
	// teste3.matricula = 456;
	// strcpy(teste3.nome, "abigail");
	// teste3.p1 = 2;
	// teste3.p2 = 3;
	// teste3.p3 = 7;

	// insere(&ptrlista, teste1);
	// insere(&ptrlista, teste2);
    // insere(&ptrlista, teste3);
	imprimir(ptrlista);

	printf("%d\n", *ptrlista);

	printf("\n"); 
	printf(" ==============================================\n");
	printf(" ||           SEJA BEM VINDO(A) AO           || \n");
	printf(" ||         DIÁRIO DE CLASSE VIRTUAL!        || \n");
	printf(" ==============================================\n");


	do{
		printf("\n"); 
		printf(" ==============================================\n");
		printf("  Por favor, escolha uma das opções abaixo: \n\n");
		printf("	1) Inserir um aluno. \n");
		printf("	2) Remover um aluno. \n"); 
		printf("	3) Imprimir a lista de alunos. \n");
		printf("	4) Mostrar a maior e a menor nota. \n");
		printf("	5) Ver a situação dos alunos. \n");
		printf("	6) Ordenar os alunos pela maior nota. \n");
		printf("	0) Sair. \n");
		printf("     -> ");
		scanf("%d", &opcao);
	
	
		switch (opcao){

		  	case 1 :
		  		printf("\n\n");
				printf("  Para inserir um novo aluno, informe os dados abaixo: \n\n");
				printf("  Nome: ");
				getchar(); 
				gets(elem.nome);

				printf("  Matrícula: ");
				scanf("%d", &elem.matricula);

				printf("  Nota da P1: ");
				scanf("%f", &elem.p1);

				printf("  Nota da P2: ");
				scanf("%f", &elem.p2);

				printf("  Nota da P3: ");
				scanf("%f", &elem.p3);

		  		insere(&ptrlista, elem);
		  		
				break;
		      
		    case 2 :
				printf("  Para remover um aluno, informe sua matrícula:   ");
		     	scanf("%d", &mat);
				remove_elem(&ptrlista,mat);	
				break;
		    
			case 3 :
				printf("  Alunos da turma: \n");
				imprimir(ptrlista);
				break;

			case 4 : 
				maiorNota(ptrlista);
				menorNota(ptrlista);
				break;

			case 5 :
				situacaoAluno(ptrlista);
				break;

			case 6 :
				ordena(&ptrlista);
				break;
			}
		}
	while(opcao != 0);
	printf("\n\n  Saindo...");

	return 0;
}
