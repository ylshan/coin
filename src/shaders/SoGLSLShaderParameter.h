#ifndef COIN_SOGLSLSHADERPARAMETER_H
#define COIN_SOGLSLSHADERPARAMETER_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

#ifndef COIN_INTERNAL
#error this is a private header file
#endif

// *************************************************************************

#include <Inventor/SbString.h>
#include <Inventor/C/glue/glp.h>

#include "SoGLShaderParameter.h"

// *************************************************************************

class SoGLSLShaderParameter : public SoGLShaderParameter
{
public: // satisfy SoGLShaderParameter protocol interface
  virtual SoShader::Type shaderType(void) const;

  virtual void set1f(const SoGLShaderObject * shader, const float value, const char * name, const int id);
  virtual void set2f(const SoGLShaderObject * shader, const float * value, const char * name, const int id);
  virtual void set3f(const SoGLShaderObject * shader, const float * value, const char * name, const int id);
  virtual void set4f(const SoGLShaderObject * shader, const float * value, const char * name, const int id);

  virtual void set1fv(const SoGLShaderObject * shader, const int num, const float* value, const char* name, const int id);
  virtual void set2fv(const SoGLShaderObject * shader, const int num, const float* value, const char* name, const int id);
  virtual void set3fv(const SoGLShaderObject * shader, const int num, const float* value, const char* name, const int id);
  virtual void set4fv(const SoGLShaderObject * shader, const int num, const float* value, const char* name, const int id);

  virtual void setMatrix(const SoGLShaderObject * shader, const float * value, const char * name, const int id);  
  virtual void setMatrixArray(const SoGLShaderObject * shader, const int num, const float * value, const char * name, const int id);

public:
  SoGLSLShaderParameter(void);
  virtual ~SoGLSLShaderParameter();

private:
  GLint    location;
  SbString cacheName;
  int      cacheSize;
  GLenum   cacheType;

  SbBool isValid(const SoGLShaderObject * shader, const char * name, 
		 GLenum type, int * num=NULL);
};

#endif /* ! COIN_SOGLSLSHADERPARAMETER_H */