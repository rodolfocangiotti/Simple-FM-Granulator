/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "types.h"

//==============================================================================
SimpleFMGranulatorAudioProcessor::SimpleFMGranulatorAudioProcessor():
#ifndef JucePlugin_PreferredChannelConfigurations
  AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                .withInput  ("Input",  AudioChannelSet::stereo(), true)
#endif
                .withOutput ("Output", AudioChannelSet::stereo(), true)
#endif
                ),
                parameters(*this, nullptr, "SimpleFMGranulatorParams", createParameters()),
#endif
  grainStream() {
  minTimeDelta = parameters.getRawParameterValue("minTimeDelta");
  maxTimeDelta = parameters.getRawParameterValue("maxTimeDelta");
  minDuration = parameters.getRawParameterValue("minDuration");
  maxDuration = parameters.getRawParameterValue("maxDuration");
  minHarmonicity = parameters.getRawParameterValue("minHarmonicity");
  maxHarmonicity = parameters.getRawParameterValue("maxHarmonicity");
  minModulationIndex = parameters.getRawParameterValue("minModulationIndex");
  maxModulationIndex = parameters.getRawParameterValue("maxModulationIndex");
  minFrequency = parameters.getRawParameterValue("minFrequency");
  maxFrequency = parameters.getRawParameterValue("maxFrequency");
  minAmplitude = parameters.getRawParameterValue("maxAmplitude");
  maxAmplitude = parameters.getRawParameterValue("minAmplitude");
  minPan = parameters.getRawParameterValue("minPan");
  maxPan = parameters.getRawParameterValue("maxPan");
  modEnvelope = parameters.getRawParameterValue("modEnvelope");
  mainEnvelope = parameters.getRawParameterValue("mainEnvelope");
}

SimpleFMGranulatorAudioProcessor::~SimpleFMGranulatorAudioProcessor() {
}

//==============================================================================
const String SimpleFMGranulatorAudioProcessor::getName() const {
  return JucePlugin_Name;
}

bool SimpleFMGranulatorAudioProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
  return true;
#else
  return false;
#endif
}

bool SimpleFMGranulatorAudioProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
  return true;
#else
  return false;
#endif
}

bool SimpleFMGranulatorAudioProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
  return true;
#else
  return false;
#endif
}

double SimpleFMGranulatorAudioProcessor::getTailLengthSeconds() const {
  return 0.0;
}

int SimpleFMGranulatorAudioProcessor::getNumPrograms() {
  return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
  // so this should be at least 1, even if you're not really implementing programs.
}

int SimpleFMGranulatorAudioProcessor::getCurrentProgram() {
  return 0;
}

void SimpleFMGranulatorAudioProcessor::setCurrentProgram (int index) {
}

const String SimpleFMGranulatorAudioProcessor::getProgramName (int index) {
  return {};
}

void SimpleFMGranulatorAudioProcessor::changeProgramName (int index, const String& newName) {
}

//==============================================================================
void SimpleFMGranulatorAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
  // Use this method as the place to do any pre-playback
  // initialisation that you need..
  initGrainStream();
}

void SimpleFMGranulatorAudioProcessor::releaseResources() {
  // When playback stops, you can use this as an opportunity to free up any
  // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SimpleFMGranulatorAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const {
#if JucePlugin_IsMidiEffect
  ignoreUnused (layouts);
  return true;
#else
  // This is the place where you check if the layout is supported.
  // In this template code we only support mono or stereo.
  if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
      && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
    return false;

  // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
  if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
    return false;
#endif

  return true;
#endif
}
#endif

void SimpleFMGranulatorAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) {
  ScopedNoDenormals noDenormals;
  auto totalNumInputChannels  = getTotalNumInputChannels();
  auto totalNumOutputChannels = getTotalNumOutputChannels();

  // In case we have more outputs than inputs, this code clears any output
  // channels that didn't contain input data, (because these aren't
  // guaranteed to be empty - they may contain garbage).
  // This is here to avoid people getting screaming feedback
  // when they first compile a plugin, but obviously you don't need to keep
  // this code if your algorithm always overwrites all the output channels.
  for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    buffer.clear (i, 0, buffer.getNumSamples());

  // This is the place where you'd normally do the guts of your plugin's
  // audio processing...
  // Make sure to reset the state if your inner loop is processing
  // the samples and the outer loop is handling the channels.
  // Alternatively, you can process the samples with the channels
  // interleaved by keeping the same state.

  setGrainStreamParams();
  auto* chanLeft = buffer.getWritePointer(0);
  auto* chanRight = buffer.getWritePointer(1);
  for (int samp = 0; samp < buffer.getNumSamples(); samp++) {
    StereoOutput streamOut = grainStream.process();
    chanLeft[samp] = streamOut.leftSample;
    chanRight[samp] = streamOut.rightSample;
  }
}

//==============================================================================
bool SimpleFMGranulatorAudioProcessor::hasEditor() const {
  return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SimpleFMGranulatorAudioProcessor::createEditor() {
  return new SimpleFMGranulatorAudioProcessorEditor (*this);
}

//==============================================================================
void SimpleFMGranulatorAudioProcessor::getStateInformation (MemoryBlock& destData) {
  // You should use this method to store your parameters in the memory block.
  // You could do that either as raw data, or use the XML or ValueTree classes
  // as intermediaries to make it easy to save and load complex data.

  auto state = parameters.copyState();
  std::unique_ptr<XmlElement> xml(state.createXml());
  copyXmlToBinary(*xml, destData);
}

void SimpleFMGranulatorAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
  // You should use this method to restore your parameters from this memory block,
  // whose contents will have been created by the getStateInformation() call.

  std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
  if (xmlState.get() != nullptr) {
    if (xmlState->hasTagName(parameters.state.getType())) {
      parameters.replaceState(ValueTree::fromXml(*xmlState));
    }
  }

}

// ********************
AudioProcessorValueTreeState::ParameterLayout SimpleFMGranulatorAudioProcessor::createParameters() {
  std::vector<std::unique_ptr<RangedAudioParameter>> params;

  params.push_back(std::make_unique<AudioParameterFloat>("minTimeDelta", "Min. Time Delta", NormalisableRange<float>(1.0, 1000.0, 0.1, 0.5), 250.0));
  params.push_back(std::make_unique<AudioParameterFloat>("maxTimeDelta", "Max. Time Delta", NormalisableRange<float>(1.0, 1000.0, 0.1, 0.5), 250.0));
  params.push_back(std::make_unique<AudioParameterFloat>("minDuration", "Min. Duration", NormalisableRange<float>(1.0, 1000.0, 0.1, 0.5), 250.0));
  params.push_back(std::make_unique<AudioParameterFloat>("maxDuration", "Max. Duration", NormalisableRange<float>(1.0, 1000.0, 0.1, 0.5), 250.0));
  params.push_back(std::make_unique<AudioParameterFloat>("minHarmonicity", "Min. Harmonicity", NormalisableRange<float>(0.01, 10.0, 0.01, 0.5), 1.0));
  params.push_back(std::make_unique<AudioParameterFloat>("maxHarmonicity", "Max. Harmonicity", NormalisableRange<float>(0.01, 10.0, 0.01, 0.5), 1.0));
  params.push_back(std::make_unique<AudioParameterFloat>("minModulationIndex", "Min. Modulation Index", NormalisableRange<float>(0.01, 10.0, 0.01, 1.0), 0.01));
  params.push_back(std::make_unique<AudioParameterFloat>("maxModulationIndex", "Max. Modulation Index", NormalisableRange<float>(0.01, 10.0, 0.01, 1.0), 0.01));
  params.push_back(std::make_unique<AudioParameterFloat>("minFrequency", "Min. Frequency", NormalisableRange<float>(20.0, 2000.0, 0.1, 0.5), 110.0));
  params.push_back(std::make_unique<AudioParameterFloat>("maxFrequency", "Max. Frequency", NormalisableRange<float>(20.0, 2000.0, 0.1, 0.5), 110.0));
  params.push_back(std::make_unique<AudioParameterFloat>("minAmplitude", "Amplitude", NormalisableRange<float>(0.0, 1.0, 0.001, 0.5), 0.75));
  params.push_back(std::make_unique<AudioParameterFloat>("maxAmplitude", "Max. Amplitude", NormalisableRange<float>(0.0, 1.0, 0.001, 0.5), 0.75));
  params.push_back(std::make_unique<AudioParameterChoice>("modEnvelope", "Modulation Envelope", StringArray("Bell", "Triangle", "Trapezoid", "Sawtooth", "Rectangle", "Random"), 0));
  params.push_back(std::make_unique<AudioParameterChoice>("mainEnvelope", "Envelope", StringArray("Bell", "Triangle", "Trapezoid", "Sawtooth", "Rectangle", "Random"), 0));
  params.push_back(std::make_unique<AudioParameterFloat>("minPan", "Min. Pan", NormalisableRange<float>(0.0, 1.0, 0.01, 1.0), 0.5));
  params.push_back(std::make_unique<AudioParameterFloat>("maxPan", "Max. Pan", NormalisableRange<float>(0.0, 1.0, 0.01, 1.0), 0.5));


  return {params.begin(), params.end()};
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
  return new SimpleFMGranulatorAudioProcessor();
}

void SimpleFMGranulatorAudioProcessor::initGrainStream() {
  setGrainStreamParams();
}

void SimpleFMGranulatorAudioProcessor::setGrainStreamParams() {
  *minTimeDelta = *minTimeDelta >= *maxTimeDelta ? *maxTimeDelta : *minTimeDelta;
  *maxTimeDelta = *maxTimeDelta <= *minTimeDelta ? *minTimeDelta : *maxTimeDelta;
  *minDuration = *minDuration >= *maxDuration ? *maxDuration : *minDuration;
  *maxDuration = *maxDuration <= *minDuration ? *minDuration : *maxDuration;
  *minHarmonicity = *minHarmonicity >= *maxHarmonicity ? *maxHarmonicity : *minHarmonicity;
  *maxHarmonicity = *maxHarmonicity <= *minHarmonicity ? *minHarmonicity : *maxHarmonicity;
  *minModulationIndex = *minModulationIndex >= *maxModulationIndex ? *maxModulationIndex : *minModulationIndex;
  *maxModulationIndex = *maxModulationIndex <= *minModulationIndex ? *minModulationIndex : *maxModulationIndex;
  *minFrequency = *minFrequency >= *maxFrequency ? *maxFrequency : *minFrequency;
  *maxFrequency = *maxFrequency <= *minFrequency ? *minFrequency : *maxFrequency;
  *minAmplitude = *minAmplitude >= *maxAmplitude ? *maxAmplitude : *minAmplitude;
  *maxAmplitude = *maxAmplitude <= *minAmplitude ? *minAmplitude : *maxAmplitude;
  *minPan = *minPan >= *maxPan ? *maxPan : *minPan;
  *maxPan = *maxPan <= *minPan ? *minPan : *maxPan;
  
  grainStream.setSampleRate(getSampleRate());
  grainStream.setMinimumTimeDelta(*minTimeDelta * 0.001);
  grainStream.setMaximumTimeDelta(*maxTimeDelta * 0.001);
  grainStream.setMinimumDuration(*minDuration * 0.001);
  grainStream.setMaximumDuration(*maxDuration * 0.001);
  grainStream.setMinimumModulationFrequency(*minHarmonicity * *minFrequency);
  grainStream.setMaximumModulationFrequency(*maxHarmonicity * *maxFrequency);
  grainStream.setMinimumModulationAmplitude(*minModulationIndex * *minHarmonicity * *minFrequency);
  grainStream.setMaximumModulationAmplitude(*maxModulationIndex * *maxHarmonicity * *maxFrequency);
  grainStream.setMinimumMainFrequency(*minFrequency);
  grainStream.setMaximumMainFrequency(*maxFrequency);
  grainStream.setMinimumMainAmplitude(*minAmplitude);
  grainStream.setMaximumMainAmplitude(*maxAmplitude);
  grainStream.setMinimumPan(*minPan);
  grainStream.setMaximumPan(*maxPan);
  EnvelopeID monEnvID = static_cast<EnvelopeID>(*modEnvelope);
  grainStream.setModulationEnvelopeFunction(monEnvID);
  EnvelopeID mainEnvID = static_cast<EnvelopeID>(*mainEnvelope);
  grainStream.setMainEnvelopeFunction(mainEnvID);
  grainStream.setOscillatorWavetable(SINE_WAVE);
}
