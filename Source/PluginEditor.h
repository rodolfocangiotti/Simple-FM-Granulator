/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================

class SimpleFMGranulatorAudioProcessorEditor  : public AudioProcessorEditor {
public:
  SimpleFMGranulatorAudioProcessorEditor (SimpleFMGranulatorAudioProcessor&);
  ~SimpleFMGranulatorAudioProcessorEditor();

  //==============================================================================
  void paint (Graphics&) override;
  void resized() override;

private:
  // This reference is provided as a quick way for your editor to
  // access the processor object that created it.
  SimpleFMGranulatorAudioProcessor& processor;

  Slider minTimeDeltaSlider;
  Label minTimeDeltaLabel;
  Slider maxTimeDeltaSlider;
  Label maxTimeDeltaLabel;
  Slider minDurationSlider;
  Label minDurationLabel;
  Slider maxDurationSlider;
  Label maxDurationLabel;
  Slider minHarmonicitySlider;
  Label minHarmonicityLabel;
  Slider maxHarmonicitySlider;
  Label maxHarmonicityLabel;
  Slider minModulationIndexSlider;
  Label minModulationIndexLabel;
  Slider maxModulationIndexSlider;
  Label maxModulationIndexLabel;
  Slider minFrequencySlider;
  Label minFrequencyLabel;
  Slider maxFrequencySlider;
  Label maxFrequencyLabel;
  Slider minAmplitudeSlider;
  Label minAmplitudeLabel;
  Slider maxAmplitudeSlider;
  Label maxAmplitudeLabel;
  Slider minPanSlider;
  Label minPanLabel;
  Slider maxPanSlider;
  Label maxPanLabel;
  ComboBox modEnvelopeCombo;
  Label modEnvelopeLabel;
  ComboBox mainEnvelopeCombo;
  Label mainEnvelopeLabel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SimpleFMGranulatorAudioProcessorEditor)

public:
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minTimeDeltaValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxTimeDeltaValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minDurationValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxDurationValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minHarmonicityValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxHarmonicityValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minModulationIndexValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxModulationIndexValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minFrequencyValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxFrequencyValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minAmplitudeValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxAmplitudeValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> minPanValue;
  std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> maxPanValue;
  std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> modEnvelopeValue;
  std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> mainEnvelopeValue;
};
