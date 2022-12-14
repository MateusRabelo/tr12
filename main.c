// incluindo a biblioteca a ser utilizada
#include "heap.h"

//criando uma função do tipo HEAP (já definido)

// a função vai basicamente definir os valores e alocar na memória tudo o que for necessário, 
// limpando os lixos necessários de serem limpos para não dar nenhum problema de memory trash
HEAP* HEAP_create(int n, COMP* compara) {
	HEAP* heap = malloc(sizeof(HEAP));
	heap->elems = malloc(n * sizeof(void*));
	heap->N = n;
	heap->P = 0;
	heap->comparador = compara;

	return heap;
}

// aqui a função vai adicionar os valores pedidos, utilizando de técnicas de heap já vistas
// para adicionar valores e já ordenar nos devidos índices
void HEAP_add(HEAP* heap, void* newelem) {
	// decindindo quando será a posição do heap atual
	if (heap->P < heap->N) {
		heap->elems[heap->P] = newelem;
		// definindo a posição do heap atual
		int pos = heap->P;

		// adicionando valores e organizando os valores na heap
		while (heap->comparador(heap->elems[pos], heap->elems[(pos - 1) / 2]) > 0) {
			void* aux = heap->elems[pos];
			heap->elems[pos] = heap->elems[(pos - 1) / 2];
			heap->elems[(pos - 1) / 2] = aux;
			// aplicando na posição da heap
			pos = (pos - 1) / 2;
		}	

		heap->P++;
	}
}
// HEAP_remove vai justamente remover os valores da heap, e novamente reorganizar os valores na heap
void* HEAP_remove(HEAP* heap) {
	void* min = heap->elems[0];

	// organinzando os itens na heap para a remoção do mínimo
	heap->elems[0] = heap->elems[heap->P - 1];
	heap->elems[heap->P - 1] = min;
	
	heap->P--;

	// definindo pai e filho da heap
	int pai = 0;
	int filho = pai * 2 + 1;
	
	// seguindo os valores da árvore da heap
	while (filho < heap->P) {
		if (filho + 1 < heap->P) {
			if (heap->comparador(heap->elems[filho], heap->elems[filho + 1]) < 0) {
				filho += 1;
			}
		}

		// aqui tem as funções de remoção para cada filho do mesmo pai, 
		// já que cada pai possui dois filhos, e um pode ser maior que o outro
		if (heap->comparador(heap->elems[pai], heap->elems[filho]) < 0) {
			void* aux = heap->elems[pai];
			heap->elems[pai] = heap->elems[filho];
			heap->elems[filho] = aux;

			// caso filho 1
			pai = filho;
			filho = pai * 2 + 1;
		} else {
			// caso filho 2
			filho = heap->P + 1;
		}
	}

	return min;
}

// função para comparar os respectivos valores
int comparar(void* x, void* y) {
	int xx = *((int*) x);
	int yy = *((int*) y);

	return xx < yy ? 1 : xx == yy ? 0 : -1;
}	

// e aqui temos a função principal, que irá rodar todo o programa
int main() {
    // definindo valores iniciais
	const int heap_SIZE = 10;
	const int heap_REMOVE = 2;

    // definindo comportamento da variável heap
	HEAP* heap = HEAP_create(heap_SIZE, comparar);

    // heap em us[tamanho do heap
	int meuHeap[heap_SIZE];

    // apresentação do heap inicial
	printf("HEAP INICIALIZADO: ");
	for (int i = 0; i < heap_SIZE; i++) {
        // definindo o tamanho do heap, imprimindo o heap e sí
		meuHeap[i] = rand() % heap_SIZE;
		printf("%d - ", meuHeap[i]);
	}
	printf("FIM\n\n");

    // calcula a adição de valores nos indíces do heap
	for (int i = 0; i < heap_SIZE; i++) {
		HEAP_add(heap, &meuHeap[i]);
	}

    // imprimindo os itens removidos
	printf("ITENS REMOVIDOS: ");
    // calcula para imprimir os itens removidos
	for (int i = 0; i < heap_REMOVE; i++) {
		printf("%d - ", *((int*) HEAP_remove(heap)));
	}
	printf("FIM\n\n");

    // imprimi o heap final
	printf("HEAP FINAL: ");
    // calculando os valores do heap depois de todas as alterações
	for (int i = 0; i < heap->P; i++) {
		printf("%d - ", *((int*) heap->elems[i]));
	}
	printf("FIM\n");

	return 0;
}