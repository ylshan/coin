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
  \class SoLinePatternElement Inventor/elements/SoLinePatternElement.h
  \brief The SoLinePatternElement class is yet to be documented.

  FIXME: write doc.
*/

#include <Inventor/elements/SoLinePatternElement.h>


#include <assert.h>

SO_ELEMENT_SOURCE(SoLinePatternElement);

/*!
  This static method initializes static data for the
  SoLinePatternElement class.
*/

void
SoLinePatternElement::initClass(void)
{
  SO_ELEMENT_INIT_CLASS(SoLinePatternElement, inherited);
}

/*!
  The destructor.
*/

SoLinePatternElement::~SoLinePatternElement(void)
{
}

//! FIXME: write doc.

void
SoLinePatternElement::set(SoState * const state,
                          SoNode * const node,
                          const int32_t pattern)
{
    SoInt32Element::set(classStackIndex, state, node, pattern);
}

//! FIXME: write doc.

void
SoLinePatternElement::init(SoState * state)
{
  inherited::init(state);

  this->data = SoLinePatternElement::getDefault();
}

//! FIXME: write doc.

//$ EXPORT INLINE
void
SoLinePatternElement::set(SoState * const state, const int32_t pattern)
{
  set(state, NULL, pattern);
}

//! FIXME: write doc.

//$ EXPORT INLINE
int32_t
SoLinePatternElement::get(SoState * const state)
{
  return SoInt32Element::get(classStackIndex, state);
}

//! FIXME: write doc.

//$ EXPORT INLINE
int32_t
SoLinePatternElement::getDefault()
{
  return CONTINUOUS;
}
