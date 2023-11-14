# CSLP - Projects
### Our projects for the CSLP class of 2023/2024
---

<p align="center">
    <img src="https://i.imgur.com/dEcZSls.png" height="300px">
</p>

&nbsp;

[![All Contributors](https://img.shields.io/badge/Contributors-3-brightgreen.svg?style=for-the-badge)](#contributors-)
[![PRs Welcome](https://img.shields.io/badge/Completed%20Deliverables-Del%201-orange.svg?style=for-the-badge)](http://makeapullrequest.com)
[![PRs Welcome](https://img.shields.io/badge/Current%20Deliverables-Del%202%20and%203-blue.svg?style=for-the-badge)](http://makeapullrequest.com)

## Project Structure
```
. # <- root
├── clean.sh
├── doxy-clean.sh
├── Examples_cpp
│   ├── classes-test.cpp
│   ├── hello_world.cpp
│   ├── README.md
│   ├── vectors.cpp
│   └── vectors.out
├── Projeto
│   ├── Deliverable_1
│   │   ├── deliverable-1-enunciado.txt
│   │   ├── Program_1
│   │   │   ├── CMakeLists.txt
│   │   │   ├── copy_images
│   │   │   ├── copy_images.cpp
│   │   │   ├── inpImg.jpg
│   │   │   └── outImg.jpg
│   │   ├── Program_3
│   │   │   ├── auto-cmake.sh
│   │   │   ├── CMakeLists.txt
│   │   │   ├── imgs
│   │   │   │   ├── ...
│   │   │   ├── kodak
│   │   │   │   ├── ...
│   │   │   ├── main
│   │   │   ├── main.cpp
│   │   │   └── vid.mp4
│   │   └── Video-Player
│   │       ├── 20230912_140658.mp4
│   │       ├── CMakeLists.txt
│   │       ├── main
│   │       ├── main.cpp
│   │       ├── run-video-player.sh
│   │       └── VideoPlayer.hpp
│   ├── Deliverable_2
│   │   ├── Program_4
│   │   │   ├── BitStream.h
│   │   │   └── test.txt
│   │   └── Program_5
│   │       ├── CMakeLists.txt
│   │       ├── main
│   │       ├── main.cpp
│   │       ├── Makefile
│   │       ├── resources
│   │       │   ├── ...
│   │       ├── tests
│   │       │   ├── Makefile
│   │       │   ├── output.bin
│   │       │   ├── unit_tests.cpp
│   │       │   └── unit_tests.out
│   │       └── unit_tests
│   ├── Deliverable_3
│   │   ├── Program_6
│   │   │   ├── clean.sh
│   │   │   ├── Golomb_Decoder.cpp
│   │   │   ├── GolombDecoder.hpp
│   │   │   ├── GolombEncoder.hpp
│   │   │   ├── Golomb_Enconder.cpp
│   │   │   └── Golomb_Param.h
│   │   └── Program_7
│   │       ├── CMakeLists.txt
│   │       ├── GolombCodingTests
│   │       ├── tests
│   │       │   └── unit_tests.cpp
│   │       └── unit_tests
│   └── Doxyfile
├── README.md
└── week_01
    └── topics.md
```

## Documentation

Created by [Doxygen](https://www.doxygen.nl/) and available inside every Deliverable's folder 

### To read the Doxygen Documentation:
```bash
# assuming you're in the repository's root
cd Project
doxygen Doxyfile
firefox ../docs/html/index.html
```
**Run each command separately** to avoid errors.

### To compile the programs:
```bash
# assuming you're in the repository's root
cd Projeto/Deliverable_X/Program_Y
cmake . && make
./programName
```

### To run the unit tests:
Only some Programs, such as `Program_5` and `Program_7`, have unit tests!
Make sure you are inside the program's directory before you run the script!
```bash
# assuming you're in the program's dir
./unit_tests
```
### To clean genereated files:
After running and testing our programs you can use `clean.sh` to clean cmake auto generated file:
```bash
# assuming you're in the repository's root
./clean.sh
```
If you want to clean doxygen auto generated documentation you can run the `doxy-clean.sh` script:
```bash
# assuming you're in the repository's root
./doxy-clean.sh
```

> **NOTE**
> If the clean scripts do not work for you try give them execute permission by running:
> ```bash
> chmod u+x <clean.sh || doxy-clean.sh> 
>```
>_

## Other stuff

Deliverables 2 and 3 have unit tests in CATCH2 which can be applied sucessfully.

## Our Team ✨

Thanks goes to these wonderful people:

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/P-Ramos16"><img src="https://avatars0.githubusercontent.com/P-Ramos16?v=3" width="100px;" alt="Ramos"/><br /><sub><b>Pedro Ramos</b><br><i>107348</i></sub></a><hr><a href="https://github.com/P-Ramos16" title="Code">💻</a> <a href="https://github.com/codesandbox/codesandbox-client/commits?author=CompuIves" title="Tests">⚠️</a> <a href="#tool-CompuIves" title="Tools">🔧</a></td>
    <td align="center"><a href="https://github.com/Dan1m4D"><img src="https://avatars0.githubusercontent.com/Dan1m4D?v=3" width="100px;" alt="Madureira"/><br /><sub><b>Daniel Madureira</b><br><i>107603</i></sub></a><hr><a href="https://github.com/Dan1m4D" title="Code">💻</a><a href="#design-CompuIves" title="Design">🎨</a><a href="#blog-CompuIves" title="Blogposts">📝</a></td>
    <td align="center"><a href="https://github.com/Rafael-Kauati"><img src="https://avatars0.githubusercontent.com/Rafael-Kauati?v=3" width="100px;" alt="Kauati"/><br /><sub><b>Rafael Kauati</b><br><i>105925</i></sub></a><hr><a href="https://github.com/Rafael-Kauati" title="Code">💻</a><a href="#tool-MergeMaestro" title="Tools">🔀</a><a href="#tool-CompuIves" title="Tools">🔧</a></td>
  </tr>
</table>

<!-- markdownlint-enable -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->
