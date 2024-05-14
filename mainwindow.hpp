#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFunctionPointer>
#include "customsquare.hpp"
#include "Controller.hpp"
#include <QGridLayout>
#include <QToolButton>
#include <QPushButton>
#include <atomic>

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

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
  unsigned int iterationsCount = 2000;
  unsigned int epochs = 400;
  Controller *controller = new Controller();
  void createActions();
  void createMenus();
  void setupMainWidget();
  QGridLayout *gridLayout;

  QMenu *gameSettingsMenu{};
  QMenu *runMenu{};
  QMenu *helpMenu{};
  QMenu *gameTypesMenu{};

  QAction *texasHoldemAct{};
  QAction *preFlopAct{};
  QAction *iterationsAct{};
  QAction *maxBetsAct{};
  QAction *exitAct{};
  QAction *startAct{};
  QAction *pauseAct{};
  QAction *stopAct{};
  QAction *aboutAct{};
  QAction *aboutQtAct{};
  void updateSquare(uint32_t row, uint32_t col, float value1, float value2, float value3);

 static constexpr std::array<std::array<uint32_t,13>,13> mapper = { 90,168,167,166,165,164,163,162,161,160,159,158,157,
                                                                    89,77, 156,155,154,153,152,151,150,149,148,147,146,
                                                                    88,76, 65, 145,144,143,142,141,140,139,138,137,136,
                                                                    87,75, 64, 54, 135,134,133,132,131,130,129,128,127,
                                                                    86,74, 63, 53, 44, 126,125,124,123,122,121,120,119,
                                                                    85,73, 62, 52, 43, 35, 118,117,116,115,114,113,112,
                                                                    84,72, 61, 51, 42, 34, 27, 111,110,109,108,107,106,
                                                                    83,71, 60, 50, 41, 33, 26, 20, 105,104,103,102,101,
                                                                    82,70, 59, 49, 40, 32, 25, 19, 14, 100,99, 98, 97,
                                                                    81,69, 58, 48, 39, 31, 24, 18, 13, 9,  96, 95, 94,
                                                                    80,68, 57, 47, 38, 30, 23, 17, 12, 8,  5,  93, 92,
                                                                    79,67, 56, 46, 37, 29, 22, 16, 11, 7,  4,  2,  91,
                                                                    78,66, 55, 45, 36, 28, 21, 15, 10, 6,  3,  1,  0 };
};

#endif
