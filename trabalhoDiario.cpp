#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <locale.h>

typedef struct sAluno{
	float p1,p2,p3, total;
	int matricula;
	char nome[50];
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
		printf("Não há alunos na lista! \n");
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
	}
}

void imprimir(CELULA *lista){ 
	CELULA *aux;
	aux = lista;
	
	printf("\n");

	if(lista_vazia(lista)){
		return;
	}else{
		while(aux != NULL){
			printf("Matrícula: %d | ", aux->info.matricula);
			printf("Nome: %s | ", aux->info.nome);
			printf("Notas: %.2f %.2f %.2f| ", aux->info.p1, aux->info.p2, aux->info.p3);
			printf("Total: %.2f\n", aux->info.total);
			printf("\n");
			aux = aux->prox;
		}
	}
	printf("\n");
}

//REMOVER O ALUNO DE ACORDO COM A MATRICULA COMO PARAMETRO	
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
   			printf("\nAluno removido com sucesso! \n");
      	}else{
  			printf("!!! ERRO !!! \n Aluno não encontrado! \n\n");
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

	printf("O aluno de maior nota é: \n");
	printf("Matricula: %d |", maior->info.matricula);
	printf("Nome: %s |", maior->info.nome);
	printf("Total: %.2f \n", maior->info.total);

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

	printf("\nO aluno de menor nota é: \n");
	printf("Matricula: %d |", menor->info.matricula);
	printf("Nome: %s |", menor->info.nome);
	printf("Total: %.2f\n", menor->info.total);

}

void situacaoAluno(CELULA *lista){
	CELULA *aux;
	aux = lista;

	if(lista_vazia(lista)){
		return;
	}else{
		while(aux != NULL){
			printf("Matricula: %d \n", aux->info.matricula);
			printf("Nome: %s \n", aux->info.nome);

			if(aux->info.total > 60){
				printf("O aluno foi aprovado!\n\n");
			}else{
				printf("O aluno foi reprovado!\n\n");
			}

			aux = aux->prox;
		}
	}
}


CELULA* FindMenorAnt(CELULA *lista){ 
	CELULA *aux = lista;
	CELULA *menor = lista;
	CELULA *ant = NULL;
	CELULA *antMenor = NULL;

	while(aux->prox!=NULL){
    	if(aux->info.total < menor->info.total){
    		menor = aux;
    		antMenor = ant;
   		}
	    ant = aux;
    	aux = aux->prox;
    }
	return antMenor;
}

//nessa função utilizei o metodo de mover pra frente para 
//facilitar o metodo de ordenação do código
void moverPraFrente(CELULA **lista){
	CELULA *aux = *lista;
	CELULA *antmenortotal = FindMenorAnt(*lista);
	CELULA *menortotal = antmenortotal->prox;
	CELULA *menor = NULL;
	CELULA *antmenor = NULL;
		
	//primeira movimentação
	antmenortotal->prox = menortotal->prox;
 	menortotal->prox = *lista;
  	*lista = menortotal;
	
	while(menortotal->prox != NULL){
		antmenor = FindMenorAnt(menortotal->prox);
		menor = antmenor->prox;
		antmenor->prox = menor->prox;
		menor->prox = *lista;
		*lista = menor;
	}
}


int main(){

	setlocale(LC_ALL, "Portuguese"); //LINGUAGEM EM PORTUGUES

	CELULA *ptrlista;
	
	ptrlista = cria_no();
	
	inicializar(&ptrlista);

	int opcao=-1;
	Aluno elem;
	int mat;

	Aluno teste1;
	teste1.matricula = 123;
	strcpy(teste1.nome, "Ana");
	teste1.p1 = 14;
	teste1.p2 = 25;
	teste1.p3 = 18;

	Aluno teste2;
	teste2.matricula = 124;
	strcpy(teste2.nome, "Joao");
	teste2.p1 = 17;
	teste2.p2 = 26;
	teste2.p3 = 34;



	insere(&ptrlista, teste1);
	insere(&ptrlista, teste2);
	imprimir(ptrlista);


	printf("\e[H\e[2J");
	do{
		printf("\n\n------ SEJA BEM VINDO(A) AO ------\n");
		printf("---- DIARIO DE CLASSE VIRTUAL ----");

		printf("\n\n  Escolha uma das opcoes abaixo: \n\n");
		printf("1) Inserir um aluno. \n");
		printf("2) Remover um aluno. \n");
		printf("3) Imprimir a lista de alunos. \n");
		printf("4) Mostrar maior e menor nota. \n");
		printf("5) Ver a situação dos alunos. \n");
		printf("6) Ordenar os alunos pela maior nota. \n");
		printf("0) Sair. \n");
		scanf("%d", &opcao);
	
		switch (opcao){

	    	
		  	case 1 :
		  		printf("\e[H\e[2J");
		  		//INSERIR TODOS DADOS DO ALUNO
				printf("Insira um aluno na lista: \n");
				printf("Nome: ");
		    	//fflush(stdin);
				getchar(); //VERIFICAR NO WINDOWS
				gets(elem.nome);

				printf("Matrícula: ");
				scanf("%d", &elem.matricula);

				printf("Nota da Primeira Prova: ");
				scanf("%f", &elem.p1);

				printf("Nota da Segunda Prova: ");
				scanf("%f", &elem.p2);

				printf("Nota da Terceira Prova: ");
				scanf("%f", &elem.p3);

		  		insere(&ptrlista, elem);
				break;
		      
		    case 2 :
		    	printf("\e[H\e[2J");
		    	imprimir(ptrlista);
				printf("Qual aluno deseja remover?  ");
		     	scanf("%d", &mat);
				remove_elem(&ptrlista,mat);
				break;
		    
			case 3 :
				printf("\e[H\e[2J");
				printf("Alunos da turma: \n");
				imprimir(ptrlista);
				break;

			case 4 : 
				printf("\e[H\e[2J");
				maiorNota(ptrlista);
				menorNota(ptrlista);
				break;

			case 5 :
				printf("\e[H\e[2J");
				situacaoAluno(ptrlista);
				break;

			case 6 :
				printf("\e[H\e[2J");
				moverPraFrente(&ptrlista);
				break;
			}
		}
	while(opcao != 0);

	return 0;
}
