#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

#define tamanho 10

struct pilha{
        int topo ;
        int item [tamanho] ;
};

typedef struct pilha Pilha;

int  inicializa (Pilha *p)
{
  (*p).topo = -1 ;
  return 0;
}

int estado(Pilha p)
{
    if(p.topo == -1 )
       return 0;  // Vazio
    else {
       if (p.topo == tamanho-1 )
          return 1;   // Cheio
       else
          return 2;  // Vazio e com espaço
    }
}

int push(Pilha *p, int x)
{

    int erro = estado (*p);
    if ((erro == 0) || (erro == 2))
    {
       (*p).topo++;
       (*p).item[(*p).topo]=x; // Empilhada
       return 0;
    }
    else
       return 1; // Impossível empilhar
}

int pop(Pilha *p)
{
    int erro = estado (*p);
    if (erro != 0)
    {
      (*p).topo--;  // Desempilhada
       return 0;
    }
    else
       return 1; // Impossível desempilhar
}


int obter_topo(Pilha p, int *dado)
{  int i;
    if(p.topo == -1 )
       return 1;   /* pilha vazia */
    else {
       *dado =  p.item[p.topo];
       return 0;
    }
}


int junta_pilhas (Pilha *P1, Pilha *P2, Pilha *P3)
{
    int dado;
    Pilha paux, paux2;

    inicializa (&paux);
    inicializa (&paux2);

    // Invertendo 'P2' e inserindo em 'paux2'
    while (estado(*P2)!=0) {
      obter_topo (*P2, &dado);
      pop (P2);
      push (&paux2, dado);
    }

    // Invertendo 'P1' e inserindo em 'paux'
    while (estado(*P1)!=0) {
      obter_topo (*P1, &dado);
      pop (P1);
      push (&paux, dado);
    }

    // Invertendo 'paux2' e inserindo em 'P3'
    while (estado(paux2)!=0) {
      obter_topo (paux2, &dado);
      pop (&paux2);
      push (P3, dado);
    }

    // Invertendo 'paux' e inserindo em 'P3'
    while (estado(paux)!=0) {
      obter_topo (paux, &dado);
      pop (&paux);
      push (P3, dado);
    }

    return (0);
}

int main(void)
{
    setlocale(LC_ALL, "portuguese");

	int tamanho_frase, i, letra, mudar_pilha = 0,
        tam_1, tam_2;
	Pilha p1, aux, aux2;

	inicializa (&p1);
	inicializa (&aux);
	inicializa (&aux2);

    //desempilha(&p1);
	//estado(p1);
	//transfere(s, &s2);

	printf("Digite o tamanho da frase (contando os espaços): ");
    scanf("%d%*c", &tamanho_frase);
    char frase_digitada[tamanho_frase];

    printf("\nDigite a frase: ");
    fgets(frase_digitada, tamanho_frase+1, stdin);

    printf("\nFrase digitada e inserida na Pilha:\n");
    for (i = 0; i < strlen(frase_digitada); i++) {
        push(&p1, frase_digitada[i]);
        obter_topo(p1, &letra);

        // Controle da variável 'mudar_pilha'
        if (frase_digitada[i] == ' ') {
             mudar_pilha = 1;
        }

        // Caso a variável mude, os caracteres passam a ser armazenados na 'aux' ao invés da 'aux2'
        if (mudar_pilha) {
            push(&aux, letra);
            tam_1++;
        } else {
            push(&aux2, letra);
            tam_2++;
        }
        pop(&p1);

        printf("%c", letra);
    }
    push(&aux, ' ');
    printf("\n\n");

    // Função para juntar pilhas
    junta_pilhas (&aux2, &aux, &p1);

    printf("Pilha invertida (apenas as letras): \n");
    for (i = 0; i <= strlen(frase_digitada); i++) {
        obter_topo(p1, &letra);
        printf("%c", letra);
        pop(&p1);
    }
    printf("\n\n");

    return 0;
}
