/*
============================
=                          =
= Desafio do Batalha Naval =
=    by: @fiercelionbr     =
=          L1onX           =
=        03/03/2025        =
=                          =
============================
*/

#include <stdio.h>

// Definição do tamanho do tabuleiro e dos navios-----------------------------------------------------------------------------------------------------------------------

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------




// Função para inicializar o tabuleiro com água (valor 0)---------------------------------------------------------------------------------------------------------------

void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------




// Função para posicionar um navio horizontalmente no tabuleiro---------------------------------------------------------------------------------------------------------

void posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = 3;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------




// Função para posicionar um navio verticalmente no tabuleiro-----------------------------------------------------------------------------------------------------------

void posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = 3;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------




// Função para posicionar um navio diagonalmente no tabuleiro (diagonal principal)--------------------------------------------------------------------------------------

void posicionarNavioDiagonalPrincipal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = 3;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------




// Função para posicionar um navio diagonalmente no tabuleiro (diagonal secundária)-------------------------------------------------------------------------------------

void posicionarNavioDiagonalSecundaria(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = 3;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------




// Função para exibir o tabuleiro no console----------------------------------------------------------------------------------------------------------------------------

void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {

    // Exibir cabeçalho com letras de A a J--------------------------------

    printf("  ");
    for (char letra = 'A'; letra < 'A' + TAMANHO_TABULEIRO; letra++) {
        printf("%c ", letra);
    }
    printf("\n");

    //---------------------------------------------------------------------

    // Exibir tabuleiro com números de 1 a 10 na lateral-------------------

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i + 1); // Exibir número da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    //---------------------------------------------------------------------
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------




// Função para inicializar a matriz de habilidade com zeros-------------------------------------------------------------------------------------------------------------
void inicializarHabilidade(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            habilidade[i][j] = 0;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------




// Função para criar a matriz de habilidade em forma de cone------------------------------------------------------------------------------------------------------------

void criarHabilidadeCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    inicializarHabilidade(habilidade);
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j <= i; j++) {
            habilidade[i][TAMANHO_HABILIDADE / 2 - i / 2 + j] = 1;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------




// Função para criar a matriz de habilidade em forma de cruz------------------------------------------------------------------------------------------------------------

void criarHabilidadeCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    inicializarHabilidade(habilidade);
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        habilidade[TAMANHO_HABILIDADE / 2][i] = 1;
        habilidade[i][TAMANHO_HABILIDADE / 2] = 1;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------





// Função para criar a matriz de habilidade em forma de octaedro---------------------------------------------------------------------------------------------------------

void criarHabilidadeOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    inicializarHabilidade(habilidade);
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        habilidade[i][TAMANHO_HABILIDADE / 2] = 1;
        habilidade[TAMANHO_HABILIDADE / 2][i] = 1;
        if (i <= TAMANHO_HABILIDADE / 2) {
            habilidade[i][TAMANHO_HABILIDADE / 2 - i] = 1;
            habilidade[i][TAMANHO_HABILIDADE / 2 + i] = 1;
            habilidade[TAMANHO_HABILIDADE - 1 - i][TAMANHO_HABILIDADE / 2 - i] = 1;
            habilidade[TAMANHO_HABILIDADE - 1 - i][TAMANHO_HABILIDADE / 2 + i] = 1;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------




// Função para sobrepor a matriz de habilidade ao tabuleiro-------------------------------------------------------------------------------------------------------------

void sobreporHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], int origemLinha, int origemColuna) {
    int offset = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int linha = origemLinha + i - offset;
            int coluna = origemColuna + j - offset;
            if (linha >= 0 && linha < TAMANHO_TABULEIRO && coluna >= 0 && coluna < TAMANHO_TABULEIRO && habilidade[i][j] == 1) {
                tabuleiro[linha][coluna] = 5;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------





int main() {

    // Declaração do tabuleiro--------------------------

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    //--------------------------------------------------




    // Inicialização do tabuleiro-----------------------

    inicializarTabuleiro(tabuleiro);

    //--------------------------------------------------




    // Coordenadas iniciais dos navios------------------

    int linhaNavioHorizontal = 2;
    int colunaNavioHorizontal = 3;
    int linhaNavioVertical = 5;
    int colunaNavioVertical = 7;
    int linhaNavioDiagonalPrincipal = 0;
    int colunaNavioDiagonalPrincipal = 0;
    int linhaNavioDiagonalSecundaria = 0;
    int colunaNavioDiagonalSecundaria = 9;

    //--------------------------------------------------




    // Posicionamento dos navios no tabuleiro-----------------------------------------------------------------

    posicionarNavioHorizontal(tabuleiro, linhaNavioHorizontal, colunaNavioHorizontal);
    posicionarNavioVertical(tabuleiro, linhaNavioVertical, colunaNavioVertical);
    posicionarNavioDiagonalPrincipal(tabuleiro, linhaNavioDiagonalPrincipal, colunaNavioDiagonalPrincipal);
    posicionarNavioDiagonalSecundaria(tabuleiro, linhaNavioDiagonalSecundaria, colunaNavioDiagonalSecundaria);

    //--------------------------------------------------------------------------------------------------------




    // Declaração das matrizes de habilidade------------------------
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    //--------------------------------------------------------------




    // Criação das matrizes de habilidade-------

    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);

    //-------------------------------------------




    // Coordenadas de origem das habilidades no tabuleiro--
    int origemConeLinha = 4;
    int origemConeColuna = 4;
    int origemCruzLinha = 6;
    int origemCruzColuna = 6;
    int origemOctaedroLinha = 8;
    int origemOctaedroColuna = 8;

    //-----------------------------------------------------




    // Sobreposição das habilidades no tabuleiro-------------------------------------------------

    sobreporHabilidade(tabuleiro, habilidadeCone, origemConeLinha, origemConeColuna);
    sobreporHabilidade(tabuleiro, habilidadeCruz, origemCruzLinha, origemCruzColuna);
    sobreporHabilidade(tabuleiro, habilidadeOctaedro, origemOctaedroLinha, origemOctaedroColuna);

    //-------------------------------------------------------------------------------------------




    // Exibição do tabuleiro no console---------------------

    printf("Tabuleiro do Batalha Naval com Habilidades:\n");
    exibirTabuleiro(tabuleiro);

    //------------------------------------------------------

    return 0;
}