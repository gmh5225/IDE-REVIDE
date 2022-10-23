# REVIDE

## Qt

From Git Bash:

```
curl -O -L https://code.qt.io/cgit/qbs/qbs.git/plain/scripts/install-qt.sh 1>nul
sh install-qt.sh --directory /d/Qt --host windows_x86 --target desktop --toolchain win64_msvc2017_64 --version 5.12.9 qt 3d qtactiveqt qtbase qtcanvas3d qtconnectivity qtdeclarative qtgamepad qtgraphicaleffects qtimageformats qtlocation qtm ultimedia qtquickcontrols qtquickcontrols2 qtremoteobjects qtscxml qtsensors qtserialbus qtserialport qtspeech qtsvg qt tools qttranslations qtwebchannel qtwebsockets qtwebview qtwinextras qtxmlpatterns d3dcompiler_47 opengl32sw
```

Alternatively you can download and install Qt from [here](https://www.qt.io/offline-installers).

## LLVM

TODO: Add instructions on how to produce this package.

You can download a prebuilt package for Visual Studio 2019 at https://github.com/LLVMParty/REVIDE/releases/tag/libraries.

## Building

```bash
cmake -B build -DCMAKE_PREFIX_PATH="C:\Qt\5.15.2\msvc2019_64;E:\llvm\llvm-15.0.3-win64" -DCMAKE_INSTALL_PREFIX=install
```

You should also be able to use CLion or Visual Studio to open the repository so you don't have to manually run CMake.
