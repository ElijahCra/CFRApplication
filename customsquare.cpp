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

  int barWidth = 2;
  int barHeight = 2;

  int totalWidth = width();
  int totalHeight = height();
  int smallWidth = totalWidth - (2*barWidth);
  int smallHeight = totalHeight - (2*barHeight);

  int bar1Width = static_cast<int>(static_cast<float>(smallWidth)*num1);
  int bar2Width = static_cast<int>(static_cast<float>(smallWidth)*num2);
  int bar3Width = smallWidth - bar1Width - bar2Width;

  painter.fillRect(0, 0, totalWidth, height(), QColor(192, 0, 0));
  painter.fillRect(barWidth, barHeight, bar1Width, smallHeight, QColor(192, 254, 58));
  painter.fillRect(bar1Width, barHeight, bar2Width, smallHeight, QColor(9, 22, 200));
  painter.fillRect(bar1Width + bar2Width, barHeight, bar3Width, smallHeight, Qt::black);

}