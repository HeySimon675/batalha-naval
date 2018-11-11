void Submarino(char m[20][20], int n, char id) {
    extern int POS;
    int  i, erro = 0;
    int largura = 4;
    int altura = 1;
    for (i = 0; i < n; i++) {
        erro=0;
        POS = rand() % 4;
        if (POS%2)
            Posicao(&largura,&altura);
        while (!erro) {
            erro = Posicionadora(m, largura, altura, id);
        }
    }
}