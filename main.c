#include <stdio.h>
#include <stdlib.h>

int linhas = 0;
int colunas = 0;
int destinoX = 0;
int destinoY = 0;

void readLabirinto(int** labirinto) {
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      int cell;
      scanf("%d", &cell);
      labirinto[i][j] = cell;
    }
  }
}

int** allocLabirinto() {
  int** m = (int**) malloc(linhas * sizeof(int*));

  for (int i = 0; i < linhas; i++) {
    m[i] = (int*) malloc(colunas * sizeof(int));
  }

  return m;
}

void printLabirinto(int** labirinto) {
    for(int i = 0; i < linhas; i++) {
        for(int j = 0; j < colunas; j++) {
            printf("%d ", labirinto[i][j]);
        }
        printf("\n");
    }
}


int isDentroMatriz(int x, int y) {
    //Aqui apenas verificamos se as coordenadas estão dentro dos limites do labirinto
    return x < colunas && x >= 0 && y < linhas && y >= 0;
}


int isParede(int x, int y, int** labirinto) {
   //Para essa implementação estamos considerando que a parede (caminho instransponível) será representado por 1 
    return labirinto[x][y] == 1;
}

int isVisitado(int x, int y, int** labirinto) {
    //Para essa implementação estamos considerando que celulas ja visitadas serão representadas por 3 
    return labirinto[x][y] == 3;
}

//Se a célula visitada fizer parte de um caminho viável retornamos a QUANTIDADE de caminhos viáveis a partir DAQUELA célula,
//levando em conta as células visitadas naquele encaminhamento.
int solve(int x, int y, int** labirinto) {
    if(x == destinoX && y == destinoY) {
        //Objetivo final encontrado, retornar que foi encontrado 1 caminho;
        return 1;
    }

    if(!isDentroMatriz(x, y) || isParede(x, y, labirinto) || isVisitado(x, y, labirinto)) {
        //Caminho sem saída encontrado, voltar na recursão com o valor 0
        return 0;
    }

    //Ao "pôr os pés" na célula nova definiremos em nossa matriz que ela foi visitada ao definirmos o valor "3" para ela
    labirinto[x][y] = 3;

    int saidas = 0;

    //Primeiro veremos se o caminho a célula a cima é um caminho viável
    saidas += solve(x, y - 1, labirinto);

    //Após verificarmos os caminhos possíveis acima
    //tentaremos os caminhos possíveis a esquerda

    saidas += solve(x - 1, y, labirinto);

    //Após verificarmos os caminhos possíveis a esquerda
    //tentaremos os caminhos possíveis a baixo
    
    saidas += solve(x, y + 1, labirinto);

    //Após verificarmos os caminhos possíveis a baixo
    //tentaremos os caminhos possíveis a direita
    
    saidas += solve(x + 1, y, labirinto);


    //Como ja visitamos todos os caminhos possíveis a partir da célula atual retornaremos a camada superior da nossa recursão.
    //Como "desvisitaremos" essa célula, a "pintamos" como não-visitada novamente 
    labirinto[x][y] = 0;

    return saidas;

}

int main() {
    scanf("%d %d", &linhas, &colunas);
    destinoX = colunas - 1;
    destinoY = linhas - 1;
    
    int** labirinto = allocLabirinto();
    readLabirinto(labirinto);
    
    printLabirinto(labirinto);

    int ans = solve(0, 0, labirinto);

    printf("%d\n", ans); 

}