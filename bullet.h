#pragma once

#include <QtCore>

class Bullet
{
public:
	Bullet();
	void setPos (const QPoint &pos) {
		_pos = pos;
	}
	QPoint getPos() {
		return _pos;
	}
	int getSize() {
		return _size;
	}
	int getAngle() {
		return _angle;
	}
	int getSpeed() {
		return _speed;
	}
	void setSpeed(int speed) {
		_speed = speed;
	}
	void setAngle(int angle) {
		_angle = angle;
	}
	int getKillAnimation() {
		return _killAnimation;
	}
	void animation() {
		_killAnimation++;
	}

private:
	int _speed;
	int _angle;
	QPoint _pos;
	int _size = 9;
	int _killAnimation = 0;
};
