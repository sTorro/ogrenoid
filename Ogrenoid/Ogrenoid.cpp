/*
 * This file is part of Ogrenoid project.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version. This program is distributed in the hope that
 * it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with triviazo-project.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright ® 2014 Sergio Torró.
 */

#include "stdafx.h"
#include "Ogrenoid.hpp"

Ogrenoid::Ogrenoid(void) : m_root(new Ogre::Root), m_shutDown(false)
{
	if (!(m_root->showConfigDialog()))
		throw std::runtime_error("The user has cancelled the configuration dialog!");

	//Initialize the game
	m_renderWindow = m_root->initialise(true, "Ogrenoid");
	m_sceneManager = m_root->createSceneManager(Ogre::SceneType::ST_GENERIC);

	//Create the camera
	m_camera = m_sceneManager->createCamera("mainCamera");
	m_camera->setPosition(Ogre::Vector3(0, 0, 200));
	m_camera->lookAt(Ogre::Vector3(0, 0, 0));
	m_camera->setNearClipDistance(5);
	m_camera->setFarClipDistance(1000);

	//Set the viewport
	m_viewport = m_renderWindow->addViewport(m_camera);
	m_viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	//Aspect Ratio
	auto aspectRatio = Ogre::Real(m_viewport->getActualWidth()) / (m_viewport->getActualHeight());
	m_camera->setAspectRatio(aspectRatio);

	//Ambient light
	m_sceneManager->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));
	Ogre::Light* lightPtr = m_sceneManager->createLight("ambientLight");
	lightPtr->setPosition(0, 0, 50);

	//Render window parameters
	unsigned long hWnd;
	m_renderWindow->getCustomAttribute("WINDOW", &hWnd);
	OIS::ParamList paramList;
	paramList.insert(OIS::ParamList::value_type("WINDOW",
	                 Ogre::StringConverter::toString(hWnd)));

	//Keyboard
	m_inputManager = OIS::InputManager::createInputSystem(paramList);
	m_keyboard = static_cast<OIS::Keyboard*>(m_inputManager->createInputObject(OIS::OISKeyboard, true));
	m_keyboard->setEventCallback(this);

	//Add the frame listener to root
	m_root->addFrameListener(this);

	//TODO: Load resources
}

Ogrenoid::~Ogrenoid(void)
{
	m_inputManager->destroyInputObject(m_keyboard);
	OIS::InputManager::destroyInputSystem(m_inputManager);
	delete m_root;
}

//////////////////////////////////////////////////////////////////
// MAIN METHODS
//////////////////////////////////////////////////////////////////
void Ogrenoid::go(void)
{
	//if (!setup()) return;
	createScene();
	m_root->startRendering();
}

void Ogrenoid::createScene(void)
{
	//TODO
}

//////////////////////////////////////////////////////////////////
// RENDERING
//////////////////////////////////////////////////////////////////
bool Ogrenoid::frameStarted(const Ogre::FrameEvent& arg)
{
	m_keyboard->capture();
	return !m_shutDown;
}

bool Ogrenoid::frameEnded(const Ogre::FrameEvent& arg)
{
	return !m_shutDown;
}

//////////////////////////////////////////////////////////////////
// KEYBOARD
//////////////////////////////////////////////////////////////////
bool Ogrenoid::keyPressed(const OIS::KeyEvent& arg)
{
	return true;
}

bool Ogrenoid::keyReleased(const OIS::KeyEvent& arg)
{
	if (arg.key == OIS::KC_ESCAPE)
		m_shutDown = true;

	return true;
}