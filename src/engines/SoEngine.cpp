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
  \class SoEngine SoEngine.h Inventor/engines/SoEngine.h
  \brief SoEngine is the base class for Coin engines.
  \ingroup engines

  Engines enables the application programmers to make complex
  connections between fields.

  The most common cases where you use engines are: 1) to constrain the
  values of a field with regard to the contents of one or more other
  fields in the scene graph, 2) as a convenient way to animate parts
  of the scene graph.

  The reference count of an engine will be increased by 1 for each
  connection made to one of its engine outputs, and decreased by one
  for a disconnect. See SoEngineOutput::addConnection() and
  SoEngineOutput::removeConnection(). When the reference count goes
  down to zero, the engine will automatically be destroyed, and
  subsequent attempts at using the engine will lead to a crash.

  If you want complete control over when an engine gets destructed,
  use SoBase::ref() and SoBase::unref() for explicit
  referencing/dereferencing.
*/

#include <Inventor/engines/SoEngines.h>
#include <Inventor/engines/SoOutputData.h>
#include <Inventor/lists/SoEngineList.h>
#include <Inventor/lists/SoEngineOutputList.h>
#include <coindefs.h> // COIN_STUB()

#if COIN_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // COIN_DEBUG

// FIXME: document these properly. 20000405 mortene.
/*!
  \fn const SoEngineOutputData * SoEngine::getOutputData(void) const
  \internal
*/
/*!
  \fn void SoEngine::evaluate(void)
  \internal
*/


// Don't set value explicitly to SoType::badType(), to avoid a bug in
// Sun CC v4.0. (Bitpattern 0x0000 equals SoType::badType()).
SoType SoEngine::classTypeId;

#define FLAG_ISNOTIFYING 0x1

/*!
  Default constructor.
*/
SoEngine::SoEngine(void)
{
  this->flags = 0;
}

/*!
  Destructor.
*/
SoEngine::~SoEngine()
{
#if COIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoEngine::~SoEngine", "%p", this);
#endif // debug
}

// Overrides SoBase::destroy().
void
SoEngine::destroy(void)
{
#if COIN_DEBUG && 0 // debug
  SbName n = this->getName();
  SoType t = this->getTypeId();
  SoDebugError::postInfo("SoEngine::destroy", "start -- '%s' (%s)",
                         n.getString(),
                         t.getName().getString());
#endif // debug

  // evaluate() before we actually destruct. It would be too late
  // during the destructor, as the SoEngine::evaluate() method is pure
  // virtual.
  //
  // The explicit call here is done so attached fields will get the
  // chance to update before we die. SoField::disconnect() will
  // normally call SoEngine::evaluate(), but we disable that feature
  // by setting SoEngineOutput::isEnabled() to FALSE before
  // decoupling.
  this->evaluateWrapper();

  // SoBase destroy().
  inherited::destroy();

#if COIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoEngine::destroy", "done -- '%s' (%s)",
                         n.getString(),
                         t.getName().getString());
#endif // debug
}

// Doc from superclass.
void
SoEngine::initClass(void)
{
  SoEngine::classTypeId =
    SoType::createType(SoFieldContainer::getClassTypeId(), SbName("Engine"));

  SoEngine::initClasses();
}

/*!
  Initializes all engines. Automatically called from
  SoEngine::initClass() upon initialization of Coin.
*/
void
SoEngine::initClasses(void)
{
  SoBoolOperation::initClass();
  SoCalculator::initClass();
  SoComposeVec2f::initClass();
  SoComposeVec3f::initClass();
  SoComposeVec4f::initClass();
  SoDecomposeVec2f::initClass();
  SoDecomposeVec3f::initClass();
  SoDecomposeVec4f::initClass();
  SoComposeRotation::initClass();
  SoComposeRotationFromTo::initClass();
  SoDecomposeRotation::initClass();
  SoComposeMatrix::initClass();
  SoDecomposeMatrix::initClass();
  SoComputeBoundingBox::initClass();
  SoConcatenate::initClass();
  SoCounter::initClass();
  SoElapsedTime::initClass();
  SoFieldConverter::initClass();
  SoGate::initClass();
  SoInterpolate::initClass();
    SoInterpolateFloat::initClass();
    SoInterpolateRotation::initClass();
    SoInterpolateVec2f::initClass();
    SoInterpolateVec3f::initClass();
    SoInterpolateVec4f::initClass();
  SoOnOff::initClass();
  SoOneShot::initClass();
  SoSelectOne::initClass();
  SoTimeCounter::initClass();
  SoTransformVec3f::initClass();
  SoTriggerAny::initClass();
}

// overloaded from parent
SoType
SoEngine::getClassTypeId(void)
{
  return SoEngine::classTypeId;
}

/*!
  Adds all outputs to list. Returns the number of outputs added to the
  list.
*/
int
SoEngine::getOutputs(SoEngineOutputList & l) const
{
  const SoEngineOutputData * outputs = this->getOutputData();
  if (outputs == NULL) return 0;

  int n = outputs->getNumOutputs();
  for (int i = 0; i < n; i++) {
    l.append(outputs->getOutput(this, i));
  }
  return n;
}

/*!
  Returns the output with name \a outputname, or \c NULL if no such
  output exists.
*/
SoEngineOutput *
SoEngine::getOutput(const SbName & outputname) const
{
  const SoEngineOutputData * outputs = this->getOutputData();
  if (outputs == NULL) return NULL;
  int n = outputs->getNumOutputs();
  for (int i = 0; i < n; i++) {
    if (outputs->getOutputName(i) == outputname)
      return outputs->getOutput(this, i);
  }
  return NULL;
}

/*!
  Sets \outputname to the name of \a output. Returns \c FALSE if no
  such output is contained within the engine instance.
*/
SbBool
SoEngine::getOutputName(const SoEngineOutput * output,
                        SbName & outputname) const
{
  const SoEngineOutputData * outputs = this->getOutputData();
  if (outputs == NULL) return FALSE;

  int n = outputs->getNumOutputs();
  for (int i = 0; i < n; i++) {
    if (outputs->getOutput(this, i) == output) {
      outputname = outputs->getOutputName(i);
      return TRUE;
    }
  }
  return FALSE;
}

/*!
  Returns the engine named \a name, or \c NULL if no such engine
  exists.  If several engines have been registered under the same
  name, returns the \e last one which was registered.
*/
SoEngine *
SoEngine::getByName(const SbName & name)
{
  return (SoEngine *)SoBase::getNamedBase(name, SoEngine::getClassTypeId());
}

/*!
  Finds all engines named \a name. Returns the number of engines added
  to the \a el list.
*/
int
SoEngine::getByName(const SbName & name, SoEngineList & el)
{
  return SoBase::getNamedBases(name, el, SoEngine::getClassTypeId());
}

/*!
  Called when an input is changed. The default method does nothing,
  but subclasses may overload this method to do the The Right Thing
  when a specific field is changed.
*/
void
SoEngine::inputChanged(SoField * which)
{
}

// doc in parent
void
SoEngine::notify(SoNotList * nl)
{
#if COIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoEngine::notify", "%p - %s, start",
                         this, this->getTypeId().getName().getString());
#endif // debug

  // Avoid recursive notification calls.
  if (this->isNotifying()) return;
  this->flags |= FLAG_ISNOTIFYING;

  // FIXME: we don't add ourselves to the notification list. This
  // should probably be done, but I've postponed it until we see the
  // need to fix all interaction with the notification list. 20000911 mortene.


  // Let engine know that a field changed, so we can recalculate
  // internal variables, if necessary.
  this->inputChanged(nl->getLastField());

  // Notify the slave fields connected to our engine outputs.
  const SoEngineOutputData * outputs = this->getOutputData();
  int numoutputs = outputs->getNumOutputs();
  for (int i = 0; i < numoutputs; i++)
    outputs->getOutput(this, i)->touchSlaves(nl, this->isNotifyEnabled());

  this->flags &= ~FLAG_ISNOTIFYING;

#if COIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoEngine::notify", "%p - %s, done",
                         this, this->getTypeId().getName().getString());
#endif // debug
}

/*!
  Triggers an engine evaluation.
*/
void
SoEngine::evaluateWrapper(void)
{
  const SoEngineOutputData * outputs = this->getOutputData();
  int i, n = outputs->getNumOutputs();
  for (i = 0; i < n; i++) {
    outputs->getOutput(this, i)->prepareToWrite();
  }
  this->evaluate();
  for (i = 0; i < n; i++) {
    outputs->getOutput(this, i)->doneWriting();
  }
}

/*!
  Returns the SoFieldData class which holds information about inputs
  in this engine.
*/
const SoFieldData **
SoEngine::getInputDataPtr(void)
{
  return NULL; // base class has no output
}

/*!
  Returns the SoEngineOutputData class which holds information about
  the outputs in this engine.
*/
const SoEngineOutputData **
SoEngine::getOutputDataPtr(void)
{
  return NULL; // base class has no input
}

// overloaded from parent
SbBool
SoEngine::readInstance(SoInput * in, unsigned short flags)
{
  // FIXME: I believe there's code missing here for reading
  // SoUnknownEngine instances. 20000919 mortene.
  return inherited::readInstance(in, flags);
}

// overloaded from parent
void
SoEngine::writeInstance(SoOutput * out)
{
  if (this->writeHeader(out, FALSE, TRUE)) return;
  inherited::writeInstance(out);
  this->writeFooter(out);
}

/*!
  Writes the types of engine outputs for extension engines
  (i.e. engines not built in to Coin).
*/
void
SoEngine::writeOutputTypes(SoOutput * out)
{
  COIN_STUB();
}

/*!
  Returns a copy of the engine. Input connections are shallow copied.
*/
SoEngine *
SoEngine::copy(void) const
{
  // This code is like a combination of SoNode::copy() and
  // SoNode::addToCopyDict() (minus the children traversal -- engines
  // don't have children).

  SoFieldContainer::initCopyDict();

  // This snippet is the same as SoNode::addToCopyDict().
  SoEngine * cp = (SoEngine *)SoFieldContainer::checkCopy(this);
  if (!cp) {
    cp = (SoEngine *)this->getTypeId().createInstance();
    assert(cp);
    SoFieldContainer::addCopy(this, cp);
  }

  // Call findCopy() to have copyContents() run once.
  SoEngine * dummy = (SoEngine *)SoFieldContainer::findCopy(this, TRUE);
  assert(dummy == cp);

  SoFieldContainer::copyDone();
  return cp;
}

// Overloaded from parent class.
SoFieldContainer *
SoEngine::copyThroughConnection(void) const
{
  // Important note: _don't_ switch checkCopy() here with findCopy(),
  // as we're not supposed to create copies of containers "outside"
  // the part of the scene graph which is involved in the copy
  // operation.
  SoFieldContainer * connfc = SoFieldContainer::checkCopy(this);
  if (connfc) return connfc;

  // If we're outside the scenegraph.
  if (this->shouldCopy() == FALSE) return (SoFieldContainer *)this;

  // Ok, make the first copy and return its pointer.
  SoEngine * cp = (SoEngine *)SoFieldContainer::findCopy(this, TRUE);
  assert(cp);
  return cp;
}

/*!
  Returns whether this engine should be copied or simply referenced in
  a copy operation.

  Engines which are not really part of the scenegraph should not be
  copied.
*/
SbBool
SoEngine::shouldCopy(void) const
{
  SbBool result = FALSE;

  SoFieldList fl;
  int nr = this->getFields(fl);
  for (int i=0; i < nr; i++) {
    if (fl[i]->referencesCopy()) {
      result = TRUE;
      break;
    }
  }

#if COIN_DEBUG && 0 // debug
  SoDebugError::postInfo("SoEngine::shouldCopy", "%p - %s, result==%s",
                         this, this->getTypeId().getName().getString(),
                         result ? "TRUE" : "FALSE");
#endif // debug

  return result;
}

/*!
  Returns whether we're in a notification process. This is needed to
  avoid double notification when an engine enables outputs during
  inputChanged().
*/
SbBool
SoEngine::isNotifying(void) const
{
  return (this->flags & FLAG_ISNOTIFYING) != 0;
}
