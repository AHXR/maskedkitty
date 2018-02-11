#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QMouseEvent>

namespace Ui {
class window;
}

class window : public QMainWindow
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0);
    ~window();

private slots:
    void on_btnOpen_pressed();

    void on_btnBuild_pressed();

    void on_spnAmount_valueChanged(int arg1);

    void on_lstTypes_itemSelectionChanged();

    void on_btnOpenIcon_pressed();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::window *ui;
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};

#endif // WINDOW_H
