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

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("assets/meshes",
	    "FileSystem", "meshes" );
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
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
	m_theBall = new TheBall(m_sceneManager);
	m_playerPaddle = new Paddle(m_sceneManager);

	//Left wall
	auto leftWallEntity = m_sceneManager->createEntity("leftWall", "cube.mesh");
	auto leftWallNode = m_sceneManager->getRootSceneNode()->createChildSceneNode("leftWall");
	leftWallNode->attachObject(leftWallEntity);
	leftWallNode->setPosition(-110, 0, 0);
	leftWallNode->setScale(2.0, 100.00, 1.0);

	//Right wall
	auto rightWallEntity = m_sceneManager->createEntity("rightWall", "cube.mesh");
	auto rightWallNode = m_sceneManager->getRootSceneNode()->createChildSceneNode("rightWall");
	rightWallNode->attachObject(rightWallEntity);
	rightWallNode->setPosition(110, 0, 0);
	rightWallNode->setScale(2.0, 100.00, 1.0);

	//Upper wall
	auto upperWallEntity = m_sceneManager->createEntity("upperWall", "cube.mesh");
	auto upperWallNode = m_sceneManager->getRootSceneNode()->createChildSceneNode("upperWall");
	upperWallNode->attachObject(upperWallEntity);
	upperWallNode->setPosition(0, 82, 0);
	upperWallNode->setScale(190.0, 2.0, 1.0);

	//Bottom wall
	auto bottomWallEntity = m_sceneManager->createEntity("bottomWall", "cube.mesh");
	auto bottomWallNode = m_sceneManager->getRootSceneNode()->createChildSceneNode("bottomWall");
	bottomWallNode->attachObject(bottomWallEntity);
	bottomWallNode->setPosition(0, -82, 0);
	bottomWallNode->setScale(190.0, 2.0, 1.0);

	//Ambient light
	m_sceneManager->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));
	Ogre::Light* lightPtr = m_sceneManager->createLight("ambientLight");
	lightPtr->setPosition(0, 0, 50);
}

//////////////////////////////////////////////////////////////////
// RENDERING
//////////////////////////////////////////////////////////////////
bool Ogrenoid::frameStarted(const Ogre::FrameEvent& arg)
{
	m_keyboard->capture();
	m_theBall->move(arg.timeSinceLastFrame);

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