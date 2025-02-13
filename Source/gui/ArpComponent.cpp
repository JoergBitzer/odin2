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


#include "ArpComponent.h"
#include <JuceHeader.h>

ArpComponent::ArpComponent(OdinAudioProcessor &p_processor, AudioProcessorValueTreeState &vts) :
    m_processor(p_processor), m_value_tree(vts), m_step_0(vts, 0), m_step_1(vts, 1), m_step_2(vts, 2), m_step_3(vts, 3),
    m_step_4(vts, 4), m_step_5(vts, 5), m_step_6(vts, 6), m_step_7(vts, 7), m_step_8(vts, 8), m_step_9(vts, 9),
    m_step_10(vts, 10), m_step_11(vts, 11), m_step_12(vts, 12), m_step_13(vts, 13), m_step_14(vts, 14),
    m_step_15(vts, 15), m_on("arp_on", "On"),
    m_one_shot("arp_one_shot", "1-Shot"),m_mod_transpose("arp_mod_transpose", "Md/Trns") {
	addAndMakeVisible(m_step_0);
	addAndMakeVisible(m_step_1);
	addAndMakeVisible(m_step_2);
	addAndMakeVisible(m_step_3);
	addAndMakeVisible(m_step_4);
	addAndMakeVisible(m_step_5);
	addAndMakeVisible(m_step_6);
	addAndMakeVisible(m_step_7);
	addAndMakeVisible(m_step_8);
	addAndMakeVisible(m_step_9);
	addAndMakeVisible(m_step_10);
	addAndMakeVisible(m_step_11);
	addAndMakeVisible(m_step_12);
	addAndMakeVisible(m_step_13);
	addAndMakeVisible(m_step_14);
	addAndMakeVisible(m_step_15);

	m_octave_selector.OnValueChange = [&](int p_new_value) {
		m_value_tree.state.getChildWithName("misc").setProperty("arp_octaves", p_new_value, nullptr);
	};
	m_octave_selector.valueToText = [](int p_value) {
		if (p_value > 1) {
			return std::to_string(p_value) + " Octaves";
		} else {
			return std::to_string(p_value) + " Octave";
		}
	};
	m_octave_selector.setLegalValues({1, 2, 3, 4});

	addAndMakeVisible(m_octave_selector);
	m_octave_selector.setMouseDragDivisor(20.f);
	m_octave_selector.setColor(Colour(10, 40, 50));
	m_octave_selector.setTooltip("Sets how many octaves the arpeggio will play");

	m_steps_selector.OnValueChange = [&](int p_new_value) {
		setNumberLEDsToShow(p_new_value);
		m_value_tree.state.getChildWithName("misc").setProperty("arp_steps", p_new_value, nullptr);
	};
	m_steps_selector.valueToText = [](int p_value) {
		if (p_value > 1) {
			return std::to_string(p_value) + " Steps";
		} else {
			return std::to_string(p_value) + " Step";
		}
	};
	m_steps_selector.setLegalValues({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});

	addAndMakeVisible(m_steps_selector);
	m_steps_selector.setMouseDragDivisor(20.f);
	m_steps_selector.setColor(Colour(10, 40, 50));
	m_steps_selector.setTooltip("Sets how many steps the step sequence has before it wraps around");

	m_direction.OnValueChange = [&](int p_new_value) {
		m_value_tree.state.getChildWithName("misc").setProperty("arp_direction", p_new_value, nullptr);
	};
	m_direction.valueToText = [&](int p_value) {
		return OdinArpeggiator::ArpPatternToString((OdinArpeggiator::ArpPattern)p_value).toStdString();
	};
	m_direction.setLegalValues({(int)OdinArpeggiator::ArpPattern::Up,
	                            (int)OdinArpeggiator::ArpPattern::Down,
	                            (int)OdinArpeggiator::ArpPattern::UpAndDown,
	                            (int)OdinArpeggiator::ArpPattern::DownAndUp,
	                            (int)OdinArpeggiator::ArpPattern::Random,
	                            (int)OdinArpeggiator::ArpPattern::CrawlUp,
	                            (int)OdinArpeggiator::ArpPattern::CrawlDown});
	addAndMakeVisible(m_direction);
	m_direction.setMouseDragDivisor(20.f);
	m_direction.setColor(Colour(10, 40, 50));
	m_direction.setTooltip("Sets the direction of the arpeggio being played");

	m_gate.OnValueChange = [&](int p_new_value) {
		m_value_tree.state.getChildWithName("misc").setProperty("arp_gate", p_new_value, nullptr);
	};
	m_gate.valueToText = [&](int p_value) {
		if (p_value < 100) {
			return "Gate: " + std::to_string(p_value) + "%";
		} else {
			return "Gate " + std::to_string(p_value) + "%";
		}
	};
	m_gate.setLegalValues({10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 125, 150, 175, 200});
	addAndMakeVisible(m_gate);
	m_gate.setMouseDragDivisor(20.f);
	m_gate.setColor(Colour(10, 40, 50));
	m_gate.setTooltip("Sets how long each note is triggered, before a note-off is sent");

	m_sync_time.OnValueChange = [&](int p_left, int p_right) {
		m_value_tree.state.getChildWithName("misc").setProperty("arp_synctime_numerator", p_left, nullptr);
		m_value_tree.state.getChildWithName("misc").setProperty("arp_synctime_denominator", p_right, nullptr);
	};
	m_sync_time.setTooltip("Sets the time for the arpeggiator synced to the track");
	addAndMakeVisible(m_sync_time);

	m_on.setClickingTogglesState(true);
	addAndMakeVisible(m_on);
	m_on.setTooltip("Turns the arpeggiator on or off");
	m_on.setTriggeredOnMouseDown(true);
	m_on.setColour(juce::DrawableButton::ColourIds::backgroundOnColourId, juce::Colour());

	m_mod_transpose.setClickingTogglesState(true);
	addAndMakeVisible(m_mod_transpose);
	m_mod_transpose.setTooltip("Toggles between the knob-rows for mod 2 or transpose");
	m_mod_transpose.setTriggeredOnMouseDown(true);
	m_mod_transpose.setColour(juce::DrawableButton::ColourIds::backgroundOnColourId, juce::Colour());
	m_mod_transpose.onClick = [&](){
		setModTranspose(!m_mod_transpose.getToggleState());
	};

	m_one_shot.setClickingTogglesState(true);
	addAndMakeVisible(m_one_shot);
	m_one_shot.setTooltip("Makes the sequence stop after it ran through every step once");
	m_one_shot.setTriggeredOnMouseDown(true);
	m_one_shot.setColour(juce::DrawableButton::ColourIds::backgroundOnColourId, juce::Colour());

	m_on_attach.reset(new OdinButtonAttachment(m_value_tree, "arp_on", m_on));
	m_one_shot_attach.reset(new OdinButtonAttachment(m_value_tree, "arp_one_shot", m_one_shot));
	m_mod_transpose_attach.reset(new OdinButtonAttachment(m_value_tree, "arp_mod_transpose", m_mod_transpose));
}

ArpComponent::~ArpComponent() {
}

void ArpComponent::paint(Graphics &g) {
	//g.drawImageAt(m_background, 0, 0);
	//g.setColour(Colours::black);
	//g.drawRect(getLocalBounds(), 1); // draw an outline around the component
}

void ArpComponent::resized() {
}

void ArpComponent::setGUIBig() {
	m_GUI_big = true;

	m_octave_selector.setTopLeftPosition(OCTAVE_SELECTOR_X_150, OCTAVE_SELECTOR_Y_150);
	m_steps_selector.setTopLeftPosition(STEP_SELECTOR_X_150, STEP_SELECTOR_Y_150);
	m_direction.setTopLeftPosition(DIRECTION_SELECTOR_X_150, DIRECTION_SELECTOR_Y_150);
	m_gate.setTopLeftPosition(GATE_SELECTOR_X_150, GATE_SELECTOR_Y_150);
	m_sync_time.setTopLeftPosition(SYNC_TIME_ARP_POS_X_150, SYNC_TIME_ARP_POS_Y_150);

	juce::Image on_off_1 =
	    ImageCache::getFromMemory(BinaryData::button_on_off_1_150_png, BinaryData::button_on_off_1_150_pngSize);
	juce::Image on_off_2 =
	    ImageCache::getFromMemory(BinaryData::button_on_off_2_150_png, BinaryData::button_on_off_2_150_pngSize);
	juce::Image on_off_3 =
	    ImageCache::getFromMemory(BinaryData::button_on_off_3_150_png, BinaryData::button_on_off_3_150_pngSize);
	juce::Image on_off_4 =
	    ImageCache::getFromMemory(BinaryData::button_on_off_4_150_png, BinaryData::button_on_off_4_150_pngSize);

	juce::DrawableImage on_off_draw1;
	juce::DrawableImage on_off_draw2;
	juce::DrawableImage on_off_draw3;
	juce::DrawableImage on_off_draw4;

	on_off_draw1.setImage(on_off_1);
	on_off_draw2.setImage(on_off_2);
	on_off_draw3.setImage(on_off_3);
	on_off_draw4.setImage(on_off_4);
	m_on.setBounds(ON_OFF_POS_X_150, ON_OFF_POS_Y_150, on_off_1.getWidth(), on_off_1.getHeight());

	juce::Image one_shot_1 =
	    ImageCache::getFromMemory(BinaryData::button_one_shot_1_150_png, BinaryData::button_one_shot_1_150_pngSize);
	juce::Image one_shot_2 =
	    ImageCache::getFromMemory(BinaryData::button_one_shot_2_150_png, BinaryData::button_one_shot_2_150_pngSize);
	juce::Image one_shot_3 =
	    ImageCache::getFromMemory(BinaryData::button_one_shot_3_150_png, BinaryData::button_one_shot_3_150_pngSize);
	juce::Image one_shot_4 =
	    ImageCache::getFromMemory(BinaryData::button_one_shot_4_150_png, BinaryData::button_one_shot_4_150_pngSize);

	juce::DrawableImage one_shot_draw1;
	juce::DrawableImage one_shot_draw2;
	juce::DrawableImage one_shot_draw3;
	juce::DrawableImage one_shot_draw4;

	one_shot_draw1.setImage(one_shot_1);
	one_shot_draw2.setImage(one_shot_2);
	one_shot_draw3.setImage(one_shot_3);
	one_shot_draw4.setImage(one_shot_4);
	m_one_shot.setBounds(ONE_SHOT_POS_X_150, ONE_SHOT_POS_Y_150, one_shot_1.getWidth(), one_shot_1.getHeight());



	juce::Image mod_transpose_1 =
	    ImageCache::getFromMemory(BinaryData::button_mod_transpose_1_150_png, BinaryData::button_mod_transpose_1_150_pngSize);
	juce::Image mod_transpose_2 =
	    ImageCache::getFromMemory(BinaryData::button_mod_transpose_2_150_png, BinaryData::button_mod_transpose_2_150_pngSize);
	juce::Image mod_transpose_3 =
	    ImageCache::getFromMemory(BinaryData::button_mod_transpose_3_150_png, BinaryData::button_mod_transpose_3_150_pngSize);
	juce::Image mod_transpose_4 =
	    ImageCache::getFromMemory(BinaryData::button_mod_transpose_4_150_png, BinaryData::button_mod_transpose_4_150_pngSize);

	juce::DrawableImage mod_transpose_draw1;
	juce::DrawableImage mod_transpose_draw2;
	juce::DrawableImage mod_transpose_draw3;
	juce::DrawableImage mod_transpose_draw4;

	mod_transpose_draw1.setImage(mod_transpose_1);
	mod_transpose_draw2.setImage(mod_transpose_2);
	mod_transpose_draw3.setImage(mod_transpose_3);
	mod_transpose_draw4.setImage(mod_transpose_4);
	m_mod_transpose.setBounds(MOD_TRANSPOSE_POS_X_150, MOD_TRANSPOSE_POS_Y_150, mod_transpose_1.getWidth(), mod_transpose_1.getHeight());

	for (int step = 0; step < NUMBER_OF_STEPS; ++step) {

		m_step_0.setBounds(STEP_COMPONENT_POS_X_150 + 0 * STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_POS_Y_150,
		                   STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_HEIGHT_150);
		m_step_0.setGUIBig();

		m_step_1.setBounds(STEP_COMPONENT_POS_X_150 + 1 * STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_POS_Y_150,
		                   STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_HEIGHT_150);
		m_step_1.setGUIBig();

		m_step_2.setBounds(STEP_COMPONENT_POS_X_150 + 2 * STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_POS_Y_150,
		                   STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_HEIGHT_150);
		m_step_2.setGUIBig();

		m_step_3.setBounds(STEP_COMPONENT_POS_X_150 + 3 * STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_POS_Y_150,
		                   STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_HEIGHT_150);
		m_step_3.setGUIBig();

		m_step_4.setBounds(STEP_COMPONENT_POS_X_150 + 4 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150,
		                   STEP_COMPONENT_POS_Y_150,
		                   STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_HEIGHT_150);
		m_step_4.setGUIBig();

		m_step_5.setBounds(STEP_COMPONENT_POS_X_150 + 5 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150,
		                   STEP_COMPONENT_POS_Y_150,
		                   STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_HEIGHT_150);
		m_step_5.setGUIBig();

		m_step_6.setBounds(STEP_COMPONENT_POS_X_150 + 6 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150,
		                   STEP_COMPONENT_POS_Y_150,
		                   STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_HEIGHT_150);
		m_step_6.setGUIBig();

		m_step_7.setBounds(STEP_COMPONENT_POS_X_150 + 7 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150,
		                   STEP_COMPONENT_POS_Y_150,
		                   STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_HEIGHT_150);
		m_step_7.setGUIBig();

		m_step_8.setBounds(STEP_COMPONENT_POS_X_150 + 8 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150 * 2,
		                   STEP_COMPONENT_POS_Y_150,
		                   STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_HEIGHT_150);
		m_step_8.setGUIBig();

		m_step_9.setBounds(STEP_COMPONENT_POS_X_150 + 9 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150 * 2,
		                   STEP_COMPONENT_POS_Y_150,
		                   STEP_COMPONENT_WIDTH_150,
		                   STEP_COMPONENT_HEIGHT_150);
		m_step_9.setGUIBig();

		m_step_10.setBounds(STEP_COMPONENT_POS_X_150 + 10 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150 * 2,
		                    STEP_COMPONENT_POS_Y_150,
		                    STEP_COMPONENT_WIDTH_150,
		                    STEP_COMPONENT_HEIGHT_150);
		m_step_10.setGUIBig();

		m_step_11.setBounds(STEP_COMPONENT_POS_X_150 + 11 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150 * 2,
		                    STEP_COMPONENT_POS_Y_150,
		                    STEP_COMPONENT_WIDTH_150,
		                    STEP_COMPONENT_HEIGHT_150);
		m_step_11.setGUIBig();

		m_step_12.setBounds(STEP_COMPONENT_POS_X_150 + 12 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150 * 3,
		                    STEP_COMPONENT_POS_Y_150,
		                    STEP_COMPONENT_WIDTH_150,
		                    STEP_COMPONENT_HEIGHT_150);
		m_step_12.setGUIBig();

		m_step_13.setBounds(STEP_COMPONENT_POS_X_150 + 13 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150 * 3,
		                    STEP_COMPONENT_POS_Y_150,
		                    STEP_COMPONENT_WIDTH_150,
		                    STEP_COMPONENT_HEIGHT_150);
		m_step_13.setGUIBig();

		m_step_14.setBounds(STEP_COMPONENT_POS_X_150 + 14 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150 * 3,
		                    STEP_COMPONENT_POS_Y_150,
		                    STEP_COMPONENT_WIDTH_150,
		                    STEP_COMPONENT_HEIGHT_150);
		m_step_14.setGUIBig();

		m_step_15.setBounds(STEP_COMPONENT_POS_X_150 + 15 * STEP_COMPONENT_WIDTH_150 + STEP_COMPONENT_SPACING_150 * 3,
		                    STEP_COMPONENT_POS_Y_150,
		                    STEP_COMPONENT_WIDTH_150,
		                    STEP_COMPONENT_HEIGHT_150);
		m_step_15.setGUIBig();
	}

	//m_background = ImageCache::getFromMemory(BinaryData::arp_backdrop_150_png, BinaryData::arp_backdrop_150_pngSize);


	//DBG("SIZE: " + std::to_string(getX()) + ", " + std::to_string(getY()) + ", " + std::to_string(getWidth()) + ", " + std::to_string(getHeight()) );
}
void ArpComponent::setGUISmall() {
	m_GUI_big = false;

	m_octave_selector.setTopLeftPosition(OCTAVE_SELECTOR_X_100, OCTAVE_SELECTOR_Y_100);
	m_steps_selector.setTopLeftPosition(STEP_SELECTOR_X_100, STEP_SELECTOR_Y_100);
	m_direction.setTopLeftPosition(DIRECTION_SELECTOR_X_100, DIRECTION_SELECTOR_Y_100);
	m_gate.setTopLeftPosition(GATE_SELECTOR_X_100, GATE_SELECTOR_Y_100);
	m_sync_time.setTopLeftPosition(SYNC_TIME_ARP_POS_X_100, SYNC_TIME_ARP_POS_Y_100);

	juce::Image on_off_1 =
	    ImageCache::getFromMemory(BinaryData::button_on_off_1_png, BinaryData::button_on_off_1_pngSize);
	juce::Image on_off_2 =
	    ImageCache::getFromMemory(BinaryData::button_on_off_2_png, BinaryData::button_on_off_2_pngSize);
	juce::Image on_off_3 =
	    ImageCache::getFromMemory(BinaryData::button_on_off_3_png, BinaryData::button_on_off_3_pngSize);
	juce::Image on_off_4 =
	    ImageCache::getFromMemory(BinaryData::button_on_off_4_png, BinaryData::button_on_off_4_pngSize);

	juce::DrawableImage on_off_draw1;
	juce::DrawableImage on_off_draw2;
	juce::DrawableImage on_off_draw3;
	juce::DrawableImage on_off_draw4;

	on_off_draw1.setImage(on_off_1);
	on_off_draw2.setImage(on_off_2);
	on_off_draw3.setImage(on_off_3);
	on_off_draw4.setImage(on_off_4);
	m_on.setBounds(ON_OFF_POS_X_100, ON_OFF_POS_Y_100, on_off_1.getWidth(), on_off_1.getHeight());

	juce::Image one_shot_1 =
	    ImageCache::getFromMemory(BinaryData::button_one_shot_1_png, BinaryData::button_one_shot_1_pngSize);
	juce::Image one_shot_2 =
	    ImageCache::getFromMemory(BinaryData::button_one_shot_2_png, BinaryData::button_one_shot_2_pngSize);
	juce::Image one_shot_3 =
	    ImageCache::getFromMemory(BinaryData::button_one_shot_3_png, BinaryData::button_one_shot_3_pngSize);
	juce::Image one_shot_4 =
	    ImageCache::getFromMemory(BinaryData::button_one_shot_4_png, BinaryData::button_one_shot_4_pngSize);

	juce::DrawableImage one_shot_draw1;
	juce::DrawableImage one_shot_draw2;
	juce::DrawableImage one_shot_draw3;
	juce::DrawableImage one_shot_draw4;

	one_shot_draw1.setImage(one_shot_1);
	one_shot_draw2.setImage(one_shot_2);
	one_shot_draw3.setImage(one_shot_3);
	one_shot_draw4.setImage(one_shot_4);
	m_one_shot.setBounds(ONE_SHOT_POS_X_100, ONE_SHOT_POS_Y_100, one_shot_1.getWidth(), one_shot_1.getHeight());

	juce::Image mod_transpose_1 =
	    ImageCache::getFromMemory(BinaryData::button_mod_transpose_1_png, BinaryData::button_mod_transpose_1_pngSize);
	juce::Image mod_transpose_2 =
	    ImageCache::getFromMemory(BinaryData::button_mod_transpose_2_png, BinaryData::button_mod_transpose_2_pngSize);
	juce::Image mod_transpose_3 =
	    ImageCache::getFromMemory(BinaryData::button_mod_transpose_3_png, BinaryData::button_mod_transpose_3_pngSize);
	juce::Image mod_transpose_4 =
	    ImageCache::getFromMemory(BinaryData::button_mod_transpose_4_png, BinaryData::button_mod_transpose_4_pngSize);

	juce::DrawableImage mod_transpose_draw1;
	juce::DrawableImage mod_transpose_draw2;
	juce::DrawableImage mod_transpose_draw3;
	juce::DrawableImage mod_transpose_draw4;

	mod_transpose_draw1.setImage(mod_transpose_1);
	mod_transpose_draw2.setImage(mod_transpose_2);
	mod_transpose_draw3.setImage(mod_transpose_3);
	mod_transpose_draw4.setImage(mod_transpose_4);
	m_mod_transpose.setBounds(MOD_TRANSPOSE_POS_X_100, MOD_TRANSPOSE_POS_Y_100, mod_transpose_1.getWidth(), mod_transpose_1.getHeight());


	for (int step = 0; step < NUMBER_OF_STEPS; ++step) {

		m_step_0.setBounds(STEP_COMPONENT_POS_X_100 + 0 * STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_POS_Y_100,
		                   STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_HEIGHT_100);
		m_step_0.setGUISmall();

		m_step_1.setBounds(STEP_COMPONENT_POS_X_100 + 1 * STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_POS_Y_100,
		                   STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_HEIGHT_100);
		m_step_1.setGUISmall();

		m_step_2.setBounds(STEP_COMPONENT_POS_X_100 + 2 * STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_POS_Y_100,
		                   STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_HEIGHT_100);
		m_step_2.setGUISmall();

		m_step_3.setBounds(STEP_COMPONENT_POS_X_100 + 3 * STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_POS_Y_100,
		                   STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_HEIGHT_100);
		m_step_3.setGUISmall();

		m_step_4.setBounds(STEP_COMPONENT_POS_X_100 + 4 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100,
		                   STEP_COMPONENT_POS_Y_100,
		                   STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_HEIGHT_100);
		m_step_4.setGUISmall();

		m_step_5.setBounds(STEP_COMPONENT_POS_X_100 + 5 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100,
		                   STEP_COMPONENT_POS_Y_100,
		                   STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_HEIGHT_100);
		m_step_5.setGUISmall();

		m_step_6.setBounds(STEP_COMPONENT_POS_X_100 + 6 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100,
		                   STEP_COMPONENT_POS_Y_100,
		                   STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_HEIGHT_100);
		m_step_6.setGUISmall();

		m_step_7.setBounds(STEP_COMPONENT_POS_X_100 + 7 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100,
		                   STEP_COMPONENT_POS_Y_100,
		                   STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_HEIGHT_100);
		m_step_7.setGUISmall();

		m_step_8.setBounds(STEP_COMPONENT_POS_X_100 + 8 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100 * 2,
		                   STEP_COMPONENT_POS_Y_100,
		                   STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_HEIGHT_100);
		m_step_8.setGUISmall();

		m_step_9.setBounds(STEP_COMPONENT_POS_X_100 + 9 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100 * 2,
		                   STEP_COMPONENT_POS_Y_100,
		                   STEP_COMPONENT_WIDTH_100,
		                   STEP_COMPONENT_HEIGHT_100);
		m_step_9.setGUISmall();

		m_step_10.setBounds(STEP_COMPONENT_POS_X_100 + 10 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100 * 2,
		                    STEP_COMPONENT_POS_Y_100,
		                    STEP_COMPONENT_WIDTH_100,
		                    STEP_COMPONENT_HEIGHT_100);
		m_step_10.setGUISmall();

		m_step_11.setBounds(STEP_COMPONENT_POS_X_100 + 11 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100 * 2,
		                    STEP_COMPONENT_POS_Y_100,
		                    STEP_COMPONENT_WIDTH_100,
		                    STEP_COMPONENT_HEIGHT_100);
		m_step_11.setGUISmall();

		m_step_12.setBounds(STEP_COMPONENT_POS_X_100 + 12 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100 * 3,
		                    STEP_COMPONENT_POS_Y_100,
		                    STEP_COMPONENT_WIDTH_100,
		                    STEP_COMPONENT_HEIGHT_100);
		m_step_12.setGUISmall();

		m_step_13.setBounds(STEP_COMPONENT_POS_X_100 + 13 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100 * 3,
		                    STEP_COMPONENT_POS_Y_100,
		                    STEP_COMPONENT_WIDTH_100,
		                    STEP_COMPONENT_HEIGHT_100);
		m_step_13.setGUISmall();

		m_step_14.setBounds(STEP_COMPONENT_POS_X_100 + 14 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100 * 3,
		                    STEP_COMPONENT_POS_Y_100,
		                    STEP_COMPONENT_WIDTH_100,
		                    STEP_COMPONENT_HEIGHT_100);
		m_step_14.setGUISmall();

		m_step_15.setBounds(STEP_COMPONENT_POS_X_100 + 15 * STEP_COMPONENT_WIDTH_100 + STEP_COMPONENT_SPACING_100 * 3,
		                    STEP_COMPONENT_POS_Y_100,
		                    STEP_COMPONENT_WIDTH_100,
		                    STEP_COMPONENT_HEIGHT_100);
		m_step_15.setGUISmall();
	}
	//DBG("SIZE: " + std::to_string(getX()) + ", " + std::to_string(getY()) + ", " + std::to_string(getWidth()) + ", " + std::to_string(getHeight()) );

	//m_background = ImageCache::getFromMemory(BinaryData::arp_backdrop_png, BinaryData::arp_backdrop_pngSize);
}

void ArpComponent::timerCallback() {
	int led_active = m_processor.m_step_led_active.get();

	if (led_active != -1) {
		setLEDActive(led_active);
	} else {
		setNoLEDActive();
	}
}

void ArpComponent::setLEDActive(int p_LED) {
	m_step_0.setLEDActive(p_LED);
	m_step_1.setLEDActive(p_LED);
	m_step_2.setLEDActive(p_LED);
	m_step_3.setLEDActive(p_LED);
	m_step_4.setLEDActive(p_LED);
	m_step_5.setLEDActive(p_LED);
	m_step_6.setLEDActive(p_LED);
	m_step_7.setLEDActive(p_LED);
	m_step_8.setLEDActive(p_LED);
	m_step_9.setLEDActive(p_LED);
	m_step_10.setLEDActive(p_LED);
	m_step_11.setLEDActive(p_LED);
	m_step_12.setLEDActive(p_LED);
	m_step_13.setLEDActive(p_LED);
	m_step_14.setLEDActive(p_LED);
	m_step_15.setLEDActive(p_LED);
}

void ArpComponent::setNoLEDActive() {
	m_step_0.setLEDActive(-1);
	m_step_1.setLEDActive(-1);
	m_step_2.setLEDActive(-1);
	m_step_3.setLEDActive(-1);
	m_step_4.setLEDActive(-1);
	m_step_5.setLEDActive(-1);
	m_step_6.setLEDActive(-1);
	m_step_7.setLEDActive(-1);
	m_step_8.setLEDActive(-1);
	m_step_9.setLEDActive(-1);
	m_step_10.setLEDActive(-1);
	m_step_11.setLEDActive(-1);
	m_step_12.setLEDActive(-1);
	m_step_13.setLEDActive(-1);
	m_step_14.setLEDActive(-1);
	m_step_15.setLEDActive(-1);
}

void ArpComponent::setNumberLEDsToShow(int p_number) {
	m_step_0.setShowLED(p_number);
	m_step_1.setShowLED(p_number);
	m_step_2.setShowLED(p_number);
	m_step_3.setShowLED(p_number);
	m_step_4.setShowLED(p_number);
	m_step_5.setShowLED(p_number);
	m_step_6.setShowLED(p_number);
	m_step_7.setShowLED(p_number);
	m_step_8.setShowLED(p_number);
	m_step_9.setShowLED(p_number);
	m_step_10.setShowLED(p_number);
	m_step_11.setShowLED(p_number);
	m_step_12.setShowLED(p_number);
	m_step_13.setShowLED(p_number);
	m_step_14.setShowLED(p_number);
	m_step_15.setShowLED(p_number);
}

void ArpComponent::forceValueTreeOntoComponents(ValueTree p_tree) {

	m_octave_selector.setValue((int)m_value_tree.state.getChildWithName("misc")["arp_octaves"]);

	setNumberLEDsToShow((int)m_value_tree.state.getChildWithName("misc")["arp_steps"]);
	m_steps_selector.setValue((int)m_value_tree.state.getChildWithName("misc")["arp_steps"]);

	m_direction.setValue((int)m_value_tree.state.getChildWithName("misc")["arp_direction"]);
	m_gate.setValue((int)m_value_tree.state.getChildWithName("misc")["arp_gate"]);
	m_sync_time.setValues((int)m_value_tree.state.getChildWithName("misc")["arp_synctime_numerator"],
	                      (int)m_value_tree.state.getChildWithName("misc")["arp_synctime_denominator"]);

	setModTranspose(!m_mod_transpose.getToggleState());
}


void ArpComponent::setVisibleAndStartTimer(bool p_set_visible){
	if(p_set_visible){
		startTimer(ARP_TIMER_MILLISECS);
	} else {
		stopTimer();
	}
	setVisible(p_set_visible);
}


void ArpComponent::setModTranspose(bool p_is_mod){
	m_step_0.setModTranspose(p_is_mod);
	m_step_1.setModTranspose(p_is_mod);
	m_step_2.setModTranspose(p_is_mod);
	m_step_3.setModTranspose(p_is_mod);
	m_step_4.setModTranspose(p_is_mod);
	m_step_5.setModTranspose(p_is_mod);
	m_step_6.setModTranspose(p_is_mod);
	m_step_7.setModTranspose(p_is_mod);
	m_step_8.setModTranspose(p_is_mod);
	m_step_9.setModTranspose(p_is_mod);
	m_step_10.setModTranspose(p_is_mod);
	m_step_11.setModTranspose(p_is_mod);
	m_step_12.setModTranspose(p_is_mod);
	m_step_13.setModTranspose(p_is_mod);
	m_step_14.setModTranspose(p_is_mod);
	m_step_15.setModTranspose(p_is_mod);
}