/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2001 by Systems in Motion. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation. See the
 *  file LICENSE.LGPL at the root directory of the distribution for
 *  more details.
 *
 *  If you want to use Coin for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition license.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  http://www.sim.no support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
\**************************************************************************/

/*!
  \class SoToVRMLAction Inventor/include/SoToVRMLAction.h
  \brief The SoToVRMLAction class builds a new scene graph using only
  VRML 1.0 nodes.
*/

#include <Inventor/SbName.h>
#include <Inventor/actions/SoToVRMLAction.h>
#include <coindefs.h> // COIN_STUB()


SO_ACTION_SOURCE(SoToVRMLAction);

// Overridden from parent class.
void
SoToVRMLAction::initClass(void)
{
  SO_ACTION_INIT_CLASS(SoToVRMLAction, SoAction);
}


/*!
  A constructor.
*/

SoToVRMLAction::SoToVRMLAction(void)
{
  COIN_STUB();
}

/*!
  The destructor.
*/

SoToVRMLAction::~SoToVRMLAction(void)
{
  // FIXME: implement.
}

/*!
  This method is called before the traversal is begun.
*/

void
SoToVRMLAction::beginTraversal(SoNode * /* node */)
{
  COIN_STUB();
}
