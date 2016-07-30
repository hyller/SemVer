## SemVer
SemVer is a Utility to Bump Semantic Version String in C header, java, and text file.

Travis Linux build status:[![Build Status](https://travis-ci.org/hyller/SemVer.svg?branch=master)](https://travis-ci.org/hyller/SemVer)

AppVeyor Windows build status:[![Build status](https://ci.appveyor.com/api/projects/status/26b3umg466awcd6m?svg=true)](https://ci.appveyor.com/project/hyller/semver)

Coverage:[![Coverage Status](https://coveralls.io/repos/github/hyller/SemVer/badge.svg?branch=master)](https://coveralls.io/github/hyller/SemVer?branch=master)

## Context
These steps would be done to release a software normally
1) Create a souce file which contain version string.
2) Increase version number manually, for example, increase 0.1.0 to 0.2.0.  
3) Rebuild your software and get the target file manually, for example target.hex.  
4) Append the version number to the target file manually, for example target_0.2.0.hex.  

**SemVer** aims to do the step 1, step 2 and step 3.


## What can SemVer Do

**SemVer** creates version head file, increases version and appends the version to a file name.  
The version format defined in [semver.org](http://semver.org).  

## Build from Code

There are prebuild binaries for windows in folder bin. You can try to use them directly.

If you want to build it from code. Compile tool is GCC. 
Mingw or Cygwin need be installed on windows.
GCC need be installed on Linux.

Run 'make' to build the executable binary.

## Example

Create a head file version.h with initial version value 0.1.0  
	semver -i0.1.0 version.h

Increase the version value to 0.1.1  
	semver -z version.h

Increase the version value to 0.2.0  
	semver -y version.h

Increase the version value to 1.0.0  
	semver -x version.h

Append version to file target.hex to target_1.0.0.hex  
	semver -atarget.hex version.h




