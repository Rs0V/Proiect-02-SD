
#pragma once
#ifndef FIBOHEAP

#include <iostream>
#include <vector>

class FiboHeap {
	class Node {
	public:
		int value;
		int degree;

		bool child_removed;

		Node* parent;
		Node* child;

		Node* prev_sibling;
		Node* next_sibling;

		Node(int _value)
			:
			value(_value),
			degree(0),
			child_removed(false),
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
	int find_size_();

public:
	FiboHeap()
		:
		size(0),
		min_root(nullptr),
		root_list(nullptr)
	{}

	int min();
	void insert(int _value);
	void attach(int _value, FiboHeap* heap);
	static FiboHeap* unite(FiboHeap* heap1, FiboHeap* heap2);
	bool find(int _value);
	int extract_min();
	void remove(int _value);

	friend std::ostream& operator<<(std::ostream& os, const FiboHeap& heap) {
		Node* node = heap.root_list;
		if (!node)
			return os;

		int i = 1;
		int printed = 1;

		os << *node << " ";
		node = node->next_sibling;
		for (; node != heap.root_list and heap.size - printed > 0; node = node->next_sibling, ++i) {
			os << *node << " ";
			++printed;
			if (node->child) {
				FiboHeap child_heap;
				child_heap.root_list = node->child;
				printed += child_heap.find_size_();
				os << child_heap;
			}
		}
		return os;
	}
};

#endif // !FIBOHEAP
