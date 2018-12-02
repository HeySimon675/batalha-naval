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
        if(Ojogo->Player->tab->matriz_campo[row][cow].valor=='#'){  //ACERTOU NA AGUA
            Ojogo->Player->tab->matriz_campo[row][cow].visivel=1;
            printf("tiro na agua\n");
            return(1);
        }
        else if(Ojogo->Player->tab->matriz_campo[row][cow].valor=='0'){ //caso acerte uma bomba
            Ojogo->Player->tab->matriz_campo[row][cow].visivel=1; //POSIÇÃO VISIVEL
            numerador= Ojogo->Player->tab->matriz_campo[row][cow].id - '0'; //numerador do tipo
            Ojogo->Player->tab->barcos[0].barcos[numerador]=0;  //zera o contador de casas disponiveis da bomba
            Ojogo->Player->frota_total--;   //diminui a frota total;
            printf("Atingiu uma bomba\n");
            return (1);
        }else {
            id = Ojogo->Player->tab->matriz_campo[row][cow].valor - '0';
            Ojogo->Player->tab->matriz_campo[row][cow].visivel=1;//POSICAO VISIVEL
            numerador= Ojogo->Player->tab->matriz_campo[row][cow].id - '0'; //numerador do tipo
            Ojogo->Player->tab->barcos[id].barcos[numerador]--;  //subtrai uma casa do contador barcos
            Ojogo->ia->n_alvos++;   //novo alvo adicionado
            //preechimento do novo alvo, o novo alvo recebe o id do barco
            Ojogo->ia->alvo[Ojogo->ia->n_alvos-1]->id= Ojogo->Player->tab->matriz_campo[row][cow].valor;
            Ojogo->ia->alvo[Ojogo->ia->n_alvos-1]->inicial = Ojogo->Player->tab->matriz_campo[row][cow].inicial;
            Ojogo->ia->alvo[Ojogo->ia->n_alvos-1]->row = row;
            Ojogo->ia->alvo[Ojogo->ia->n_alvos-1]->cow = cow;
            Ojogo->ia->alvo[Ojogo->ia->n_alvos-1]->n = numerador;
            return (1);
        }
    }
}

int TiroIA(Game* Ojogo){
    int alvo_atual,i=0;
    int row, cow, inicial_sentido, loop;
    char id;
    int num ;
    if(Ojogo->ia->n_alvos) { //caso algum alvo ja tenha sido acertado
        alvo_atual = Ojogo->ia->n_alvos - 1; // recebe o indice do ultimo alvo descoberto
        inicial_sentido = Ojogo->ia->alvo[alvo_atual]->inicial;
        //coleta linha e coluna do alvo
        row = Ojogo->ia->alvo[alvo_atual]->row;
        cow = Ojogo->ia->alvo[alvo_atual]->cow;
        id = Ojogo->ia->alvo[alvo_atual]->id;
        num = Ojogo->ia->alvo[alvo_atual]->n;

        if (!inicial_sentido) {
            //estrategia de cruz
            if (cow > 0) {//POSIÇÃO A ESQUERDA
                if (!Ojogo->Player->tab->matriz_campo[row][cow - 1].visivel) {  //posição oculta
                    if (Ojogo->Player->tab->matriz_campo[row][cow - 1].valor != '#') { //caso nao seja agua
                            Ojogo->ia->alvo[alvo_atual]->cow--; //muda a posição do alvo
                            //recebe as coordenadas da posição inicial e o sentido do barco
                            Ojogo->ia->alvo[alvo_atual]->inicial = Ojogo->Player->tab->matriz_campo[row][cow -1].inicial;
                            Ojogo->Player->tab->matriz_campo[row][cow - 1].visivel = 1; //posição fica visivel
                            Ojogo->Player->tab->barcos[id].barcos[num]--;   //diminui em 1 o numero de posiçoes ativas do barco
                            if(!Ojogo->Player->tab->barcos[id].barcos[num]){
                                Ojogo->Player->frota_total--;
                            }
                            return (0);

                    }else{
                        Ojogo->Player->tab->matriz_campo[row][cow - 1].visivel = 1;
                        return (0);
                    }

                }
            } else if (cow < 20) {
                //testa com cow+1
                if (!Ojogo->Player->tab->matriz_campo[row][cow + 1].visivel) {  //posição oculta
                    if (Ojogo->Player->tab->matriz_campo[row][cow + 1].valor != '#') { //caso nao seja agua
                            Ojogo->ia->alvo[alvo_atual]->cow++; //muda a posição do alvo
                            //recebe as coordenadas da posição inicial e o sentido do barco
                            Ojogo->ia->alvo[alvo_atual]->inicial = Ojogo->Player->tab->matriz_campo[row][cow + 1].inicial;
                            Ojogo->Player->tab->matriz_campo[row][cow + 1].visivel = 1; //posição fica visivel
                            Ojogo->Player->tab->barcos[id].barcos[num]--;   //diminui em 1 o numero de posiçoes ativas do barco
                            if(!Ojogo->Player->tab->barcos[id].barcos[num]){
                                Ojogo->Player->frota_total--;
                            }
                        return (0);
                    }else{
                        Ojogo->Player->tab->matriz_campo[row][cow + 1].visivel = 1; //posição fica visivel
                        return (0);
                    }
                }
            } else if (row > 0) {
                //testa com row-1
                if (!Ojogo->Player->tab->matriz_campo[row - 1][cow].visivel) {  //posição oculta
                    if (Ojogo->Player->tab->matriz_campo[row - 1][cow].valor != '#') { //caso nao seja agua

                            Ojogo->ia->alvo[alvo_atual]->row--; //muda a posição do alvo
                            //recebe as coordenadas da posição inicial e o sentido do barco
                            Ojogo->ia->alvo[alvo_atual]->inicial = Ojogo->Player->tab->matriz_campo[row -
                                                                                                    1][cow].inicial;
                            Ojogo->Player->tab->matriz_campo[row - 1][cow].visivel = 1; //posição fica visivel
                            Ojogo->Player->tab->barcos[id].barcos[num]--;   //diminui em 1 o numero de posiçoes ativas do barco
                        if(!Ojogo->Player->tab->barcos[id].barcos[num]){
                            Ojogo->Player->frota_total--;
                        }
                        return (0);
                    }else{
                        Ojogo->Player->tab->matriz_campo[row - 1][cow].visivel = 1; //posição fica visivel
                        return (0);
                    }
                }
            } else if (row < 20) {
                //testa com row+1
                if (!Ojogo->Player->tab->matriz_campo[row + 1][cow].visivel) {  //posição oculta
                    if (Ojogo->Player->tab->matriz_campo[row + 1][cow].valor != '#') { //caso nao seja agua
                            Ojogo->ia->alvo[alvo_atual]->cow++; //muda a posição do alvo
                            //recebe as coordenadas da posição inicial e o sentido do barco
                            Ojogo->ia->alvo[alvo_atual]->inicial = Ojogo->Player->tab->matriz_campo[row + 1][cow].inicial;
                            Ojogo->Player->tab->matriz_campo[row + 1][cow].visivel = 1; //posição fica visivel
                            Ojogo->Player->tab->barcos[id].barcos[num]--;   //diminui em 1 o numero de posiçoes ativas do barco
                        if(!Ojogo->Player->tab->barcos[id].barcos[num]){
                            Ojogo->Player->frota_total--;
                        }
                        return (0);
                    }else{
                        Ojogo->Player->tab->matriz_campo[row + 1][cow].visivel = 1; //posição fica visivel
                        return (0);

                    }
                }
            }
        } else {
            switch (id) { //estrategia padrão caso a posição inicial esteja no alvo

                //A POSIÇÃO INICIAL FOI ACERTADA CONFORME O SENTIDO, ENTAO EXECUTA A ESTRATEGIA PADRAO
                case '1':   //AVIAO
                    switch (inicial_sentido){
                        case 1: //NORTE
                            if(!Ojogo->Player->tab->matriz_campo[row][cow-1].visivel){//tenta cow-1
                                if(Ojogo->Player->tab->matriz_campo[row][cow-1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow-1].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row][cow+1].visivel){ //tenta cow+1
                                if(Ojogo->Player->tab->matriz_campo[row][cow+1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow+1].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else{  // row-1
                                if(Ojogo->Player->tab->matriz_campo[row-1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row-1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }
                            break;
                        case 2: //SUL
                            if(!Ojogo->Player->tab->matriz_campo[row][cow-1].visivel){//tenta cow-1
                                if(Ojogo->Player->tab->matriz_campo[row][cow-1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow-1].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row][cow+1].visivel){ //tenta cow+1
                                if(Ojogo->Player->tab->matriz_campo[row][cow+1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow+1].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else{  // row+1
                                if(Ojogo->Player->tab->matriz_campo[row+1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row+1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }
                            break;
                        case 3:     //LESTE
                            if(!Ojogo->Player->tab->matriz_campo[row-1][cow].visivel){//tenta row-1
                                if(Ojogo->Player->tab->matriz_campo[row-1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row-1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row+1][cow].visivel){ //tenta row+1
                                if(Ojogo->Player->tab->matriz_campo[row+1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row+1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else{  // cow-1
                                if(Ojogo->Player->tab->matriz_campo[row][cow-1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow-1].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }

                            break;
                        case 4: //OESTE
                            if(!Ojogo->Player->tab->matriz_campo[row-1][cow].visivel){//tenta row-1
                                if(Ojogo->Player->tab->matriz_campo[row-1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row-1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){

                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row+1][cow].visivel){ //tenta row+1
                                if(Ojogo->Player->tab->matriz_campo[row+1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row+1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else{  // cow+1
                                if(Ojogo->Player->tab->matriz_campo[row][cow+1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow+1].visivel=1;
                                    Ojogo->Player->tab->barcos[1].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[1].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }
                            break;
                    }


                    break;
                case '2': //SUBMARINO, DESATIVADO POIS SUBMARINO NAO ESTA NA MATRIZ
                    switch (inicial_sentido){
                        case 1:
                            for(i=0;i<4;i++){   //percorre verticalmente o paviao
                                if(!Ojogo->Player->tab->matriz_campo[row+i][cow].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row+i][cow].id==num){
                                        Ojogo->Player->tab->matriz_campo[row+i][cow].visivel=1;
                                        Ojogo->Player->tab->barcos[4].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[4].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou submarino\n");
                                        return (0); // acertou a posição
                                    }
                                }
                            }
                            break;

                        case 2:
                            for(i=0;i<4;i++){   //percorre verticalmente o paviao
                                if(!Ojogo->Player->tab->matriz_campo[row-i][cow].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row-i][cow].id==num){
                                        Ojogo->Player->tab->matriz_campo[row-i][cow].visivel=1;
                                        Ojogo->Player->tab->barcos[4].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[4].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou submarino\n");
                                        return (0); // acertou a posição
                                    }
                                }
                            }
                            break;

                        case 3:
                            for(i=0;i<4;i++){   //percorre verticalmente o paviao
                                if(!Ojogo->Player->tab->matriz_campo[row][cow+i].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row][cow+i].id==num){
                                        Ojogo->Player->tab->matriz_campo[row][cow+i].visivel=1;
                                        Ojogo->Player->tab->barcos[4].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[4].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou submarino\n");
                                        return (0); // acertou a posição
                                    }
                                }
                            }
                            break;

                        case 4:
                            for(i=0;i<4;i++){   //percorre verticalmente o paviao
                                if(!Ojogo->Player->tab->matriz_campo[row][cow-i].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row][cow-i].id==num){
                                        Ojogo->Player->tab->matriz_campo[row][cow-i].visivel=1;
                                        Ojogo->Player->tab->barcos[4].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[4].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou submarino\n");
                                        return (0); // acertou a posição
                                    }
                                }
                            }
                            break;
                    }
                    break;
                case '3':   //ESPIAO
                case '4': //ESPIAO, codigo vai ser o mesmo que pra '3'
                    switch (inicial_sentido){
                        case 2: //SUL
                            if(!Ojogo->Player->tab->matriz_campo[row][cow-1].visivel){//tenta cow-1
                                if(Ojogo->Player->tab->matriz_campo[row][cow-1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow-1].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row][cow+1].visivel){ //tenta cow+1
                                if(Ojogo->Player->tab->matriz_campo[row][cow+1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow+1].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row-1][cow].visivel){  // row-1
                                if(Ojogo->Player->tab->matriz_campo[row-1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row-1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;

                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }else if(!Ojogo->Player->tab->matriz_campo[row-2][cow].visivel){  // row-2
                                if(Ojogo->Player->tab->matriz_campo[row-2][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row-2][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }else {  // row-3
                                if(Ojogo->Player->tab->matriz_campo[row-3][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row-3][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }
                            break;



                        case 1: //NORTE
                            if(!Ojogo->Player->tab->matriz_campo[row][cow-1].visivel){//tenta cow-1
                                if(Ojogo->Player->tab->matriz_campo[row][cow-1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow-1].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row][cow+1].visivel){ //tenta cow+1
                                if(Ojogo->Player->tab->matriz_campo[row][cow+1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow+1].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row+1][cow].visivel){  // row+1
                                if(Ojogo->Player->tab->matriz_campo[row+1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row+1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }else if(!Ojogo->Player->tab->matriz_campo[row+2][cow].visivel){  // row+2
                                if(Ojogo->Player->tab->matriz_campo[row+2][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row+2][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }else {  // row+3
                                if(Ojogo->Player->tab->matriz_campo[row+3][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row+3][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }
                            break;



                        case 4:     //OESTE
                            if(!Ojogo->Player->tab->matriz_campo[row-1][cow].visivel){//tenta row-1
                                if(Ojogo->Player->tab->matriz_campo[row-1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row-1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row+1][cow].visivel){ //tenta row+1
                                if(Ojogo->Player->tab->matriz_campo[row+1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row+1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row][cow-1].visivel){  // cow-1
                                if(Ojogo->Player->tab->matriz_campo[row][cow-1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow-1].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }else if(!Ojogo->Player->tab->matriz_campo[row][cow-2].visivel){  // cow-2
                                if(Ojogo->Player->tab->matriz_campo[row][cow-2].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow-2].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }else {  // cow-3
                                if(Ojogo->Player->tab->matriz_campo[row][cow-3].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow-3].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }
                            break;


                        case 3: //LESTE
                            if(!Ojogo->Player->tab->matriz_campo[row-1][cow].visivel){//tenta row-1
                                if(Ojogo->Player->tab->matriz_campo[row-1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row-1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row+1][cow].visivel){ //tenta row+1
                                if(Ojogo->Player->tab->matriz_campo[row+1][cow].id==num){
                                    Ojogo->Player->tab->matriz_campo[row+1][cow].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }

                            }else if(!Ojogo->Player->tab->matriz_campo[row][cow+1].visivel){  // cow+1
                                if(Ojogo->Player->tab->matriz_campo[row][cow+1].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow+1].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;

                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }else if(!Ojogo->Player->tab->matriz_campo[row][cow+2].visivel){  // cow+2
                                if(Ojogo->Player->tab->matriz_campo[row][cow+2].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow+2].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }else {  // cow+3
                                if(Ojogo->Player->tab->matriz_campo[row][cow+3].id==num){
                                    Ojogo->Player->tab->matriz_campo[row][cow+3].visivel=1;
                                    Ojogo->Player->tab->barcos[id-'0'].barcos[num]--;
                                    if(!Ojogo->Player->tab->barcos[id-'0'].barcos[num]){
                                        Ojogo->Player->frota_total--;
                                        Ojogo->ia->n_alvos--;
                                    }
                                    printf("Acertou aviao\n");
                                    return (0); // acertou a posição
                                }else{
                                    //NOVO ALVO
                                }
                            }
                            break;
                    }


                    break;
                case '5':   //  PORTA AVIOES, DESATIVADO
                    switch (inicial_sentido){
                        case 1 :
                            for(i=0;i<5;i++){   //percorre verticalmente o paviao
                                if(!Ojogo->Player->tab->matriz_campo[row+i][cow+1].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row+i][cow+1].id==num){
                                        Ojogo->Player->tab->matriz_campo[row+i][cow+1].visivel=1;
                                        Ojogo->Player->tab->barcos[5].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[5].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou aviao\n");
                                        return (0); // acertou a posição
                                    }else{
                                        //NOVO ALVO
                                    }
                                }else if(!Ojogo->Player->tab->matriz_campo[row+i][cow].visivel){
                                        if(Ojogo->Player->tab->matriz_campo[row+i][cow].id==num){
                                            Ojogo->Player->tab->matriz_campo[row+i][cow].visivel=1;
                                            Ojogo->Player->tab->barcos[5].barcos[num]--;
                                            if(!Ojogo->Player->tab->barcos[5].barcos[num]){
                                                Ojogo->Player->frota_total--;
                                                Ojogo->ia->n_alvos--;
                                            }
                                            printf("Acertou aviao\n");
                                            return (0); // acertou a posição
                                        }else{
                                            //NOVO ALVO
                                        }
                                }
                            }
                            break;
                        case 2:
                            for(i=0;i<5;i++){   //percorre verticalmente o paviao
                                if(!Ojogo->Player->tab->matriz_campo[row-i][cow+1].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row-i][cow+1].id==num){
                                        Ojogo->Player->tab->matriz_campo[row-i][cow+1].visivel=1;
                                        Ojogo->Player->tab->barcos[5].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[5].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou aviao\n");
                                        return (0); // acertou a posição
                                    }else{
                                        //NOVO ALVO
                                    }
                                }else if(!Ojogo->Player->tab->matriz_campo[row-i][cow].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row-i][cow].id==num){
                                        Ojogo->Player->tab->matriz_campo[row-i][cow].visivel=1;
                                        Ojogo->Player->tab->barcos[5].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[5].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou aviao\n");
                                        return (0); // acertou a posição
                                    }else{
                                        //NOVO ALVO
                                    }
                                }
                            }
                            break;
                        case 3:
                            for(i=0;i<5;i++){   //percorre verticalmente o paviao
                                if(!Ojogo->Player->tab->matriz_campo[row+1][cow+i].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row+1][cow+i].id==num){
                                        Ojogo->Player->tab->matriz_campo[row+1][cow+i].visivel=1;
                                        Ojogo->Player->tab->barcos[5].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[5].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou aviao\n");
                                        return (0); // acertou a posição
                                    }else{
                                        //NOVO ALVO
                                    }
                                }else if(!Ojogo->Player->tab->matriz_campo[row][cow+i].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row][cow+i].id==num){
                                        Ojogo->Player->tab->matriz_campo[row][cow+i].visivel=1;
                                        Ojogo->Player->tab->barcos[5].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[5].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou aviao\n");
                                        return (0); // acertou a posição
                                    }else{
                                        //NOVO ALVO
                                    }
                                }
                            }
                            break;

                        case 4:
                            for(i=0;i<5;i++){   //percorre verticalmente o paviao
                                if(!Ojogo->Player->tab->matriz_campo[row+1][cow-i].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row+1][cow-i].id==num){
                                        Ojogo->Player->tab->matriz_campo[row+1][cow-i].visivel=1;
                                        Ojogo->Player->tab->barcos[5].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[5].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou aviao\n");
                                        return (0); // acertou a posição
                                    }else{
                                        //NOVO ALVO
                                    }
                                }else if(!Ojogo->Player->tab->matriz_campo[row][cow+i].visivel){
                                    if(Ojogo->Player->tab->matriz_campo[row][cow+i].id==num){
                                        Ojogo->Player->tab->matriz_campo[row][cow+i].visivel=1;
                                        Ojogo->Player->tab->barcos[5].barcos[num]--;
                                        if(!Ojogo->Player->tab->barcos[5].barcos[num]){
                                            Ojogo->Player->frota_total--;
                                            Ojogo->ia->n_alvos--;
                                        }
                                        printf("Acertou aviao\n");
                                        return (0); // acertou a posição
                                    }else{
                                        //NOVO ALVO
                                    }
                                }
                            }
                            break;
                    }
                    break;
            }

        }

    }else{   //CASO NAO TENHAM ALVOS
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