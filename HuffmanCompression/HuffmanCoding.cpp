#include "HuffmanCoding.h"

HuffmanCoding::HuffmanCoding(string file)
{
	this->filename = file;
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
		pqueue.push(HuffmanNode(HuffmanPair(pair.first, pair.second)));
	}

	//Some temporary printing code
	/*while (!pqueue.empty())
	{
		std::cout << pqueue.top().getData().getData() << " : " << pqueue.top().getData().getFrequency() << std::endl;
		pqueue.pop();
	}*/

	return pqueue;
}
