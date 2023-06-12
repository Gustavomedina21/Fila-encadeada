#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
} Fila;

void enfileira(Fila* fila, int i) {
    Node* novo = (Node*)malloc(sizeof(Node));  // Cria um novo nó

    novo->data = i;  // Define o valor do nó como o valor passado

    if (fila->head == NULL) {  // Caso a fila esteja vazia
        fila->head = novo;  // O novo nó se torna a cabeça da fila
        novo->next = novo;  // O próximo e o anterior do novo nó apontam para ele mesmo
        novo->prev = novo;
    } else {
        Node* ultimo = fila->head->prev;  // Obtém o último nó da fila

        ultimo->next = novo;  // O próximo do último nó aponta para o novo nó
        novo->prev = ultimo;  // O anterior do novo nó aponta para o último nó

        novo->next = fila->head;  // O próximo do novo nó aponta para a cabeça da fila
        fila->head->prev = novo;  // O anterior da cabeça da fila aponta para o novo nó
    }
}

int desenfileira(Fila* fila) {
    if (fila->head == NULL) {  // Caso a fila esteja vazia
        printf("Erro: fila vazia\n");
        exit(1);
    }

    int valor;
    Node* primeiro = fila->head;  // Obtém o primeiro nó da fila

    if (primeiro->next == primeiro) {  // Caso haja apenas um nó na fila
        fila->head = NULL;  // A fila fica vazia
        valor = primeiro->data;  // Armazena o valor do primeiro nó
        free(primeiro);  // Libera a memória do primeiro nó
    } else {
        Node* proximo = primeiro->next;  // Obtém o próximo nó
        Node* ultimo = primeiro->prev;  // Obtém o último nó

        fila->head = proximo;  // O próximo nó se torna a cabeça da fila
        proximo->prev = ultimo;  // O anterior do próximo nó aponta para o último nó
        ultimo->next = proximo;  // O próximo do último nó aponta para o próximo nó

        valor = primeiro->data;  // Armazena o valor do primeiro nó
        free(primeiro);  // Libera a memória do primeiro nó
    }

    return valor;
}

int vazia(Fila fila) {
    return (fila.head == NULL) ? 1 : 0;  // Retorna 1 se a fila está vazia, caso contrário, retorna 0
}

void mostra(Fila fila) {
    if (fila.head == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Node* atual = fila.head;

    do {
        printf("%d ", atual->data);
        atual = atual->next;
    } while (atual != fila.head);

    printf("\n");
}

void mostraInverso(Fila fila) {
    if (fila.head == NULL) {
        printf("Fila vazia\n");
        return;
    }

    Node* atual = fila.head->prev;

    do {
        printf("%d ", atual->data);
        atual = atual->prev;
    } while (atual != fila.head->prev);

    printf("\n");
}

int main() {
    Fila fila;
    fila.head = NULL;

    enfileira(&fila, 1);
    enfileira(&fila, 2);
    enfileira(&fila, 3);

    mostra(fila);  // Saída: 1 2 3
    mostraInverso(fila);  // Saída: 3 2 1

    int valor = desenfileira(&fila);
    printf("Valor removido: %d\n", valor);  // Saída: Valor removido: 1

    mostra(fila);  // Saída: 2 3

    return 0;
}
