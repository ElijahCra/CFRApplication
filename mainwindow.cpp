//
// Created by Elijah Crain on 2/25/24.
//


#include "mainwindow.h"
#include <QHBoxLayout>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  // Toolbar setup
  toolBar = addToolBar("My Toolbar");
  auto *button1 = new QPushButton("Button 1");
  toolBar->addWidget(button1);
  // Add more buttons as needed...

  connect(button1, &QPushButton::clicked, this, &MainWindow::button1Clicked); // Connect button

  auto *centralWidget = new QWidget;
  gridLayout = new QGridLayout(centralWidget);
  setCentralWidget(centralWidget);

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

}

MainWindow::~MainWindow() = default;

void MainWindow::button1Clicked() {
  for (CustomSquare* square : squares) {
    square->setValues(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);
  }
}

// ... Add slots for other buttons
