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

#pragma once
#ifndef _OGRENOID_H_
#define _OGRENOID_H_

#include "stdafx.h"

class Ogrenoid : public Ogre::FrameListener, public OIS::KeyListener
{
	public:
		Ogrenoid(void);
		~Ogrenoid(void);
		void go(void);

	protected:
		void createScene(void);

		// Rendering
		bool frameStarted(const Ogre::FrameEvent&);
		bool frameEnded(const Ogre::FrameEvent&);

		// Keyboard
		bool keyPressed(const OIS::KeyEvent&);
		bool keyReleased(const OIS::KeyEvent&);

	private:
		Ogre::Root* m_root;
		Ogre::SceneManager* m_sceneManager;
		Ogre::RenderWindow* m_renderWindow;
		Ogre::Viewport* m_viewport;
		Ogre::Camera* m_camera;

		OIS::InputManager* m_inputManager;
		OIS::Keyboard* m_keyboard;

		bool m_shutDown;
};

#endif //_OGRENOID_H_