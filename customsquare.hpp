//
// Created by Elijah Crain on 2/25/24.
//

#ifndef CFRAPP__CUSTOMSQUARE_H_
#define CFRAPP__CUSTOMSQUARE_H_

#include <QWidget>
#include <QPainter>

class CustomSquare : public QWidget
{
 Q_OBJECT

  QSize sizeHint() const override { return QSize(100, 100); } // Adjust the size as needed


 public:
  explicit CustomSquare(QWidget *parent = nullptr);

  void setValues(float value1, float value2, float value3);

 protected:
  void paintEvent(QPaintEvent *event) override;

 private:
  float num1 = 1.f/3.f, num2 = 1.f/3.f, num3 = 1.f/3.f;
};

#endif //CFRAPP__CUSTOMSQUARE_H_
