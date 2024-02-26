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

  auto *mainLayout = new QVBoxLayout; // A vertical layout to hold everything

  // ---- Column Label Setup ----
  auto* columnLabelLayout = new QHBoxLayout; // Horizontal layout for column labels
  QStringList cardRanks = {"A", "K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
  for (int i = 0; i < 13; ++i) {
    auto *label = new QLabel(cardRanks[i]);
    columnLabelLayout->addWidget(label);
  }
  mainLayout->addLayout(columnLabelLayout); // Add column labels to main layout

  // ---- Grid Setup ----
  auto *centralWidget = new QWidget;
  gridLayout = new QGridLayout(centralWidget);
  mainLayout->addWidget(centralWidget); // Add grid to main layout

  int numSquares = 169;
  for (int i = 0; i < numSquares; ++i) {
    auto *square = new CustomSquare();
    square->setValues(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX); // Example random values
    gridLayout->addWidget(square, i / 13, i % 13);
    squares.append(square);
  }


// Row labels (similarly)
  auto* rowLabelLayout = new QVBoxLayout;
  for (int i = 0; i < 13; ++i) {
    auto *label = new QLabel(cardRanks[i]);
    rowLabels.append(label);
    rowLabelLayout->addWidget(label);
  }
  gridLayout->addLayout(rowLabelLayout, 1, 0, 13, 1);

  auto *mainWidget = new QWidget; // Create a new widget for the main layout
  mainWidget->setLayout(mainLayout); // Set the layout on this widget
  setCentralWidget(mainWidget);

}

MainWindow::~MainWindow() = default;

void MainWindow::button1Clicked() {
  for (CustomSquare* square : squares) {
    square->setValues(rand()/(float)RAND_MAX, rand()/(float)RAND_MAX, rand()/(float)RAND_MAX);
  }
}

// ... Add slots for other buttons
