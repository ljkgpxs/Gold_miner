#include "common.h"
#include "resProperties.h"

#define ID_DIAMOND_ALW	1.5
#define ID_BSTONE_ALW	1.0
#define ID_SSTONE_ALW	1.1
#define ID_BAG_ALW	1.5
#define ID_GOLD_ALW	2.0

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
		alw = ID_GOLD_ALW;
		weight = 5;
		score = 22;
		break;
	case ID_GOLD:
		alw = ID_GOLD_ALW;
		weight = 5;
		score = 500;
		break;
	case ID_SSTONE:
		alw = ID_SSTONE_ALW;
		weight = 3;
		score = 11;
		break;
	case ID_DIAMOND:
		alw = ID_DIAMOND_ALW;
		weight = 1;
		score = 600;
		break;
	case ID_BAG:
		alw = ID_BAG_ALW;
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
		alw = ID_BSTONE_ALW;
		break;
	case ID_GOLD:
		alw = ID_GOLD_ALW;
		break;
	case ID_SSTONE:
		alw = ID_SSTONE_ALW;
		break;
	case ID_DIAMOND:
		alw = ID_DIAMOND_ALW;
		break;
	case ID_BAG:
		alw = ID_BAG_ALW;
		break;
	}
	return alw;
}

