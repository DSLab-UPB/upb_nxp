This is a standalone program that use the bundle and myolinux library to run in real time the classify network. You need to add in CMakeLists.txt the following informations:
1. The path to myolinux library. The library can be found at https://github.com/brokenpylons/MyoLinux. You can either install the library as a stand alone library, or modify the CMakeListst.txt to download the library.
2. The path to bundle generated library. 

There is also a need to add the bundle generated weight file to the build location, since the program reads from it.


The following changes need to be done in order to run a different bundle:
1. Change the name of exposed function and config. Right now they are called "network". This name should be the same as the name used in step2.
2. Change the name of the input / output layer.
3. Change the function of extracted features (if your network was trained on different features)


This program allows 3 types of classify (depending on the value of type variable):
1. Single prediction mode
2. Multi prediction mode with counting vote (sum of argmax over each prediction)
3. Multi prediction mode with sum vote (argmax over sum of predictions)


This program was inspired by our Python program that use the Myo armband and the original network to classify in real time the gestures, but it was changed to use the Glow generated bundle and C++ libraries.
