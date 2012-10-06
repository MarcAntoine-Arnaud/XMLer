// -*- C++ -*-
/* ------------------------------------ */
/* C++ class header (BaseXMLNode)       */
/* Author: Alexei Panov <me@elemc.name> */
/* ------------------------------------ */
/* Name: DocumentXMLNode
   Description:
*/
#ifndef DOCUMENTXMLNODE_H
#define DOCUMENTXMLNODE_H

#include <QtXml/QXmlStreamWriter>
#include <QtCore/QTextCodec>
#include <QtCore/QFile>
#include "basexmlnode.h"
#include "elementxmlnode.h"
#include "attrxmlnode.h"

class DocumentXMLNode : public BaseXMLNode
{
Q_OBJECT
public:
  explicit DocumentXMLNode();
  ~DocumentXMLNode();

  void appendChild(BaseXMLNode *child);
  quint32 childCount() const;
  XMLNodePtrList childs() const;
  QString name () const;
  QString qName () const;
  QString namespaceURI () const;

  BaseXMLNode *documentNode() const;

  void setFileName( const QString & name );
  QString fileName () const;
  void setCodec ( const QString & codecName );
  void setCodec ( QTextCodec * codec_in );
  void setVersion ( const QString & version );
  bool save ( const QString &fn );

private:
  BaseXMLNode *rootNode;
  QString _fileName;

  /* document settings */
  bool _document_auto_formatting;
  int _document_formatting_indent;

  QTextCodec *codec;
  QString _version;

  bool saveNode ( QXmlStreamWriter &writer,  BaseXMLNode *node );
  
};

#endif
