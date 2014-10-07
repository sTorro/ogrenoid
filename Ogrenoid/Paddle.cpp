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
#include "Paddle.hpp"

Paddle::Paddle(Ogre::SceneManager* sceneManager)
	: m_sceneManager(sceneManager)
{
	//Add the ball to the scene
	Ogre::Entity* paddleEntity = m_sceneManager->createEntity("Paddle", "cube.mesh");
	// Create a SceneNode and attach the Entity to it
	m_paddleNode = m_sceneManager->getRootSceneNode()->createChildSceneNode("PaddleNode");
	m_paddleNode->attachObject(paddleEntity);
	m_paddleNode->setScale(Ogre::Real(12.0F), Ogre::Real(2.0F), Ogre::Real(2.0F));
	m_paddleNode->setPosition(0.0F, -70.0F, 0.0f);
}

Paddle::~Paddle(void)
{
	//Empty
}
