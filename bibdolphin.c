#include "bibdolphin.h"

Lista criar_lista_vazia(){//cria uma lista vazia
    Lista nova_lista;
    nova_lista.primeiro = (Ponteiro)malloc(sizeof(Item));
    nova_lista.primeiro->proximo_i = NULL;
    nova_lista.ultimo = nova_lista.primeiro;
    return nova_lista;
}

Lista inserir_lista(Lista lista,int num){//insere um elemento na lista
    lista.ultimo->proximo_i = (Ponteiro)malloc(sizeof(Item));
    lista.ultimo = lista.ultimo->proximo_i;
    lista.ultimo->conteudo_i = num;
    lista.ultimo->proximo_i = NULL;
    return lista;
}

void imprimir_lista(Lista lista){//imprime uma lista
    Ponteiro atual = lista.primeiro;
    while(1){
        if(atual->proximo_i == NULL){
            printf("|%d|\n",atual->conteudo_i);
            return;
        }
        else printf("|%d|->",atual->conteudo_i);
        atual = atual->proximo_i;
    }
}

Grafo criar_grafo_vazio(){//criar um grafo vazio
    Grafo grafo;
    int i;
    //pra cada vértice criar uma lista vazia
    for(i=0;i<NumeroDeGolfinhos;i++){
        Lista vertice = criar_lista_vazia();
        vertice.primeiro->conteudo_i = i+1;
        vertice.primeiro->grau=0;
        grafo.list_adj[i] = vertice;        
    }
    return grafo;
}

void imprimir_grafo(Grafo grafo){//imprime o grafo e os graus de cada vértice (tarefa 1)
    int i;
    Lista vertice;
    system("clear");
    for(i=0;i<NumeroDeGolfinhos;i++){
        vertice = grafo.list_adj[i];
        imprimir_lista(vertice);
        printf("Grau: %d\n",vertice.primeiro->grau);
    }
}

Grafo rede_social(Grafo grafo){//cria a rede social de golfinhos como um grafo
    FILE *arquivo_base;
    char linha[100];
    int num1,num2,i;

    arquivo_base = fopen("soc-dolphins.mtx","r");
    if(!arquivo_base) printf("Não foi possível abrir o arquivo!\n");
    else{
        while(!feof(arquivo_base)){
            fgets(linha,100,arquivo_base);
            if(linha[0] != '%'){
                //transforma a linha lida em números inteiros operáveis
                if(linha[1] == ' '){
                    //num1 é <10
                    num1 = linha[0] - '0';
                    //num2 é <10
                    if(linha[3] == '\n')
                        num2 = linha[2] - '0';
                    //num2 é >10
                    else
                        num2 = ((linha[2]-'0')*10)+(linha[3]-'0');
                }
                else{
                    //num1 é >10
                    num1 = ((linha[0] - '0')*10)+(linha[1] - '0');
                    //num2 é <10
                    if(linha[4] == '\n')
                        num2 = linha[3]-'0';
                    //num2 é >10  
                    else
                        num2 = ((linha[3]-'0')*10)+(linha[4] - '0');
                }
                /*monta as arestas no grafo
                ideia: percorrer o grafo buscando o num1 e colocar num2 na lista de arestas
                e depois percorrer o grafo buscando num2 e colocar num1 na lista de arestas*/
                if(num1 != 62 || num2 != 62){
                    for(i=0;i<NumeroDeGolfinhos;i++){
                        if(grafo.list_adj[i].primeiro->conteudo_i == num1){
                            grafo.list_adj[i] = inserir_lista(grafo.list_adj[i],num2);
                            grafo.list_adj[i].primeiro->grau++;           
                        }
                    }
                    for(i=0;i<NumeroDeGolfinhos;i++){
                        if(grafo.list_adj[i].primeiro->conteudo_i == num2){
                            grafo.list_adj[i] = inserir_lista(grafo.list_adj[i],num1);
                            grafo.list_adj[i].primeiro->grau++;
                        }
                    }
                }
            } 
        }
    }
    fclose(arquivo_base);
    return grafo;
}
Lista_T criar_lista_t_vazia(){//cria uma lista de triangulos vazia
    Lista_T nova_lista_t;
    nova_lista_t.primeiro_t = (Ponteiro_T)malloc(sizeof(Triangulos));
    nova_lista_t.primeiro_t->proximo_t = NULL;
    nova_lista_t.ti = 0;
    nova_lista_t.ultimo_t = nova_lista_t.primeiro_t;
    return nova_lista_t;
}
Lista_T inserir_lista_t(Lista_T lista_t, Ponteiro_T t){
    lista_t.ultimo_t->proximo_t = (Ponteiro_T)malloc(sizeof(Triangulos));
    lista_t.ultimo_t = lista_t.ultimo_t->proximo_t;
    lista_t.ultimo_t->v1 = t->v1;
    lista_t.ultimo_t->v2 = t->v2;
    lista_t.ultimo_t->v3 = t->v3;
    lista_t.ultimo_t->proximo_t = NULL;
    return lista_t;
}

int busca_triangulo(Grafo grafo, int i){
    int j,k,l;
    Ponteiro ref,ref_v,subref,subref_v,subsubref,subsubref_v; 
    Lista_T triangulos = criar_lista_t_vazia();
    Ponteiro_T t = (Ponteiro_T)malloc(sizeof(Triangulos));

    ref = grafo.list_adj[i].primeiro; //ponteiro pra ref
    t->v1 = ref->conteudo_i;//salvando v1 em caso de formação de triângulo
    //percorrer a lista de vizinhos de ref
    ref_v = ref->proximo_i;
    for(j=0;j<ref->grau;j++){
        //capturar o ponteiro de ref_v no grafo e salvar em subref
        for(k=0;k<NumeroDeGolfinhos;k++){
            if(grafo.list_adj[k].primeiro->conteudo_i == ref_v->conteudo_i){
                subref = grafo.list_adj[k].primeiro;
                break;
            }
        }
        t->v2 = subref->conteudo_i;//salvando v2 em caso de possível formação de triângulo
        subref_v = subref->proximo_i;
        for(l=0;l<subref->grau;l++){
            //percorrer a lista de vizinhos de subref
            //capturar o ponteiro de subref_v e salvar em subsubref
            for(k=0;k<NumeroDeGolfinhos;k++){
                if(grafo.list_adj[k].primeiro->conteudo_i == subref_v->conteudo_i){
                    subsubref = grafo.list_adj[k].primeiro;
                    break;
                }
            }
            //verificar se na lista de vizinhos de subsubref há ref
            subsubref_v = subsubref->proximo_i;
            for(k=0;k<subsubref->grau;k++){
                if(subsubref_v->conteudo_i == ref->conteudo_i){
                    t->v3 = subsubref->conteudo_i;//formado o triângulo
                    triangulos = inserir_lista_t(triangulos,t);
                    triangulos.ti++;
                    break;
                }
                subsubref_v = subsubref_v->proximo_i;
            }
            subref_v = subref_v->proximo_i;
        }
        //percorrer a lista de vizinhos de ref_v
        ref_v = ref_v->proximo_i;
    }
    return (triangulos.ti/2);
}
void coef_aglomeracao(Grafo grafo){
    int i,ti,ni,num,den;
    float c,c_medio = 0.0;
    Lista_T triangulos[NumeroDeGolfinhos];
    system("clear");
    for(i=0;i<NumeroDeGolfinhos;i++){
        ni = grafo.list_adj[i].primeiro->grau; 
        ti = busca_triangulo(grafo,i);
        num = 2*ti; den = ni*(ni-1);
        if(den != 0)
            c = (float)num/(float)den;
        else c = 0.000;
        c_medio += c;
        printf("|%d| -> c = %.3f\n",grafo.list_adj[i].primeiro->conteudo_i,c);
    }
    c_medio /= (float)NumeroDeGolfinhos;
    grafo.coef_medio = c_medio;
    printf("coef_medio = %.3f\n",grafo.coef_medio);
}