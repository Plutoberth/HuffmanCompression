#include "HuffmanCoding.h"

HuffmanCoding::HuffmanCoding(string file)
{
	this->filename = file;
}

HuffmanNode HuffmanCoding::getHuffmanTree()
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

	return res;
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
