//
// Created by Elijah Crain on 2/25/24.
//

#ifndef CFRAPP__MAINWINDOW_H_
#define CFRAPP__MAINWINDOW_H_

#include <QMainWindow>
#include <QGridLayout>
#include <QToolBar>
#include <QPushButton>
#include <QWidget> // Base class for custom squares (if needed)
#include "customsquare.h"
#include <QLabel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
 Q_OBJECT

  QVector<CustomSquare*> squares;

  QVector<QLabel*> columnLabels; // Keep track of column labels
  QVector<QLabel*> rowLabels; // Keep track of row labels

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void button1Clicked();

 private:
  Ui::MainWindow *ui{};
  QGridLayout *gridLayout;
  QToolBar *toolBar;
  // Potentially QVector<QWidget*> squares;  // If not using a custom square widget
};


#endif //CFRAPP__MAINWINDOW_H_
