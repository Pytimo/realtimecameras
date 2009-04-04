============
Introduction
============

This is the source code accompaniment to the book "Real Time Cameras" by Mark 
Haigh-Hutchinson.

It's official home is hosted at Google Code here:
http://code.google.com/p/realtimecameras/

The web site for the book is:
http://www.realtimecameras.com

====================
Building and Running
====================

Windows
-------

To set up the RTC Environment:
* Grab the code from Google Code.  It is assumed it is in C:\RTC
* Install the newest Ogre32 SDK from http://www.ogre3d.org
* If you want to open Microsoft Visual Studio 2005 or Visual Studio Express, 
  run C:\RTC\Win32\rtc_vs2005.bat
* If you want to open a command prompt with the proper environment, run 
  C:\RTC\Win32\rtc_cmd.bat

Sample locations:
* C:\RTC\demo\parameters\build\msvc8e
* C:\RTC\demo\sample_00\build\msvc8e

Mac
---

NOTE: Mac has not been fully tested

To set up the RTC Environment:
* Grab the code from Google Code.
* Install the newest Ogre32 SDK from http://www.ogre3d.org
* In XCode's Source Trees, set the following:
** OGRE_HOME - Installation path of OGRE
** RTC_PATH - Path of where you put the "Real Time Cameras" code

=======
License
=======

This code is protected under the MIT License.

Copyright (c) 2009 Mark Haigh-Hutchinson

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
