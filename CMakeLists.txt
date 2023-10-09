cmake_minimum_required(VERSION 3.10)
project(SoundEffects)

include_directories(include
  exceptions)

add_executable(simple-dsp 
  src/main.cpp
  src/modes.cpp
  src/fileReader.cpp
  src/soundEffects.cpp
  src/wavHeader.cpp
  include/wavHeader.h
  include/fileReader.h
  include/modes.h
  include/soundEffects.h
  exceptions/soundEffectsException.h
)