#ifndef __PROJ_FOUR_AVL_HPP
#define __PROJ_FOUR_AVL_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>

template<typename T1, typename T2>
class TreeNode
{
public: 
	T1 key;
	T2 value;
	TreeNode* left;
	TreeNode* right;
	TreeNode(T1 k, T2 v, TreeNode* left, TreeNode* right);
	~TreeNode();
};

class ElementNotFoundException : public RuntimeException 
{
public:
	ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};



template<typename Key, typename Value>
class MyAVLTree
{
private:
	// fill in private member data here
	// If you need to declare private functions, do so here too.
	TreeNode<Key, Value>* root;
	void static delete_1(TreeNode<Key,Value>* T);

public:
	MyAVLTree();

	// In general, a copy constructor and assignment operator
	// are good things to have.
	// For this quarter, I am not requiring these. 
	//	MyAVLTree(const MyAVLTree & st);
	//	MyAVLTree & operator=(const MyAVLTree & st);


	// The destructor is, however, required. 
	~MyAVLTree();

	// size() returns the number of distinct keys in the tree.
	size_t size() const noexcept;

	// isEmpty() returns true if and only if the tree has no values in it. 
	bool isEmpty() const noexcept;

	// contains() returns true if and only if there
	//  is a (key, value) pair in the tree
	//	that has the given key as its key.
	bool contains(const Key & k) const; 

	// find returns the value associated with the given key
	// If !contains(k), this will throw an ElementNotFoundException
	// There needs to be a version for const and non-const MyAVLTrees.
	Value & find(const Key & k);
	const Value & find(const Key & k) const;

	// Inserts the given key-value pair into 
	// the tree and performs the AVL re-balance
	// operation, as described in lecture. 
	// If the key already exists in the tree, 
	// you may do as you please (no test cases in
	// the grading script will deal with this situation)
	void insert(const Key & k, const Value & v);

	// in general, a "remove" function would be here
	// It's a little trickier with an AVL tree
	// and I am not requiring it for this quarter's ICS 46.
	// You should still read about the remove operation
	// in your textbook. 

	// The following three functions all return
	// the set of keys in the tree as a standard vector.
	// Each returns them in a different order.
	std::vector<Key> inOrder() const;
	std::vector<Key> preOrder() const;
	std::vector<Key> postOrder() const;


};

template<typename Key, typename Value>
void MyAVLTree<Key,Value>::delete_1(TreeNode<Key,Value>* T)
{
	if (T.left != nullptr)
	{
		delete(T.left);
	}
	if (T.right != nullptr)
	{
		delete(T.right);
	}
	if (T.right == nullptr && T.left == nullptr)
	{
		delete T;
	}
}

template<typename T1,typename T2>
TreeNode<T1,T2>::TreeNode(T1 k, T2 v, TreeNode* left, TreeNode* right)
{
	key = k;
	value = v;
	left = left;
	right = right;
}


template<typename Key, typename Value>
MyAVLTree<Key,Value>::MyAVLTree()
{
	root = nullptr;
}

template<typename Key, typename Value>
MyAVLTree<Key,Value>::~MyAVLTree()
{
	delete(root);
}

template<typename Key, typename Value>
size_t MyAVLTree<Key, Value>::size() const noexcept
{

}

template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::isEmpty() const noexcept
{
	return (root == nullptr);
}


template<typename Key, typename Value>
bool MyAVLTree<Key, Value>::contains(const Key &k) const
{

	TreeNode<Key,Value>* current = root;
	while (current != nullptr)
	{
		if (k < current->key)
		{
			current = current->left;
		}
		else if (k > current->key)
		{
			current = current->right;
		}
		else
		{
			return true;
		}
	}
	return false;
}



template<typename Key, typename Value>
Value & MyAVLTree<Key, Value>::find(const Key & k)
{
	TreeNode<Key,Value>* current = root;
	while (current != nullptr)
	{
		if (k < current->key)
		{
			current = current->left;
		}
		else if (k > current->key)
		{
			current = current->right;
		}
		else
		{
			return current->value;
		}
	}
	throw ElementNotFoundException("Key not found");
}

template<typename Key, typename Value>
const Value & MyAVLTree<Key, Value>::find(const Key & k) const
{
	TreeNode<Key,Value>* current = root;
	while (current != nullptr)
	{
		if (k < current->key)
		{
			current = current->left;
		}
		else if (k > current->key)
		{
			current = current->right;
		}
		else
		{
			return current->value;
		}
	}
	throw ElementNotFoundException("Key not found");
}

template<typename Key, typename Value>
void MyAVLTree<Key, Value>::insert(const Key & k, const Value & v)
{
	TreeNode<Key,Value>* current = root;
	while (current != nullptr)
	{
		if (k < current->key)
		{
			current = current->left;
		}
		else if (k > current->key)
		{
			current = current->right;
		}
	}
	current = new TreeNode<Key,Value>(k,v,nullptr,nullptr);
}




template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::inOrder() const
{
	std::vector<Key> foo;
	return foo; 
}


template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::preOrder() const
{
	std::vector<Key> foo;
	return foo; 
}


template<typename Key, typename Value>
std::vector<Key> MyAVLTree<Key, Value>::postOrder() const
{
	std::vector<Key> foo;
	return foo; 
}







#endif 