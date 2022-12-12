#include "heap.h"

HEAP* HEAP_create(int n, COMP* compara) {
	HEAP* heap = malloc(sizeof(HEAP));
	heap->elems = malloc(n * sizeof(void*));
	heap->N = n;
	heap->P = 0;
	heap->comparador = compara;

	return heap;
}	

void HEAP_add(HEAP* heap, void* newelem) {
  if (heap->P < heap->N) {
    heap->elems[heap->P] = newelem;
	int posicao = heap->P;

	while (heap->comparador(heap->elems[posicao], heap->elems[(posicao - 1) / 2]) > 0) { //laço para encontrar a posicao auxiliar e adicionar o elemento
		void* aux = heap->elems[posicao];
		heap->elems[posicao] = heap->elems[(posicao - 1) / 2];
		heap->elems[(posicao - 1) / 2] = aux;	
		posicao = (posicao - 1) / 2;
	}	

	heap->P++;
  }
}

void* HEAP_remove(HEAP* heap) {
	if (heap->P > 0) {
		void* min = heap->elems[0];
		heap->P--;

		heap->elems[0] = heap->elems[heap->P];
		heap->elems[heap->P] = min;

		int pai = 0;
		int filho = pai * 2 + 1;
		
		while (filho < heap->P) { //laço para reestruturar a heap
			if (filho + 1 < heap->P) {
				if (heap->comparador(heap->elems[filho], heap->elems[filho + 1]) < 0) {
					filho += 1;
				}
			}

			if (heap->comparador(heap->elems[pai], heap->elems[filho]) < 0) {
				void* aux = heap->elems[pai];
				heap->elems[pai] = heap->elems[filho];
				heap->elems[filho] = aux;

				pai = filho;
				filho = pai * 2 + 1;
			} else {
				break;
			}
		}

		return min;
	}
}
