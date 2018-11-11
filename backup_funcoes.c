void Submarino(char m[20][20], int n, char id) {
    int pos, i, erro = 0;
    int largura = 4;
    int altura = 1;
    for (i = 0; i < n; i++) {
        erro=0;
        pos = rand() % 2;
        if (pos)
            Posicao(&largura,&altura);
        while (!erro) {
            erro = Posicionadora(m, largura, altura, id);
        }
    }
}


void Porta_Avioes(char m[20][20], int n) {
    int pos, i, erro = 0;
    char id = '5';
    int largura = 5;
    int altura = 2;
    for (i = 0; i < n; i++) {

        erro=0;
        pos = rand() % 2;
        if (pos)
            Posicao(&largura,&altura);
        while (!erro) {     //Continua até conseguir posicionar a embarcação
            erro = Posicionadora(m, largura, altura, id);
        }
    }
}

void Aviao (char m[20][20], int n,char id){
    extern int POS;
    int largura ,altura;
    int  i, erro = 0;
    for (i = 0; i < n; i++) {
        largura = 2;
        altura = 3;
        erro = 0;
        POS = rand() % 2;    //guarda a posição da figura em uma variavel externa
        if (POS)
            Posicao(&largura,&altura);
        while (!erro) {
            erro = Posicionadora(m, largura, altura, id);
        }
    }
}
void Coloca_Aviao (char m[20][20], int i_inicial,int j_inicial,int i_final,int j_final){
    extern int POS;
    int i,j;
    char id='1';
    if (POS){
        i=i_inicial;
        m[i_inicial+1][j_inicial+1]=id;
        for (j = j_inicial; j < j_final; j++)
            m[i][j] = id;   //coloca a "cauda" do avião
    }
    else{
        j=j_inicial+1;
        for (i = i_inicial; i < i_final; i++)
            m[i][j] = id;
        m[i_inicial+1][j_inicial]=id;
    }
}