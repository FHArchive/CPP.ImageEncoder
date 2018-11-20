# CPP.ImageEncoder
This program encodes text in a bitmap image (.bmp). It works by using LSB  steganography which is the process of modifying the least significant bit  of a pixel to store part of a character. 
# Language information 
This program is written in C++ using Visual Studio Community Edition 2017 on Windows 10. To install this IDE, go to https://visualstudio.microsoft.com/ 
# How to run 
## Method 1 
1. Download or clone this GitHub repository 
2. (If downloaded) Extract the zip archive
3. Open the project by going to File> Open> Project/Solution 
4. Run the program by pressing the green play button or with F5
## Method 2
1. Download or clone this GitHub repository 
2. (If downloaded) Extract the zip archive
3. Go to bin> Debug
4. Double click the .exe file (note that windows will ask if you want to run the file – only run executables that you trust)


# Define application constants
The default values for kHeaderSize, kFooterSize and kMaxSecretLen are 1024. This can be changed with minimal impact on the program

- kHeaderSize
The minimum value that I would recommend setting this to would be 256. After a quick look on Wikipedia, it looks like anywhere between 16 and 196 bytes are required for the header. Setting it at 256 or higher seems safe.

- kFooterSize
It doesn't look like a bitmap has a footer. This was included for .jpg images. Play around with it if you would like but there is certainly no harm in leaving it at the default value 

- kMaxSecretLen
This was included to stop the python version crashing. Though it has the added benefit of outputting a reasonable amount of text to the screen. Using larger values will decrease the speed of the program, and increase the amount of text outputted but shouldn't have an adverse effect

- kCleanImageName
I've done an MD5 hash of "CLEAN" and appended it to the filename to reduce the chance of overwriting an important file

# Functions 
Read image file in 
```
FILE* ReadImg(std::string image_name)
```
Write image file  
```
FILE* WriteImg(std::string image_name) 
```
Get the size of the image in bytes to prevent overwriting footer
```
int GetSize(std::string image_name) 
```
Replace the least significant bit with a 0 
```
int WriteCleanImg(std::string input_image_name, std::string output_image_name)
```
Write a secret message to the image 
```
int WriteEncodedImg(std::string input_image_name, std::string output_image_name,
	std::string secret_msg)
```
Read the encoded image 
```
int ReadEncodedImg(std::string input_image_name) 
```
The CLI
```
int Cli()
```

# Using the GUI 
"Clean, Encode, Clean and Encode (.bmp only), Decode or Quit? (C, e, a, d, q)"

- Entering 'c' will clean an image (specified by its path)
- Entering 'e' will encode an image (specified by its path)
- Entering 'a' will clean and encode an image (specified by its path)
- Entering 'd' will decode an image (specified by its path)
- Entering 'q' will quit the program 

"Type the name of the input image (include the file extension and path if required)"

- Enter the path to an input image 

"Type the name of the output image (include the file extension and path if required)"

- If the user selected Clean, Encode, or Clean and Encode. Enter the path of an output image 
   
"Type the secret message (max kMaxSecretLen characters)"

- If the user selected Encode, or Clean and Encode. Enter a message for the program to encode in the image  
