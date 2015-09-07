/*
  This file is part of the juce_faustllvm JUCE module
  Written by Oliver Larkin
  Contemporary Music Research Centre
  Music Department, University of York
  License: GPL
  
  based on Faustgen~ by GRAME
  
*/

#include <modules/juce_core/juce_core.h>
#include <modules/juce_audio_processors/juce_audio_processors.h>
#include <modules/juce_gui_basics/juce_gui_basics.h>

#define FAUSTFLOAT float

#define DEFAULT_FAUST_DSP_SEARCHPATH "~/Library/Application Support/pMix2/FaustNodes"

#define FAUSTGEN_VERSION "0.99b"

#if JUCE_MAC || JUCE_LINUX
  #define FAUST_DRAW_PATH "/var/tmp/"
  #define SEPARATOR '/'
#elif JUCE_WIN32
  #define FAUST_DRAW_PATH "\\faustgen-resources\\"
  #define SEPARATOR '\\'
#endif

#define LLVM_OPTIMIZATION 3
#define DEFAULT_CODE "declare name \"Faust Effect\";\n\ngain = hslider(\"gain\", 1., 0., 1., 0.);\nprocess = _*(gain);"
//#define DEFAULT_CODE "import(\"math.lib\"); \nimport(\"maxmsp.lib\"); \nimport(\"music.lib\"); \nimport(\"oscillator.lib\"); \nimport(\"reduce.lib\"); \nimport(\"filter.lib\"); \nimport(\"effect.lib\"); \n \nprocess=_,_;"

#define HTML_WRAPPER "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\"> \
<html> \
<head> \
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"> \
<title>SVG viewer</title> \
</head> \
<body style=\"background-color: #FAFAFA; font-family: arial, sans-serif; font-size: 12px; min-width: 700px;\"> \
<embed src=\"process.svg\" type=\"image/svg+xml\" style=\"background-color: white; padding:20px; width: 90%; box-shadow: 1px 1px 5px 2px #C8C8C8; box-sizing: border-box; margin-left: 5%; margin-top: 40px;\"> \
</body> \
</html>"

#define LOG Logger::getCurrentLogger()->writeToLog

#include "source/FaustAudioPluginInstance.h"
#include "source/FaustAudioProcessorParameter.h"
#include "source/FaustCodeTokenizer.h"
#include "source/FaustPluginFormat.h"
// #include "source/FaustDSPWatcher.h"
// #include "source/FaustFileFilter.h"
// #include "source/FaustGenFactory.h"
