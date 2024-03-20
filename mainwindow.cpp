//
// Created by Elijah Crain on 2/28/24.
//
#include <QtWidgets>

#include "mainwindow.hpp"

//! [0]
MainWindow::MainWindow()
{
  QWidget *widget = new QWidget;
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

  int numSquares = 169;
  for (int i = 0; i < numSquares; ++i) {
    auto *square = new CustomSquare();
    square->setValues(1.f/3.f, 1.f/3.f, 1.f/3.f);
    gridLayout->addWidget(square, i / 13 + 1, i % 13 + 1);
    squares.append(square);
  }
  createActions();
  createMenus();

  QString message = tr("Select Run and Start to begin computing");
  statusBar()->showMessage(message);

  setWindowTitle(tr("CFR"));
  setMinimumSize(160, 160);
  resize(800, 400);

  cfrThread = new CFRThread(this);
  connect(cfrThread, &CFRThread::squareUpdated, this, &MainWindow::updateSquare);

}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu menu(this);
  menu.addAction(stopAct);
  menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

void MainWindow::updateSquare(int row, int col, float value1, float value2, float value3)
{
  int index = row * 13 + col;
  if (index >= 0 && index < squares.size()) {
    squares[index]->setValues(value1, value2, value3);
  }
}

void MainWindow::texasHoldem()
{

}

void MainWindow::preFlop()
{

}

void MainWindow::iterations()
{

}

void MainWindow::maxBets()
{

}

void MainWindow::start()
{
  int epochs = 5;
  for (int i=0; i<epochs; ++i) {
  cfrThread->run();
}}

void MainWindow::pause()
{

}

void MainWindow::stop()
{
  //cfrThread->terminate();
  //cfrThread->wait();
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
//! [5]
  texasHoldemAct = new QAction(
      tr("&TexasHoldem"), this);
  texasHoldemAct->setShortcuts(QKeySequence::New);
  texasHoldemAct->setStatusTip(tr("Switch Game Type to Texas Holdem"));
  connect(texasHoldemAct, &QAction::triggered, this, &MainWindow::texasHoldem);
//! [4]

  preFlopAct = new QAction(
      tr("&PreFlop..."), this);
  preFlopAct->setShortcuts(QKeySequence::Open);
  preFlopAct->setStatusTip(tr("Switch Game Type to Texas Holdem"));
  connect(preFlopAct, &QAction::triggered, this, &MainWindow::preFlop);
//! [5]

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

  copyAct = new QAction(
      tr("&Copy"), this);
  copyAct->setShortcuts(QKeySequence::Copy);
  copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                           "clipboard"));
  connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

  pasteAct = new QAction(
      tr("&Paste"), this);
  pasteAct->setShortcuts(QKeySequence::Paste);
  pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                            "selection"));
  connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

  boldAct = new QAction(
      tr("&Bold"), this);
  boldAct->setCheckable(true);
  boldAct->setShortcut(QKeySequence::Bold);
  boldAct->setStatusTip(tr("Make the text bold"));
  connect(boldAct, &QAction::triggered, this, &MainWindow::bold);

  QFont boldFont = boldAct->font();
  boldFont.setBold(true);
  boldAct->setFont(boldFont);

  italicAct = new QAction(
      tr("&Italic"), this);
  italicAct->setCheckable(true);
  italicAct->setShortcut(QKeySequence::Italic);
  italicAct->setStatusTip(tr("Make the text italic"));
  connect(italicAct, &QAction::triggered, this, &MainWindow::italic);

  QFont italicFont = italicAct->font();
  italicFont.setItalic(true);
  italicAct->setFont(italicFont);

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
    runMenu->addAction(copyAct);
    runMenu->addAction(pasteAct);
    runMenu->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    subMenu = runMenu->addMenu(tr("&Format"));
    subMenu->addAction(boldAct);
    subMenu->addAction(italicAct);
    subMenu->addSeparator()->setText(tr("Alignment"));
}

