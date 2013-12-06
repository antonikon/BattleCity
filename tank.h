#pragma once

#include <QtCore>

class Tank
{
public:
	Tank();
	bool isMove() {
		return _isMove;
	}
	QPoint getPos() {
		return _pos;
	}
	void setPos(const QPoint &pos) {
		_pos = pos;
	}
	int getSize() {
		return _size;
	}
	void setSize(int size) {
		_size = size;
	}
	int getAngle() {
		return _angle;
	}
	void setAngle(int angle) {
		_angle = angle;
	}
	void startReloading() {
		_reloading = _reloadTime;
	}
	void reloading() {
		if (_reloading > 0) {
			_reloading--;
		}
	}
	bool readyFire() {
		if (_reloading == 0) {
			return true;
		}
		return false;
	}
	void hit() {
		_hp--;
	}
	int getHp() {
		return _hp;
	}
	int getTeam() {
		return _team;
	}
	void setTeam(int team) {
		_team = team;
	}
	void animation() {
		_killAnimation++;
	}
	int getKillAnimation() {
		return _killAnimation;
	}
	void setSpeed(int speed) {
		_speed = speed;
	}
	int getSpeed() {
		return _speed;
	}
	void move(bool value)
	{
		_isMove = value;
	}
	void rotate(int angle)
	{
		_angle = angle;
	}
private:
	QPoint _pos;
	int _size = 50;
	int _angle = 0;
	bool _isMove = false;
	int _hp = 3;
	int _reloading = 0, _reloadTime = 10;
	int _team = 0;
	int _killAnimation = 0;
	int _speed = 6;
};
