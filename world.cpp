#include "world.h"

World::World()
{
	QImage *image = new QImage("data/player1.png");
	_images.append(image);
	image = new QImage("data/enemy1.png");
	_images.append(image);
	image = new QImage("data/wall2.png");
	_images.append(image);
	image = new QImage("data/wall1.png");
	_images.append(image);
	image = new QImage("data/bullet.png");
	_images.append(image);
	image = new QImage("data/base.png");
	_images.append(image);
	image = new QImage("data/boom1.png");
	_images.append(image);
	image = new QImage("data/boom2.png");
	_images.append(image);
	image = new QImage("data/gameOver.png");
	_images.append(image);
	image = new QImage("data/title.png");
	_images.append(image);
	startVideo();
	//loadMission(0);
}

void World::updateTanks()
{
	for (int q = 0; q < _tankList.size(); q++) {
		_tankList[q]->reloading();
		if (_tankList[q]->getHp() == 0) {
			if (_tankList[q]->getKillAnimation() == 15)
			{
				if (_tankList[q] == _playerTank) {
					_playerTank = nullptr;
				}
				delete _tankList[q];
				_tankList.remove(q);
			} else {
				_tankList[q]->animation();
			}
		}
		else if (_tankList[q]->isMove()) {
			QPoint pos = _tankList[q]->getPos();
			void *status = testCollision(_tankList[q]->getSpeed(), _tankList[q]);
			if (status == nullptr) {
				switch (_tankList[q]->getAngle()) {
					case 0: {
						_tankList[q]->setPos(QPoint(pos.x(), pos.y() - _tankList[q]->getSpeed()));
						break;
					}
					case 1: {
						_tankList[q]->setPos(QPoint(pos.x() + _tankList[q]->getSpeed(), pos.y()));
						break;
					}
					case 2: {
						_tankList[q]->setPos(QPoint(pos.x(), pos.y() + _tankList[q]->getSpeed()));
						break;
					}
					case 3: {
						_tankList[q]->setPos(QPoint(pos.x() - _tankList[q]->getSpeed(), pos.y()));
						break;
					}
				}
			} else {
				_tankList[q]->move(false);
			}
		}
	}
}

void World::moveBullets()
{
	for (int q = 0; q < _bulletList.size(); q++) {
		if (_bulletList[q]->getKillAnimation() != 0) {
			if (_bulletList[q]->getKillAnimation() == 10) {
				delete _bulletList[q];
				_bulletList.remove(q);
			} else {
				_bulletList[q]->animation();
			}
		} else {
			QPoint pos = _bulletList[q]->getPos();
			bool withTank;
			void *status = testCollision(_bulletList[q]->getSpeed(), _bulletList[q], false, &withTank);
			if (status == nullptr) {
				switch (_bulletList[q]->getAngle()) {
					case 0: {
						_bulletList[q]->setPos(QPoint(pos.x(), pos.y() - _bulletList[q]->getSpeed()));
						break;
					}
					case 1: {
						_bulletList[q]->setPos(QPoint(pos.x() + _bulletList[q]->getSpeed(), pos.y()));
						break;
					}
					case 2: {
						_bulletList[q]->setPos(QPoint(pos.x(), pos.y() + _bulletList[q]->getSpeed()));
						break;
					}
					case 3: {
						_bulletList[q]->setPos(QPoint(pos.x() - _bulletList[q]->getSpeed(), pos.y()));
						break;
					}
				}
			} else {
				if (withTank) {
					Tank *tank = ((Tank*)status);
					tank->hit();
					if (tank->getHp() == 0) {
						tank->setSize(0);
					}
				} else {
					Wall *wall = ((Wall*)status);
					wall->hit();
					if (wall->getHp() == 0) {
						for (int i = 0; i < _wallList.size(); i++) {
							if (_wallList[i] == wall) {
								if (_wallList[i] == _playerBase) {
									_playerBase = nullptr;
								}
								delete _wallList[i];
								_wallList.remove(i);
							}
						}
					}
				}
				_bulletList[q]->animation();
			}
		}
	}
}

void World::paintWorld(QPainter *painter)
{
	if (!_isGameOver) {
		for (int q = 0; q < _tankList.size(); q++) {
			QTransform transform;
			int angle = 0;
			switch (_tankList[q]->getAngle()) {
				case 1: {
					angle = 90;
					break;
				}
				case 2: {
					angle = 180;
					break;
				}
				case 3: {

					angle = 270;
					break;
				}
			}
			transform.rotate(angle);
			QImage image;
			if (_tankList[q]->getKillAnimation() == 0) {
					if (_tankList[q]->getTeam() == 1) {
						image = *_images[0];
					} else if (_tankList[q]->getTeam() == 0) {
						image = *_images[1];
					} else if (_tankList[q]->getTeam() == 2) {
						image = *_images[9];
						painter->drawImage(_tankList[q]->getPos(),image);
						continue;
					}
					image = image.transformed(transform);
					painter->drawImage(_tankList[q]->getPos(),image);
			} else {
				image = *_images[7];
				painter->drawImage(_tankList[q]->getPos().x() + _tankList[q]->getSize() / 2 - image.width() / 4,
								   _tankList[q]->getPos().y() + _tankList[q]->getSize() / 2 - image.height() / 4 ,
								   image);
			}
		}
		for (int q = 0; q < _wallList.size(); q++) {
			QImage image;
			switch (_wallList[q]->getType()) {
				case 0: {
					image = *_images[2];
					break;
				}
				case 1: {
					image = *_images[3];
					break;
				}
				case 2: {
					image = *_images[5];
					break;
				}

			}
			painter->drawImage(_wallList[q]->getPos(), image);
		}
		for (int q = 0; q < _bulletList.size(); q++) {
			QTransform transform;
			int angle = 0;
			switch (_bulletList[q]->getAngle()) {
				case 1: {
					angle = 90;
					break;
				}
				case 2: {
					angle = 180;
					break;
				}
				case 3: {

					angle = 270;
					break;
				}
			}
			transform.rotate(angle);
			QImage image;
			if (_bulletList[q]->getKillAnimation() == 0) {
				image = _images[4]->transformed(transform);
				painter->drawImage(_bulletList[q]->getPos(),image);
			} else {
				image = *_images[6];
				painter->drawImage(_bulletList[q]->getPos().x() + _bulletList[q]->getSize() / 2 - image.width() / 2,
								   _bulletList[q]->getPos().y() + _bulletList[q]->getSize() / 2 - image.height() / 2
								   ,image);
			}
		}
	} else {
		painter->drawImage(140,205, *_images[8]);
	}
}

void World::update()
{
	if (_playerBase == nullptr) {
		gameOver();
	} else if (_playerTank == nullptr) {
		if (_playerLife > 0) {
			_playerLife--;
			Tank *tank = new Tank;
			tank->setPos(_spawnPos[0]);
			_playerTank = tank;
			_tankList.append(tank);
		} else {
			gameOver();
		}
	} else if (_tankList.size() < 3) {
		if (_enemyLife > 0) {
			_enemyLife--;
			Tank *tank = new Tank;
			tank->setTeam(1);
			tank->setPos(_spawnPos[_tankList.size()]);
			tank->setAngle(2);
			_tankList.append(tank);
		}
	}
	if (_isVideo) {
		playVideo();
	} else {
		moveBots();
	}
	updateTanks();
	moveBullets();
}

void World::moveSignal(int angle)
{
	if (_playerTank != nullptr) {
		if (angle == -1) {
			_playerTank->move(false);
		} else if (_playerTank->getAngle() != angle) {
			_playerTank->move(false);
			_playerTank->setAngle(angle);
		} else if (_playerTank->getAngle() == angle) {
			_playerTank->move(true);
		}
	}
}

void World::fire(Tank *tank)
{
	if (tank == nullptr) {
		tank = _playerTank;
	}
	if (tank->readyFire()) {
		QPoint pos;
		pos.setX(tank->getPos().x() + tank->getSize() / 2 - 4);
		pos.setY(tank->getPos().y() + tank->getSize() / 2 - 4);
		switch (tank->getAngle()) {
			case 0: {
				pos.setY(pos.y() - tank->getSize() / 2 - 5);
				break;
			}
			case 1: {
				pos.setX(pos.x() + tank->getSize() / 2 + 5);
				break;
			}
			case 2: {
				pos.setY(pos.y() + tank->getSize() / 2 + 5);
				break;
			}
			case 3: {
				pos.setX(pos.x() - tank->getSize() / 2 - 5);
				break;
			}
		}
		Bullet *bullet = new Bullet;
		bullet->setPos(pos);
		bullet->setAngle(tank->getAngle());
		bullet->setSpeed(18);
		_bulletList.append(bullet);
		tank->startReloading();
	}
}

void *World::testCollision(int speed, void *object, bool isTank, bool *withTank)
{
	QPoint pos;
	int angle;
	int size;
	if (isTank) {
		pos = ((Tank*)object)->getPos();
		angle = ((Tank*)object)->getAngle();
		size = ((Tank*)object)->getSize();
	} else {
		pos = ((Bullet*)object)->getPos();
		angle = ((Bullet*)object)->getAngle();
		size = ((Bullet*)object)->getSize();
	}
	switch (angle) {
		case 0: {
			pos.setY(pos.y() - speed);
			break;
		}
		case 1: {
			pos.setX(pos.x() + speed);
			break;
		}
		case 2: {

			pos.setY(pos.y() + speed);
			break;
		}
		case 3: {
			pos.setX(pos.x() - speed);
			break;
		}
	}
	for (int q = 0; q < _tankList.size(); q++) {
		QPoint tankPos = _tankList[q]->getPos();
		int tankSize = _tankList[q]->getSize();
		if (_tankList[q] != object & _tankList[q]->getSize() > 0) {
			if (!((pos.x() > tankPos.x() + tankSize || pos.x() + size < tankPos.x())
				|| (pos.y() > tankPos.y() + tankSize || pos.y() + size < tankPos.y()))) {
				if (withTank != nullptr) {
					*withTank = true;
				}
				return _tankList[q];
			}
		}
	}
	for (int q = 0; q < _wallList.size(); q++) {
		QPoint wallPos = _wallList[q]->getPos();
		int wallSize = _wallList[q]->getSize();
		if (!((pos.x() > wallPos.x() + wallSize || pos.x() + size < wallPos.x())
			|| (pos.y() > wallPos.y() + wallSize || pos.y() + size < wallPos.y()))) {
			if (withTank != nullptr) {
				*withTank = false;
			}
			return _wallList[q];
		}
	}
	return nullptr;
}

void World::gameOver()
{
	for (int q = 0; q < _tankList.size(); q++) {
		delete _tankList[0];
	}
	_tankList.clear();
	for (int q = 0; q < _wallList.size(); q++) {
		delete _wallList[0];
	}
	_wallList.clear();
	for (int q = 0; q < _bulletList.size(); q++) {
		delete _bulletList[0];
	}
	_bulletList.clear();
	_isGameOver = true;
	_playerBase = nullptr;
	_playerTank = nullptr;
}

void World::loadMission(int index)
{
	_isGameOver = false;
	switch (index) {
		case 0: {
			_playerLife = 3;
			_enemyLife = 10;
			_spawnPos.append(QPoint(237, 350));
			_spawnPos.append(QPoint(25, 25));
			_spawnPos.append(QPoint(400, 25));

			addWall(QPoint(225,450),2);

			addWall(QPoint(225,425),0);
			addWall(QPoint(250,425),0);
			addWall(QPoint(200,425),0);
			addWall(QPoint(275,425),0);
			addWall(QPoint(200,450),0);
			addWall(QPoint(275,450),0);
			addWall(QPoint(200,475),0);
			addWall(QPoint(275,475),0);

			addWallRect(QPoint(50,300),QPoint(100, 450),0);
			addWallRect(QPoint(400,300),QPoint(450, 450),0);

			addWallRect(QPoint(100,100), QPoint(400, 200), 0);

			addWallRect(QPoint(-25,-25), QPoint(500, 0), 3);
			addWallRect(QPoint(-25,-25), QPoint(0, 500), 3);
			addWallRect(QPoint(0,500), QPoint(500, 525), 3);
			addWallRect(QPoint(500,0), QPoint(525, 500), 3);

			/*Tank *tank = new Tank;
			tank->setPos(QPoint(50,50));
			_tankList.append(tank);
			_playerTank = tank;*/
			break;
		}
	}
}

void World::addWall(const QPoint &pos, int type)
{
	Wall *wall = new Wall(type);
	wall->setPos(pos);
	_wallList.append(wall);
	if (type == 2) {
		_playerBase = wall;
	}
}

void World::addWallRect(const QPoint &start, const QPoint &end, int type)
{
	int width = (end.x() - start.x()) / 25;
	int height = (end.y() - start.y()) / 25;
	for (int q = 0; q < width; q ++) {
		for (int i = 0; i < height; i++) {
			addWall(QPoint(start.x() + 25 *q, start.y() + 25 * i), type);
		}
	}
}

void World::moveBots()
{
	for (int q = 0; q < _tankList.size(); q++) {
		if (_tankList[q]->getTeam() == 1) {
			if (_tankList[q]->isMove() == false) {
				_tankList[q]->move(true);
				_tankList[q]->setAngle(rand()%4);
			}
			if (_playerTank != nullptr) {
				switch (_tankList[q]->getAngle()) {
					case 0: {
						if (qAbs(_tankList[q]->getPos().x() - _playerTank->getPos().x()) < 50
							& _tankList[q]->getPos().y() - _playerTank->getPos().y() > 0) {
							fire(_tankList[q]);
						}
						break;
					}
					case 1: {
						if (qAbs(_tankList[q]->getPos().y() - _playerTank->getPos().y()) < 50
							& _tankList[q]->getPos().x() - _playerTank->getPos().x() < 0) {
							fire(_tankList[q]);
						}
						break;
					}
					case 2: {
						if (qAbs(_tankList[q]->getPos().x() - _playerTank->getPos().x()) < 50
							& _tankList[q]->getPos().y() - _playerTank->getPos().y() < 0) {
							fire(_tankList[q]);
						}
						break;
					}
					case 3: {
						if (qAbs(_tankList[q]->getPos().y() - _playerTank->getPos().y()) < 50
							& _tankList[q]->getPos().x() - _playerTank->getPos().x() > 0) {
							fire(_tankList[q]);
						}
						break;
					}
				}
			}
		}
	}
}

void World::startVideo()
{
	QSound::play("data/menu.wav");
	Wall *base = new Wall(2);
	_playerBase = base;
	Tank *tank = new Tank;
	_playerTank = tank;
	_enemyLife = 0;
	_playerLife = 0;
	tank = new Tank;
	tank->setPos(QPoint(225,450));
	tank->setTeam(0);
	tank->move(true);
	tank->setSpeed(3);
	_tankList.append(tank);

	tank = new Tank;
	tank->setPos(QPoint(175,510));
	tank->setTeam(1);
	tank->move(true);
	tank->setSpeed(2);
	_tankList.append(tank);

	tank = new Tank;
	tank->setPos(QPoint(245,510));
	tank->setTeam(1);
	tank->move(true);
	tank->setSpeed(2);
	_tankList.append(tank);

	_isVideo = true;

}

void World::playVideo()
{
	if (_tankList.size() == 3) {
		_other++;
		if (_other % 30 == 0) {
			fire(_tankList[1]);
		} else if (_other % 51 == 0) {
			fire(_tankList[2]);
		}
	} else if (_tankList.size() == 2 & _other > 0 & _other < 1000) {
		_tankList[0]->move(false);
		_tankList[1]->move(false);
		_tankList[0]->rotate(3);
		_tankList[1]->rotate(1);
		_other = 0;

	} else if (_tankList.size() == 2 &_other == 0) {
		_other = -1;
		for (int q = 0; q < 8; q ++) {
			Tank *tank = new Tank;
			tank->setPos(QPoint(q * 50 + 12 * q + 6,-50));
			tank->setTeam(0);
			tank->setAngle(2);
			tank->setSpeed(1);
			tank->move(true);
			_tankList.append(tank);
		}
	} else if (_other <= -1 & _other > -50) {
		_other--;
	} else if (_other == -50) {
		_other--;
		_tankList[0]->setAngle(2);
		_tankList[1]->setAngle(2);
		_tankList[0]->move(true);
		_tankList[1]->move(true);
	}
	else if (_other <= -51 & _tankList.size() == 10) {
		_other--;
		if (_other % 50 == 0) {
			for (int q = 0 ; q < 8; q ++) {
				fire(_tankList[q + 2]);
			}
		}
	} else if ( _tankList.size() == 8 & _other < 0) {
		Tank *tank = new Tank;
		tank->setTeam(2);
		tank->setPos(QPoint(156, - 70));
		tank->setAngle(2);
		tank->setSpeed(1);
		tank->setSize(0);
		tank->move(true);
		_tankList.append(tank);
	} else if (_tankList.size() == 9 & _other < 0) {
		if (_tankList[8]->getPos().y() == 216) {
			_tankList[8]->move(false);
			_other = 0;
		}
	} else if (_tankList.size() == 9 & _other >= 0) {
		_other++;
		if (_other == 625) {
			for (int q = 0; q < _tankList.size() - 1; q++) {
				delete _tankList[0];
			}
			_tankList.remove(0,8);
			for (int q = 0; q < 8; q ++) {
				Tank *tank = new Tank;
				tank->setPos(QPoint(-50,q * 50 + 12 * q + 6));
				tank->setTeam(0);
				tank->setAngle(1);
				tank->setSpeed(rand() % 4 + 1);
				tank->move(true);
				_tankList.append(tank);
			}
			for (int q = 0; q < 8; q ++) {
				Tank *tank = new Tank;
				tank->setPos(QPoint(550,q * 50 + 12 * q + 6));
				tank->setTeam(1);
				tank->setAngle(3);
				tank->setSpeed(rand() % 4 + 1);
				tank->move(true);
				_tankList.append(tank);
			}
			_other = 1000;
		}
	} else if (_other == 1000 & _tankList.size() != 1) {
		for (int q = 1; q < _tankList.size(); q ++) {
			int f = rand() % 2;
			if (f == 1) {
				fire(_tankList[q]);
			}
		}
	} else if (_other >= 1000 & _tankList.size() == 1){
		_other++;
		if (_other == 1100) {
			delete _playerBase;
			delete _playerTank;
			gameOver();
			loadMission(0);
			_isVideo = false;
		}
	}
}
