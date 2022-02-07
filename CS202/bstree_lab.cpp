#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "bstree.hpp"
using namespace std;
using CS202::BSTree;
using CS202::BSTNode;

/* ---------------------------------------------- */
/* You'll write all of these as part of your lab. */
//Finds the depth of a node by starting at the root and searching for the node, returns the level that node is on. returns -1 if node isnt there
int BSTree::Depth(const string &key) const{
	BSTNode* node;
	int depth;
	
	depth = 0;
	node = sentinel->right;
	while(node->key != key){
		if(key < node->key){
			node = node->left;
			depth++;
		}
		if(key > node->key){
			node = node->right;
			depth++;
		}
		if(node->key == key){
			return depth;
		}
		if(node->key == sentinel->key || node->key == sentinel->right->key) return -1;
	}
	return depth;
}
//Recursively finds the height of the tree by calling recursive_find_height
int BSTree::Height() const{
	int height;

	height=recursive_find_height(sentinel->right);

	return height;
}
//Creates sorted vector of keys by calling make_key_vector
vector <string> BSTree::Ordered_Keys() const
{
	vector<string> rv;
	make_key_vector(sentinel->right, rv);

	return rv;
}
//Copy constructor creates sentinel then uses assignment operator to copy tree
BSTree::BSTree(const BSTree &t)        
{
	sentinel = new BSTNode;
	sentinel->key = t.sentinel->key;
	sentinel->parent = NULL;
	sentinel->left = NULL;
	sentinel->right = NULL;
	sentinel->val = NULL;
	*this = t;
}
//gets vectors of ordered keys and vals and calls make_balanced_tree and returns pointer to itself
BSTree& BSTree::operator= (const BSTree &t) {
	vector<string> keys;
	vector<void *> vals;	
	
	keys = t.Ordered_Keys();
	vals =  t.Ordered_Vals();
	sentinel->right = make_balanced_tree(keys, vals, 0, t.size);
	size = t.size;
	return *this;
}
//Finds height of tree by doing a post order traversal on tree, comparing depths of each leaf node.
int BSTree::recursive_find_height(const BSTNode *n) const{	
	int height=0;
	int lheight, rheight;
	if(n==sentinel){return height;}
	if(n->left ==  sentinel && n->right == sentinel && n!=sentinel){return Depth(n->key)+1;}
	if(n->left == sentinel && n->right != sentinel){height = recursive_find_height(n->right);}
	if(n->left != sentinel && n->right == sentinel){height = recursive_find_height(n->left);}
	if(n->left != sentinel && n->right != sentinel){
		lheight = recursive_find_height(n->left);
		rheight = recursive_find_height(n->right);
		if(lheight > rheight){

			height = lheight;
		}else{
			height = rheight;
		}
	}
	return height;
}
//Makes sorted vector of keys by doing in order traversal of tree
void BSTree::make_key_vector(const BSTNode *n, vector<string> &v) const{	
	if(n->left ==  sentinel && n->right == sentinel && n!=sentinel){
		v.push_back(n->key);
		return;
	}
	if(n->left == sentinel && n->right != sentinel){
		v.push_back(n->key);
		make_key_vector(n->right,v);
	}
	if(n->left != sentinel && n->right == sentinel){
		make_key_vector(n->left,v);
		v.push_back(n->key);
	}
	if(n->left != sentinel && n->right != sentinel){
		make_key_vector(n->left,v);
		v.push_back(n->key);
		make_key_vector(n->right,v);
	}
}
//Recursively makes balanced tree by doing post order traversal and setting values
BSTNode *BSTree::make_balanced_tree(const vector<string> &sorted_keys, 
		const vector<void *> &vals,
		size_t first_index,
		size_t num_indices) const
{
	BSTNode *node =  new BSTNode;
	int index, half_indices;
//if the number of indicies is one, node has no children so sets values and sets children to sentinel and returns.
	if(num_indices == 1){
		node->key = sorted_keys[first_index];
		node->val = vals[first_index];
		node->left = sentinel;
		node->right =  sentinel;
		return node;
	}
	if(num_indices == 0){
		return sentinel;
	}
	half_indices = num_indices/2;
	index = first_index+half_indices;
	node->parent = sentinel;
//If the number of indices is odd, sets key, val, left, and right and sets children's parent to node
	if(num_indices%2==1){
		node->key = sorted_keys[index];
		node->val = vals[index];
		node->left = make_balanced_tree(sorted_keys, vals, first_index, half_indices);
		node->left->parent = node;
		node->right = make_balanced_tree(sorted_keys, vals, index+1, half_indices);
		node->right->parent = node;
//If the number of indices is even, sets key, val, left, and right and sets children's parent to node
	}else{
		node->key = sorted_keys[index];
		node->val = vals[index];
		node->left = make_balanced_tree(sorted_keys, vals, first_index, half_indices);
		node->left->parent = node;
		if(index-1 == 0){
			node-> right = sentinel;
			return node;
		}
		node->right = make_balanced_tree(sorted_keys, vals, index+1, half_indices-1);
		node->right->parent = node;
	}
	
	return node;
}
