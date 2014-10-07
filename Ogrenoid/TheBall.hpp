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
#ifndef _THE_BALL_H_
#define _THE_BALL_H_

class TheBall
{
	public:
		explicit TheBall(Ogre::SceneManager*);
		~TheBall(void);

		void move(Ogre::Real);

	private:
		Ogre::SceneManager* m_sceneManager;
		Ogre::SceneNode* m_ballNode;
		int m_speed;
		Ogre::Vector3 m_direction;
};

#endif //_THE_BALL_H_