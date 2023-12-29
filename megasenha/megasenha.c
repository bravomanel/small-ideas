#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void shutdownSystem() {
    #ifdef _WIN32
        // Code for Windows shutdown
        system("shutdown /s /t 0");
    #elif __linux__
        // Code for Linux shutdown
        system("shutdown now");
    #else
        // Code for other operating systems (if needed)
        printf("Shutdown not supported on this operating system\n");
    #endif
}

int checaAcerto(int *arrayJogador, int *arrayCasa) {
    int total = -1;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (arrayJogador[i] == arrayCasa[j]) {
                total++;
            }
        }
    }
    return total;
}

void sortear(int *sorteados) {
    for (int i = 0; i < 6; i++) {
        sorteados[i] = 0;
    }
    srand(time(NULL));
    int size = 0;
    while (size < 6) {
        int temp = rand() % 60 + 1;
        for (int i = 0; i < 6; i++) {
            if (sorteados[i] == temp) {
                break;
            }
        }
        sorteados[size] = temp;
        size++;
    }
}

void imprimirNumeros(int arr[]) {
    for (int i = 0; i < 60; i++) {
        if (i % 10 == 0){
            printf("\n");
        }
        if (arr[i] == 0) {
            printf("X ");
        } else {
            printf("%d ", arr[i]);
        }
    }
}

void jogar(int *numerosEscolhidos) {
    int array[60] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
              11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
              21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
              31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
              41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
              51, 52, 53, 54, 55, 56, 57, 58, 59, 60};
    int quantidadeEscolhidos = 0;
    while (quantidadeEscolhidos < 6) {
        imprimirNumeros(array);
        printf("\nEscolha um numero:");
        int num = 0;
        scanf("%d", &num);
        if (num > 0 && num <= 60) {
            if (array[num - 1] == 0) {
                printf("Numero ja escolhido\n");
            } else {
                numerosEscolhidos[quantidadeEscolhidos] = array[num - 1];
                quantidadeEscolhidos++;
                array[num - 1] = 0;
            }
        } else {
            printf("Numero invalido\n");
        }
    }
}

void intro() {
    printf("Bem vindo ao jogo da Mega Senha!\n");
    printf("O jogo consiste em acertar os numeros.\n");
    printf("Voce recebera recompencas de acordo com a quantidade de acertos.\n");
    printf("Cuidado! Se voce errar, tambem haverao penalizacões...\n");
}

void menu() {
    printf("\n");
    printf("1 - Jogar\n");
    printf("2 - Mostrar Fichas\n");
    printf("3 - Resgatar Premio\n");
    printf("4 - Mostrar Premios\n");
    printf("0 - Desistir (arregar)\n");	
}

void main() {
    int fichas = 3;
    intro();


    while (1) {
        menu();
        printf("\nEscolha uma opcao: ");
        int opc = 0;
        scanf("%d", &opc);
        if (opc == 1) {
            int numerosJogador[6];
            jogar(numerosJogador);
            printf("\nSeus numeros: ");
            for (int i = 0; i < 6; i++) {
                printf("%d ", numerosJogador[i]);
            }

        
            int numerosSorteados[6];
            sortear(numerosSorteados);
            printf("\nNumeros sorteados: ");
            for (int i = 0; i < 6; i++) {
                printf("%d ", numerosSorteados[i]);
            }
        
            int acertos = checaAcerto(numerosJogador, numerosSorteados);
            printf("\nVoce acertou %d numeros e ganhou %d pontos\n", acertos +1, acertos);
            fichas += acertos;
            printf("Suas fichas: %d\n", fichas);
            if (fichas <= 0) {
                printf("Voce perdeu o jogo\n");
                sleep(4);
                // system("shutdown -s -t 0");
                system("shutdown /s /t 0");
                break;
            }
        } else if (opc == 2) {
            printf("Suas fichas: %d\n", fichas);
        } else if (opc == 3) {
            printf("Avise o administrador para resgatar premio\n");
        } else if (opc == 4) {
            printf("\n");
            printf("10 - Premio Misterioso\n");
            printf("9 - 2 reais\n");
            printf("8 - 1 real\n");
            printf("7 - 50 centavos\n");
            printf("6 - nada\n");
            printf("...-nada\n");
            printf("1 - nada\n");
            printf("0 - Voce perde...\n");
        } else if (opc == 0) {
            printf("Desistir (arregar)\n");
        } else {
            printf("Opcao invalida\n");
        }
    }
}