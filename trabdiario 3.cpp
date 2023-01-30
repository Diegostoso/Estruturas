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
		printf("\n               ---- Ops! Não há alunos na lista! ---- \n\n");
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
		printf("\n               ---- Houve um problema na alocaçãoo do nó! ----\n\n");
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
		printf("\n               ---- Aluno(a) inserido(a) com sucesso! ----\n");
	}
}

//Imprime todos os dados dos alunos
void imprimir(CELULA *lista){ 
	CELULA *aux = lista;
	
	printf("\n");

	if(lista_vazia(lista)){
		return;
	}else{
		while(aux != NULL){
			printf("  =======================================================================\n");
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
	CELULA *aux = *lista;
	CELULA *ant = *lista;

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
   			free(aux);
   			printf("\n               ---- Aluno(a) removido com sucesso! ----\n");
      	}else{
      		if(aux == NULL){
      			printf("\n               ---- Este aluno não está na lista! ---- \n\n");
			}
      	}

  	}
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
	printf("  =======================================================================\n");
	printf("	O aluno de maior nota é: \n\n");
	printf("	Matrícula: %d \n", maior->info.matricula);
	printf("	Nome:      %s \n", maior->info.nome);
	printf("	Total:     %.2f \n\n", maior->info.total);

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
	printf("  =======================================================================\n");
	printf("	O aluno de menor nota é: \n\n");
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
			printf("  =======================================================================\n");
			printf("	Matricula: %d \n", aux->info.matricula);
			printf("	Nome: %s \n", aux->info.nome);

			if(aux->info.total > 60){
				printf("	O(a) aluno(a) foi aprovado!\n\n");
			}else{
				printf("	O(a) aluno(a) foi reprovado!\n\n");
			}
			aux = aux->prox;
		}
	}
}

void moverPraFrente(CELULA **lista, CELULA *ant){
	CELULA *menor = ant->prox;
	ant->prox = menor->prox;
	menor->prox = *lista;
	*lista = menor;
}

void ordenaNota(CELULA **lista){
	//inicializa todos os ponteiros no inicio da lista, exceto o *menor
	CELULA *aux = *lista;
	CELULA *menortotal = *lista;
	CELULA *antMenor = *lista;
	CELULA *ant = *lista;
	CELULA *menor;
	
	if(lista_vazia(*lista)){
		return;
	}
	
	while(aux != NULL){
    	if(aux->info.total < menortotal->info.total){
    		menortotal = aux;
    		antMenor = ant;
   		}
	    ant = aux;
    	aux = aux->prox;
    }

	if(menortotal != *lista)
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
		if (menor == menortotal->prox)
			antMenor = menortotal;
		moverPraFrente(lista, antMenor);
	}
	
	printf("\n- A ordenação foi realizada com sucesso, para vizualizar digite a opção 3 -\n");
}

void ordenaMatricula(CELULA **lista){
	//inicializa todos os ponteiros no inicio da lista, exceto o *menor
	CELULA *aux = *lista;
	CELULA *menormat = *lista;
	CELULA *ant = *lista;
	CELULA *antMenor = *lista;
	CELULA *menor;
	
	if(lista_vazia(*lista)){
		return;
	}
	
	while(aux != NULL){
    	if(aux->info.matricula > menormat->info.matricula){
    		menormat = aux;
    		antMenor = ant;
   		}
	    ant = aux;
    	aux = aux->prox;
    }

	if(menormat != *lista)
		moverPraFrente(lista, antMenor);

	while(menormat->prox != NULL)
	{
		aux = menormat->prox;
		menor = aux;
		while(aux != NULL)
		{
			if(aux->info.matricula > menor->info.matricula)
			{
				menor = aux;
				antMenor = ant;
   			}
			ant = aux;
			aux = aux->prox;
		}
		if (menor == menormat->prox)
			antMenor = menormat;
		moverPraFrente(lista, antMenor);
	}
	
	printf("\n- A ordenação foi realizada com sucesso, para vizualizar digite a opção 3 -\n");
}

int main(){
	setlocale(LC_ALL, "Portuguese"); //Faz alterar a linguagem para portugues
	system("mode con: cols=75 lines=40"); //Redimensiona o tamanho da tela de execução
	system("color 70");

	CELULA *ptrlista;	
	ptrlista = cria_no();	
	inicializar(&ptrlista);
	
	int opcao=-1;
	int mat;
	Aluno elem;

	Aluno teste1;
	teste1.matricula = 4;
	strcpy(teste1.nome, "Ana");
	teste1.p1 = 14;
	teste1.p2 = 25;
	teste1.p3 = 18;

	Aluno teste2;
	teste2.matricula = 2;
	strcpy(teste2.nome, "João");
	teste2.p1 = 17;
	teste2.p2 = 26;
	teste2.p3 = 34;

    Aluno teste3;
	teste3.matricula = 5;
	strcpy(teste3.nome, "Abigail");
	teste3.p1 = 2;
	teste3.p2 = 3;
	teste3.p3 = 7;
	
	Aluno teste4;
	teste4.matricula = 1;
	strcpy(teste4.nome, "Maria");
	teste4.p1 = 33;
	teste4.p2 = 33;
	teste4.p3 = 33;

	insere(&ptrlista, teste1);
	insere(&ptrlista, teste2);
    insere(&ptrlista, teste3);
    insere(&ptrlista, teste4);
	//imprimir(ptrlista);


	printf("\n"); 
	printf("  =======================================================================\n");
	printf("  ||                       SEJA BEM VINDO(A) AO                        || \n");
	printf("  ||                     DIÁRIO DE CLASSE VIRTUAL!                     || \n");
	printf("  =======================================================================\n");


	do{
		printf("\n"); 
		printf("  =======================================================================\n");
		printf("                  Por favor, escolha uma das opções abaixo: \n\n");
		printf("	1) Inserir um aluno. \n");
		printf("	2) Remover um aluno. \n"); 
		printf("	3) Imprimir a lista de alunos. \n");
		printf("	4) Mostrar a maior e a menor nota. \n");
		printf("	5) Ver a situação dos alunos. \n");
		printf("	6) Ordenar os alunos pela maior nota. \n");
		printf("	7) Ordenar os alunos pela matrícula. \n");
		printf("	0) Sair. \n\n");
		printf("     -> ");
		scanf("%d", &opcao);
	
	
		switch (opcao){

		  	case 1 :
		  		printf("\n");
		  		printf("  =======================================================================\n");
				printf("           Para inserir um novo aluno, informe os dados abaixo: \n\n");
				printf("	- Nome: ");
				getchar(); 
				gets(elem.nome);

				printf("	- Matrícula: ");
				scanf("%d", &elem.matricula);

				printf("	- Nota da P1: ");
				scanf("%f", &elem.p1);

				printf("	- Nota da P2: ");
				scanf("%f", &elem.p2);

				printf("	- Nota da P3: ");
				scanf("%f", &elem.p3);

		  		insere(&ptrlista, elem);
		  		
				break;
		      
		    case 2 :
		    	if(lista_vazia(ptrlista)){
		    		printf(" ");
				} else {		    	
			    	printf("\n");
			    	printf("  =======================================================================\n");
					printf("             Para remover um aluno, informe sua matrícula: \n");
					printf("     -> ");
			     	scanf("%d", &mat);
					remove_elem(&ptrlista,mat);	
				}
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
				ordenaNota(&ptrlista);
				break;
				
			case 7 :
				ordenaMatricula(&ptrlista);
				break;
				
			//Caso o usuário digitar um numero que não está no menu
			default:
				printf("                        ---- Opção inválida! ----");
				exit(1);
			}
		}
	while(opcao != 0);
	printf("\n\n  Saindo...");

	return 0;
}
