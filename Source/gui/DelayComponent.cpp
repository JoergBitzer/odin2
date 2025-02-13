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

#include "DelayComponent.h"
#include "../JuceLibraryCode/JuceHeader.h"

DelayComponent::DelayComponent(AudioProcessorValueTreeState &vts, bool p_is_standalone) :
    m_sync("sync", juce::DrawableButton::ButtonStyle::ImageRaw),
    m_pingpong("pingpong", juce::DrawableButton::ButtonStyle::ImageRaw), m_value_tree(vts),
    m_delay_synctime_denominator_identifier("delay_synctime_denominator"),
    m_delay_synctime_numerator_identifier("delay_synctime_numerator"), m_is_standalone_plugin(p_is_standalone) {

	m_delay_time_attach.reset(new OdinKnobAttachment(m_value_tree, "delay_time", m_time));
	m_delay_feedback_attach.reset(new OdinKnobAttachment(m_value_tree, "delay_feedback", m_feedback));
	m_delay_hp_attach.reset(new OdinKnobAttachment(m_value_tree, "delay_hp", m_HP));
	m_delay_ducking_attach.reset(new OdinKnobAttachment(m_value_tree, "delay_ducking", m_ducking));
	m_delay_dry_attach.reset(new OdinKnobAttachment(m_value_tree, "delay_dry", m_dry));
	m_delay_wet_attach.reset(new OdinKnobAttachment(m_value_tree, "delay_wet", m_wet));

	m_sync.setClickingTogglesState(true);
	m_sync.setTriggeredOnMouseDown(true);
	m_sync.setColour(juce::DrawableButton::ColourIds::backgroundOnColourId, juce::Colour());
	m_sync.setTooltip("Syncs the delay time to your track");
	addAndMakeVisible(m_sync);
	m_sync.onClick = [&]() {
		setSync(m_sync.getToggleState());
		m_value_tree.state.getChildWithName("fx").setProperty(
		    (Identifier)("delay_sync"), m_sync.getToggleState() ? 1.f : 0.f, nullptr);
		m_value_tree.state.getChildWithName("fx").sendPropertyChangeMessage((Identifier)("delay_sync"));
	};

	m_pingpong.setClickingTogglesState(true);
	m_pingpong.setTriggeredOnMouseDown(true);
	m_pingpong.setColour(juce::DrawableButton::ColourIds::backgroundOnColourId, juce::Colour());
	m_pingpong.setTooltip("Makes the left and right delay channels cross their feedback");
	addAndMakeVisible(m_pingpong);

	m_time.setSliderStyle(Slider::RotaryVerticalDrag);
	m_time.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	m_time.setRange(TIME_MIN, TIME_MAX);
	m_time.setTextValueSuffix(" s");
	m_time.setNumDecimalPlacesToDisplay(3);
	m_time.setKnobTooltip("The time for the signal to echo back");
	addAndMakeVisible(m_time);

	m_feedback.setSliderStyle(Slider::RotaryVerticalDrag);
	m_feedback.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	m_feedback.setKnobTooltip("How much to echo back");
	addAndMakeVisible(m_feedback);

	m_HP.setSliderStyle(Slider::RotaryVerticalDrag);
	m_HP.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	m_HP.setTextValueSuffix(" Hz");
	m_HP.setNumDecimalPlacesToDisplay(1);
	m_HP.setKnobTooltip("The cutoff frequency\n for a highpass filter\n which is "
	                    "applied\nto the signals");
	addAndMakeVisible(m_HP);

	m_ducking.setSliderStyle(Slider::RotaryVerticalDrag);
	m_ducking.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	m_ducking.setKnobTooltip("Lowers the wet volume\nwhen a signal is at the\ninput of the delay\nUse "
	                         "this to declutter\nyour sounds");
	addAndMakeVisible(m_ducking);

	m_dry.setSliderStyle(Slider::RotaryVerticalDrag);
	m_dry.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	m_dry.setKnobTooltip("Volume of the input signal");
	addAndMakeVisible(m_dry);

	m_wet.setSliderStyle(Slider::RotaryVerticalDrag);
	m_wet.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	m_wet.setKnobTooltip("Volume of the delayed signal only");
	addAndMakeVisible(m_wet);

	m_pingpong_attach.reset(new OdinButtonAttachment(m_value_tree, "delay_pingpong", m_pingpong));

	m_sync_time.OnValueChange = [&](int p_left, int p_right) {
		m_value_tree.state.getChildWithName("fx").setProperty(m_delay_synctime_numerator_identifier, p_left, nullptr);
		m_value_tree.state.getChildWithName("fx").setProperty(
		    m_delay_synctime_denominator_identifier, p_right, nullptr);
	};
	m_sync_time.setTopLeftPosition(SYNC_TIME_DELAY_POS_X, SYNC_TIME_DELAY_POS_Y);
	m_sync_time.setTooltip("Set the delay time in sync to your track");
	addChildComponent(m_sync_time);

	m_feedback.setNumDecimalPlacesToDisplay(3);
	m_ducking.setNumDecimalPlacesToDisplay(3);
	m_dry.setNumDecimalPlacesToDisplay(3);
	m_wet.setNumDecimalPlacesToDisplay(3);

	SET_CTR_KEY(m_time);
	SET_CTR_KEY(m_feedback);
	SET_CTR_KEY(m_HP);
	SET_CTR_KEY(m_ducking);
	SET_CTR_KEY(m_dry);
	SET_CTR_KEY(m_wet);

	forceValueTreeOntoComponents(m_value_tree.state);
}

DelayComponent::~DelayComponent() {
}

void DelayComponent::paint(Graphics &g) {
	g.setColour(COL_LIGHT);
	g.drawRect(getLocalBounds(), 1);
}

void DelayComponent::forceValueTreeOntoComponents(ValueTree p_tree) {
	m_sync_time.setValues(m_value_tree.state.getChildWithName("fx")[m_delay_synctime_numerator_identifier],
	                      m_value_tree.state.getChildWithName("fx")[m_delay_synctime_denominator_identifier]);
	m_sync.setToggleState((float)m_value_tree.state.getChildWithName("fx")["delay_sync"] > 0.5f, dontSendNotification);
	setSync((float)m_value_tree.state.getChildWithName("fx")["delay_sync"] > 0.5f);
	//send change message to set member in processor
	m_value_tree.state.getChildWithName("fx").sendPropertyChangeMessage((Identifier)("delay_sync"));
}

void DelayComponent::setGUIBig() {
	m_GUI_big = true;

	juce::Image sync_1 =
	    ImageCache::getFromMemory(BinaryData::buttonsync_1_150_png, BinaryData::buttonsync_1_150_pngSize);
	juce::Image sync_2 =
	    ImageCache::getFromMemory(BinaryData::buttonsync_2_150_png, BinaryData::buttonsync_2_150_pngSize);
	juce::Image sync_3 =
	    ImageCache::getFromMemory(BinaryData::buttonsync_3_150_png, BinaryData::buttonsync_3_150_pngSize);
	juce::Image sync_4 =
	    ImageCache::getFromMemory(BinaryData::buttonsync_4_150_png, BinaryData::buttonsync_4_150_pngSize);

	juce::DrawableImage sync_draw1;
	juce::DrawableImage sync_draw2;
	juce::DrawableImage sync_draw3;
	juce::DrawableImage sync_draw4;

	sync_draw1.setImage(sync_1);
	sync_draw2.setImage(sync_2);
	sync_draw3.setImage(sync_3);
	sync_draw4.setImage(sync_4);

	m_sync.setImages(
	    &sync_draw2, &sync_draw2, &sync_draw1, &sync_draw1, &sync_draw4, &sync_draw4, &sync_draw3, &sync_draw3);
	m_sync.setBounds(
	    OdinHelper::c150(DELAY_SYNC_POS_X), OdinHelper::c150(DELAY_SYNC_POS_Y), sync_1.getWidth(), sync_1.getHeight());

	juce::Image pingpong_1 =
	    ImageCache::getFromMemory(BinaryData::buttonpingpong_1_150_png, BinaryData::buttonpingpong_1_150_pngSize);
	juce::Image pingpong_2 =
	    ImageCache::getFromMemory(BinaryData::buttonpingpong_2_150_png, BinaryData::buttonpingpong_2_150_pngSize);
	juce::Image pingpong_3 =
	    ImageCache::getFromMemory(BinaryData::buttonpingpong_3_150_png, BinaryData::buttonpingpong_3_150_pngSize);
	juce::Image pingpong_4 =
	    ImageCache::getFromMemory(BinaryData::buttonpingpong_4_150_png, BinaryData::buttonpingpong_4_150_pngSize);

	juce::DrawableImage pingpong_draw1;
	juce::DrawableImage pingpong_draw2;
	juce::DrawableImage pingpong_draw3;
	juce::DrawableImage pingpong_draw4;

	pingpong_draw1.setImage(pingpong_1);
	pingpong_draw2.setImage(pingpong_2);
	pingpong_draw3.setImage(pingpong_3);
	pingpong_draw4.setImage(pingpong_4);

	m_pingpong.setImages(&pingpong_draw2,
	                     &pingpong_draw2,
	                     &pingpong_draw1,
	                     &pingpong_draw1,
	                     &pingpong_draw4,
	                     &pingpong_draw4,
	                     &pingpong_draw3,
	                     &pingpong_draw3);
	m_pingpong.setBounds(OdinHelper::c150(DELAY_PINGPONG_POS_X),
	                     OdinHelper::c150(DELAY_PINGPONG_POS_Y),
	                     pingpong_1.getWidth(),
	                     pingpong_1.getHeight());
	juce::Image metal_knob_big =
	    ImageCache::getFromMemory(BinaryData::metal_knob_big_150_png, BinaryData::metal_knob_big_150_pngSize);
	juce::Image black_knob_mid =
	    ImageCache::getFromMemory(BinaryData::black_knob_mid_150_png, BinaryData::black_knob_mid_150_pngSize);
	m_time.setStrip(metal_knob_big, N_KNOB_FRAMES);
	m_feedback.setStrip(metal_knob_big, N_KNOB_FRAMES);
	addAndMakeVisible(m_feedback);
	m_HP.setStrip(black_knob_mid, N_KNOB_FRAMES);
	m_ducking.setStrip(black_knob_mid, N_KNOB_FRAMES);
	m_dry.setStrip(black_knob_mid, N_KNOB_FRAMES);
	m_wet.setStrip(black_knob_mid, N_KNOB_FRAMES);
	m_sync_time.setTopLeftPosition(OdinHelper::c150(SYNC_TIME_DELAY_POS_X), OdinHelper::c150(SYNC_TIME_DELAY_POS_Y));

	m_time.setBounds(OdinHelper::c150(TIME_POS_X) - 2,
	                 OdinHelper::c150(TIME_POS_Y) - 2,
	                 OdinHelper::c150(METAL_KNOB_BIG_SIZE_X),
	                 OdinHelper::c150(METAL_KNOB_BIG_SIZE_Y));
	m_feedback.setBounds(OdinHelper::c150(FEEDBACK_POS_X) - 2,
	                     OdinHelper::c150(FEEDBACK_POS_Y) - 1,
	                     OdinHelper::c150(METAL_KNOB_BIG_SIZE_X),
	                     OdinHelper::c150(METAL_KNOB_BIG_SIZE_Y));
	m_HP.setBounds(OdinHelper::c150(DELAY_HP_POS_X) - 2,
	               OdinHelper::c150(DELAY_HP_POS_Y) - 2,
	               OdinHelper::c150(BLACK_KNOB_MID_SIZE_X),
	               OdinHelper::c150(BLACK_KNOB_MID_SIZE_Y));
	m_ducking.setBounds(OdinHelper::c150(DUCKING_POS_X) - 2,
	                    OdinHelper::c150(DUCKING_POS_Y) - 2,
	                    OdinHelper::c150(BLACK_KNOB_MID_SIZE_X),
	                    OdinHelper::c150(BLACK_KNOB_MID_SIZE_Y));
	m_dry.setBounds(OdinHelper::c150(DRY_POS_X) - 2,
	                OdinHelper::c150(DRY_POS_Y) - 2,
	                OdinHelper::c150(BLACK_KNOB_MID_SIZE_X),
	                OdinHelper::c150(BLACK_KNOB_MID_SIZE_Y));
	m_wet.setBounds(OdinHelper::c150(WET_POS_X) - 2,
	                OdinHelper::c150(WET_POS_Y) - 2,
	                OdinHelper::c150(BLACK_KNOB_MID_SIZE_X),
	                OdinHelper::c150(BLACK_KNOB_MID_SIZE_Y));

	juce::Image delay_image;
	if ((float)m_value_tree.state.getChildWithName("fx")["delay_sync"] < 0.5f) {
		delay_image = ImageCache::getFromMemory(BinaryData::delaynosync_150_png, BinaryData::delaynosync_150_pngSize);
	} else {
		delay_image = ImageCache::getFromMemory(BinaryData::delaysync_150_png, BinaryData::delaysync_150_pngSize);
	}
	setImage(delay_image);
	m_sync_time.setGUIBig();

	forceValueTreeOntoComponents(m_value_tree.state);
}

void DelayComponent::setGUISmall() {
	m_GUI_big = false;

	juce::Image sync_1 = ImageCache::getFromMemory(BinaryData::buttonsync_1_png, BinaryData::buttonsync_1_pngSize);
	juce::Image sync_2 = ImageCache::getFromMemory(BinaryData::buttonsync_2_png, BinaryData::buttonsync_2_pngSize);
	juce::Image sync_3 = ImageCache::getFromMemory(BinaryData::buttonsync_3_png, BinaryData::buttonsync_3_pngSize);
	juce::Image sync_4 = ImageCache::getFromMemory(BinaryData::buttonsync_4_png, BinaryData::buttonsync_4_pngSize);

	juce::DrawableImage sync_draw1;
	juce::DrawableImage sync_draw2;
	juce::DrawableImage sync_draw3;
	juce::DrawableImage sync_draw4;

	sync_draw1.setImage(sync_1);
	sync_draw2.setImage(sync_2);
	sync_draw3.setImage(sync_3);
	sync_draw4.setImage(sync_4);

	m_sync.setImages(
	    &sync_draw2, &sync_draw2, &sync_draw1, &sync_draw1, &sync_draw4, &sync_draw4, &sync_draw3, &sync_draw3);
	m_sync.setBounds(DELAY_SYNC_POS_X, DELAY_SYNC_POS_Y, sync_1.getWidth(), sync_1.getHeight());

	juce::Image pingpong_1 =
	    ImageCache::getFromMemory(BinaryData::buttonpingpong_1_png, BinaryData::buttonpingpong_1_pngSize);
	juce::Image pingpong_2 =
	    ImageCache::getFromMemory(BinaryData::buttonpingpong_2_png, BinaryData::buttonpingpong_2_pngSize);
	juce::Image pingpong_3 =
	    ImageCache::getFromMemory(BinaryData::buttonpingpong_3_png, BinaryData::buttonpingpong_3_pngSize);
	juce::Image pingpong_4 =
	    ImageCache::getFromMemory(BinaryData::buttonpingpong_4_png, BinaryData::buttonpingpong_4_pngSize);

	juce::DrawableImage pingpong_draw1;
	juce::DrawableImage pingpong_draw2;
	juce::DrawableImage pingpong_draw3;
	juce::DrawableImage pingpong_draw4;

	pingpong_draw1.setImage(pingpong_1);
	pingpong_draw2.setImage(pingpong_2);
	pingpong_draw3.setImage(pingpong_3);
	pingpong_draw4.setImage(pingpong_4);

	m_pingpong.setImages(&pingpong_draw2,
	                     &pingpong_draw2,
	                     &pingpong_draw1,
	                     &pingpong_draw1,
	                     &pingpong_draw4,
	                     &pingpong_draw4,
	                     &pingpong_draw3,
	                     &pingpong_draw3);
	m_pingpong.setBounds(DELAY_PINGPONG_POS_X, DELAY_PINGPONG_POS_Y, pingpong_1.getWidth(), pingpong_1.getHeight());
	juce::Image metal_knob_big =
	    ImageCache::getFromMemory(BinaryData::metal_knob_big_png, BinaryData::metal_knob_big_pngSize);
	juce::Image black_knob_mid =
	    ImageCache::getFromMemory(BinaryData::black_knob_mid_png, BinaryData::black_knob_mid_pngSize);
	m_time.setStrip(metal_knob_big, N_KNOB_FRAMES);
	m_feedback.setStrip(metal_knob_big, N_KNOB_FRAMES);
	addAndMakeVisible(m_feedback);
	m_HP.setStrip(black_knob_mid, N_KNOB_FRAMES);
	m_ducking.setStrip(black_knob_mid, N_KNOB_FRAMES);
	m_dry.setStrip(black_knob_mid, N_KNOB_FRAMES);
	m_wet.setStrip(black_knob_mid, N_KNOB_FRAMES);
	m_sync_time.setTopLeftPosition(SYNC_TIME_DELAY_POS_X, SYNC_TIME_DELAY_POS_Y);

	m_time.setBounds(TIME_POS_X, TIME_POS_Y, METAL_KNOB_BIG_SIZE_X, METAL_KNOB_BIG_SIZE_Y);
	m_feedback.setBounds(FEEDBACK_POS_X, FEEDBACK_POS_Y, METAL_KNOB_BIG_SIZE_X, METAL_KNOB_BIG_SIZE_Y);
	m_HP.setBounds(DELAY_HP_POS_X, DELAY_HP_POS_Y, BLACK_KNOB_MID_SIZE_X, BLACK_KNOB_MID_SIZE_Y);
	m_ducking.setBounds(DUCKING_POS_X, DUCKING_POS_Y, BLACK_KNOB_MID_SIZE_X, BLACK_KNOB_MID_SIZE_Y);
	m_dry.setBounds(DRY_POS_X, DRY_POS_Y, BLACK_KNOB_MID_SIZE_X, BLACK_KNOB_MID_SIZE_Y);
	m_wet.setBounds(WET_POS_X, WET_POS_Y, BLACK_KNOB_MID_SIZE_X, BLACK_KNOB_MID_SIZE_Y);

	juce::Image delay_image;
	if ((float)m_value_tree.state.getChildWithName("fx")["delay_sync"] < 0.5f) {
		delay_image = ImageCache::getFromMemory(BinaryData::delaynosync_png, BinaryData::delaynosync_pngSize);
	} else {
		delay_image = ImageCache::getFromMemory(BinaryData::delaysync_png, BinaryData::delaysync_pngSize);
	}
	m_sync_time.setGUISmall();
	setImage(delay_image);

	forceValueTreeOntoComponents(m_value_tree.state);
}

void DelayComponent::setSync(bool p_sync_on) {
	if (p_sync_on != m_sync_on) {
		m_sync_on = p_sync_on;

		if (m_GUI_big) {
			if (m_sync_on) {
				m_background =
				    ImageCache::getFromMemory(BinaryData::delaysync_150_png, BinaryData::delaysync_150_pngSize);
			} else {
				m_background =
				    ImageCache::getFromMemory(BinaryData::delaynosync_150_png, BinaryData::delaynosync_150_pngSize);
			}
		} else {
			if (m_sync_on) {
				m_background = ImageCache::getFromMemory(BinaryData::delaysync_png, BinaryData::delaysync_pngSize);
			} else {
				m_background = ImageCache::getFromMemory(BinaryData::delaynosync_png, BinaryData::delaynosync_pngSize);
			}
		}

		if (p_sync_on) {
			m_time.setVisible(false);
			m_sync_time.setVisible(true);
		} else {
			m_time.setVisible(true);
			m_sync_time.setVisible(false);
		}
		repaint();
	}
}