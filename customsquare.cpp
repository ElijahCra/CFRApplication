//
// Created by Elijah Crain on 2/25/24.
//

#include "customsquare.hpp"
#include <iostream>

CustomSquare::CustomSquare(QWidget *parent) : QWidget(parent) {}

void CustomSquare::setValues(float value1, float value2, float value3) {
  num1 = value1;
  num2 = value2;
  num3 = value3;
  update(); // Request a repaint
}

void CustomSquare::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  int totalWidth = width();
  int bar1Width = static_cast<int>(static_cast<float>(totalWidth)*num1);
  int bar2Width = static_cast<int>(static_cast<float>(totalWidth)*num2);
  int bar3Width = totalWidth - bar1Width - bar2Width;

  painter.fillRect(0, 0, bar1Width, height(), Qt::green);
  painter.fillRect(bar1Width, 0, bar2Width, height(), Qt::red);
  painter.fillRect(bar1Width + bar2Width, 0, bar3Width, height(), Qt::black);

}