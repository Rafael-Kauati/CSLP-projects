# Deliverable 4

<p align="center">
    <img src="https://github.com/Rafael-Kauati/CSLP-projects/blob/main/Projeto/Deliverable_4/ScreenShots/screenshot_greyscale_frame.png?raw=true" height="250px">
    <img src="https://github.com/Rafael-Kauati/CSLP-projects/blob/main/Projeto/Deliverable_4/ScreenShots/screenshot_rgb_frame.png?raw=true" height="250px">
    <img src="https://github.com/Rafael-Kauati/CSLP-projects/blob/main/Projeto/Deliverable_4/ScreenShots/screenshot_video.png?raw=true" height="250px">
</p>

## Description

This deliverable encompasses implementing a video codec based on the Golomg and BitStream deliverables previously developed

This codec relies on block based motion compensation and predictive coding, with a similar codec to the JPEG algorithms.

The final codec must be lossless and include all the required information to decode a file inside the binary file itself.

## File System

The tests are inside the root (of the deliverable).

- Input image/video files are stored inside the TestFiles/ folder.
- Binary files are stored inside the BinOutput/ folder.
- Output images/videos are stored inside the OutputFiles/ folder.
- Required classes are stored inside the Predictor/ and Golomb/ folders.

```
. # Deliverable 4
├── CMakeFiles
│
├── Golomb
│   ├── Golomb.cpp
│   ├── Golomb_Decoder.cpp
│   ├── Golomb_Decoder.hpp
│   ├── Golomb_Encoder.cpp
│   └── Golomb_Encoder.hpp
│
├── OutputFiles
│   ├── output.mp4
│   ├── output.png
│   └── outputRGB.png
│
├── Predictor
│   ├── BitStream.h
│   └── Frame_Predicter.h
│
├── ScreenShots
│   ├── screenshot_greyscale_frame.png
│   ├── screenshot_rgb_frame.png
│   └── screenshot_video.png
│
├── TestFiles
│   ├── ducks_30_frames.y4m
│   ├── tennis_sif.y4m
│   ├── testImage.png
│   └── testImageRGB.jpg
│
├── BinOutput
│   └── output.bin
│
├── CMakeLists.txt
├── README.md
└── unit_tests.cpp
```

## Code Components
#### Frame Predicter
The Frame predicter is the class that analyses and develops the final values used to encode the input frames.

This class also manages all other inner classes and guarantees they have all the values they need to fully work.


For encoding, the frame predicter accepts frames one by one and predicts the values of each pixel.

These values are then passed along to the Golomb encoder.


For decoding, the frame predictor calls the Golomb decoder which then promptly returns the values as needed.

The predicter then compares the value with the previous and assembles the decoded frame.


#### Golomb
The Golomb classes have two main functions: encode a number and decode a given number.

This encoding/decoding is then called multiple times by some set functions and all the required values to read or write are transmited to/from the BitStream class.

Our Golomb implementation takes into account negative numbers by transforming all into positive representations.

This means all encoded number are positive and even numbers are the equivalent to positive numbers, and odd numbers are equivalent to negative numbers.

Ex (encoded number, actual number) :
    -> 0 = 0
    -> 1 = -1
    -> 2 = 1
    -> 3 = -2
    -> 4 = 2
    ...

The algorithm used is:
```
if (number < 0) {
    encodedNumber = 2 x abs(number) - 1;
}
else {
    encodedNumber = 2 x abs(number);
}
```


#### BitStream
The Bistream is the class used to abstract single bit reads and writes to the final binary file.

It can read and write bits as needed and sequencially.


#### Unit Tests
The unit tests are seperated into three distinct groups:
    - Greyscale image
    - Colour (RGB or YUV) image
    - Colour video

All three do a complete check of the integrity of the final decoded file against all the pixels of the original files.

This file can also be used as a "template" for using our final video codec on other projects.


## How to test
Similar to the other deliverables, our unit tests can be run by:

1- Compiling the required files
```bash
# assuming you're in the program's dir
cmake . && make
```
2- Executing the unit tests
```bash
./unit_tests
```


## OPENCV Disclosure
In this code, we use openCV to manage videos and frames.

The OpenCV library converts YUV frames to RGB frames internaly, and while the option for maintaning YUV compatibility was once implemented, it was removed.

We must keep in mind that a lot of the large .bin files created by our supposed "compression" algorithm became twice as large as the original file largely due to this fact, and with some more time parts of our code should be rewritten to remove the need for OpenCV, so as to manipulate the input YUV videos manually.


## Variable Tests
To test which JPEG predictor we will use in our deliverable, we tested all of them with a YUV file of aproximatly 18.1MiB (19 008 946 Bytes), that has about 15 frames.

The tests evaluate time to encode and decode (in milliseconds) aswell as final binary file size.

    - JPEG  1: 
        -> time: 3279 / 8121
        -> size of bin: 29,9 MiB (31 302 247 Bytes)

    - JPEG  2:
        -> time: 3449 / 8187
        -> size of bin: 34,1 MiB (35 796 992 Bytes)

    - JPEG  3:
        -> time: 3429 / 13300
        -> size of bin: 37,0 MiB (38 819 772 Bytes)

    - JPEG  4:
        -> time: 3430 / 13310
        -> size of bin: 30,9 MiB (32 400 157 Bytes)

    - JPEG  5:
        -> time: 3509 / 8152
        -> size of bin: 29,0 MiB (30 375 371 Bytes)

    - JPEG  6:
        -> time: 3331 / 8163
        -> size of bin: 30,5 MiB (31 952 330 Bytes)

    - JPEG  7:
        -> time: 3157 / 8242
        -> size of bin: 29,5 MiB (30 890 049 Bytes)

    - JPEG LS:
        -> time: 3898 / 8354
        -> size of bin: 27,9 MiB (29 270 245 Bytes)

After this test, we concluded that we must try JPEG 1, 6 and LS with the final 4:4:4 YUV file.

We cut the file into a smaller 100 frame 266.0MiB size and tested them again:

    - JPEG  1: 
        -> time: 22 595 / 75 034
        -> size of bin: 180,2 MiB (188 974 064) Bytes)

    - JPEG  6:
        -> time: 29 791 / 76 355
        -> size of bin: 195,9 MiB (205 432 629 Bytes)

    - JPEG LS:
        -> time: 36 210 / 81 308
        -> size of bin: 181,2 MiB (189 956 886 Bytes)


## Parameters chosen
After the running previous tests, we started eliminating some of the codecs.


JPEG 2 and 3 took much more file size and are too biased on the file's contents to be viable.

JPEG 4, 5 and 7 is better but still depends too much on if the image is too complex.


JPEG 1 faired very well on our tests, but like the others the result is probably biased on the image, making the performance very unpredictable.

JPEG LS consumes less space on the disk compared to JPEG 6, but at a slightly larger performance loss.

This performance loss is enough for us to prefer JPEG 6, but if the application demanded more compression, JPEG LS would be a better alternative.

## Conclusions
Concluding these tests, we chose JPEG 6 for our implementation, with a good compression ratio without compromising performance by much.

These tests are using an Golomb M parameter of 8, since it gave us the best performance when tested on previous deliverables.
