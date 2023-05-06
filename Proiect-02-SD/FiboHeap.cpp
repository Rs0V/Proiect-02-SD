
#include "FiboHeap.h"
#include <queue>

int FiboHeap::min() {
	return min_root->value;
}

void FiboHeap::insert(int _value) {
	Node* node = new Node(_value);
	node->prev_sibling = node;
	node->next_sibling = node;

	if (root_list) {
		node->next_sibling = root_list;
		node->prev_sibling = root_list->prev_sibling;
		root_list->prev_sibling->next_sibling = node;
		root_list->prev_sibling = node;
	}
	else
		root_list = node;

	if (min_root == nullptr or node->value < min_root->value)
		min_root = node;

	++size;
}

void FiboHeap::attach(int _value, FiboHeap* heap) {
	Node* attach_to = find_(_value, root_list);
	if (attach_to) {
		if (attach_to->child) {
			Node* acps = attach_to->child->prev_sibling;
			attach_to->child->prev_sibling = heap->root_list->prev_sibling;
			heap->root_list->prev_sibling->next_sibling = attach_to->child;
			acps->next_sibling = heap->root_list;
			heap->root_list->prev_sibling = acps;
		}
		else
			attach_to->child = heap->root_list;
	}
	size += heap->size;
}

FiboHeap* FiboHeap::unite(FiboHeap* heap1, FiboHeap* heap2) {
	FiboHeap* new_heap = new FiboHeap();
	new_heap->root_list = heap1->root_list;

	if (heap1->min_root->value < heap2->min_root->value)
		new_heap->min_root = heap1->min_root;
	else
		new_heap->min_root = heap2->min_root;

	// Middle Connection
	Node* h2rp = heap2->root_list->prev_sibling;
	heap2->root_list->prev_sibling = heap1->root_list->prev_sibling;
	heap1->root_list->prev_sibling->next_sibling = heap2->root_list;

	// Looped Connection
	heap1->root_list->prev_sibling = h2rp;
	h2rp->next_sibling = heap1->root_list;

	new_heap->size = heap1->size + heap2->size;

	return new_heap;
}

FiboHeap::Node* FiboHeap::find_(int _value, Node* start) {
	Node* node = start;
	int i = 0;
	std::queue<Node*> next_to_search;
	for (; i < size; node = node->next_sibling, ++i) {
		if (node->value == _value)
			return node;
		if(node->child and node->value < _value)
			next_to_search.push(node->child);
	}
	while(next_to_search.empty() == false) {
		Node* ret = find_(_value, next_to_search.front());
		if (ret)
			return ret;
		next_to_search.pop();
	}
	return nullptr;
}

bool FiboHeap::find(int _value) {
	return (find_(_value, root_list));
}

int FiboHeap::extract_min() {
	int minimum = min_root->value;

	remove_(min_root);

	Node* node = root_list;
	if (node) {
		min_root = node;
		node = node->next_sibling;
		for (; node != root_list; node = node->next_sibling) {
			if (node->value < min_root->value)
				min_root = node;
		}
	}
	return minimum;
}

void FiboHeap::remove_(Node* node) {
	 auto del_helper = [&](auto&& del_helper, Node* _node) -> int {
		Node* __node = _node;
		if (__node) {
			del_helper(del_helper, __node);
			Node* next = __node->next_sibling;

			__node->prev_sibling->next_sibling = __node->next_sibling;
			__node->next_sibling->prev_sibling = __node->prev_sibling;
			delete __node;

			__node = next;
			while (__node != _node) {
				del_helper(del_helper, __node);
				Node* next = __node->next_sibling;
				delete __node;
				__node = next;
			}
		}
		return 0;
	};
	del_helper(del_helper, node->child);

	node->prev_sibling->next_sibling = node->next_sibling;
	node->next_sibling->prev_sibling = node->prev_sibling;
	delete node;
}

void FiboHeap::remove(int _value) {
	remove_(find_(_value, root_list));
}

int FiboHeap::find_size_() {
	Node* node = root_list;
	if (!node)
		return 0;
	int s = 1;
	for (; node != root_list; node = node->next_sibling) {
		if (node->child) {
			FiboHeap child_heap;
			child_heap.root_list = node->child;
			s += child_heap.find_size_();
		}
	}
	return s;
}
