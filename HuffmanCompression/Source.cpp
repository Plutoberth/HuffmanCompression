#include <iostream>
#include "HuffmanCoding.h"

int main()
{
	HuffmanCoding huffman("C:/Users/Nir/Documents/test.txt");
	HuffmanNodeSmartPtr node = huffman.getHuffmanTree();
	CharMap map = huffman.getHuffmanCharMap(*node);
	BufferedBitFile file("C:/Users/Nir/Documents/bitdata.dat");
	file.write(node->serialize());
	return 0;
}