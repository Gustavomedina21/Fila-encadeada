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
    Node* novo = (Node*)malloc(sizeof(Node));  // Cria um novo n�

    novo->data = i;  // Define o valor do n� como o valor passado

    if (fila->head == NULL) {  // Caso a fila esteja vazia
        fila->head = novo;  // O novo n� se torna a cabe�a da fila
        novo->next = novo;  // O pr�ximo e o anterior do novo n� apontam para ele mesmo
        novo->prev = novo;
    } else {
        Node* ultimo = fila->head->prev;  // Obt�m o �ltimo n� da fila

        ultimo->next = novo;  // O pr�ximo do �ltimo n� aponta para o novo n�
        novo->prev = ultimo;  // O anterior do novo n� aponta para o �ltimo n�

        novo->next = fila->head;  // O pr�ximo do novo n� aponta para a cabe�a da fila
        fila->head->prev = novo;  // O anterior da cabe�a da fila aponta para o novo n�
    }
}

int desenfileira(Fila* fila) {
    if (fila->head == NULL) {  // Caso a fila esteja vazia
        printf("Erro: fila vazia\n");
        exit(1);
    }

    int valor;
    Node* primeiro = fila->head;  // Obt�m o primeiro n� da fila

    if (primeiro->next == primeiro) {  // Caso haja apenas um n� na fila
        fila->head = NULL;  // A fila fica vazia
        valor = primeiro->data;  // Armazena o valor do primeiro n�
        free(primeiro);  // Libera a mem�ria do primeiro n�
    } else {
        Node* proximo = primeiro->next;  // Obt�m o pr�ximo n�
        Node* ultimo = primeiro->prev;  // Obt�m o �ltimo n�

        fila->head = proximo;  // O pr�ximo n� se torna a cabe�a da fila
        proximo->prev = ultimo;  // O anterior do pr�ximo n� aponta para o �ltimo n�
        ultimo->next = proximo;  // O pr�ximo do �ltimo n� aponta para o pr�ximo n�

        valor = primeiro->data;  // Armazena o valor do primeiro n�
        free(primeiro);  // Libera a mem�ria do primeiro n�
    }

    return valor;
}

int vazia(Fila fila) {
    return (fila.head == NULL) ? 1 : 0;  // Retorna 1 se a fila est� vazia, caso contr�rio, retorna 0
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

    mostra(fila);  // Sa�da: 1 2 3
    mostraInverso(fila);  // Sa�da: 3 2 1

    int valor = desenfileira(&fila);
    printf("Valor removido: %d\n", valor);  // Sa�da: Valor removido: 1

    mostra(fila);  // Sa�da: 2 3

    return 0;
}
