// -*- C++ -*-
/* ------------------------------------ */
/* C++ class source (QApplication)      */
/* Author: Alexei Panov <me@elemc.name> */
/* ------------------------------------ */
/* Name: XMLerApplication
   Description:
*/
#include "xmlerapplication.h"

XMLerApplication::XMLerApplication ( int & argc, char ** argv ) :
  QApplication(argc, argv)
{
#ifdef Q_WS_MAC
  setAttribute ( Qt::AA_DontShowIconsInMenus );
#endif
  autoOpenFiles.clear();
  if ( argc > 1) {
    for( int n = 1; n < argc; n++ ) {
      char *param = *(argv+n);
      QFile paramFile(param);
      if ( paramFile.exists() )
        autoOpenFiles.append( QString(param) );
    }
  }
  selectIconTheme ();
  setWindowIcon( QIcon::fromTheme( "XMLer" ) );
}

XMLerApplication::~XMLerApplication ()
{
  windowList.clear();
}

bool XMLerApplication::hasFilesInParams() const
{
  return ( autoOpenFiles.size() > 0 );
}

void XMLerApplication::openFiles ()
{
  int opened = 0;
  for ( int i = 0; i < autoOpenFiles.count(); i++ ) {
    MainWindow *mw = new MainWindow;
    mw->show();
    bool ok = mw->loadDocument( autoOpenFiles.at(i) );
    opened += 1;
  }

  if ( opened == 0 ) {
    MainWindow *mw = new MainWindow;
    mw->show();
    return;
  }
}
void XMLerApplication::selectIconTheme ()
{
  /* CLEANIT:
  QString generic_icon_to_check = "code-context";
  if ( !QIcon::hasThemeIcon( generic_icon_to_check ) )*/
  QString fallback_icon_theme = "oxygen-internal";
  QIcon::setThemeName( fallback_icon_theme );
}
bool XMLerApplication::notify ( QObject * receiver, QEvent * e )
{
  if ( e->type() == QEvent::Show ) {
    if ( MainWindow *mw = qobject_cast<MainWindow*>(receiver) )
      appendChildWindow ( mw );
  }
  else if ( e->type() == QEvent::Close ) {
    if ( MainWindow *mw = qobject_cast<MainWindow*>(receiver) )
      removeChildWindow ( mw );
  }
  else if ( e->type() == QEvent::WindowTitleChange ) {
    if ( MainWindow *mw = qobject_cast<MainWindow*>(receiver) )
      changedChildWindowTitle ( mw );
  }
  return QApplication::notify ( receiver, e );
}
void XMLerApplication::appendChildWindow ( MainWindow *mw )
{
  if ( !windowList.contains ( mw ) )
    windowList.append ( mw );
}
void XMLerApplication::removeChildWindow ( MainWindow *mw )
{
  if ( !windowList.contains ( mw ) )
    return;

  int idx = windowList.indexOf ( mw );
  windowList.removeAt ( idx );
}
void XMLerApplication::changedChildWindowTitle ( MainWindow *mw )
{
  // TODO: make something
}
