#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFunctionPointer>
#include "customsquare.hpp"
#include "Worker.hpp"
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

 public slots:
  void texasHoldem();
  void preFlop();
  void iterations();
  void maxBets();
  void start();
  void pause();
  void stop();
  void about();
  void aboutQt();

  void handleControllerResults(const std::array<std::vector<float>, 169>& strats);

 private:
  Controller *controller;
  QTimer *timer;
  void createActions();
  void createMenus();
  QGridLayout *gridLayout;

  QMenu *gameSettingsMenu;
  QMenu *runMenu;
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
  QAction *aboutAct;
  QAction *aboutQtAct;
  //QLabel *infoLabel;
  void updateSquare(int row, int col, float value1, float value2, float value3);
};

#endif
