#include "common.h"
#include "resProperties.h"

float resProperties::getAlw()
{
	return alw;
}

int resProperties::getId()
{
	return id;
}

float resProperties::getWeight()
{
	return weight;
}

void resProperties::setId(int resId)
{
	id = resId;
	switch(id) {
	case ID_BSTONE:
		alw = 1.0;
		weight = 5;
		score = 22;
		break;
	case ID_GOLD:
		alw = 1.0;
		weight = 5;
		score = 500;
		break;
	case ID_SSTONE:
		alw = 2.0;
		weight = 4;
		score = 11;
		break;
	case ID_DIAMOND:
		alw = 3.0;
		weight = 1;
		score = 600;
		break;
	case ID_BAG:
		alw = 1.5;
		weight = 3;
		score = 450;
		break;
	case -1:
		alw = 0;
		weight = 0;
		score = 0;
		break;
	}
}

resProperties::resProperties(int resId)
{
	this->setId(resId);
}

float getAlw(int resId)
{
	float alw = 0;
	switch(resId) {
	case ID_BSTONE:
		alw = 1.0;
		break;
	case ID_GOLD:
		alw = 1.0;
		break;
	case ID_SSTONE:
		alw = 2.0;
		break;
	case ID_DIAMOND:
		alw = 3.0;
		break;
	case ID_BAG:
		alw = 1.5;
		break;
	}
	return alw;
}
