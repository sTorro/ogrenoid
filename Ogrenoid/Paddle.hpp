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
#ifndef _PADDLE_H_
#define _PADDLE_H_

class Paddle
{
	public:
		explicit Paddle(Ogre::SceneManager*);
		~Paddle(void);

	private:
		Ogre::SceneManager* m_sceneManager;
		Ogre::SceneNode* m_paddleNode;
};

#endif //_PADDLE_H_