#include <Common.h>

#include <GTA/UI/Text.h>
#include <GTA/UI/UI.h>

#include <shv/natives.h>

NAMESPACE_BEGIN;

UIText::UIText()
	: m_color(1.0f)
{
}

UIText::UIText(const std::string &text)
	: m_color(1.0f)
{
	m_text = text;
}

UIText::~UIText()
{
}

float UIText::Measure()
{
	UI::_SET_TEXT_ENTRY_FOR_WIDTH("STRING");
	uiAddLongString(m_text.c_str());
	return UI::_GET_TEXT_SCREEN_WIDTH(m_font);
}

int UIText::LineCount()
{
	if (!m_wrapping) {
		return 1;
	}

	UI::_SET_TEXT_GXT_ENTRY("STRING");
	uiAddLongString(m_text.c_str());
	return UI::_GET_TEXT_SCREEN_LINE_COUNT(0.0f, 0.5f);
}

void UIText::Render(const glm::vec2 &pos)
{
	glm::vec2 spos = uiScreenScale(pos);

	UI::SET_TEXT_FONT(m_font);
	UI::SET_TEXT_COLOUR((int)(m_color.r * 255.0f), (int)(m_color.g * 255.0f), (int)(m_color.b * 255.0f), (int)(m_color.a * 255.0f));
	UI::SET_TEXT_SCALE(1.0f, m_scale);

	if (m_align == UITA_Center) {
		UI::SET_TEXT_CENTRE(TRUE);
	} else if (m_align == UITA_Right) {
		UI::SET_TEXT_RIGHT_JUSTIFY(TRUE);
		UI::SET_TEXT_WRAP(0, spos.x);
	}

	if (m_dropShadow) {
		UI::SET_TEXT_DROP_SHADOW();
	}
	if (m_outline) {
		UI::SET_TEXT_OUTLINE();
	}

	if (m_wrapping) {
		float sWrapSize = m_wrapSize / (float)ui_screenWidth;
		UI::SET_TEXT_WRAP(spos.x, spos.x + sWrapSize);
	}

	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("jamyfafi"); //TODO: What is this magic string?
	uiAddLongString(m_text.c_str());
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(spos.x, spos.y);
}

NAMESPACE_END;