/*
** Odin 2 Synthesizer Plugin
** Copyright (C) 2020 - 2021 TheWaveWarden
**
** Odin 2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Odin 2 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/

#include "LFOSelectorComponent.h"
#include "../GlobalIncludes.h"
#include "../JuceLibraryCode/JuceHeader.h"

LFOSelectorComponent::LFOSelectorComponent() : m_up("up", "Up"), m_down("down", "Down") {

	m_display.setInlay(1);
	addAndMakeVisible(m_display);

	m_up.setClickingTogglesState(true);
	addAndMakeVisible(m_up);
	m_up.setTriggeredOnMouseDown(false);
	m_up.setColour(juce::DrawableButton::ColourIds::backgroundOnColourId, juce::Colour());
	m_up.onClick = [&]() { decrement(); };

	m_down.setClickingTogglesState(true);
	addAndMakeVisible(m_down);
	m_down.setTriggeredOnMouseDown(false);
	m_down.setColour(juce::DrawableButton::ColourIds::backgroundOnColourId, juce::Colour());
	m_down.onClick = [&]() { increment(); };

	m_display.toParentMouseDown = [&](const MouseEvent e) {
		mouse_reference_value = -e.getScreenY();
		m_drag_initial_value  = m_value;
		Component::mouseDown(e);
	};

	m_display.toParentMouseDrag = [&](const MouseEvent e) {
		float mouse_moved = mouse_reference_value + e.getScreenY();

		float m_max = m_display.getNrOfWaves() - 1;
		float m_min = 0.f;

		int new_value = m_drag_initial_value + mouse_moved / 20.f;
		new_value     = new_value > m_max ? m_max : new_value;
		new_value     = new_value < m_min ? m_min : new_value;

		setValue(new_value);

		Component::mouseDrag(e);
	};

	m_display.toParentMouseUp = [&](const MouseEvent e) { Component::mouseUp(e); };
	m_display.onClick         = [&]() {
        m_popup.showMenuAsync(PopupMenu::Options(), [&](int ret) {
            if (ret) {
                // ret values are offset by one to allow popup return 0 == nothing
                setValue(ret - 1);
            }
            getTopLevelComponent()->repaint();
        });
	};

	m_up.setRepeatSpeed(BUTTON_REPEAT_INITIAL_DELAY, BUTTON_REPEAT_DELAY);
	m_down.setRepeatSpeed(BUTTON_REPEAT_INITIAL_DELAY, BUTTON_REPEAT_DELAY);

	m_popup.setLookAndFeel(&m_popup_look_and_feel);
	m_popup.addItem(1, "si");
	m_popup.addItem(2, "sa");
	m_popup.addItem(3, "tr");
	m_popup.addItem(4, "sq50");
	m_popup.addItem(5, "sq25");
	m_popup.addItem(6, "sq12");
	m_popup.addItem(7, "pe");
	m_popup.addSeparator();
	m_popup.addItem(8, "sh");
	m_popup.addSeparator();
	m_popup.addItem(9, "p4");
	m_popup.addItem(10, "p6");
	m_popup.addItem(11, "p8");
	m_popup.addItem(12, "p12");
	m_popup.addSeparator();
	m_popup.addItem(13, "s3");
	m_popup.addItem(14, "s4");
	m_popup.addItem(15, "s6");
	m_popup.addItem(16, "s8");
	m_popup.addItem(17, "s12");
	m_popup.addSeparator();
	m_popup.addItem(18, "w1");
	m_popup.addItem(19, "w2");
	m_popup.addItem(20, "w3");
	m_popup.addSeparator();
	m_popup.addItem(21, "c1");
	m_popup.addItem(22, "c2");
	m_popup.addItem(23, "c3");
}

LFOSelectorComponent::~LFOSelectorComponent() {
	m_popup.setLookAndFeel(nullptr);
}

void LFOSelectorComponent::paint(Graphics &g) {
	g.setColour(COL_LIGHT);
	g.drawRect(getLocalBounds(), 1);
}

void LFOSelectorComponent::resized() {

	auto bounds        = getLocalBounds();
	auto button_bounds = bounds.removeFromRight(H);

	m_up.setBounds(button_bounds.removeFromTop(proportionOfHeight(0.5f)));
	m_down.setBounds(button_bounds);
	m_display.setBounds(bounds);

	m_display.clearWaves();

	juce::Image sine = ImageCache::getFromMemory(BinaryData::sine_150_png, BinaryData::sine_150_pngSize);
	m_display.addWave(sine);
	juce::Image saw = ImageCache::getFromMemory(BinaryData::saw_150_png, BinaryData::saw_150_pngSize);
	m_display.addWave(saw);
	juce::Image triangle = ImageCache::getFromMemory(BinaryData::triangle_150_png, BinaryData::triangle_150_pngSize);
	m_display.addWave(triangle);
	juce::Image square = ImageCache::getFromMemory(BinaryData::square50_150_png, BinaryData::square50_150_pngSize);
	m_display.addWave(square);
	juce::Image square25 = ImageCache::getFromMemory(BinaryData::square25_150_png, BinaryData::square25_150_pngSize);
	m_display.addWave(square25);
	juce::Image square12 = ImageCache::getFromMemory(BinaryData::square12_150_png, BinaryData::square12_150_pngSize);
	m_display.addWave(square12);
	juce::Image peak = ImageCache::getFromMemory(BinaryData::peak_150_png, BinaryData::peak_150_pngSize);
	m_display.addWave(peak);
	juce::Image SH = ImageCache::getFromMemory(BinaryData::SH_150_png, BinaryData::SH_150_pngSize);
	m_display.addWave(SH);
	juce::Image pyram4 = ImageCache::getFromMemory(BinaryData::pyram4_150_png, BinaryData::pyram4_150_pngSize);
	m_display.addWave(pyram4);
	juce::Image pyram6 = ImageCache::getFromMemory(BinaryData::pyram6_150_png, BinaryData::pyram6_150_pngSize);
	m_display.addWave(pyram6);
	juce::Image pyram8 = ImageCache::getFromMemory(BinaryData::pyram8_150_png, BinaryData::pyram8_150_pngSize);
	m_display.addWave(pyram8);
	juce::Image pyram12 = ImageCache::getFromMemory(BinaryData::pyram12_150_png, BinaryData::pyram12_150_pngSize);
	m_display.addWave(pyram12);
	juce::Image stair3 = ImageCache::getFromMemory(BinaryData::stair3_150_png, BinaryData::stair3_150_pngSize);
	m_display.addWave(stair3);
	juce::Image stair4 = ImageCache::getFromMemory(BinaryData::stair4_150_png, BinaryData::stair4_150_pngSize);
	m_display.addWave(stair4);
	juce::Image stair6 = ImageCache::getFromMemory(BinaryData::stair6_150_png, BinaryData::stair6_150_pngSize);
	m_display.addWave(stair6);
	juce::Image stair8 = ImageCache::getFromMemory(BinaryData::stair8_150_png, BinaryData::stair8_150_pngSize);
	m_display.addWave(stair8);
	juce::Image stair12 = ImageCache::getFromMemory(BinaryData::stair12_150_png, BinaryData::stair12_150_pngSize);
	m_display.addWave(stair12);
	juce::Image wavedraw1 = ImageCache::getFromMemory(BinaryData::wavedraw1_150_png, BinaryData::wavedraw1_150_pngSize);
	m_display.addWave(wavedraw1);
	juce::Image wavedraw2 = ImageCache::getFromMemory(BinaryData::wavedraw2_150_png, BinaryData::wavedraw2_150_pngSize);
	m_display.addWave(wavedraw2);
	juce::Image wavedraw3 = ImageCache::getFromMemory(BinaryData::wavedraw3_150_png, BinaryData::wavedraw3_150_pngSize);
	m_display.addWave(wavedraw3);
	juce::Image chipdraw1 = ImageCache::getFromMemory(BinaryData::chipdraw1_150_png, BinaryData::chipdraw1_150_pngSize);
	m_display.addWave(chipdraw1);
	juce::Image chipdraw2 = ImageCache::getFromMemory(BinaryData::chipdraw2_150_png, BinaryData::chipdraw2_150_pngSize);
	m_display.addWave(chipdraw2);
	juce::Image chipdraw3 = ImageCache::getFromMemory(BinaryData::chipdraw3_150_png, BinaryData::chipdraw3_150_pngSize);
	m_display.addWave(chipdraw3);
}