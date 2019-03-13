#include <iostream>
#include "HuffmanCoding.h"

int main()
{
	HuffmanCoding huffman("C:/Users/Nir/Documents/test.txt");
	HuffmanNodeSmartPtr node = huffman.getHuffmanTree();
	node->serialize("C:/Users/Nir/Documents/serializetest.dat");
	return 0;
}