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

#ifndef COIN_SONODEKITCATALOG_H
#define COIN_SONODEKITCATALOG_H

#include <Inventor/SoType.h>
#include <Inventor/lists/SbList.h>

class SbName;


#define SO_CATALOG_NAME_NOT_FOUND -1


class COIN_DLL_API SoNodekitCatalog {
public:
  static void initClass(void);

  SoNodekitCatalog(void);
  ~SoNodekitCatalog();

  int getNumEntries(void) const;
  int getPartNumber(const SbName & name) const;
  const SbName & getName(int part) const;

  SoType getType(int part) const;
  SoType getType(const SbName & name) const;
  SoType getDefaultType(int part) const;
  SoType getDefaultType(const SbName & name) const;
  SbBool isNullByDefault(int part) const;
  SbBool isNullByDefault(const SbName & name) const;

  SbBool isLeaf(int part) const;
  SbBool isLeaf(const SbName & name) const;
  const SbName & getParentName(int part) const;
  const SbName & getParentName(const SbName & name) const;
  int getParentPartNumber(int part) const;
  int getParentPartNumber(const SbName & name) const;
  const SbName & getRightSiblingName(int part) const;
  const SbName & getRightSiblingName(const SbName & name) const;
  int getRightSiblingPartNumber(int part) const;
  int getRightSiblingPartNumber(const SbName & name) const;

  SbBool isList(int part) const;
  SbBool isList(const SbName & name) const;
  SoType getListContainerType(int part) const;
  SoType getListContainerType(const SbName & name) const;
  const SoTypeList & getListItemTypes(int part) const;
  const SoTypeList & getListItemTypes(const SbName & name) const;

  SbBool isPublic(int part) const;
  SbBool isPublic(const SbName & name) const;

  SoNodekitCatalog * clone(SoType type) const;

  SbBool addEntry(const SbName & name, SoType type, SoType defaulttype,
                  SbBool isdefaultnull, const SbName & parent,
                  const SbName & rightsibling, SbBool islist,
                  SoType listcontainertype, SoType listitemtype,
                  SbBool ispublic);
  void addListItemType(int part, SoType type);
  void addListItemType(const SbName & name, SoType type);

  void narrowTypes(const SbName & name, SoType newtype, SoType newdefaulttype);
  void setNullByDefault(const SbName & name, SbBool nullbydefault);

  SbBool recursiveSearch(int part, const SbName & name,
                         SoTypeList * checked) const;

  void printCheck(void) const;

private:
  SbBool reallyAddEntry(class CatalogItem * newitem);

  int getPartNumber(const SbList<class CatalogItem *> & l,
                    const SbName & name) const;
  void addListItemType(const SbList<class CatalogItem *> & l,
                       int part, SoType type);
  SbBool addListItemType(const SbList<class CatalogItem *> & l,
                         const SbName & name, SoType type);

  SbList<class CatalogItem *> items;
  SbList<class CatalogItem *> delayeditems;
};

#endif // !COIN_SONODEKITCATALOG_H
