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
			pqueue.push(new HuffmanNode(HuffmanPair(0, first->getDataRef().second + second->getDataRef().second),
				first, second));
		}
	}

	//Because we're returning a smart ptr to a class that manages its resources, the caller doesn't need to think about memory allocations.
	return HuffmanNodeSmartPtr(first);
}

CharMap HuffmanCoding::getHuffmanCharMap()
{
	return this->getHuffmanCharMap(*this->getHuffmanTree());
}

CharMap HuffmanCoding::getHuffmanCharMap(const HuffmanNode& tree)
{
	CharMap map;
	bitArray arr;
	//Scan the binary tree with our function
	HuffmanCoding::_scanBinaryTree(&tree, map, arr);
	return map;
}

bool HuffmanCoding::write(string filename)
{
	//[2 BYTES: Size of binary tree][Binary tree][Huffman data][1 BYTE: Bits filled in the last byte]

	uint16_t sizeOfTree = 0;
	uint8_t bitsFilled = 0;
	BufferedBitFile file(filename);
	std::ifstream fileToEncode(this->filename); //file to encode the contents of
	bool success = file.is_open() && fileToEncode.is_open();
	char currentChar = 0;
	
	//If both files could be opened
	if (success)
	{
		HuffmanNodeSmartPtr tree = this->getHuffmanTree();
		byteArray treeBytes = tree->serialize();
		CharMap map = this->getHuffmanCharMap(*tree);
		sizeOfTree = treeBytes.size();

		//Write the size of the tree
		file.write((byte*) &sizeOfTree, sizeof(uint16_t));
		file.write(treeBytes);

		//Go over chars and encode
		while (fileToEncode >> std::noskipws >> currentChar)
		{
			file.write(map[currentChar]);
		}

		bitsFilled = file.flush_and_fill(0);
		file.write((byte*)&bitsFilled, sizeof(uint8_t));
	}

	return success;
}

HuffmanPriorityQueue HuffmanCoding::getFrequencyQueue()
{
	//A sorted map to store our frequencies
	std::map<char, int> frequencyMap;
	//Input stream to read the file
	std::ifstream datafile(this->filename);
	char buffer[DEFAULT_BUFFER_SIZE] = { 0 };
	HuffmanPriorityQueue pqueue;
	char currentChar;

	//Make sure that we opened the file
	if (datafile.is_open())
	{
		//Iterate over the file char by char
		while (!datafile.eof())
		{
			datafile.read(buffer, DEFAULT_BUFFER_SIZE - 1);
			for (size_t i = 0; i < DEFAULT_BUFFER_SIZE - 1; i++)
			{
				frequencyMap[currentChar]++;
			}
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

	return pqueue;
}

//Pre-order scanning for the binary tree
void HuffmanCoding::_scanBinaryTree(HuffmanNode const* tree, CharMap & map, bitArray currentLocation)
{
	const HuffmanPair& nodeData = tree->getDataRef();
	if (nodeData.first != 0)
	{
		map[nodeData.first] = currentLocation;
	}
	
	//Scan left child
	if (tree->getLeftChild())
	{
		//Add a 0 to signify a left turn and send the bit vector, then pop it
		currentLocation.push_back(0);
		HuffmanCoding::_scanBinaryTree(tree->getLeftChild(), map, currentLocation);
		currentLocation.pop_back();
	}

	if (tree->getRightChild())
	{
		//Add a 1 to signify a right turn and then send the bit vector.
		//No need to pop it as it dies in the next line anyway.
		currentLocation.push_back(1);
		HuffmanCoding::_scanBinaryTree(tree->getRightChild(), map, currentLocation);
	}
}
