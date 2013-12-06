#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	startTimer(20);
	_keys.append(false); // 0 - Up
	_keys.append(false); // 1 - Left
	_keys.append(false); // 2 - Down
	_keys.append(false); // 3 - Right
	_keys.append(false); // 4 - FIRE !!!
}

void MainWindow::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.fillRect(0,0,500,500,Qt::black);
	_world.paintWorld(&painter);
}

void MainWindow::timerEvent(QTimerEvent *)
{
	int angle = -1;
	for (int q = 0; q < 4; q++) {
		if (_keys[q] == true) {
			angle = q;
			break;
		}
	}
	_world.moveSignal(angle);
	if (_keys[4]) {
		_world.fire();
	}
	_world.update();
	update();
}

void MainWindow::keyPressEvent(QKeyEvent *key)
{
	switch (key->key()) {
		case Qt::Key_Up: {
			_keys[0] = true;
			_keys[1] = false;
			_keys[2] = false;
			_keys[3] = false;
			break;
		}
		case Qt::Key_Right: {
			_keys[0] = false;
			_keys[1] = true;
			_keys[2] = false;
			_keys[3] = false;
			break;
		}
		case Qt::Key_Down: {
			_keys[0] = false;
			_keys[1] = false;
			_keys[2] = true;
			_keys[3] = false;
			break;
		}
		case Qt::Key_Left: {
			_keys[0] = false;
			_keys[1] = false;
			_keys[2] = false;
			_keys[3] = true;
			break;
		}
		case Qt::Key_Space: {
			_keys[4] = true;
			break;
		}
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent *key)
{
	switch (key->key()) {
		case Qt::Key_Up: {
			_keys[0] = false;
			break;
		}
		case Qt::Key_Right: {
			_keys[1] = false;
			break;
		}
		case Qt::Key_Down: {
			_keys[2] = false;
			break;
		}
		case Qt::Key_Left: {
			_keys[3] = false;
			break;
		}
		case Qt::Key_Space: {
			_keys[4] = false;
			break;
		}
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}
