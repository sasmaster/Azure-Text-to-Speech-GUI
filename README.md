# Azure-Text-to-Speech-GUI
Qt based GUI app to convert text into speech (sound) using Microsoft Azure Cognitive services

## This project was created for personal needs and is still under active development. To use this code
you will have to download Azure Speech C++ SDK and link it with the project project.(See .pro file for more details)
You will also have to open Azure Cognitive Services account (free),configure API user keys and region.
You need this information to connect with the service from any endpoint you planning to use it from. 
For the code itself,there is nothing fancy there."Hello world" style C++ API tutorial can be found here:

https://github.com/Azure-Samples/cognitive-services-speech-sdk/blob/master/samples/cpp/windows/console/samples/speech_synthesis_samples.cpp

I just put on top of it GUI to be able to configure different languages,voices and text rapidly,
instead of messing with those parameters in code or command line.

The GUI allows outputting the voice into .wav audio file ,or play it with the system speakers.
There are several voices set by default, see Language combo box, for English US/UK and Hebrew.
At the moment you will have to add more via modifying the code. See mainwindow.cpp file.
I will probably add an external config file to make it more convenient.
 

![Alt text](screenshot.JPG?raw=true "Software screenshot")


