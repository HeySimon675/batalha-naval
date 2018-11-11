void Coloca_Aviao (char m[20][20], int i_inicial,int j_inicial,int i_final,int j_final){
    extern int POS;
    int i,j;
    char id='1';
        switch (POS) {
            case 0:
                j = j_inicial + 1;
                for (i = i_inicial; i < i_final; i++)
                    m[i][j] = id;
                m[i_inicial + 1][j_inicial] = id;
                break;
            case 1:
                i = i_inicial;
                m[i_inicial + 1][j_inicial + 1] = id;
                for (j = j_inicial; j < j_final; j++)
                    m[i][j] = id;   //coloca a "cauda" do avião
                break;
            case 2 :
                j = j_inicial;
                for (i = i_inicial; i < i_final; i++)
                    m[i][j] = id;
                m[i_inicial + 1][j_inicial+1] = id;
                break;
            case 3:
                i = i_inicial+1;
                m[i_inicial][j_inicial + 1] = id;
                for (j = j_inicial; j < j_final; j++)
                    m[i][j] = id;   //coloca a "cauda" do avião
                break;
        }
}