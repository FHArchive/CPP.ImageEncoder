/*
Kieran W / 2018
Image encoder
This program encodes text in a bitmap image (.bmp). It works by using LSB 
steganography which is the process of modifying the least significant bit 
of a pixel to store part of a character. 
*/

/*
I'm going to follow the google c++ style guide found at the following url 
https://google.github.io/styleguide/cppguide.html
I will also keep lines to 80 chars wide 
*/

/*
Header files to include 
*/
#include <iostream>
#include <string>
#include <sstream>

/*
Disable the security warning of using fopen().  
*/
#pragma warning(disable : 4996)

/*
Define application constants
*/
const int kHeaderSize = 1024;
const int kFooterSize = 1024;
const int kMaxSecretLen = 1024;
const std::string kCleanImageName = "CLEANa88a6a0c276fd853999a1faedf19c00e.bmp";

/*
Read image file in
*/
FILE* ReadImg(std::string image_name) {
	FILE * read_img =  fopen(image_name.c_str(), "rb");
	return read_img;
}

/*
Write image file 
*/
FILE* WriteImg(std::string image_name) {
	return fopen(image_name.c_str(), "wb");
}

/*
Get the size of the image in bytes to prevent overwriting footer
*/
int GetSize(std::string image_name) {
	struct stat image_details;
	int success = stat(image_name.c_str(), &image_details);
	return success == 0 ? image_details.st_size : -1;
}

/*
Clean the bitmap image so the sectret string can be written to 
*/
int WriteCleanImg(std::string input_image_name, std::string output_image_name){
	// Take the input image and get its size
	FILE* input_img = ReadImg(input_image_name);
	int input_img_size = GetSize(input_image_name);
	// Create/ overwrite the output image 
	FILE* output_image = WriteImg(output_image_name);
	// Copy the header
	for (int byte = 0; byte < kHeaderSize;
		byte++) {
		unsigned char head_buf;
		fread(&head_buf, 1, 1, input_img);
		fwrite(&head_buf, 1, 1, output_image);
	}
	// For the bytes not in the Header or Footer
	for (int byte = 0; byte < input_img_size - (kHeaderSize + kFooterSize);
		byte++ ){
		// Set the LSB to 0 and write it to the output image 
		unsigned char buffer;
		fread(&buffer, 1, 1, input_img);
		unsigned char buffer_to_write = buffer & 254;
		fwrite(&buffer_to_write, 1, 1, output_image);
	}
	// Copy the header
	for (int byte = 0; byte < kFooterSize;
		byte++) {
		unsigned char foot_buf;
		fread(&foot_buf, 1, 1, input_img);
		fwrite(&foot_buf, 1, 1, output_image);
	}
	// Return 0 for success
	return 0;
}

/*
Write a secret message to the image
*/
int WriteEncodedImg(std::string input_image_name, std::string output_image_name,
	std::string secret_msg) {
	// Take the input image and get its size
	FILE* input_img = ReadImg(input_image_name);
	int input_img_size = GetSize(input_image_name);
	// Create/ overwrite the output image 
	FILE* output_image = WriteImg(output_image_name);
	// Copy the header
	for (int byte = 0; byte < kHeaderSize;
		byte++) {
		unsigned char head_buf;
		fread(&head_buf, 1, 1, input_img);
		fwrite(&head_buf, 1, 1, output_image);
	}
	// Calculate the number of times the for loop needs to run 
	int secret_length = strnlen(secret_msg.c_str(), kMaxSecretLen);
	int secret_bytes = secret_length * 8;

	// For the bytes not in the Header or Footer
	for (int byte = 0; byte < secret_bytes;
		byte++) {
		// Read the byte from the input file
		unsigned char buffer;
		fread(&buffer, 1, 1, input_img);
		// Split the secret message up 
		unsigned char char_to_write = secret_msg[byte / 8];
		int bit = byte % 8;
		unsigned char lsb = (char_to_write >> bit) & 1;
		// Write the lsb to the output file 
		unsigned char buffer_to_write = buffer | lsb;
		fwrite(&buffer_to_write, 1, 1, output_image);
	}
	// Copy everything else
	for (int byte = 0; byte < input_img_size - (kHeaderSize + secret_bytes);
		byte++) {
		unsigned char foot_buf;
		fread(&foot_buf, 1, 1, input_img);
		fwrite(&foot_buf, 1, 1, output_image);
	}
	// Return 0 for success
	return 0;
}

/*
Read a secret from an image 
*/
int ReadEncodedImg(std::string input_image_name) {
	// Take the input image 
	FILE* input_img = ReadImg(input_image_name);
	// Skip the header
	for (int byte = 0; byte < kHeaderSize;
		byte++) {
		unsigned char head_buf;
		fread(&head_buf, 1, 1, input_img);
	}
	// Define the output to be printed 
	std::string secret_msg;
	for (int byte = 0; byte < kMaxSecretLen; byte++) {
		// For each secret_char in secret_msg
		unsigned char secret_char = 0;
		for (int bit = 0; bit < 8; bit++) {
			// For each bit in secret_char
			unsigned char lsb;
			// Read a byte 
			fread(&lsb, 1, 1, input_img);
			// Select the lsb and shift it to the correct position in secret_char
			lsb &= 1;
			secret_char += lsb << bit;
		}
		// Add each secret_char to secret_msg
		secret_msg += secret_char;
	}
	// Print the string and Return 0 for success
	std::cout << secret_msg;
	return 0;

}

/*
The user interface 
*/
int Cli() {
	std::cout << "Clean, Encode, Clean and Encode (.bmp only), Decode or Quit? ";
	std::cout << "(C, e, a, d, q) \n>";
	char choice;
	std::cin >> choice;
	if (choice > 90) {
		choice -= 32;
	}

	// Quit application 
	if (choice == 'Q') {
		return 1;
	}

	// All functions require the path to the input image
	std::cout << "Type the name of the input image (include the file extension ";
	std::cout << "and path if required) \n>";
	std::string input_image_name;
	std::cin >> input_image_name;

	std::string output_image_name;
	std::string secret_msg;

	// Some functions require additional parameters 
	if (choice != 'D') {
		std::cout << "Type the name of the output image (include the file extension ";
		std::cout << "and path if required) \n>";
		std::cin >> output_image_name;
	}
	if (choice == 'E' | choice == 'A') {
		std::cout << "Type the secret message (max " << kMaxSecretLen;
		std::cout << " characters) \n>";
		std::getline(std::cin, secret_msg);
	}

	// Run the required function for each choice
	switch (choice) {
	case 'E': WriteEncodedImg(input_image_name, output_image_name, secret_msg);
	case 'A': {
		WriteCleanImg(input_image_name, kCleanImageName);
		WriteEncodedImg(kCleanImageName, output_image_name, secret_msg);
	}
	case 'D': ReadEncodedImg(input_image_name);
	default: WriteCleanImg(input_image_name, output_image_name);
	}

	return 0;
}

/*
Run the CLI while the user has not finished
*/
int main()
{
	int finished = 0;
	while (!finished) {
		finished = Cli();
	}
}