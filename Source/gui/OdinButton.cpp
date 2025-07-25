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

#include "OdinButton.h"
#include "../ConfigFileManager.h"
#include "../PluginProcessor.h"
#include "UIAssetManager.h"

OdinAudioProcessor *OdinButton::m_processor;

void OdinButton::paintButton(juce::Graphics &g, bool p_highlight, bool p_pressed) {

	if (m_type == Type::unassigned) {
		// this is still used on the Spline ad component

		static constexpr auto stroke = 1.5f;

		const juce::Colour spline_accent_colour    = juce::Colour(0xfff2960b);
		const juce::Colour spline_highlight_colour = juce::Colour(0xffD4C350);

        const auto corner = 4.0f;

		g.setColour(juce::Colours::black.withAlpha(0.2f));
		g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(stroke / 2.0f), corner);

		g.setColour(p_highlight ? spline_highlight_colour : spline_accent_colour);
		g.drawRoundedRectangle(getLocalBounds().toFloat().reduced(stroke / 2.0f), corner, stroke);

		if (getToggleState() && !p_highlight) {
			g.setColour(spline_accent_colour.withAlpha(0.15f));
			g.fillRoundedRectangle(getLocalBounds().toFloat().reduced(stroke / 2.0f), corner);
		}

		g.setColour(p_highlight ? spline_highlight_colour : spline_accent_colour);
		g.setFont(juce::Font(H * 0.6f, 1));
		g.drawText(m_button_text, getLocalBounds(), juce::Justification::centred, false);

		return;
	}

	// ordering of assets:
	//bttn_off.png
	//bttn_off_hover.png
	//bttn_off_pressed.png
	//bttn_on.png
	//bttn_on_hover.png
	//bttn_on_pressed.png

	auto asset = m_ui_asset_base;
	if (getToggleState()) {
		asset += 3;
	}

	if (p_pressed) {
		asset += 2;
	} else if (p_highlight) {
		asset += 1;
	}

	auto background  = UIAssetManager::getInstance()->getUIAsset(UIAssets::Indices(asset), ConfigFileManager::getInstance().getOptionGuiScale());
	const auto alpha = isEnabled() ? 1.0f : MODULE_DISABLED_ALPHA;
	g.setColour(juce::Colours::white.withAlpha(alpha));
	g.drawImageAt(background, 0, 0);

	const auto text_alpha = p_pressed ? 0.8f : alpha;
	auto colour           = getToggleState() ? COL_TEXT_BLUE_DARK : COL_TEXT_BLUE;

	g.setColour(colour.withAlpha(text_alpha));
	g.setFont(Helpers::getAldrichFont(float(H) * m_font_height_relative));
	g.drawText(m_button_text, getLocalBounds().removeFromBottom(proportionOfHeight(0.94f)), juce::Justification::centred, false);
}

void DoubleTextButton::paintButton(juce::Graphics &g, bool p_highlight, bool p_pressed) {
	auto asset = int(UIAssets::Indices::bttn_7x5_off);

	if (p_pressed) {
		asset += 2;
	} else if (p_highlight) {
		asset += 1;
	}

	auto background  = UIAssetManager::getInstance()->getUIAsset(UIAssets::Indices(asset), ConfigFileManager::getInstance().getOptionGuiScale());
	const auto alpha = isEnabled() ? 1.0f : MODULE_DISABLED_ALPHA;
	g.setColour(juce::Colours::white.withAlpha(alpha));
	g.drawImageAt(background, 0, 0);

	const auto text_alpha = p_pressed ? 0.8f : alpha;
	auto colour           = COL_TEXT_BLUE;

	g.setColour(colour.withAlpha(text_alpha));
	g.setFont(Helpers::getAldrichFont(float(H) * 0.4f));
	g.drawText(getToggleState() ? m_on_text : m_off_text, getLocalBounds().removeFromBottom(proportionOfHeight(0.94f)), juce::Justification::centred, false);
}