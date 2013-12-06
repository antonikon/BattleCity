#pragma once

#include <QtCore>

class Wall
{
public:
	Wall(int type = 0);
	QPoint getPos() {
		return _pos;
	}
	int getSize() {
		return _size;
	}
	void setPos(const QPoint &pos) {
		_pos = pos;
	}
	void hit() {
		_hp--;
	}
	int getHp() {
		return _hp;
	}
	int getType() {
		return _type;
	}

private:
	QPoint _pos;
	int _size = 25;
	int _hp = 5;
	int _type = 0;
};
