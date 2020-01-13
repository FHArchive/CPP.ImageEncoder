<p float="left">
<a href="../../"><img src="https://img.shields.io/github/languages/top/FredHappyface/CPP.ImageEncoder.svg?style=flat-square" alt="Github top language"></a>
<a href="https://www.codacy.com/manual/FredHappyface/CPP.ImageEncoder"><img src="https://img.shields.io/codacy/grade/d82e81ee345a4c74b42fd9f8b4f00e64.svg?style=flat-square" alt="Codacy grade"></a>
<a href="https://www.codacy.com/manual/FredHappyface/CPP.ImageEncoder"><img src="https://img.shields.io/codacy/coverage/d82e81ee345a4c74b42fd9f8b4f00e64.svg?style=flat-square" alt="Codacy coverage"></a>
<a href="../../"><img src="https://img.shields.io/github/repo-size/FredHappyface/CPP.ImageEncoder.svg?style=flat-square" alt="Repository size"></a>
<a href="../../issues"><img src="https://img.shields.io/github/issues/FredHappyface/CPP.ImageEncoder.svg?style=flat-square" alt="Issues"></a>
<a href="/LICENSE.md"><img src="https://img.shields.io/github/license/FredHappyface/CPP.ImageEncoder.svg?style=flat-square" alt="License"></a>
<a href="../../commits/master"><img src="https://img.shields.io/github/commit-activity/m/FredHappyface/CPP.ImageEncoder.svg?style=flat-square" alt="Commit activity"></a>
<a href="../../commits/master"><img src="https://img.shields.io/github/last-commit/FredHappyface/CPP.ImageEncoder.svg?style=flat-square" alt="Last commit"></a>
</p>

# CPP.ImageEncoder

<img src="readme-assets/icons/name.png" alt="Project Icon" width="750">

This program encodes text in a bitmap image (.bmp). It works by using LSB
steganography which is the process of modifying the least significant bit
of a pixel to store part of a character.


## Define application constants
The default values for kHeaderSize, kFooterSize and kMaxSecretLen are
1024. This can be changed with minimal impact on the program

- kHeaderSize
The minimum value that I would recommend setting this to would be 256.
After a quick look on Wikipedia, it looks like anywhere between 16 and
196 bytes are required for the header. Setting it at 256 or higher
seems safe.

- kFooterSize
It doesn't look like a bitmap has a footer. This was included for .jpg
images. Play around with it if you would like but there is certainly no
harm in leaving it at the default value

- kMaxSecretLen
This was included to stop the python version crashing. Though it has the
added benefit of outputting a reasonable amount of text to the screen.
Using larger values will decrease the speed of the program, and increase
the amount of text outputted but shouldn't have an adverse effect

- kCleanImageName
I've done an MD5 hash of "CLEAN" and appended it to the filename to reduce
the chance of overwriting an important file

## Functions
Read image file in
```cpp
FILE* ReadImg(std::string image_name)
```
Write image file
```cpp
FILE* WriteImg(std::string image_name)
```
Get the size of the image in bytes to prevent overwriting footer
```cpp
int GetSize(std::string image_name)
```
Replace the least significant bit with a 0
```cpp
int WriteCleanImg(std::string input_image_name, std::string output_image_name)
```
Write a secret message to the image
```cpp
int WriteEncodedImg(std::string input_image_name, std::string output_image_name,
	std::string secret_msg)
```
Read the encoded image
```cpp
int ReadEncodedImg(std::string input_image_name)
```
The CLI
```cpp
int Cli()
```

## Using the CLI
"Clean, Encode, Clean and Encode (.bmp only), Decode or Quit?
(C, e, a, d, q)"

- Entering 'c' will clean an image (specified by its path)
- Entering 'e' will encode an image (specified by its path)
- Entering 'a' will clean and encode an image (specified by its path)
- Entering 'd' will decode an image (specified by its path)
- Entering 'q' will quit the program

"Type the name of the input image (include the file extension
and path if required)"

- Enter the path to an input image

"Type the name of the output image (include the file extension
and path if required)"

- If the user selected Clean, Encode, or Clean and Encode. Enter
the path of an output image

"Type the secret message (max kMaxSecretLen characters)"

- If the user selected Encode, or Clean and Encode. Enter a message
for the program to encode in the image


## Language information
This program is written in C++ using Visual Studio Community Edition 2017
on Windows 10. To install this IDE, go to https://visualstudio.microsoft.com/
## How to run
### Method 1
1. Download or clone this GitHub repository
2. (If downloaded) Extract the zip archive
3. Open the project by going to File> Open> Project/Solution
4. Run the program by pressing the green play button or with F5
### Method 2
1. Download or clone this GitHub repository
2. (If downloaded) Extract the zip archive
3. Go to bin> Debug
4. Double click the .exe file (note that windows will ask if you want to
run the file – only run executables that you trust)


## Download
### Clone
#### Using The Command Line
1. Press the Clone or download button in the top right
2. Copy the URL (link)
3. Open the command line and change directory to where you wish to
clone to
4. Type 'git clone' followed by URL in step 2
```bash
$ git clone https://github.com/FredHappyface/CPP.ImageEncoder
```

More information can be found at
<https://help.github.com/en/articles/cloning-a-repository>

#### Using GitHub Desktop
1. Press the Clone or download button in the top right
2. Click open in desktop
3. Choose the path for where you want and click Clone

More information can be found at
<https://help.github.com/en/desktop/contributing-to-projects/cloning-a-repository-from-github-to-github-desktop>

### Download Zip File

1. Download this GitHub repository
2. Extract the zip archive
3. Copy/ move to the desired location


## Licence
MIT License
Copyright (c) FredHappyface
(See the [LICENSE](/LICENSE.md) for more information.)
