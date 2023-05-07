
#include "FiboHeap.h"
#include <queue>
#include <stack>

int FiboHeap::min() const {
	return min_root->value;
}

FiboHeap& FiboHeap::insert(int _value) {
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

	if (min_root == nullptr)
		min_root = node;
	else if (node->value < min_root->value)
		min_root = node;

	++size;
	return *this;
}

FiboHeap& FiboHeap::attach(int _value, FiboHeap* heap) {
	Node* f = find_(_value, root_list);
	if (f) {
		Node* attach_to = f;
		if (attach_to) {
			if (attach_to->child) {
				Node* acps = attach_to->child->prev_sibling;
				attach_to->child->prev_sibling = heap->root_list->prev_sibling;
				heap->root_list->prev_sibling->next_sibling = attach_to->child;
				acps->next_sibling = heap->root_list;
				heap->root_list->prev_sibling = acps;
			}
			else {
				attach_to->child = heap->root_list;
				heap->root_list->parent = attach_to;
			}
		}
		size += heap->size;
	}
	else {
		std::cout << "Couldn't attach heap. Value { " << _value << " } doesn't exist.";
	}
	return *this;
}

FiboHeap FiboHeap::unite(FiboHeap* heap1, FiboHeap* heap2) {
	FiboHeap new_heap;
	new_heap.root_list = heap1->root_list;

	if (heap1->min_root->value < heap2->min_root->value)
		new_heap.min_root = heap1->min_root;
	else
		new_heap.min_root = heap2->min_root;

	// Middle Connection
	Node* h2rp = heap2->root_list->prev_sibling;
	heap2->root_list->prev_sibling = heap1->root_list->prev_sibling;
	heap1->root_list->prev_sibling->next_sibling = heap2->root_list;

	// Looped Connection
	heap1->root_list->prev_sibling = h2rp;
	h2rp->next_sibling = heap1->root_list;

	new_heap.size = heap1->size + heap2->size;

	return new_heap;
}

FiboHeap::Node* FiboHeap::find_(int _value, Node* start) {
	Node* node = start;
	std::queue<Node*> next_to_search;

	if (node->value == _value)
		return node;
	if (node->child and node->value < _value)
		next_to_search.push(node->child);

	node = node->next_sibling;
	for (; node != start; node = node->next_sibling) {
		if (node->value == _value)
			return node;
		if (node->child and node->value < _value)
			next_to_search.push(node->child);
	}
	while (next_to_search.empty() == false) {
		Node* ret = find_(_value, next_to_search.front());
		if (ret)
			return ret;
		next_to_search.pop();
	}
	return nullptr;
}

bool FiboHeap::find(int _value) {
	Node* node = find_(_value, root_list);
	return (node);
}

int FiboHeap::extract_min() {
	int minimum = min_root->value;

	if (root_list == min_root)
		root_list = nullptr;

	remove_(min_root);
	min_root = nullptr;
	find_min_root_();

	return minimum;
}

void FiboHeap::remove_(Node* node) {
	auto del_helper = [&](auto&& del_helper, Node* _node) -> int {
		Node* __node = _node;
		if (__node) {
			del_helper(del_helper, __node->child);

			std::stack<Node*>to_free;
			to_free.push(__node);
			__node = __node->next_sibling;

			while (__node != _node) {
				del_helper(del_helper, __node->child);
				to_free.push(__node);
				__node = __node->next_sibling;
			}
			while (to_free.empty() == false) {
				to_free.top()->parent = nullptr;
				to_free.top()->child = nullptr;
				to_free.top()->prev_sibling = nullptr;
				to_free.top()->next_sibling = nullptr;

				delete to_free.top();
				to_free.top() = nullptr;
				to_free.pop();
				--size;
			}
		}
		return 0;
	};
	del_helper(del_helper, node->child);

	if (node->parent and node != node->next_sibling) {
		node->parent->child = node->next_sibling;
		node->next_sibling->parent = node->parent;
	}
	node->prev_sibling->next_sibling = node->next_sibling;
	node->next_sibling->prev_sibling = node->prev_sibling;

	node->parent = nullptr;
	node->child = nullptr;
	node->prev_sibling = nullptr;
	node->next_sibling = nullptr;

	delete node;
	node = nullptr;
	--size;
}

void FiboHeap::remove(int _value) {
	Node* node = find_(_value, root_list);
	remove_(node);
}

void FiboHeap::clear() {
	while (root_list)
		extract_min();
	size = 0;
}

void FiboHeap::find_size_() {
	Node* node = root_list;
	if (!node)
		return;
	int s = 1;
	
	if (node->child) {
		FiboHeap child_heap;
		child_heap.root_list = node->child;
		child_heap.find_size_();
		s += child_heap.size;
	}
	node = node->next_sibling;
	for (; node != root_list; node = node->next_sibling) {
		if (node->child) {
			FiboHeap child_heap;
			child_heap.root_list = node->child;
			child_heap.find_size_();
			s += child_heap.size;
		}
		++s;
	}
	size = s;
}

void FiboHeap::find_min_root_() {
	Node* node = root_list;
	if (!node)
		return;

	if (min_root == nullptr or node->value < min_root->value)
		min_root = node;
	node = node->next_sibling;

	for (; node != root_list; node = node->next_sibling) {
		if (min_root == nullptr or node->value < min_root->value)
			min_root = node;
	}
}

bool FiboHeap::empty() const {
	return !(size > 0);
}
