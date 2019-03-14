#include <iostream>
#include "HuffmanCoding.h"

int main()
{
	HuffmanCoding huffman("C:/Users/Nir/Documents/test.txt");
	HuffmanNodeSmartPtr node = huffman.getHuffmanTree();
	CharMap map = huffman.getHuffmanCharMap(*node);
	huffman.write("C:/Users/Nir/Documents/test.hfmn");
	return 0;
}