//
// Created by root on 21/11/18.
//
#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#define TAMANHO 20

Game* NovoGame(char* tab1,char* tab2){
    //ESSA FUNÇÃO IRA CHAMAR A FUNÇÃO CRIA TABULEIRO DUAS VEZES, O PROCESSO SERA DA SEGUINTE FORMA
    //A FUNÇÃO GeraTabuleiro SERA CHAMADA DUAS VEZES, COM tab1 e tab2
    //IRA RETORNAR UM ARQUIVO TXT COM AS INFORMAÇÕES SOBRE O TABULEIRO, O ENDEREÇO DESSE ARQUIVO SERÁ PASSADO
    //PARA A FUNÇÃO CRIA TABULEIRO, QUE VAI LER ESSES ARQUIVOS E COLOCAR AS EMBARCAÇÕES NA MATRIZ DE CELULAS

    Game* game_atual = (Game*) malloc (sizeof(Game));
    game_atual->Player  = CadastraJogador(0,tab1);
    game_atual->Maquina = CadastraJogador(1,tab2);
    game_atual->fim_de_jogo=0;
    game_atual->ia=IniciaIA();


}


int coovalida( int* i, char* cow) {// repete até entrar com uma coordenada valida
    int j = (*cow) - 'A';
    if ((*i) > 19 || j > 19) {
        printf("coordenada invalida tente novamente\n");
        return (1);
    }
}

int TiroDeJogador(Game* Ojogo) {
    int i, j;
    int tipo, n;
    char coluna;
    int loop;
    system("clear");
    PrintaTabuleiro(Ojogo->Maquina->tab->matriz_campo, TAMANHO);
    printf("Digite coordenadas na forma \"x y\" com X sendo linha e Y coluna, digite a letra em maiusculo\n");
    scanf("%d %c", &i, &coluna);
    j = coluna - 'A';
    if (coovalida(&i, &coluna)) {
        loop = TiroDeJogador(Ojogo);
    } else {
        if (!Ojogo->Maquina->tab->matriz_campo[i][j].visivel) { // celula nao foi acertada ainda
            Ojogo->Maquina->tab->matriz_campo[i][j].visivel = 1;
            //se o valor da posição for # foi tiro na agua
            if (Ojogo->Maquina->tab->matriz_campo[i][j].valor != '#') {
                n = Ojogo->Maquina->tab->matriz_campo[i][j].id - '0';
                tipo = Ojogo->Maquina->tab->matriz_campo[i][j].valor - '0';
                Ojogo->Maquina->tab->barcos[tipo].barcos[n] -= 1;
                if (!Ojogo->Maquina->tab->barcos[tipo].barcos[n]) {
                    printf("afundou\n");
                    Ojogo->Maquina->frota_total--;
                    if (!Ojogo->Maquina->frota_total) {
                        Ojogo->Player->vencedor = 1;
                        Ojogo->fim_de_jogo = 1;
                    }
                    //Todas as posições do barco ja foram acertadas, assim, frotaTotal--
                    //talvez seja uma boa printar o que o barco foi afundado
                }
            } else {
                printf("tiro na agua\n");
            }

            //senao é verificado qual tipo de barco foi acertado, usando seu id faz o acesso ao tad Barcos, e usando o contador na celular acessa o barco em questão,
            // então barcos[tipo]->[id] -= 1
            return (0); //tiro efetuado
        } else {
            printf("Posição ja marcada, tente outro valor\n");
            TiroDeJogador(Ojogo);
        }
    }
}

int TiroAleatorio (Game* Ojogo){
    int row, cow, numerador,id;
    row = rand()%20;
    cow = rand()%11;
    cow += rand()%9;
    if(Ojogo->Player->tab->matriz_campo[row][cow].visivel){
        return (TiroAleatorio(Ojogo));
    }
    else{   //caso a posição ainda nao tenha sido acertada
        if(Ojogo->Player->tab->matriz_campo[row][cow].valor=='0'){ //caso acerte uma bomba
            Ojogo->Player->tab->matriz_campo[row][cow].visivel=1;
            numerador= Ojogo->Player->tab->matriz_campo[row][cow].id - '0'; //numerador do tipo
            Ojogo->Player->tab->barcos[0].barcos[numerador]=0;  //zera o contador de casas disponiveis da bomba
            Ojogo->Player->frota_total--;   //diminui a frota total;
            printf("Atingiu uma bomba\n");
        }else {
            id = Ojogo->Player->tab->matriz_campo[row][cow].valor - '0';
            switch (id){        // O NOVO ALVO É UMA EMBARCAÇÃO COM ID != 0
                case 1:

                    break;
                case 2:

                    break;
                case 3:

                    break;
                case 4:

                    break;
                case 5:

                    break;
            }
        }
    }


}

int TiroIA(Game* Ojogo){
    int alvo_atual;
    int row, cow, inicial_sentido, loop;
    if(Ojogo->ia->n_alvos){ //caso algum alvo ja tenha sido acertado
        alvo_atual=Ojogo->ia->n_alvos-1; // recebe o indice do ultimo alvo descoberto
        inicial_sentido=Ojogo->ia->alvo[alvo_atual]->inicial;
            switch (Ojogo->ia->alvo[alvo_atual]->id){ //estrategia padrão caso a posição inicial seja acertada

                //VERIFICIA SE A POSIÇÃO INICIAL FOI ACERTADA E QUAL FOI O SENTIDO, ENTAO EXECUTA A ESTRATEGIA PADRAO
                //SE A POSIÇÃO INICIAL FOR ENCONTRADA NA ESTRATEGIA CRUZ ELA SUBSTITUI A COORDENADA NO TAD ALVOS
                case '1':   //AVIAO

                    if(inicial_sentido){
                        //FUNÇÃO QUE ATIRA SEGUINDO A ESTRATEGIA PADRAO
                    }
                    else{
                        //estrategia de cruz
                    }
                    break;
                case '2': //SUBMARINO, DESATIVADO POIS SUBMARINO NAO ESTA NA MATRIZ
                    if(inicial_sentido){
                        //FUNÇÃO QUE ATIRA SEGUINDO A ESTRATEGIA PADRAO
                    }else{
                        //estrategia cruz
                    }
                break;
                case '3':   //ESPIAO

                    if(inicial_sentido){
                        //FUNÇÃO QUE ATIRA SEGUINDO A ESTRATEGIA PADRAO
                    }
                    else{
                    //estrategia cruz
                    }
                    break;
                case '4': //ESPIAO, codigo vai ser o mesmo que pra '3'

                    if(inicial_sentido){
                        //FUNÇÃO QUE ATIRA SEGUINDO A ESTRATEGIA PADRAO
                    }
                    else{
                        //estrategia cruz
                    }
                    break;
                case '5':   //  PORTA AVIOES, DESATIVADO

                    if(inicial_sentido){
                        //FUNÇÃO QUE ATIRA SEGUINDO A ESTRATEGIA PADRAO
                    }
                    else{
                        //estrategia cruz
                    }
                    break;
            }

        }
        else{   //CASO NA TENHAM ALVOS
            loop = TiroAleatorio(Ojogo);
        }
    return (0);
}

void AtirarPlayer(Game* Ojogo,int id) {
    if (!id) {
        if(!TiroDeJogador(Ojogo)){
           printf("\n Vez da maquina \n");
        }
    } else {
        srand(time(NULL));
        if(!TiroIA(Ojogo)){
            printf("\n Vez da maquina \n");

        }
    }
}

void DestroiGame(Game* game){

}