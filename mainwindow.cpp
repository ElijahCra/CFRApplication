//
// Created by Elijah Crain on 2/28/24.
//
#include <QtWidgets>
#include "mainwindow.hpp"
#include "Controller.hpp"


MainWindow::MainWindow()
{
  auto *widget = new QWidget;
  setCentralWidget(widget);
  gridLayout = new QGridLayout(widget);
// Column Labels
  QStringList cardRanks = {"A", "K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
  for (int i = 0; i < 13; ++i) {
    auto *label = new QLabel(cardRanks[i]);
    label->setAlignment(Qt::AlignCenter); // Center the label text
    gridLayout->addWidget(label, 0, i + 1); // Place in top row, offset for row labels
  }

  // Row labels
  for (int i = 0; i < 13; ++i) {
    auto *label = new QLabel(cardRanks[i]);
    label->setAlignment(Qt::AlignCenter); // Center the label text
    gridLayout->addWidget(label, i + 1, 0);  // Place in first column, offset for column labels
  }

  constexpr int numSquares = 169;
  for (int i = 0; i < numSquares; ++i) {
    auto *square = new CustomSquare();
    square->setValues(1.F/3.F, 1.F/3.F, 1.F/3.F);
    gridLayout->addWidget(square, i / 13 + 1, i % 13 + 1);
    squares.append(square);
  }
  createActions();
  createMenus();

  const QString message = tr("Select Run and Start to begin computing");
  statusBar()->showMessage(message);



  setWindowTitle(tr("CFR"));
  setMinimumSize(160, 160);
  resize(800, 600);

  controller = new Controller();
  connect(controller, &Controller::resultsReadyForUI, this, &MainWindow::handleControllerResults);
}



void MainWindow::handleControllerResults(const std::array<std::vector<float>, 169>& strats) {
  // Iterate over 'strats' and call 'updateSquare' accordingly
  for (u_int32_t row = 0; row < 13; ++row) {
    for (u_int32_t col = 0; col < 13; ++col) {
      u_int32_t index = mapper[row][col];
      std::vector<float> const& values = strats[index];
      updateSquare(row, col, values[0], values[1], values[2]);
    }
  }
}

void MainWindow::updateSquare(const uint32_t row, const uint32_t col, const float value1, const float value2, const float value3)
{
  uint32_t index = row * 13 + col;
  if (index < squares.size()) {
    squares[index]->setValues(value1, value2, value3);
  }
}

void MainWindow::start()
{
  statusBar()->clearMessage();
  shouldStop = false;

  int epochs = 5000;
  int i=0;
  while (i<epochs && !shouldStop) {
    ++i;
    if (shouldStop) {break;}
    controller->operate(epochs, iterationsCount);
  }}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu menu(this);
  menu.addAction(stopAct);
  menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::texasHoldem()
{

}

void MainWindow::preFlop()
{

}

void MainWindow::iterations(){}

void MainWindow::maxBets()
{

}



void MainWindow::pause()
{

}

void MainWindow::stop()
{
  shouldStop = true;
}


void MainWindow::about()
{
  QMessageBox::about(this, tr("About Menu"),
                     tr("The <b>Menu</b> example shows how to create "
                        "menu-bar menus and context menus."));
}

void MainWindow::aboutQt()
{

}

void MainWindow::createActions() {
  texasHoldemAct = new QAction(
      tr("&TexasHoldem"), this);
  texasHoldemAct->setShortcuts(QKeySequence::New);
  texasHoldemAct->setStatusTip(tr("Switch Game Type to Texas Holdem"));
  connect(texasHoldemAct, &QAction::triggered, this, &MainWindow::texasHoldem);

  preFlopAct = new QAction(
      tr("&PreFlop..."), this);
  preFlopAct->setShortcuts(QKeySequence::Open);
  preFlopAct->setStatusTip(tr("Switch Game Type to Preflop"));
  connect(preFlopAct, &QAction::triggered, this, &MainWindow::preFlop);

  iterationsAct = new QAction(
      tr("&Iterations"), this);
  iterationsAct->setShortcuts(QKeySequence::Save);
  iterationsAct->setStatusTip(tr("Select Iteration Count"));
  connect(iterationsAct, &QAction::triggered, this, &MainWindow::iterations);

  maxBetsAct = new QAction(
      tr("&Max Bets..."), this);
  maxBetsAct->setShortcuts(QKeySequence::Print);
  maxBetsAct->setStatusTip(tr("Select Max Bets per Round"));
  connect(maxBetsAct, &QAction::triggered, this, &MainWindow::maxBets);

  exitAct = new QAction(
      tr("E&xit"), this);
  exitAct->setShortcuts(QKeySequence::Quit);
  exitAct->setStatusTip(tr("Exit the application"));
  connect(exitAct, &QAction::triggered, this, &QWidget::close);

  startAct = new QAction(
      tr("&Start"), this);
  startAct->setShortcuts(QKeySequence::Refresh);
  startAct->setStatusTip(tr("Start Computation"));
  connect(startAct, &QAction::triggered, this, &MainWindow::start);

  pauseAct = new QAction(
      tr("&Pause"), this);
  pauseAct->setShortcuts(QKeySequence::Redo);
  pauseAct->setStatusTip(tr("Pause Computation"));
  connect(pauseAct, &QAction::triggered, this, &MainWindow::pause);

  stopAct = new QAction(
      tr("&Stop"), this);
  stopAct->setShortcuts(QKeySequence::Cut);
  stopAct->setStatusTip(tr("Cancel Computation"));
  connect(stopAct, &QAction::triggered, this, &MainWindow::stop);

  aboutAct = new QAction(
      tr("&About"), this);
  aboutAct->setStatusTip(tr("Show the application's About box"));
  connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

  aboutQtAct = new QAction(tr("About &Qt"), this);
  aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
  connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
  connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);
}
void MainWindow::createMenus() {
    gameSettingsMenu = menuBar()->addMenu(tr("&Settings"));
    gameTypesMenu = gameSettingsMenu->addMenu(tr("&Game Types"));
    gameTypesMenu->addAction(texasHoldemAct);
    gameTypesMenu->addAction(preFlopAct);
    gameSettingsMenu->addAction(iterationsAct);
    gameSettingsMenu->addAction(maxBetsAct);
    gameSettingsMenu->addSeparator();
    gameSettingsMenu->addAction(exitAct);
    runMenu = menuBar()->addMenu(tr("&Run"));
    runMenu->addAction(startAct);
    runMenu->addAction(pauseAct);
    runMenu->addSeparator();
    runMenu->addAction(stopAct);
    runMenu->addSeparator();
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

}
