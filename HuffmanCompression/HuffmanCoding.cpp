#include "HuffmanCoding.h"

HuffmanNodeSmartPtr HuffmanCoding::_getHuffmanTree(string filename)
{
	HuffmanNode* first = nullptr;
	HuffmanNode* second = nullptr;
	HuffmanPriorityQueue pqueue = HuffmanCoding::_getFrequencyQueue(filename);
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

CharMap HuffmanCoding::_getHuffmanCharMap(const HuffmanNode& tree)
{
	CharMap map;
	//Scan the binary tree with our function
	HuffmanCoding::_scanBinaryTree(&tree, map);
	return map;
}

bool HuffmanCoding::compress(string source, string target)
{
	//[2 BYTES: Size of binary tree][Binary tree][1 BYTE: Excess bits in the last byte][Huffman data]

	uint16_t sizeOfTree = 0;
	uint8_t bitsFilled = 0;
	BufferedBitFile encodedFile(target);
	std::ifstream fileToEncode(source); //file to encode the contents of
	bool success = encodedFile.is_open() && fileToEncode.is_open();
	char buffer[DEFAULT_BUFFER_SIZE] = { 0 };
	
	//If both files could be opened
	if (success)
	{
		HuffmanNodeSmartPtr tree = HuffmanCoding::_getHuffmanTree(source);
		byteArray treeBytes = tree->serialize();
		CharMap map = HuffmanCoding::_getHuffmanCharMap(*tree);
		uint64_t excessBitsLoc = 0;
		sizeOfTree = static_cast<uint16_t>(treeBytes.size());

		//Write the size of the tree
		encodedFile.write((byte*) &sizeOfTree, sizeof(sizeOfTree));
		encodedFile.write(treeBytes);
		encodedFile.flush();
		excessBitsLoc = encodedFile.tellp();
		encodedFile.seekp(excessBitsLoc + 1);

		//Go over chars and encode
		while (!fileToEncode.eof())
		{
			memset(buffer, NULL, DEFAULT_BUFFER_SIZE);
			fileToEncode.read(buffer, DEFAULT_BUFFER_SIZE - 1);
			for (size_t i = 0; buffer[i] != NULL; i++)
			{
				encodedFile.write(map[buffer[i]]);
			}
		}

		bitsFilled = encodedFile.flush_and_fill(0);
		encodedFile.seekp(excessBitsLoc);
		encodedFile.write((byte*)&bitsFilled, sizeof(bitsFilled));
	}

	return success;
}

bool HuffmanCoding::decompress(string source, string target)
{
	int numBits = 0;
	uint8_t excessBits = 0;
	HuffmanNode tree;
	HuffmanNode* currentNode = &tree;
	std::ifstream fileToDecode(source, std::ios::binary);
	//Treat newlines as regular bytes
	fileToDecode.unsetf(std::ios::skipws);

	std::ofstream decompressedFile(target);

	bool success = fileToDecode.is_open() && decompressedFile.is_open();

	if (success)
	{
		{
			uint16_t sizeOfTree = 0;
			byteArray treeBytes = {};
			fileToDecode.read(reinterpret_cast<char*>(&sizeOfTree), sizeof(sizeOfTree));
			//Use resize and not reserve as vector.data() only guarantees that [vector.data() + vector.size()] is a valid range, not [vector.data() + vector.capacity()]
			treeBytes.resize(sizeOfTree);
			fileToDecode.read(reinterpret_cast<char*>(treeBytes.data()), sizeOfTree);
			//Initialize the tree with the needed bytes
			tree = HuffmanNode(treeBytes);
		}

HuffmanPriorityQueue HuffmanCoding::_getFrequencyQueue(string filename)
{
	//A sorted map to store our frequencies
	std::map<char, int> frequencyMap;
	//Input stream to read the file
	std::ifstream datafile(filename);
	char buffer[DEFAULT_BUFFER_SIZE] = { 0 };
	HuffmanPriorityQueue pqueue;

	//Make sure that we opened the file
	if (datafile.is_open())
	{
		//Iterate over the file char by char
		while (!datafile.eof())
		{
			memset(buffer, NULL, DEFAULT_BUFFER_SIZE);
			datafile.read(buffer, DEFAULT_BUFFER_SIZE - 1);
			for (size_t i = 0; buffer[i] != NULL; i++)
			{
				frequencyMap[buffer[i]]++;
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
		pqueue.push(new HuffmanNode(pair));
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
		//Add a 0 to signify a left turn and send the bit vector, then pop it because the function came back
		currentLocation.push_back(0);
		HuffmanCoding::_scanBinaryTree(tree->getLeftChild(), map, currentLocation);
		currentLocation.pop_back();
	}

	if (tree->getRightChild())
	{
		//1 marks a right turn in our encoding
		currentLocation.push_back(1);
		HuffmanCoding::_scanBinaryTree(tree->getRightChild(), map, currentLocation);
	}
}
