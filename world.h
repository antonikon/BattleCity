#pragma once

#include <QtCore>
#include <QPainter>
#include <QtMultimedia/QSound>
#include "tank.h"
#include "wall.h"
#include "bullet.h"

class World
{
public:
	World();
	void updateTanks();
	void moveBullets();
	void paintWorld(QPainter *painter);
	void update();
	void moveSignal(int angle);
	void fire(Tank *tank = nullptr);
private:
	void *testCollision(int speed, void *object, bool isTank = true, bool *withTank = nullptr);
	void gameOver();
	void loadMission(int index);
	void addWall(const QPoint &pos, int type);
	void addWallRect(const QPoint &start, const QPoint &end, int type = 0);
	void moveBots();
	void startVideo();
	void playVideo();
private:
	QVector <Tank*> _tankList;
	Tank *_playerTank = nullptr;
	Wall* _playerBase = nullptr;
	QVector <Wall*> _wallList;
	QVector <QImage*> _images;
	QVector <Bullet*> _bulletList;
	bool _isGameOver = false;
	bool _isVideo = false;
	int _playerLife = 3, _enemyLife = 10;
	QVector <QPoint> _spawnPos;
	int _other = 0;
};
