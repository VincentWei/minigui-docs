MiniGUI User Manual

Version 3.0 (revised edition 5)

For MiniGUI Version 3.0.

Beijing FMSoft Technologies Co. Ltd.

Feb, 2018

Copyright Claim
===============

MiniGUI User Manual Version 3.0 (revised edition 5) for MiniGUI Ver
3.0.x.

Copyright © 2003\~2018, Beijing FMSoft Technologies Co., Ltd.\
All rights reserved.

By whatever means you get the entire or partial text or photograph data
in this guide, no matter mechanical or electronic, you are only
authorized by Beijing FMSoft Technologies Co., Ltd. the reading right.
Any format conversion, redistribution, dissemination, and copying its
entire or partial content, or using text or photograph there in for
commercial purpose without written permission will be regarded as
tortuous, and may result in severe civil or criminal punishment.

Contents

Copyright Claim 1

1 Introduction to MiniGUI 1

1.1 A Brief Introduction 1

1.2 Documents for MiniGUI 2

1.3 MiniGUI Source Code and Samples 2

1.4 Optional Components of MiniGUI 3

1.5 miniStudio development tools 4

1.6 About this Manual 5

2 Configuring, Compiling, and Installing MiniGUI 6

2.1 Customization of Compiling Configuration Options 6

2.1.1 Configuration in GNU Development Environment by Configure Script 7

2.1.2 Configuration under Non-GNU environment 11

2.2 Detailed Description on Compiling, Configuration Options of MiniGUI
11

2.2.1 Operating System Options and Macros 11

2.2.2 Target Board Related Options and Macros 12

2.2.3 Runtime Mode Related Options and Macros 13

2.2.4 Graphics Engine Related Options and Macros 14

2.2.5 Input Engine Related Options and Macros 16

2.2.6 Keyboard Layout Related Options and Macros 17

2.2.7 System Global Configuration Options and Macros 18

2.2.8 Character Set and Font Related Options and Macros 19

2.2.9 Image File Format Related Options and Macros 23

2.2.10 Appearance Style Related Options and Macros 24

2.2.11 Control Related Options and Macros 24

2.2.12 Other Options and Macros 25

2.3 Minimum Configuration Options 26

2.3.1 Using GNU Configure Script 26

2.3.2 Corresponding mgconfig.h 27

2.4 Compiling and Installing MiniGUI 37

2.4.1 compile and install the dependent library 37

2.4.2 compile and install the virtual framebuffer program 38

2.4.3 Compiling and Installing MiniGUI in the GNU Development
Environment 39

2.4.4 Install MiniGUI Resource Package 40

2.4.5 compile and run MiniGUI sample 40

2.5 Compiling and Installing MiniGUI in Non-GNU Development Environment
40

2.6 Use Ubuntu on Windows to configure and compile MiniGUI 43

3 MiniGUI runtime configuration options 44

3.1 Configuration File 45

3.1.1 Section system 45

3.1.2 Section fbcon 46

3.1.3 Section qvfb 46

3.1.4 Section pc\_xvfb 46

3.1.5 Section rawbitmapfonts, varbitmapfonts, qpf, truetypefonts, and
type1fonts 47

3.1.5 Section systemfont 48

3.1.6 Section mouse 49

3.1.7 Section event 49

3.1.8 Section classic 50

3.1.9 Default Configuration File 52

3.2 Incore Configuration Options 60

3.2.1 Structure ETCSETCTION 60

3.2.2 ETC\_S Structure 62

3.2.3 Listing of mgetc.c 62

3.3 Sample of Configuration 76

3.3.1 Runtime Configuration when only Support for ISO8859-1 Charset 76

3.3.2 Specifying Different Graphic Engine and Input Engine 76

4 Developing MiniGUI Application in Windows 78

Appendix A Frequent Ask Questions (FAQs) 80

A.1 Questions Relevant to GPL Versions 80

A.2 Questions Relevant to MiniGUI Application Fields 80

A.3 Questions Relevant to Portability 81

A.4 Questions Relevant to Compilation 81

A.5 Questions Relevant to Input Engines 82

A.6 Runtime Questions 83

A.7 Common Error Messages 83

