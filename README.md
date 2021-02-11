# Azure-Text-to-Speech-GUI
Qt based GUI app to convert text into speech (sound) using Microsoft Azure Cognitive services

## This project was created for personal needs and is still under active development. To use this code
you will have to download Azure Speech SDK and link it with the Qt project. You will also have to open
Azure Cognitive Services account,configure user key and region. You need this information to connect with the
service from any endpoint you planning to use the service from. 
For the code itself,there is nothing fancy there. C++ API usage can be learnt from here:
https://github.com/Azure-Samples/cognitive-services-speech-sdk/blob/master/samples/cpp/windows/console/samples/speech_synthesis_samples.cpp

I just put on top of it GUI to be able to configure different languages,voices and text rapidly,instead of messing with those parameters in code
(if using as a cmd app).


