#pragma once

class resProperties {
	int id;
	float alw;
	float weight;
public:
	int score;
	resProperties(int resId = -1);
	void setId(int resId);
	float getAlw();
	int getId();
	float getWeight();
};

float getAlw(int id);
