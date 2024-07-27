#pragma once
#include <string>

class rbNode
{
private:
	enum color_t { BLACK, RED };
	rbNode* parent;
	rbNode* left;
	rbNode* right;
	enum color_t colour;
	
public:
	rbNode* getParentNode(rbNode* n);
	rbNode* getGrandParentNode(rbNode* n);
	rbNode* getLeftOrRightNode(rbNode* n);
	rbNode* getUncleNode(rbNode* n);
	void rotateNodeLeft(rbNode* n);
	void rotateNodeRight(rbNode* n);
	rbNode* insertNewNode(rbNode* root, rbNode* n);
	void insertRecurse(rbNode* root, rbNode* n);
	//recolours tree logic
	void insertRBTRepair(rbNode* n);
	void insertRepairA(rbNode* n);
	void insertRepairB(rbNode* n);
	void insertRepairC(rbNode* n);
	void insertRepairD(rbNode* n);
	void insertRepairE(rbNode* n);
	//recolours tree logic
	int key; //node data / number 
	void printTop(std::string pad);
};