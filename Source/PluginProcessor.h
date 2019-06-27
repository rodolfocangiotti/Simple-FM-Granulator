/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GrainStream.h"

//==============================================================================

class SimpleFMGranulatorAudioProcessor  : public AudioProcessor {
public:
  //==============================================================================
  SimpleFMGranulatorAudioProcessor();
  ~SimpleFMGranulatorAudioProcessor();

  //==============================================================================
  void prepareToPlay (double sampleRate, int samplesPerBlock) override;
  void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
  bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

  void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

  //==============================================================================
  AudioProcessorEditor* createEditor() override;
  bool hasEditor() const override;

  //==============================================================================
  const String getName() const override;

  bool acceptsMidi() const override;
  bool producesMidi() const override;
  bool isMidiEffect() const override;
  double getTailLengthSeconds() const override;

  //==============================================================================
  int getNumPrograms() override;
  int getCurrentProgram() override;
  void setCurrentProgram (int index) override;
  const String getProgramName (int index) override;
  void changeProgramName (int index, const String& newName) override;

  //==============================================================================
  void getStateInformation (MemoryBlock& destData) override;
  void setStateInformation (const void* data, int sizeInBytes) override;
  // ********************
  AudioProcessorValueTreeState parameters;
  AudioProcessorValueTreeState::ParameterLayout createParameters();

private:
  void initGrainStream();
  void setGrainStreamParams();
  // ********************
  GrainStream grainStream;

  float* minTimeDelta;
  float* maxTimeDelta;
  float* minDuration;
  float* maxDuration;
  float* minHarmonicity;
  float* maxHarmonicity;
  float* minModulationIndex;
  float* maxModulationIndex;
  float* minFrequency;
  float* maxFrequency;
  float* minAmplitude;
  float* maxAmplitude;
  float* modEnvelope;
  float* mainEnvelope;
  float* minPan;
  float* maxPan;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleFMGranulatorAudioProcessor)
};
