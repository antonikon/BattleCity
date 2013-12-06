#include "wall.h"

Wall::Wall(int type):
	_type(type)
{
	if (_type == 0) {
		_hp = 1;
	} else if (_type == 1) {
		_hp = 5;
	} else if (_type == 2) {
		_hp = 1;
		_size = 50;
	} else if (_type == 3) {
		_hp = -1;
		_type = 0;
	}
}
