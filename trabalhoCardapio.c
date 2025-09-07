#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXI 17
#define MAXN 30
#define MAXP 50

typedef struct INGREDIENTE {
    char nome[MAXN];
}INGREDIENTE;

typedef struct PESSOA {
    char nome[MAXN];
    int alergias[MAXI];
    int NA;
    int vegetariano;
    int vegano;
    int celiaco;
    int diabetico;
    int intoleranteL;
} PESSOA;

INGREDIENTE listaingredientes[MAXI]={
    {"leite"}, {"tomate"}, {"carne de porco"}, {"amendoim"}, {"mel"},
    {"ovo"},{"queijo"},{"peixe"},{"frango"},{"batata"},{"alface"}, {"frutas"},
    {"feijao"}, {"arroz"}, {"pao"}, {"macarrao"}, {"acucar"}
};

//matriz pro grafo
int matrizadj[MAXI][MAXI];
//lista pro dfs e o tamanho
int *listaadj[MAXI];
int tam[MAXI];


void addalergia(PESSOA * pessoa, int id){
    int i;
    for(i=0;i<pessoa->NA; i++){
        if(pessoa->alergias[i] == id)
            return;
    }
    pessoa->alergias[pessoa->NA++] = id;
}

int igredienteproibido(PESSOA *grupo, int tamanho, int id){
    int i;
    for(i=0;i<tamanho;i++){
        if(grupo[i].vegano && (
            !strcmp(listaingredientes[id].nome, "leite") ||
            !strcmp(listaingredientes[id].nome, "queijo") ||
            !strcmp(listaingredientes[id].nome, "ovo") ||
            !strcmp(listaingredientes[id].nome, "peixe") ||
            !strcmp(listaingredientes[id].nome, "frango") ||
            !strcmp(listaingredientes[id].nome, "carne de porco") ||
            !strcmp(listaingredientes[id].nome, "mel")
        ))
            return 1;

        if(grupo[i].vegetariano && (
            !strcmp(listaingredientes[id].nome, "carne de porco") ||
            !strcmp(listaingredientes[id].nome, "frango") ||
            !strcmp(listaingredientes[id].nome, "peixe")
        ))
            return 1;

        if(grupo[i].celiaco && (
            !strcmp(listaingredientes[id].nome, "pao") ||
            !strcmp(listaingredientes[id].nome, "macarrao")
        ))
        return 1;
        if(grupo[i].diabetico && (
            !strcmp(listaingredientes[id].nome, "acucar") ||
            !strcmp(listaingredientes[id].nome, "mel") ||
            !strcmp(listaingredientes[id].nome, "frutas")
        ))
        return 1;
        if(grupo[i].intoleranteL && (
            !strcmp(listaingredientes[id].nome, "leite") ||
            !strcmp(listaingredientes[id].nome, "queijo") ||
            !strcmp(listaingredientes[id].nome, "pao") ||
            !strcmp(listaingredientes[id].nome, "macarrao") 
        ))
        return 1;
        int j;
        for(j=0;j<grupo[i].NA;j++){
            if(grupo[i].alergias[j] == id)
            return 1;
        }
    }
    return 0;
}

void construtor(PESSOA *grupo, int tamanho){
    int i,j;
    for(i=0;i<MAXI;i++){
        for(j=0;j<MAXI;j++){
            if(!igredienteproibido(grupo, tamanho, i) && !igredienteproibido(grupo,tamanho, j)){
                matrizadj[i][j] = matrizadj[j][i]=1;
            }
        }
    }
    for(i =0; i<MAXI; i++){
        tam[i]=0;
        listaadj[i]=malloc(MAXI * sizeof(int));
        for(j=0;j<MAXI;j++){
            if(matrizadj[i][j]){
                listaadj[i][tam[i]++]=j;
            }
        }
    }
}


void DFS( int atual, int visitado[], int combinacao[], int pos, int tamC, PESSOA *grupo, int NP){
    visitado[atual]=1;
    combinacao[pos]=atual;
    int i;
    if(pos == tamC -1){
        printf("CARDAPIO VALIDO: ");
        for(i=0;i<tamC; i++){
            printf("%s%s", listaingredientes[combinacao[i]].nome, (i<tamC -1)? ", " : "\n"); //uma condiçao se nao for o ultimo bota , se for \n
        }
        visitado[atual]=0;
        return;
    }

    for(i=0;i<tam[atual]; i++){
        int vizinho = listaadj[atual][i];
        if(!visitado[vizinho]&& !igredienteproibido(grupo, NP, vizinho))
            DFS(vizinho, visitado, combinacao, pos+1, tamC, grupo, NP);
    }
    visitado[atual] = 0;
}

int main(){
    PESSOA grupo[MAXP];
    int NPESSOA, x;

    printf("Digite o numero de pessoas: ");
    scanf("%d", &NPESSOA);
    getchar();
    int i, j, k, id=-1;
    for(i=0;i<NPESSOA;i++){
        printf("\npessoa %d:\n", i+1);
        printf("Nome: ");
        fgets(grupo[i].nome, MAXN, stdin);
        grupo[i].nome[strcspn(grupo[i].nome, "\n")] = '\0';

        grupo[i].NA =0;
        grupo[i].vegetariano = grupo[i].vegano = grupo[i].celiaco = grupo[i].diabetico = grupo[i].intoleranteL = 0;

        char resposta;

        printf("E vegetariano(a)? (s/n): ");
        scanf(" %c", &resposta);
        grupo[i].vegetariano = (resposta == 's');

        printf("E vegano(a)? (s/n): ");
        scanf(" %c", &resposta);
        grupo[i].vegano = (resposta == 's');

        printf("E celiaco(a)? (s/n): ");
        scanf(" %c", &resposta);
        grupo[i].celiaco = (resposta == 's');

        printf("E diabetico(a)? (s/n): ");
        scanf(" %c", &resposta);
        grupo[i].diabetico = (resposta == 's');

        printf("E intolerante a lactose? (s/n): ");
        scanf(" %c", &resposta);
        grupo[i].intoleranteL = (resposta == 's');

        printf("Quantas alergias? ");
        int qnt;
        scanf("%d", &qnt);
        getchar();

        for(j=0;j<qnt;j++){
            char alergia[MAXN];
            printf("Nome do ingrediente %d: ", j+1);
            fgets(alergia, MAXN, stdin);
            alergia[strcspn(alergia, "\n")]= '\0';

            for(k=0;k<MAXI;k++){
                if(!strcmp(alergia, listaingredientes[k].nome)){
                    id = k;
                    break;
                }
            }
            if(id!=-1){
                addalergia(&grupo[i], id);
            }else{
                printf("ingrediente '%s' nao encontrado.\n", alergia);
            }
        }
    }
    construtor(grupo, NPESSOA);
    printf("\n---------GERACAO DE CARDAPIO--------\n");

    int tamcardapio;
    printf("quantos ingredientes voce vai querer no cardapio: ");
    scanf("%d", &tamcardapio);
    getchar();
    for(i=0;i<MAXI;i++){
        if(!igredienteproibido(grupo, NPESSOA, i)){
            int visitado[MAXI] ={0};
            int combinacao[MAXI];
            DFS(i,visitado,combinacao,0,tamcardapio,grupo,NPESSOA);
        }
    }
    for(i =0; i<MAXI;i++){
        free(listaadj[i]);
    }
    scanf("%i", x);
    return 0;
}
