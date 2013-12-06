#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include <QKeyEvent>

#include "world.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	void paintEvent(QPaintEvent *);
	void timerEvent(QTimerEvent *);
	void keyPressEvent(QKeyEvent *key);
	void keyReleaseEvent(QKeyEvent *key);
	~MainWindow();
	
private:
	Ui::MainWindow *ui;
	World _world;
	QVector  <bool> _keys;
};

#endif // MAINWINDOW_H
