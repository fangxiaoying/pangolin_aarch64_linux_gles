What does this rWhat does this do
====================================

* Porting Pangolin to NXP i.MX8/8M (aarch64) series platform on Linux.
* Add support for GLES and GLFW as Dispaly Backend 

The branch is supports Micro Processor Unit which supports GLES2.0 or a newer version.

What is Pangolin
====================================
Pangolin is a lightweight portable rapid development library for managing OpenGL
display / interaction and abstracting video input. At its heart is a simple
OpenGl viewport manager which can help to modularise 3D visualisation without
adding to its complexity, and offers an advanced but intuitive 3D navigation
handler. Pangolin also provides a mechanism for manipulating program variables
through config files and ui integration, and has a flexible real-time plotter
for visualising graphical data.
The ethos of Pangolin is to reduce the boilerplate code that normally
gets written to visualise and interact with (typically image and 3D
based) systems, without compromising performance. It also enables write-once
code for a number of platforms, currently including Windows, Linux, OSX, Android
and IOS.

## Code
Find the latest version on [Github](https://github.com/fangxiaoying/pangolin_aarch64_linux_gles.git):
```
git clone https://github.com/fangxiaoying/pangolin_aarch64_linux_gles.git
```
##  Dependencies 
Optional dependencies are enabled when found, otherwise they are silently disabled.
Check the CMake configure output for details.
#### Required Dependencies (aarch64 Soc)
* C++11
* OpenGLES ( ES2/ ES3)
* GLFW
* CMake (for build environment)
#### Recommended Dependencies 
* Python2 / Python3, for drop-down interactive console
* Wayland
#### Optional Dependencies for video input
* FFMPEG (For video decoding and image rescaling)
* DC1394 (For firewire input)
* libuvc (For cross-platform webcam video input via libusb)
* libjpeg, libpng, libtiff, libopenexr (For reading still-image sequences)
* OpenNI / OpenNI2 (For Kinect / Xtrion / Primesense capture)
* DepthSense SDK
#### Very Optional Dependencies
* Eigen / TooN (These matrix types supported in the Pangolin API.) [rencommand 3.3.8]
* Doxygen for generating html / pdf documentation.
## How to Building on IMX8/8M series Soc##
Pangolin uses the CMake portable pre-build tool. To checkout and build pangolin in the
directory 'build', execute the following at a shell (or the equivelent using a GUI):

##### **Please refer to [ORB_SLAM2_GLES](https://github.com/fangxiaoying/ORB_SLAM2_GLES/blob/main/README.md) for building pangolin_aarch64_linux_gles**
```
https://github.com/fangxiaoying/ORB_SLAM2_GLES
```

If you would like to build the documentation and you have Doxygen installed, you
can execute:
```
cmake --build . --target doc
```
**On Windows**, Pangolin will attempt to download and build *glew*, *libjpeg*, *libpng* and *zlib* automatically. It does so assuming that git is available on the path - this assumption may be wrong for windows users who have downloaded Pangolin via a zip file on github. You will instead need to download and compile the dependencies manually, and set the BUILD_EXTERN_(lib) options to false for these libraries. The alternate and recommended approach is to install [gitbash](https://git-scm.com/downloads) and work from within their provided console.
## Issues 
May meet error alert "Error: Wayland: Focusing a window requires user interaction", May fixed later.

##  Bindings 
### Python 
Python is not tested in this branch


## Original Code
[Pangolin](https://github.com/stevenlovegrove/Pangolin.git)
