
#pragma once
#ifndef FIBOHEAP

#include <iostream>
#include <vector>

class FiboHeap {
	class Node {
	public:
		int value;

		Node* parent;
		Node* child;

		Node* prev_sibling;
		Node* next_sibling;

		Node(int _value)
			:
			value(_value),
			parent(nullptr),
			child(nullptr),
			prev_sibling(nullptr),
			next_sibling(nullptr)
		{}
		friend std::ostream& operator<<(std::ostream& os, const Node& node) {
			os << node.value;
			return os;
		}
	};
	int size;
	Node* min_root;
	Node* root_list;

	Node* find_(int _value, Node* start);
	void remove_(Node* node);
	void find_size_();
	void find_min_root_();

public:
	FiboHeap()
		:
		size(0),
		min_root(nullptr),
		root_list(nullptr)
	{}

	int min() const;
	FiboHeap& insert(int _value);
	FiboHeap& attach(int _value, FiboHeap* heap);
	static FiboHeap unite(FiboHeap* heap1, FiboHeap* heap2);
	bool find(int _value);
	int extract_min();
	void remove(int _value);
	void clear();
	bool empty() const;

	friend std::ostream& operator<<(std::ostream& os, const FiboHeap& heap) {
		if (&heap == nullptr)
			return os;
		Node* node = heap.root_list;
		if (!node)
			return os;

		int printed = 1;

		os << *node << " ";
		if (node->child) {
			FiboHeap child_heap;
			child_heap.root_list = node->child;

			child_heap.find_size_();
			os << child_heap;

			printed += child_heap.size;
		}
		node = node->next_sibling;
		for (; node != heap.root_list and heap.size - printed > 0; node = node->next_sibling) {
			os << *node << " ";
			++printed;
			if (node->child) {
				FiboHeap child_heap;
				child_heap.root_list = node->child;

				child_heap.find_size_();
				os << child_heap;

				printed += child_heap.size;
			}
		}
		return os;
	}
};

#endif // !FIBOHEAP
