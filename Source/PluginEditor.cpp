/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SimpleFMGranulatorAudioProcessorEditor::SimpleFMGranulatorAudioProcessorEditor (SimpleFMGranulatorAudioProcessor& p)
  : AudioProcessorEditor (&p), processor (p) {
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.

  setSize (400, 800);

  minTimeDeltaValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minTimeDelta", minTimeDeltaSlider);
  
  minTimeDeltaSlider.setBounds(5, 5, 300, 45);
  minTimeDeltaSlider.setSliderStyle(Slider::LinearHorizontal);
  minTimeDeltaSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minTimeDeltaSlider.setTextValueSuffix(" ms");
  minTimeDeltaSlider.onValueChange = [this] {
    if (minTimeDeltaSlider.getValue() >= maxTimeDeltaSlider.getValue()) {
      maxTimeDeltaSlider.setValue(minTimeDeltaSlider.getValue());
    }
  };
  addAndMakeVisible(minTimeDeltaSlider);
  
  minTimeDeltaLabel.setBounds(305, 5, 80, 40);
  minTimeDeltaLabel.setText("Min. Time Delta", dontSendNotification);
  minTimeDeltaLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minTimeDeltaLabel);
  
  // ********************
  
  maxTimeDeltaValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxTimeDelta", maxTimeDeltaSlider);
  
  maxTimeDeltaSlider.setBounds(5, 55, 300, 45);
  maxTimeDeltaSlider.setSliderStyle(Slider::LinearHorizontal);
  maxTimeDeltaSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxTimeDeltaSlider.setTextValueSuffix(" ms");
  maxTimeDeltaSlider.onValueChange = [this] {
    if (maxTimeDeltaSlider.getValue() <= minTimeDeltaSlider.getValue()) {
      minTimeDeltaSlider.setValue(maxTimeDeltaSlider.getValue());
    }
  };
  addAndMakeVisible(maxTimeDeltaSlider);
  
  maxTimeDeltaLabel.setBounds(305, 55, 80, 40);
  maxTimeDeltaLabel.setText("Max. Time Delta", dontSendNotification);
  maxTimeDeltaLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxTimeDeltaLabel);
  
  // ********************
  
  minDurationSlider.setBounds(5, 105, 300, 45);
  minDurationSlider.setSliderStyle(Slider::LinearHorizontal);
  minDurationSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minDurationSlider.setTextValueSuffix(" ms");
  minDurationSlider.onValueChange = [this] {
    if (minDurationSlider.getValue() >= maxDurationSlider.getValue()) {
      maxDurationSlider.setValue(minDurationSlider.getValue());
    }
  };
  addAndMakeVisible(minDurationSlider);
  
  minDurationLabel.setBounds(305, 105, 80, 40);
  minDurationLabel.setText("Min. Duration", dontSendNotification);
  minDurationLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minDurationLabel);
  
  minDurationValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minDuration", minDurationSlider);
  
  // ********************
  
  maxDurationSlider.setBounds(5, 155, 300, 45);
  maxDurationSlider.setSliderStyle(Slider::LinearHorizontal);
  maxDurationSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxDurationSlider.setTextValueSuffix(" ms");
  maxDurationSlider.onValueChange = [this] {
    if (maxDurationSlider.getValue() <= minDurationSlider.getValue()) {
      minDurationSlider.setValue(maxDurationSlider.getValue());
    }
  };
  addAndMakeVisible(maxDurationSlider);
  
  maxDurationLabel.setBounds(305, 155, 80, 40);
  maxDurationLabel.setText("Max. Duration", dontSendNotification);
  maxDurationLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxDurationLabel);
  
  maxDurationValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxDuration", maxDurationSlider);
  
  // ********************
  
  minHarmonicitySlider.setBounds(5, 205, 300, 45);
  minHarmonicitySlider.setSliderStyle(Slider::LinearHorizontal);
  minHarmonicitySlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minHarmonicitySlider.onValueChange = [this] {
    if (minHarmonicitySlider.getValue() >= maxHarmonicitySlider.getValue()) {
      maxHarmonicitySlider.setValue(minHarmonicitySlider.getValue());
    }
  };
  addAndMakeVisible(minHarmonicitySlider);
  
  minHarmonicityLabel.setBounds(305, 205, 80, 40);
  minHarmonicityLabel.setText("Min. Harmonicity", dontSendNotification);
  minHarmonicityLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minHarmonicityLabel);
  
  minHarmonicityValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minHarmonicity", minHarmonicitySlider);
  
  // ********************
  
  maxHarmonicitySlider.setBounds(5, 255, 300, 45);
  maxHarmonicitySlider.setSliderStyle(Slider::LinearHorizontal);
  maxHarmonicitySlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxHarmonicitySlider.onValueChange = [this] {
    if (maxHarmonicitySlider.getValue() <= minHarmonicitySlider.getValue()) {
      minHarmonicitySlider.setValue(maxHarmonicitySlider.getValue());
    }
  };
  addAndMakeVisible(maxHarmonicitySlider);
  
  maxHarmonicityLabel.setBounds(305, 255, 80, 40);
  maxHarmonicityLabel.setText("Max. Harmonicity", dontSendNotification);
  maxHarmonicityLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxHarmonicityLabel);
  
  maxHarmonicityValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxHarmonicity", maxHarmonicitySlider);
  
  // ********************
  
  minModulationIndexSlider.setBounds(5, 305, 300, 45);
  minModulationIndexSlider.setSliderStyle(Slider::LinearHorizontal);
  minModulationIndexSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minModulationIndexSlider.onValueChange = [this] {
    if (minModulationIndexSlider.getValue() >= maxModulationIndexSlider.getValue()) {
      maxModulationIndexSlider.setValue(minModulationIndexSlider.getValue());
    }
  };
  addAndMakeVisible(minModulationIndexSlider);
  
  minModulationIndexLabel.setBounds(305, 305, 80, 40);
  minModulationIndexLabel.setText("Min. Mod. Index", dontSendNotification);
  minModulationIndexLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minModulationIndexLabel);
  
  minModulationIndexValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minModulationIndex", minModulationIndexSlider);
  
  // ********************
  
  maxModulationIndexSlider.setBounds(5, 355, 300, 45);
  maxModulationIndexSlider.setSliderStyle(Slider::LinearHorizontal);
  maxModulationIndexSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxModulationIndexSlider.onValueChange = [this] {
    if (maxModulationIndexSlider.getValue() <= minModulationIndexSlider.getValue()) {
      minModulationIndexSlider.setValue(maxModulationIndexSlider.getValue());
    }
  };
  addAndMakeVisible(maxModulationIndexSlider);
  
  maxModulationIndexLabel.setBounds(305, 355, 80, 40);
  maxModulationIndexLabel.setText("Max. Mod. Index", dontSendNotification);
  maxModulationIndexLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxModulationIndexLabel);
  
  maxModulationIndexValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxModulationIndex", maxModulationIndexSlider);
  
  // ********************
  
  minFrequencySlider.setBounds(5, 405, 300, 45);
  minFrequencySlider.setSliderStyle(Slider::LinearHorizontal);
  minFrequencySlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minFrequencySlider.setTextValueSuffix(" Hz");
  minFrequencySlider.onValueChange = [this] {
    if (minFrequencySlider.getValue() >= maxFrequencySlider.getValue()) {
      maxFrequencySlider.setValue(minFrequencySlider.getValue());
    }
  };
  addAndMakeVisible(minFrequencySlider);
  
  minFrequencyLabel.setBounds(305, 405, 80, 40);
  minFrequencyLabel.setText("Min. Frequency", dontSendNotification);
  minFrequencyLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minFrequencyLabel);
  
  minFrequencyValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minFrequency", minFrequencySlider);
  
  // ********************
  
  maxFrequencySlider.setBounds(5, 455, 300, 45);
  maxFrequencySlider.setSliderStyle(Slider::LinearHorizontal);
  maxFrequencySlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxFrequencySlider.setTextValueSuffix(" Hz");
  maxFrequencySlider.onValueChange = [this] {
    if (maxFrequencySlider.getValue() <= minFrequencySlider.getValue()) {
      minFrequencySlider.setValue(maxFrequencySlider.getValue());
    }
  };
  addAndMakeVisible(maxFrequencySlider);
  
  maxFrequencyLabel.setBounds(305, 455, 80, 40);
  maxFrequencyLabel.setText("Max. Frequency", dontSendNotification);
  maxFrequencyLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxFrequencyLabel);
  
  maxFrequencyValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxFrequency", maxFrequencySlider);
  
  // ********************
  
  minAmplitudeSlider.setBounds(5, 505, 300, 45);
  minAmplitudeSlider.setSliderStyle(Slider::LinearHorizontal);
  minAmplitudeSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minAmplitudeSlider.onValueChange = [this] {
    if (minAmplitudeSlider.getValue() >= maxAmplitudeSlider.getValue()) {
      maxAmplitudeSlider.setValue(minAmplitudeSlider.getValue());
    }
  };
  addAndMakeVisible(minAmplitudeSlider);
  
  minAmplitudeLabel.setBounds(305, 505, 80, 40);
  minAmplitudeLabel.setText("Min. Amplitude", dontSendNotification);
  minAmplitudeLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minAmplitudeLabel);
  
  minAmplitudeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minAmplitude", minAmplitudeSlider);
  
  // ********************
  
  maxAmplitudeSlider.setBounds(5, 555, 300, 45);
  maxAmplitudeSlider.setSliderStyle(Slider::LinearHorizontal);
  maxAmplitudeSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxAmplitudeSlider.onValueChange = [this] {
    if (maxAmplitudeSlider.getValue() <= minAmplitudeSlider.getValue()) {
      minAmplitudeSlider.setValue(maxAmplitudeSlider.getValue());
    }
  };
  addAndMakeVisible(maxAmplitudeSlider);
  
  maxAmplitudeLabel.setBounds(305, 555, 80, 40);
  maxAmplitudeLabel.setText("Max. Amplitude", dontSendNotification);
  maxAmplitudeLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxAmplitudeLabel);
  
  maxAmplitudeValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxAmplitude", maxAmplitudeSlider);
  
  // ********************
  
  minPanSlider.setBounds(5, 605, 300, 45);
  minPanSlider.setSliderStyle(Slider::LinearHorizontal);
  minPanSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  minPanSlider.onValueChange = [this] {
    if (minPanSlider.getValue() >= maxPanSlider.getValue()) {
      maxPanSlider.setValue(minPanSlider.getValue());
    }
  };
  addAndMakeVisible(minPanSlider);
  
  minPanLabel.setBounds(305, 605, 80, 40);
  minPanLabel.setText("Min. Pan", dontSendNotification);
  minPanLabel.setJustificationType(Justification::left);
  addAndMakeVisible(minPanLabel);
  
  minPanValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "minPan", minPanSlider);
  
  // ********************
  
  maxPanSlider.setBounds(5, 655, 300, 45);
  maxPanSlider.setSliderStyle(Slider::LinearHorizontal);
  maxPanSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 80, 40);
  maxPanSlider.onValueChange = [this] {
    if (maxPanSlider.getValue() <= minPanSlider.getValue()) {
      minPanSlider.setValue(maxPanSlider.getValue());
    }
  };
  addAndMakeVisible(maxPanSlider);
  
  maxPanLabel.setBounds(305, 655, 80, 40);
  maxPanLabel.setText("Max. Pan", dontSendNotification);
  maxPanLabel.setJustificationType(Justification::left);
  addAndMakeVisible(maxPanLabel);
  
  maxPanValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.parameters, "maxPan", maxPanSlider);
  
  // ********************
  
  modEnvelopeCombo.setBounds(5, 705, 295, 40);
  modEnvelopeCombo.setJustificationType(Justification::centred);
  modEnvelopeCombo.addItem("Bell", 1);
  modEnvelopeCombo.addItem("Triangle", 2);
  modEnvelopeCombo.addItem("Trapezoid", 3);
  modEnvelopeCombo.addItem("Sawtooth", 4);
  modEnvelopeCombo.addItem("Rectangle", 5);
  modEnvelopeCombo.addItem("Random", 6);
  addAndMakeVisible(modEnvelopeCombo);
  
  modEnvelopeLabel.setBounds(305, 705, 80, 40);
  modEnvelopeLabel.setText("Modulation Envelope", dontSendNotification);
  modEnvelopeLabel.setJustificationType(Justification::left);
  addAndMakeVisible(modEnvelopeLabel);
  
  modEnvelopeValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.parameters, "modEnvelope", modEnvelopeCombo);
    
  // ********************
  
  mainEnvelopeCombo.setBounds(5, 755, 295, 40);
  mainEnvelopeCombo.setJustificationType(Justification::centred);
  mainEnvelopeCombo.addItem("Bell", 1);
  mainEnvelopeCombo.addItem("Triangle", 2);
  mainEnvelopeCombo.addItem("Trapezoid", 3);
  mainEnvelopeCombo.addItem("Sawtooth", 4);
  mainEnvelopeCombo.addItem("Rectangle", 5);
  mainEnvelopeCombo.addItem("Random", 6);
  addAndMakeVisible(mainEnvelopeCombo);
  
  mainEnvelopeLabel.setBounds(305, 755, 80, 40);
  mainEnvelopeLabel.setText("Main Envelope", dontSendNotification);
  mainEnvelopeLabel.setJustificationType(Justification::left);
  addAndMakeVisible(mainEnvelopeLabel);
  
  mainEnvelopeValue = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.parameters, "mainEnvelope", mainEnvelopeCombo);
}

SimpleFMGranulatorAudioProcessorEditor::~SimpleFMGranulatorAudioProcessorEditor() {
}

//==============================================================================
void SimpleFMGranulatorAudioProcessorEditor::paint (Graphics& g) {
  // (Our component is opaque, so we must completely fill the background with a solid colour)
  g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

  g.setColour (Colours::white);
  g.setFont (15.0f);
  //g.drawFittedText ("SimpleFMGranulator by Cangio", 0, 700, 400, 20, Justification::centred, 1);
}

void SimpleFMGranulatorAudioProcessorEditor::resized() {
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..
}
