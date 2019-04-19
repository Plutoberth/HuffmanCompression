#include <iostream>
#include "HuffmanCoding.h"

int main()
{
	bool compressedSuccessfully = HuffmanCoding::compress("D:/test.txt", "D:/Compressed.hfmn");
	if (compressedSuccessfully)
	{
		HuffmanCoding::decompress("D:/Compressed.hfmn", "D:/Decompressed.txt");
	}
	return compressedSuccessfully;
}