#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include "avltree.hpp"
using namespace std;
using CS202::AVLTree;
using CS202::AVLNode;

void rotate (AVLNode *n);
bool imbalance(const AVLNode *n);
void fix_height(AVLNode *n);
void fix_imbalance(AVLNode *n);
//detects if node is imbalanced based on heights of children
bool imbalance(const AVLNode *n){
	int h1, h2,tmp;
	h1 = n->left->height;
	h2 = n->right->height;

	if(h2 > h1){
		tmp = h2;
		h2=h1;
		h1 = tmp;
	}
	if(h1-h2 ==1 || h1 == h2){
		return false;
	}
	return true;
}
//Rotates node and fixes heights
void rotate(AVLNode *n){
	AVLNode *parent;
	AVLNode *grandparent;
	AVLNode *tmp;
	if(n->height == 0) return;
	if(n->parent->height == 0) return;
	parent = n->parent;
	grandparent = parent->parent;
	if(parent->left == n){
		 n->right->parent = parent;
		parent->left = n->right;
		n->parent = grandparent;
		parent->parent = n;
		n->right = parent;
		if(grandparent->left == parent){
			grandparent->left = n;
		}else{
			grandparent->right = n;
		}
	}else{
		n->left->parent = parent; 
		parent->right = n->left;
		n->parent = grandparent;
		parent->parent = n;

		n->left = parent;
		if(grandparent->left == parent){
			grandparent->left = n;
		}else{
			grandparent->right = n;
		}
	}
		tmp = parent;
		fix_height(tmp);	
		while(tmp->parent->height != 0 &&(tmp->parent->height == tmp->parent->left->height+1|| tmp->parent->height == tmp->parent->right->height+1)){
			fix_height(tmp->parent);
			tmp = tmp->parent;
		}

}
//sets height of node to 1 + greatest height of child node
void fix_height(AVLNode *n){
	size_t height;
	if(n->height == 0) return;
	if(n->left->height == 0 && n->right->height == 0){
		n->height = 1;
		return;
	}
	height = n->left->height;
	if(n->right->height > height){
		height = n->right->height;
	}
	n->height = height+1;
}
//Detects type of imbalance and does rotations based on imbalance.
void fix_imbalance(AVLNode *n){
	AVLNode *child;
	AVLNode *grandchild;
	if(n->left->height > n->right->height){
			child = n->left;
			if(child->left->height >= child->right->height){
				//Left Zig Zig
				rotate(child);
			}else{
		//Left Zig Zag
				grandchild = child->right;
				rotate(grandchild);
				rotate(grandchild);
			}
		}else{
			child = n->right;
			if(child->right->height >= child->left->height){
				//Right Zig Zig;
				rotate(child);
			}else{
				//Right Zig-Zag
				grandchild = child->left;
				rotate(grandchild);
				rotate(grandchild);
			}
		}

}
//Assignment overload calls recursive_postorder_copy which returns root node of new tree.
AVLTree& AVLTree::operator= (const AVLTree &t)        
{
	sentinel->height = 0;
	this->sentinel->right = recursive_postorder_copy(t.sentinel->right);
	sentinel->right->parent = sentinel;
	this->size = t.size;
	return *this;
}

/* I simply took Insert and Delete from their binary search tree
   implementations.  They aren't correct for AVL trees, but they are
   good starting points.  */
//Inserts node into tree and rebalances if needed
bool AVLTree::Insert(const string &key, void *val)
{
	AVLNode *parent;
	AVLNode *n;
	AVLNode *tmpPar;
	AVLNode *tmpNode;
	size_t height;

	parent = sentinel;
	n = sentinel->right;
	/* Find where the key should go.  If you find the key, return false. */
	height = 1;
	while (n != sentinel) {
		if (n->key == key) return false;
		parent = n;
		n = (key < n->key) ? n->left : n->right;
		height++;
	}

	/* At this point, parent is the node that will be the parent of the new node.
	   Create the new node, and hook it in. */

	n = new AVLNode;
	n->key = key;
	n->val = val;
	n->parent = parent;
	n->height = 1;
	n->left = sentinel;
	n->right = sentinel;
	/* Use the correct pointer in the parent to point to the new node. */

	if (parent == sentinel) {
		sentinel->right = n;
	} else if (key < parent->key) {
		parent->left = n;
	} else {
		parent->right = n;
	}
	tmpPar= parent;
	tmpNode = n;
	while(tmpPar->height < tmpNode->height+1&& tmpPar !=sentinel){
		if(imbalance(tmpPar)) fix_imbalance(tmpPar);
		fix_height(tmpPar);
		tmpNode = tmpPar;
		tmpPar = tmpPar->parent;
	}


	/* Increment the size */
	size++;
	return true;
}
//Deletes node from tree and rebalances if needed.
bool AVLTree::Delete(const string &key)
{
	AVLNode *n, *parent, *mlc, *tmpNode;
	string tmpkey;
	void *tmpval;
	/* Try to find the key -- if you can't return false. */
	n = sentinel->right;
	while (n != sentinel && key != n->key) {
		n = (key < n->key) ? n->left : n->right;
	}
	if (n == sentinel) return false;

	/* We go through the three cases for deletion, although it's a little
	   different from the canonical explanation. */

	parent = n->parent;

	/* Case 1 - I have no left child.  Replace me with my right child.
	   Note that this handles the case of having no children, too. */

	if (n->left == sentinel) {
		if (n == parent->left) {
			parent->left = n->right;
		} else {
			parent->right = n->right;
		}
		if (n->right != sentinel) n->right->parent = parent;
		delete n;
		size--;

		/* Case 2 - I have no right child.  Replace me with my left child. */

	} else if (n->right == sentinel) {
		if (n == parent->left) {
			parent->left = n->left;
		} else {
			parent->right = n->left;
		}
		n->left->parent = parent;
		delete n;
		size--;

		/* If I have two children, then find the node "before" me in the tree.
		   That node will have no right child, so I can recursively delete it.
		   When I'm done, I'll replace the key and val of n with the key and
		   val of the deleted node.  You'll note that the recursive call 
		   updates the size, so you don't have to do it here. */

	} else {
		for (mlc = n->left; mlc->right != sentinel; mlc = mlc->right) ;
		tmpkey = mlc->key;
		tmpval = mlc->val;
		Delete(tmpkey);
		n->key = tmpkey;
		n->val = tmpval;
		tmpNode = parent;
		while(tmpNode != sentinel){
			if(imbalance(tmpNode)) fix_imbalance(tmpNode);
			tmpNode =  tmpNode->parent;
		}
		return true;
	}
	tmpNode = parent;
		while(tmpNode != sentinel){
			if(imbalance(tmpNode)){
				fix_imbalance(tmpNode);
			}else{
				fix_height(tmpNode);
			}
			tmpNode =  tmpNode->parent;
		}
	return true;
}


//Creates sorted vector of keys by calling make_key_vector
vector <string> AVLTree::Ordered_Keys() const{
	vector<string> rv;
	make_key_vector(sentinel->right, rv);
	return rv;
}
//Makes vector of keys
void AVLTree::make_key_vector(const AVLNode *n, vector<string> &v) const
{	
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
//Returns height of tree by returning height of root node
size_t AVLTree::Height() const{
	return sentinel->right->height;
}

/* You need to write this to help you with the assignment overload.
   It makes a copy of the subtree rooted by n.  That subtree is part
   of a different tree -- the copy will be part of the tree that
   is calling the method. */
//recursive helper for assignment overload. recursivley sets children of node and parents of children and copies values.
AVLNode *AVLTree::recursive_postorder_copy(const AVLNode *n) const{
	AVLNode *node = new AVLNode;
	node->height = n->height;
	node->key = n->key;
	node->val = n->val;
	if(n->height == 0) return sentinel;
	if(n->left->height == 0){
		node->left = sentinel;
	}
	if( n->right->height == 0){
		node->right = sentinel;
	}
	if(n->left->height != 0){
		node->left = recursive_postorder_copy(n->left);
		node->left->parent = node; 
	}
	if(n->right->height != 0){
		node->right = recursive_postorder_copy(n->right);
		node->right->parent = node;
	}

	return node;
}
