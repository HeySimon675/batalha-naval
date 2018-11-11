void Espiao (char m[20][20], int n, char id) {
    extern int POS;
    int largura ,altura;
    int  i, erro = 0;
    for (i = 0; i < n; i++) {
        largura = 4;
        altura = 3;
        erro = 0;
        POS = rand() % 4; //guarda a posição na variavel externa
        if (POS%2)
            Posicao(&largura,&altura);
        while (!erro) {
            erro = Posicionadora(m, largura, altura, id);
        }
    }
}