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
#include "TheBall.hpp"

TheBall::TheBall(Ogre::SceneManager* sceneManager)
	: m_sceneManager(sceneManager), m_speed(100), m_direction(Ogre::Vector3(1, -1, 0))
{
	//Add the ball to the scene
	Ogre::Entity* ballEntity = m_sceneManager->createEntity("Ball", "theBall.mesh");
	// Create a SceneNode and attach the Entity to it
	m_ballNode = m_sceneManager->getRootSceneNode()->createChildSceneNode("BallNode");
	m_ballNode->attachObject(ballEntity);
	m_ballNode->setScale(Ogre::Real(2.0F), Ogre::Real(2.0F), Ogre::Real(2.0F));
}

TheBall::~TheBall(void)
{
	//Empty
}

void TheBall::move(Ogre::Real time)
{
	m_ballNode->translate((m_direction * (m_speed * time)));

	//TODO check collisions and change direction...
}