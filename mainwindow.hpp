#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFunctionPointer>
#include "customsquare.hpp"
#include "CFRThread.hpp"
#include <QGridLayout>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow
{
  Q_OBJECT
  QVector<CustomSquare*> squares;
  QVector<QLabel*> columnLabels; // Keep track of column labels
  QVector<QLabel*> rowLabels; // Keep track of row labels

 public:
  MainWindow();

 protected:
#ifndef QT_NO_CONTEXTMENU
  void contextMenuEvent(QContextMenuEvent *event) override;
#endif // QT_NO_CONTEXTMENU

 private slots:
  void texasHoldem();
  void preFlop();
  void iterations();
  void maxBets();
  void start();
  void pause();
  void stop();
  void copy();
  void paste();
  void bold();
  void italic();
  void about();
  void aboutQt();

 private:
  CFRThread *cfrThread;
  QTimer *timer;
  void createActions();
  void createMenus();
  QGridLayout *gridLayout;

  QMenu *gameSettingsMenu;
  QMenu *runMenu;
  QMenu *subMenu;
  QMenu *helpMenu;
  QMenu *gameTypesMenu;
  //QActionGroup *alignmentGroup;
  //QActionGroup *GameTypeGroup;
  QAction *texasHoldemAct;
  QAction *preFlopAct;
  QAction *iterationsAct;
  QAction *maxBetsAct;
  QAction *exitAct;
  QAction *startAct;
  QAction *pauseAct;
  QAction *stopAct;
  QAction *copyAct;
  QAction *pasteAct;
  QAction *boldAct;
  QAction *italicAct;
  QAction *aboutAct;
  QAction *aboutQtAct;
  //QLabel *infoLabel;
  void updateSquare(int row, int col, float value1, float value2, float value3);
};

#endif
