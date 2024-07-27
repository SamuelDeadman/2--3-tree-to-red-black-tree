#include "rbNode.h"
#include <cassert> // used for assert
#include <stdio.h>


void rbNode::printTop(std::string pad)
{
	printf("%s%08d\n", pad.c_str(), key);
	pad = pad + "--------";
	if (left != nullptr) 
	{
		printf("LEFT: ");
		left->printTop(pad);
	}
	if (right != nullptr) 
	{
		printf("RIGHT:");
		right->printTop(pad);
	}
}

rbNode* rbNode::getParentNode(rbNode* l_node) // l_node = local node (local ie local to the function)
{
	//the roots node's parent is null
	return l_node == nullptr ? nullptr : l_node->parent;
}

rbNode* rbNode::getGrandParentNode(rbNode* l_node)
{
	//simimal to GetParent this will return null for node and childen of node.
	return getParentNode(getParentNode(l_node));
}

rbNode* rbNode::getLeftOrRightNode(rbNode* l_node)
{
	rbNode* s = getParentNode(l_node); // s ie Sibling

	// no parent means no sibling.
	if (s == nullptr) 
	{
		return nullptr;
	}

	if (l_node == s->left)
	{
		return s->right;
	}
	else 
	{
		return s->left;
	}
}

rbNode* rbNode::getUncleNode(rbNode* l_node)
{
	rbNode* u = getParentNode(l_node); //u ie uncle

	// No parent means no uncle
	return getLeftOrRightNode(u);
}

void rbNode::rotateNodeLeft(rbNode* l_node)
{
	rbNode* nnewr = l_node->right;  // nnewr ie Node NEW Right
	rbNode* nodep = getParentNode(l_node);
	assert(nnewr != nullptr);  // as the leaves of a red-black tree are null,

	//moves the nodes and children around 				   
	l_node->right = nnewr->left;
	nnewr->left = l_node;
	l_node->parent = nnewr;
	if (l_node->right != nullptr) 
	{
		l_node->right->parent = l_node;
	}

	if (nodep != nullptr)
	{
		if (l_node == nodep->left)
		{
			nodep->left = nnewr;
		}
		else if (l_node == nodep->right)
		{
			nodep->right = nnewr;
		}
	}
	//ends by seeting the new right node's parent to p
	nnewr->parent = nodep;
}

void rbNode::rotateNodeRight(rbNode* l_node) // a copy of RotateLeft but for right
{
	rbNode* nnewl = l_node->left; // nnewr ie Node NEW Left
	rbNode* nodep = getParentNode(l_node);
	assert(nnewl != nullptr);  // as the leaves of a red-black tree are null,
							  
	//moves the nodes and children around
	l_node->left = nnewl->right;
	nnewl->right = l_node;
	l_node->parent = nnewl;
	if (l_node->left != nullptr)
	{
		l_node->left->parent = l_node;
	}

	if (nodep != nullptr) {
		if (l_node == nodep->left)
		{
			nodep->left = nnewl;
		}
		else if (l_node == nodep->right)
		{
			nodep->right = nnewl;
		}
	}
	//ends by seeting the new right node's parent to p
	nnewl->parent = nodep;
}

rbNode* rbNode::insertNewNode(rbNode* l_root, rbNode* n)
{
	// inserts new Node
	insertRecurse(l_root, n);

	// repair the colour rules of the red-black
	insertRBTRepair(n);

	// finds new root
	l_root = n;
	while (getParentNode(l_root) != nullptr)
	{
		l_root = getParentNode(l_root);
	}
	return l_root;
}

void rbNode::insertRecurse(rbNode* l_root, rbNode* n)
{
	// descend to find a leaf
	if (l_root != nullptr)
	{
		if (n->key < l_root->key) 
		{
			if (l_root->left != nullptr) // null pointer means weve found a leaf 
			{
				insertRecurse(l_root->left, n);
				return;
			}
			else 
			{
				l_root->left = n;
			}
		}
		else 
		{ // n->key >= root->key
			if (l_root->right != nullptr) 
			{
				insertRecurse(l_root->right, n);
				return;
			}
			else 
			{
				l_root->right = n;
			}
		}
	}

	// insert new Node n.
	n->parent = l_root;
	n->left = nullptr;
	n->right = nullptr;
	n->colour = RED; //visualt studio compilation issue i think not logic error
}

void rbNode::insertRBTRepair(rbNode* l_root)
{
	if (getParentNode(l_root) == nullptr)
	{
		//if node has null parent then its the route and so it black following RBtree rules
		insertRepairA(l_root);
	}
	else if (getParentNode(l_root)->colour == BLACK)
	{
		insertRepairB(l_root);
	}
	else if (getUncleNode(l_root) != nullptr && getUncleNode(l_root)->colour == RED)
	{
		insertRepairC(l_root);
	}
	else 
	{
		insertRepairD(l_root);
	}
}

void rbNode::insertRepairA(rbNode* l_root)
{
	//if node has null parent then its the route and so it black following RBtree rules
	l_root->colour = BLACK;
}

void rbNode::insertRepairB(rbNode* l_root)
{
	// do nothing
	return;
}

void rbNode::insertRepairC(rbNode* l_root)
{
	getParentNode(l_root)->colour = BLACK;
	getUncleNode(l_root)->colour = BLACK;
	getGrandParentNode(l_root)->colour = RED;
	insertRBTRepair(getGrandParentNode(l_root));
}

void rbNode::insertRepairD(rbNode* l_root)
{
	rbNode* nodep = getParentNode(l_root);
	rbNode* nodeg = getGrandParentNode(l_root);

	if (l_root == nodep->right && nodep == nodeg->left)
	{
		rotateNodeLeft(nodep);
		l_root = l_root->left;
	}
	else if (l_root == nodep->left && nodep == nodeg->right)
	{
		rotateNodeRight(nodep);
		l_root = l_root->right;
	}

	insertRepairE(l_root);
}

void rbNode::insertRepairE(rbNode* l_root)
{
	rbNode* nodep = getParentNode(l_root);
	rbNode* nodeg = getGrandParentNode(l_root);

	if (l_root == nodep->left)
	{
		rotateNodeRight(nodeg);
	}
	else 
	{
		rotateNodeLeft(nodeg);
	}
	nodep->colour = BLACK;
	nodeg->colour = RED;
}