//
// Created by Eddie Hoyle on 14/11/16.
//

#ifndef SEVENGINE_WORKSHOP_WINDOW_HH
#define SEVENGINE_WORKSHOP_WINDOW_HH

#include "MainWindow.hh"


class Window : public QWidget
{
    Q_OBJECT

public:
    Window( MainWindow *mw );
    MainWindow* mainWindow;
};

#endif //SEVENGINE_WORKSHOP_WINDOW_HH
