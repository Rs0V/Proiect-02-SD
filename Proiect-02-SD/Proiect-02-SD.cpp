
#include "FiboHeap.h"

int main() {
	// EXEMPLE 1
	{
		FiboHeap heap1, heap2;

		heap1.insert(17);
		heap1.insert(5);
		heap1.insert(24);
		heap1.insert(19);
		heap1.insert(14);

		heap2.insert(6);
		heap2.insert(2);
		heap2.insert(9);
		heap2.insert(3);
		heap2.insert(12);

		FiboHeap fheap = FiboHeap::unite(&heap1, &heap2);

		std::cout << "heap1: " << heap1 << "\n";
		std::cout << "heap2: " << heap2 << "\n";
		std::cout << "fheap: " << fheap << "\n\n";

		std::cout << "Is 1 in fheap? " << fheap.find(1) << "\n";
		std::cout << "Is 12 in fheap? " << fheap.find(12) << "\n";
		std::cout << "Is 24 in fheap? " << fheap.find(24) << "\n\n";

		std::cout << "Min fheap: " << fheap.min() << "\n\n";

		std::cout << "Extracted Min from fheap: " << fheap.extract_min() << "\n";
		std::cout << "Min fheap: " << fheap.min() << "\n";
		std::cout << "fheap: " << fheap << "\n\n";

		fheap.remove(9);
		std::cout << "Removed from fheap: 9" << "\n";
		std::cout << "fheap: " << fheap << "\n\n\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n\n";
	}
	// EXEMPLE 2
	{
		FiboHeap* heap1 = new FiboHeap();
		FiboHeap* heap2 = new FiboHeap();
		FiboHeap* heap_aux = new FiboHeap();

		heap1->insert(17);
		heap1->insert(24);
		heap1->insert(23);
		heap2->insert(7);
		heap2->insert(3);

		heap_aux->insert(30);
		heap1->attach(17, heap_aux);

		delete heap_aux;
		heap_aux = new FiboHeap();

		heap_aux->insert(26);
		heap_aux->insert(46);
		heap_aux->attach(26, &FiboHeap().insert(35));
		heap1->attach(24, heap_aux);

		delete heap_aux;
		heap_aux = new FiboHeap();

		heap_aux->insert(18);
		heap_aux->insert(52);
		heap_aux->insert(41);
		heap_aux->attach(18, &FiboHeap().insert(39));
		heap_aux->attach(41, &FiboHeap().insert(44));
		heap2->attach(3, heap_aux);

		delete heap_aux;

		std::cout << "heap1: " << *heap1 << "\n";
		std::cout << "heap2: " << *heap2 << "\n";

		FiboHeap* fheap = new FiboHeap(FiboHeap::unite(heap1, heap2));
		delete heap1;
		delete heap2;
		std::cout << "fheap: " << *fheap << "\n\n";

		std::cout << "Is 26 in fheap? " << fheap->find(26) << "\n";
		std::cout << "Is 5 in fheap? " << fheap->find(5) << "\n";
		std::cout << "Is 39 in fheap? " << fheap->find(39) << "\n";
		std::cout << "Is 7 in fheap? " << fheap->find(7) << "\n\n";

		std::cout << "Min fheap: " << fheap->min() << "\n\n";

		std::cout << "Extracted Min from fheap: " << fheap->extract_min() << "\n";
		std::cout << "Min fheap: " << fheap->min() << "\n";
		std::cout << "fheap: " << *fheap << "\n\n";

		fheap->remove(26);
		std::cout << "Removed from fheap: 26" << "\n";
		std::cout << "fheap: " << *fheap << "\n\n";

		fheap->clear();
		std::cout << "Clearing fheap...\n";
		if (fheap->empty())
			std::cout << "fheap is empty.\n";

		delete fheap;
	}
	return 0;
}
