#include <iostream>
#include "HuffmanCoding.h"

#define DECOMPRESS_FLAG "--d"

#define COMPRESSION_SOURCE 1
#define COMPRESSION_TARGET 2

#define DECOMPRESSION_SOURCE 2
#define DECOMPRESSION_TARGET 3

void printUsage(char* programName)
{
	std::cout << "Usage: " << programName << " [" <<  DECOMPRESS_FLAG << "] (source) (target)" << std::endl;
}

int main(int argc, char* argv[])
{
	//This is obviously extremely simplistic, but it's not the point of the program
	bool failed = false;
	if (argc == 4)
	{
		if (string(argv[1]) == DECOMPRESS_FLAG)
		{
			if (HuffmanCoding::decompress(argv[DECOMPRESSION_SOURCE], argv[DECOMPRESSION_TARGET]))
			{
				std::cout << "Unpacked `" << argv[DECOMPRESSION_SOURCE] << "` --> `" << argv[DECOMPRESSION_TARGET] << "`" << std::endl;
			}
			else
			{
				std::cout << "I failed to decompress `" << argv[DECOMPRESSION_SOURCE] << "` into `" << argv[DECOMPRESSION_TARGET] << "`." << std::endl;
				std::remove(argv[DECOMPRESSION_TARGET]);
				failed = true;
			}
		}
		else
		{
			printUsage(argv[0]);
		}
	}
	else if (argc == 3)
	{
		if (HuffmanCoding::compress(argv[COMPRESSION_SOURCE], argv[COMPRESSION_TARGET]))
		{
			std::cout << "Packed `" << argv[COMPRESSION_SOURCE] << "` --> `" << argv[COMPRESSION_TARGET] << "`" << std::endl;
		}
		else
		{
			std::cout << "I failed to compress `" << argv[COMPRESSION_SOURCE] << "` into `" << argv[COMPRESSION_TARGET] << "`." << std::endl;
			std::remove(argv[COMPRESSION_TARGET]);
			failed = true;
		}
	}
	else //Incorrect number of parameters
	{
		printUsage(argv[0]);
		failed = true;
	}

	return failed;
}