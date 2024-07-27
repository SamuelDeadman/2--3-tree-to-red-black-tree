// algorithums_Q3.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "rbNode.h" //RED BLACK node class as specified in requirments

void test1(); // prototype - start version of input NOT USED

//Q3 Heap Sort Algorithm Sam Deadman

int main()
{
	//user guide starts
    std::cout << "How to Insert a 2-3 Tree\n";
	std::cout << "First Value you insert will be the starting Node\n\n";
	std::cout << "How to Insert a Node with 1 value  | Insert as following 'Data1'         RETURN\n";
	std::cout << "How to Insert a Node with 2 values | Insert as following 'Data1','Data2' RETURN\n";
	std::cout << "'CTRL + D' to end insert\n\n";
	//user guide ends
	//creates 'empty' node class
	rbNode* r = nullptr;
	int rc, a, b = 0;
	//max size of input (onyl allowing a node with 1 or 2 data points)
	rc = 2;
	bool start = false;
	while (rc > 0) { // 0 or -1 = error 
		rc = scanf_s("%d,%d", &a, &b);
		if (rc > 0)
		{
			if (rc > 0 && start == true)//if initaliszed add a, the first data value
			{
				printf("Inserting: %d\n", a);

				rbNode* n = new rbNode();
				n->key = a; // key = data / value / node
				r = r->insertNewNode(r, n);
			}

			if (start == false)//if not initaliszed initalisze with value a
			{
				printf("Inserting Route: %d\n", a);

				r = new rbNode();
				r->key = a; // default root
				start = true;
			}

			if (rc == 2) {
				printf("Inserting: %d\n", b); //add b, second data value

				rbNode* n = new rbNode();
				n->key = b;
				r = r->insertNewNode(r, n);
			}
		}
	}
	//used to represent the depth of the Red Black tree
	r->printTop("--------");

	printf("Output ends \n");
	printf("Output is the corrosponding Red - Black tree from the 2-3 tree data you have input\n\n");

	printf("output format .... \n");
	printf("Left / right showsn the relation to parent nodes     | The left or Right of the Above Node\n");
	printf("With depth of node shown vial the '--------' offsets | The more - the deeper the node\n\n");
	printf("Program ends");
	//end
}

void test1() //start version of input NOT USED
{ 
	rbNode* r = new rbNode();
	r->key = 1;
	int i = 2;
	while (i < 10)
	{
		rbNode* n = new rbNode();

		n->key = i;
		r = r->insertNewNode(r, n);
		i++;
		printf("in rbt %d \n", i);
	}
	r->printTop("--------");
} //start version of input NOT USED

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
