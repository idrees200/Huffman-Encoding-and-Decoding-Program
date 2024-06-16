# Huffman Encoding and Decoding Program

This C++ program implements Huffman encoding and decoding. It reads text from `input_huff.txt`, calculates character frequencies, constructs a Huffman tree, and encodes the text. It can also decode previously encoded text back to its original form.

## Features

- **Encoding**: Calculates character frequencies, constructs a Huffman tree, and encodes the text.
- **Decoding**: Decodes the encoded text back to its original form using the Huffman tree.
- **File Handling**: Supports reading from and writing to files (`input_huff.txt`, `encoded.txt`, `dd.txt`, `DECODEd.txt`, `textlen.txt`).

## Usage

1. **Compilation**: Compile the program using a C++ compiler.
2. **Input**: Place the text to be encoded in `input_huff.txt`.
3. **Encoding**: Run the program to encode the text and generate `encoded.txt`.
4. **Decoding**: Optionally choose to decode the encoded text by following the prompts.

## Files

- **main.cpp**: Contains the main program logic.
- **heap class**: Implements Huffman tree construction, encoding, and decoding methods.
- **input_huff.txt**: Input file containing text to be encoded.
- **encoded.txt**: Output file containing the encoded binary data.
- **dd.txt**: Temporary file storing Huffman tree data.
-
