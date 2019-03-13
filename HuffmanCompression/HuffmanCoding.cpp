#include "HuffmanCoding.h"

HuffmanCoding::HuffmanCoding(string file)
{
	this->filename = file;
}

HuffmanNodeSmartPtr HuffmanCoding::getHuffmanTree()
{
	HuffmanNode* first = nullptr;
	HuffmanNode* second = nullptr;
	HuffmanPriorityQueue pqueue = this->getFrequencyQueue();
	HuffmanNode res;

	while (!pqueue.empty())
	{
		first = pqueue.top();
		pqueue.pop();
		if (!pqueue.empty())
		{
			second = pqueue.top();
			pqueue.pop();
			//Create a new huffman node with the combined frequencies
			pqueue.push(new HuffmanNode(HuffmanPair(0, first->getDataRef().getFrequency() + second->getDataRef().getFrequency()),
				first, second));
		}
		else
		{
			//Store our result as raw data
			res = *first;
			//Make sure to free up the memory because we're no longer dealing with those pointers
			delete first;
		}
	}

	//Because we're returning a smart ptr to a class that manages its resources, the caller doesn't need to think about memory allocations.
	return HuffmanNodeSmartPtr(first);
}

CharMap HuffmanCoding::getHuffmanCharMap()
{
	return this->getHuffmanCharMap(*this->getHuffmanTree());
}

CharMap HuffmanCoding::getHuffmanCharMap(HuffmanNode tree)
{
	CharMap map;
	BitArray arr;
	//Scan the binary tree with our function
	this->_scanBinaryTree(&tree, map, arr);
	return map;
}

HuffmanPriorityQueue HuffmanCoding::getFrequencyQueue()
{
	//A sorted map to store our frequencies
	std::map<char, int> frequencyMap;
	//Input stream to read the file
	std::ifstream datafile(this->filename);
	HuffmanPriorityQueue pqueue;
	char currentChar;

	//Make sure that we opened the file
	if (datafile.is_open())
	{
		//Iterate over the file, char by char, without skipping whitespace
		while (datafile >> std::noskipws >> currentChar)
		{
			frequencyMap[currentChar]++;
		}
	}
	else
	{
		//TODO: Replace with my own exception
		throw new std::exception();
	}

	for (auto pair: frequencyMap)
	{
		pqueue.push(new HuffmanNode(HuffmanPair(pair.first, pair.second)));
	}

	//Some temporary printing code
	/*while (!pqueue.empty())
	{
		std::cout << pqueue.top()->getDataRef().getData() << " : " << pqueue.top()->getDataRef().getFrequency() << std::endl;
		pqueue.pop();
	}*/

	return pqueue;
}

//Pre-order scanning for the binary tree
void HuffmanCoding::_scanBinaryTree(HuffmanNode* tree, CharMap & map, BitArray currentLocation)
{
	const HuffmanPair& nodeData = tree->getDataRef();
	if (nodeData.getData() != 0)
	{
		map[nodeData.getData()] = currentLocation;
	}
	
	//Scan left child
	if (tree->getLeftChild())
	{
		//Add a 0 to signify a left turn and send the bit vector, then pop it
		currentLocation.push_back(0);
		this->_scanBinaryTree(tree->getLeftChild(), map, currentLocation);
		currentLocation.pop_back();
	}

	if (tree->getRightChild())
	{
		//Add a 1 to signify a right turn and then send the bit vector.
		//No need to pop it as it dies in the next line anyway.
		currentLocation.push_back(1);
		this->_scanBinaryTree(tree->getRightChild(), map, currentLocation);
	}
}
