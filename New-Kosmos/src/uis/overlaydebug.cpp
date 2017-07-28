﻿#include "overlaydebug.h"

overlaydebug::overlaydebug(uiobject *parent) :
	uiobject(parent, vector2(0.5f, 0.5f), vector2(1.0f, 1.0f))
{
	m_textFps = createStatus("FPS: 0", 0.94f);
	m_textUps = createStatus("UPS: 0", 0.97f);
	m_timerUpdate = new timer(0.333f);

	m_inputbutton = new inputbutton(this, vector2(0.5f, 0.3f), "Button", CENTRE);
	m_inputbutton->setActionLeft([&]()
	{
		std::cout << "Sample button pressed!" << std::endl;
	});

	m_inputslider = new inputslider(this, vector2(0.5f, 0.37f), "Slider", 0.0f, 1.0f, 0.333f, CENTRE);
	m_inputslider->setActionChange([&]()
	{
	});

	m_inputtext = new inputtext(this, vector2(0.5f, 0.44f), "Input: ", "value", CENTRE);
	m_inputtext->setActionChange([&]()
	{
	});

	m_inputmouse = new inputgrabber(this, vector2(0.5f, 0.51f), "Mouse Key: ", 0, new grabbermouse(), CENTRE);
	m_inputmouse->setActionChange([&]()
	{
	});

	m_inputkeyboard = new inputgrabber(this, vector2(0.5f, 0.58f), "Keyboard Key: ", 'w', new grabberkeyboard(), CENTRE);
	m_inputkeyboard->setActionChange([&]()
	{
	});
}

overlaydebug::~overlaydebug()
{
	delete m_textFps;
	delete m_textUps;

	delete m_inputbutton;
	delete m_inputslider;
	delete m_inputtext;
	delete m_inputmouse;
	delete m_inputkeyboard;
}

void overlaydebug::updateObject()
{
	if (m_timerUpdate->isPassedTime())
	{
		m_timerUpdate->resetStartTime();

		m_textFps->setText("FPS: " + std::to_string(static_cast<int>(1.0 / framework::get()->getDeltaRender())));
		m_textUps->setText("UPS: " + std::to_string(static_cast<int>(1.0 / framework::get()->getDelta())));
	}
}

text *overlaydebug::createStatus(const std::string &content, const float &positionY)
{
	text *result = new text(this, vector2(0.01f, 0.01f + positionY), content, 1.0f, uis::get()->candara, 0.5f, LEFT);
	result->setInScreenCoords(false);
	result->setTextColour(colour(1.0f, 1.0f, 1.0f));
	result->setBorderColour(colour(0.15f, 0.15f, 0.15f));
	result->setBorder(new driverconstant(0.04f));
	return result;
}