#include <stdio.h>
#include<stdlib.h>
#include "bibdolphin.c"
void captura_teclado(){
    char ch;
    while(ch != 'p'){
        printf("Digite 'p' seguido de ENTER para continuar:\n");
        ch= getchar();
    }
}
int main(){
    Grafo dolphin = criar_grafo_vazio();
    dolphin = rede_social(dolphin);
    char ch;
    imprimir_grafo(dolphin);
    captura_teclado();
    coef_aglomeracao(dolphin);
    
    return 0;
}