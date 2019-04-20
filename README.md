# A Huffman compression program

A very simple Huffman compression program. If you compile it with full optimizations, it runs pretty quickly. It currently only supports only ASCII strings (so, a book), but it could be extended to support UTF-8 pretty easily. 

**Compression**: `huffman.exe source.txt target.hfmn`

**Decompression**: `huffman.exe --d source.hfmn target.txt`
