
#include "FiboHeap.h"

int main() {
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

	FiboHeap* fheap = FiboHeap::unite(&heap1, &heap2);

	std::cout << "heap1: " << heap1 << "\n";
	std::cout << "heap2: " << heap2 << "\n";
	std::cout << "fheap: " << *fheap << "\n\n";

	std::cout << "Is 1 in fheap? " << fheap->find(1) << "\n";
	std::cout << "Is 12 in fheap? " << fheap->find(12) << "\n";
	std::cout << "Is 24 in fheap? " << fheap->find(24) << "\n\n";

	std::cout << "Min fheap: " << fheap->min() << "\n\n";

	std::cout << "Extracted Min from fheap: " << fheap->extract_min() << "\n";
	std::cout << "Min fheap: " << fheap->min() << "\n";
	std::cout << "fheap: " << *fheap << "\n\n";

	fheap->remove(9);
	std::cout << "Removed from fheap: 9" << "\n";
	std::cout << "fheap: " << *fheap << "\n";

	return 0;
}
