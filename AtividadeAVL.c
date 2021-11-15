#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct arvore{
    int info;
    struct arvore *esq;
    struct arvore *dir;
}arvore;

arvore *LerArvore(FILE *arq);
void ImprimirPreOrdem(arvore *a);
void ImprimirOrdem(arvore *a);
void ImprimirPosOrdem(arvore *a);
void ImprimirLargura(arvore *a, int aux, int nivel);
int CalcAltura (arvore *a);
int VerificaExistencia(arvore *a, int valor_desejado);
void NoFolhaMenor(arvore *a, int valor_desejado);
void NivelNo(arvore *a,int aux,int num_no);
void LimparArvore(arvore* a);
void *InserirNo(arvore *a,int x);
arvore *ExcluirNo(arvore *a,int x);
arvore *RotacionarEsquerda(arvore *a);
arvore *RotacionarEsquerdaSimples(arvore *a);
arvore *RotacionarEsquerdaDupla(arvore *a);
arvore *RotacionarDireita(arvore *a);
arvore *RotacionarDireitaSimples(arvore *a);
arvore *RotacionarDireitaDupla(arvore *a);
int main(){
    FILE * arq;
    int op;
    int valor_desejado, verifica, altura,aux_balanceada, aux_cheia, num_no, novo_no,apaga_no;
    char nome_arquivo[50];
    while (op!= 8)
    {    
    
    printf("\n\nO que voce deseja fazer? Digite: \n1- Para ler a arvore de um arquivo\n2- Para imprimir a arvore.\n3- Verificar se um elemento existe na arvore\n4- Imprimir o Nivel de Um no\n5- Imprimir as folhas menores que um valor\n6- Inserir um no X na arvore\n7- Remover um no X da arvore\n8- Sair\n");
    scanf("%d",&op);

    switch (op)
    {
    case 1:
        puts("Informe o nome do arquivo a ser lido");
        scanf("%s", nome_arquivo);
        arq = fopen(nome_arquivo, "rt");
        if (arq == NULL)
        {
            printf("Erro ao criar o arquivo\n");
            return 1;
        }
        arvore *a ;
        a = LerArvore(arq);
        fclose(arq);
        break;
    
    case 2:
        printf("\nImpressao Pre ordem: \n");
        ImprimirPreOrdem(a);
        printf("\n\nImpressao em ordem: \n");
        ImprimirOrdem(a);
        printf("\n\nImpressao pós ordem: \n");
        ImprimirPosOrdem(a);
        altura = CalcAltura(a);
        printf("\n\nImpressao em largura: \n");
        for (int nivel = 0; nivel < altura; nivel++){
            printf("Nivel %d : ", nivel);
            ImprimirLargura(a, 0, nivel);
            printf("\n"); 
        }
        break;
    case 3:
        puts("Informe o elemento que deseja saber existencia");
        scanf("%d", &valor_desejado);
        verifica = VerificaExistencia(a, valor_desejado);
        if(verifica ==1){
            printf("\nO numero existe");
        }
        else{
            printf("\nO numero nao existe");
        }
        break;
    case 4:
        puts("Informe o valor do no desejado");
        scanf("%d", &num_no);
        NivelNo(a,0,num_no);
        printf("\n"); 

        break;
    case 5:
        puts("Informe o elemento que deseja saber existencia de folhares menores");
        scanf("%d", &valor_desejado);
        NoFolhaMenor(a,valor_desejado);
        break;
    case 6:
        printf("Informe o no a ser inserido na arvore");
        scanf("%d",&novo_no);
        InserirNo(a,novo_no);
        break;
    case 7:
        printf("Informe o no a ser removido na arvore");
        scanf("%d",&apaga_no);
            ExcluirNo(a,apaga_no);
        break;
    case 8:
        LimparArvore(a);
        break;
    default:
        printf ("Valor invalido!\n");
    }
   
    }
    return 0;
}

arvore *LerArvore(FILE *arq){
    char c;
    int num;
    arvore *a;
    a = NULL;
    fscanf(arq,"%c",&c);
    fscanf(arq,"%d",&num);

    if(num==-1){
        fscanf(arq,"%c",&c);
        return NULL;
    }

    else{
        a = (arvore*)malloc(sizeof(arvore));
        a->info= num;
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq,"%c",&c);
        

        return a;

    }
}



arvore *RotacionarEsquerda(arvore *a){
    int altura_esquerda = CalcAltura(a->esq);
    int altura_direita = CalcAltura(a->dir);
    if (fabs(altura_esquerda - altura_direita) > 1)
    {
    arvore *b = a->dir;
    altura_esquerda = CalcAltura(b->esq);
    altura_direita = CalcAltura(b->dir);
        if (altura_esquerda > altura_direita)
        a = RotacionarEsquerdaDupla(a);
        else
        a = RotacionarEsquerdaSimples(a);
        }
    return a;
}

arvore *RotacionarEsquerdaSimples(arvore *a){
    arvore *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    return b;
}
arvore *RotacionarEsquerdaDupla(arvore *a){
    a->dir = RotacionarDireitaSimples(a->dir);
    a = RotacaoEsqSimples(a);
    return a;
}

arvore *RotacaoDir(arvore *a){
    int altura_esquerda = CalcAltura(a->esq);
    int altura_direita = CalcAltura(a->dir);
    if (fabs(altura_direita - altura_esquerda) > 1){
        arvore *b = a->esq;
        altura_esquerda = CalcAltura(a->esq);
        altura_direita = CalcAltura(a->dir);
        if (altura_direita > altura_esquerda)
        a = RotacionarDireitaDupla(a);
        else
        a = RotacionarDireitaSimples(a);
    }
    return a;
}
arvore *RotacionarDireitaSimples(arvore  *a){
    arvore *b = p->esq;
    p->esq = b->dir;
    b->dir = a;
    return b;
}
arvore *RotacionarDireitaDupla(arvore *a)
{
    a->esq = RotacionarEsquerdaSimples(a->esq);
    a = RotacionarDireitaSimples(a);
    return a;
}




void ImprimirPreOrdem(arvore *a){
     if(a!=NULL){
         printf("%d ",a->info);
         ImprimirPreOrdem(a->esq);
         ImprimirPreOrdem(a->dir);
     }
 }
void ImprimirOrdem(arvore *a){
     if(a!=NULL){
        ImprimirPreOrdem(a->esq);
        printf("%d ",a->info);
        ImprimirPreOrdem(a->dir);
     }
 }

 void ImprimirPosOrdem(arvore *a){
     if(a!=NULL){
        ImprimirPreOrdem(a->esq);
        ImprimirPreOrdem(a->dir);
        printf("%d ",a->info);

     }
 }
 void ImprimirLargura(arvore *a, int aux, int nivel){

     if(a!=NULL){
    if (aux == nivel)
      printf("%d ", a -> info);
    else{
      ImprimirLargura(a -> esq, aux + 1, nivel);
      ImprimirLargura(a -> dir, aux + 1, nivel);}
  }
}
    

int CalcAltura (arvore *a){
	int altura_direita = 0, altura_esquerda = 0;

	if(a == NULL){
        return 0;
    }
	else{
		altura_esquerda = CalcAltura(a->esq);
		altura_direita = CalcAltura(a->dir);
		
    if (altura_esquerda>altura_direita){
        return altura_esquerda + 1;
    }
		else{
            return altura_direita + 1;     
        } 
	}
}

int VerificaExistencia(arvore *a, int valor_desejado){
    if (a != NULL){

        if(valor_desejado>a->info){

        VerificaExistencia(a->dir,valor_desejado);
    }
        else if(valor_desejado<a->info){
            VerificaExistencia(a->esq,valor_desejado);
        }
        else if(valor_desejado == a->info){
            return 1;
        }
    }
    else{

       return 0;
    }
}

void NivelNo(arvore *a, int aux, int num_no){
     if(a!=NULL){
        if(num_no> a->info){
           NivelNo(a->dir, aux+1, num_no);
        }
        else if (num_no< a->info){
           NivelNo(a->esq, aux+1, num_no);
        }
        else if(num_no== a->info){
            printf("O %d no se encontra no %d° nivel",num_no, aux);
        }
}
}

void NoFolhaMenor(arvore *a, int valor_desejado){
    int folha;
    if(a != NULL){
        if(a->info>valor_desejado){
            NoFolhaMenor(a->esq,valor_desejado);

        }
        else{

            if (a->esq == NULL && a->dir == NULL){
                printf("%d ", a->info);
            }
            NoFolhaMenor(a->esq,valor_desejado);
            NoFolhaMenor(a->dir,valor_desejado);

        }
    }
}

void LimparArvore(arvore *a){
    if(a!=NULL){
        LimparArvore(a->esq);
        LimparArvore(a->dir);
        free(a);
     }
}
void *InserirNo(arvore *a,int x){
    if(a==NULL){
        a = (arvore*) malloc(sizeof (arvore));
        a->info = x;
        a->dir= NULL;
        a->esq= NULL;
    }
    else if (x <= a->info){
        a->esq = InserirNo(a->esq,x);
    }
    else{
        a->dir = InserirNo(a->dir,x);
    }
    return a;
}
arvore *ExcluirNo(arvore *a,int x){
    if(a !=NULL){
        if(a->info==x){
            if(a->esq==NULL && a->dir==NULL){
                free(a);
                return NULL;
            }
            else if(a->esq==NULL){
                arvore *aux=a->dir;
                free(a);
                return aux;
            }
            else if(a->dir==NULL){
                arvore *aux=a->esq;
                free(a);
                return aux;
            }
            else{
                arvore *aux =a->esq;
                while(aux->dir!=NULL){
                    aux = aux->dir;
                }
                a->info=aux->info;
                a->esq = ExcluirNo(a->esq,aux->info);
            }
        }
        else if(x<a->info){
            a->esq = ExcluirNo(a->esq,x);
        }
        else {
            a->dir = ExcluirNo(a->dir,x);
        }
    }
    return a;
}