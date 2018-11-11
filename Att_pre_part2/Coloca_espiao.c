void Coloca_Espiao (char m[20][20], int i_inicial,int j_inicial,int i_final,int j_final,char id){
    extern int POS;
    int i,j;
    switch (POS){
        case 0: //horizontal direcionado para a direita
            i=i_inicial+1;
            for(j=j_inicial;j < j_final; j++){
                m[i][j]=id;
            }
            m[i_inicial][j_inicial]=id;
            m[i_inicial+2][j_inicial]=id;
            break;
        case 1: //vertical para cima
            j=j_inicial+1;
            for (i = i_inicial; i < i_final; i++) {
                m[i][j] = id;
            }
            m[i-1][j_inicial] = id;     //coloca as "turbinas" da embarcação
            m[i-1][j_inicial+2] = id;
            break;
        case 2:  //horizontal direcionado para a esquerda
            i=i_inicial+1;
            for(j=j_inicial;j < j_final; j++){
                m[i][j]=id;
            }
            m[i_inicial][j_final-1]=id;
            m[i_inicial+2][j_final-1]=id;
            break;
        case 3:     //vertical para baixo
            j=j_inicial+1;
            for (i = i_inicial; i < i_final; i++) {
                m[i][j] = id;
            }
            m[i_inicial][j_inicial] = id;     //coloca as "turbinas" da embarcação
            m[i_inicial][j_inicial+2] = id;
            break;
    }

}