//
// Created by Elijah Crain on 2/28/24.
//
#include <QtWidgets>

#include "mainwindow.h"

//! [0]
MainWindow::MainWindow()
{
  QWidget *widget = new QWidget;
  setCentralWidget(widget);
  gridLayout = new QGridLayout(widget);
//! [0]
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
    square->setValues(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX); // Example random values
    gridLayout->addWidget(square, i / 13 + 1, i % 13 + 1);
    squares.append(square);
  }
//! [1]
  /*QWidget *topFiller = new QWidget;
  topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                            "invoke a context menu</i>"));
  infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
  infoLabel->setAlignment(Qt::AlignCenter);

  QWidget *bottomFiller = new QWidget;
  bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setContentsMargins(5, 5, 5, 5);
  layout->addWidget(topFiller);
  layout->addWidget(infoLabel);
  layout->addWidget(bottomFiller);
  widget->setLayout(layout);*/
//! [1]

//! [2]
  createActions();
  createMenus();

  QString message = tr("Select Run and Start to begin computing");
  statusBar()->showMessage(message);

  //QString message = tr("A context menu is available by right-clicking");
  //statusBar()->showMessage(message);

  setWindowTitle(tr("CFR"));
  setMinimumSize(160, 160);
  resize(800, 400);
}
//! [2]

//! [3]
#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
  QMenu menu(this);
  menu.addAction(stopAct);
  menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU
//! [3]

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

}

void MainWindow::pause()
{

}

void MainWindow::stop()
{

}

void MainWindow::copy()
{

}

void MainWindow::bold()
{

}

void MainWindow::italic()
{

}

void MainWindow::paste()
{

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

//! [4]
void MainWindow::createActions()
{
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


//! [6] //! [7]

//! [6]
}
//! [7]

//! [8]
void MainWindow::createMenus()
{
//! [9] //! [10]
  gameSettingsMenu = menuBar()->addMenu(tr("&Settings"));
  gameTypesMenu = gameSettingsMenu->addMenu(tr("&Game Types"));
  gameTypesMenu->addAction(texasHoldemAct);
  gameTypesMenu->addAction(preFlopAct);
//! [10]
  gameSettingsMenu->addAction(iterationsAct);
  gameSettingsMenu->addAction(maxBetsAct);

//! [11]
  gameSettingsMenu->addSeparator();
//! [11]
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
//! [8]

//! [12]
  subMenu = runMenu->addMenu(tr("&Format"));
  subMenu->addAction(boldAct);
  subMenu->addAction(italicAct);
  subMenu->addSeparator()->setText(tr("Alignment"));
}