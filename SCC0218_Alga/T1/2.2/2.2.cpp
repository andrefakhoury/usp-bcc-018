#include <bits/stdc++.h>
using namespace std;

/** Checa se uma posição é valida (indices válidos e não visitada ainda) */
bool valid(int i, int j, int x, int y, int N, vector<vector<int>>& mat) {
    return i >= 0 && j >= 0 && i < N && j < N && (i != x || j != y) && mat[i][j] == 0;
}

/** Realiza o backtracking, tentando pintar todas as posições da matriz */
bool backtrack(int color, int N, int x, int y, vector<vector<int>>& mat, vector<vector<pair<int, int>>>& ord) {
    int qtt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            qtt += mat[i][j] == 0;
        }
    }

    if (qtt == 1) {
        return true;
    }

    // percorre todas as posições válidas
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // verifica as 4 posições possíveis de triangulos
            for (int k = 0; k < 4; k++) {
                int I1 = i + ord[k][0].first, J1 = j + ord[k][0].second;
                int I2 = i + ord[k][1].first, J2 = j + ord[k][1].second;
                int I3 = i + ord[k][2].first, J3 = j + ord[k][2].second;

                // verifica se as posições são válidas
                if (valid(I1, J1, x, y, N, mat) && valid(I2, J2, x, y, N, mat) && valid(I3, J3, x, y, N, mat)) {
                    mat[I1][J1] = mat[I2][J2] = mat[I3][J3] = color + 1;
                    
                    // verifica se o backtracking dá certo
                    if (backtrack(color+1, N, x, y, mat, ord))
                        return true;
                    
                    // volta ao normal
                    mat[I1][J1] = mat[I2][J2] = mat[I3][J3] = 0;
                }
            }
        }
    }

    return false;
}

/** Função principal */
int main() {
    int n; // tamanho do tabuleiro
    scanf("%d", &n);

    int N = 1 << n; // tabuleiro tem tamanho 2^n

    int x, y;
    scanf("%d%d", &x, &y);

    vector<vector<int>> mat(N, vector<int>(N));
    vector<vector<pair<int, int>>> ord(4, vector<pair<int, int>>(3));
    
    // deltas de todos os triângulos possíveis
    ord[0] = {{0, 0}, {0, 1}, {1, 0}};
    ord[1] = {{0, 0}, {1, 0}, {1, 1}};
    ord[2] = {{0, 0}, {0, 1}, {1, 1}};
    ord[3] = {{0, 1}, {1, 0}, {1, 1}};

    backtrack(0, N, x, y, mat, ord);

    // printa a resposta final
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}