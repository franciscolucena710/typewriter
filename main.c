#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void limpar_tela(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main(void) {
    FILE *arq;
    char linhas[500][200], entrada[200];
    int total = 0, idx, ini, fim;

    if ((arq = fopen("dados.txt", "r"))) {
        while (total < 500 && fgets(linhas[total], 200, arq)) total++;
        fclose(arq);
    }

    while (1) {
        limpar_tela();
        printf("--- Anotacao atual ---  (Digite: help)\n");
        for (int i = 0; i < total; i++) {
            printf("%d: %s", i + 1, linhas[i]);
        }

        printf(">> ");
        fgets(entrada, 200, stdin);

        if (strcmp(entrada, "0\n") == 0) {
            break;
        } else if (strcmp(entrada, "\n") == 0) {
            continue;
        } else if (strcmp(entrada, "help\n") == 0) {
            limpar_tela();
            printf("--- Comandos disponiveis ---\n");
            printf("  <texto>      : adiciona uma nova linha\n");
            printf("  edit<X>      : edita a linha X (ex: edit2)\n");
            printf("  erase<X>     : apaga a linha X (ex: erase2)\n");
            printf("  erase<X>-<Y> : apaga da linha X ate Y (ex: erase1-3)\n");
            printf("  0            : salva e encerra o programa\n");
            printf("Pressione Enter para continuar...");
            getchar();
            continue;
        } else if (sscanf(entrada, "erase%d-%d", &ini, &fim) == 2 || sscanf(entrada, "erase%d", &idx) == 1) {
            if (strstr(entrada, "-") == NULL) {
                ini = fim = idx;
            }

            if (ini >= 1 && fim <= total && ini <= fim) {
                int qtd = fim - ini + 1;
                for (int i = ini - 1; i < total - qtd; i++) {
                    strcpy(linhas[i], linhas[i + qtd]);
                }
                total -= qtd;
            }
        } else if (sscanf(entrada, "edit%d", &idx) == 1) {
            if (idx >= 1 && idx <= total) {
                printf("Nova linha %d: ", idx);
                fgets(linhas[idx - 1], 200, stdin);
            }
        } else if (total < 500) {
            strcpy(linhas[total++], entrada);
        }

        arq = fopen("dados.txt", "w");
        if (arq) {
            for (int i = 0; i < total; i++) {
                fputs(linhas[i], arq);
            }
            fclose(arq);
        }
    }

    limpar_tela();
    printf("--- Anotacao ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d: %s", i + 1, linhas[i]);
    }
    printf(">> Gravacao salva, programa encerrado.\n");
    return 0;
}
