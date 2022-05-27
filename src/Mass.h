#pragma once
#include "Point.h"

class Mass
{
public:
	enum status
	{
		BLANK,
		GOAL,
		START,
		WAYPOINT,
		WALL, // �ʂ�Ȃ�
		WATER,// �i�ނ̂�1/3�ɒx���Ȃ�
		ROAD,//�i�ނ̂�3�{����
	};
	enum listed
	{
		NONE,
		OPEN,
		CLOSE,
	};
private:
	status s_ = BLANK;
	listed listed_ = NONE;   // ���X�g�ɓo�^����Ă��邩�������ɔ��f���邽�߂Ɏ��珊��
	Point pos_;   // �e�����Ă�悤�ɂ���
	Mass* pParent_ = nullptr;
	int steps_ = 0;
	double estimate_ = 0.0;

	static int getWalkCost(Mass& m)
	{
		status s = m.getStatus();
		int cost = 3;   // BLANK�̃R�X�g�F3

		if (s == ROAD)
		{
			cost /= 3;
		}
		else if (s == WATER)
		{
			cost *= 3;
		}

		return cost;
	}

	void calcCost(const Point target)
	{
		// steps_ = (pParent_ ? pParent_->steps_ : 0) + 1;
		steps_ = (pParent_ ? pParent_->steps_ : 0) + getWalkCost(*this);
		estimate_ = Point::distance(pos_, target);
	}
public:
	void setStatus(status s) { s_ = s; }
	status getStatus() const { return s_; }

	void setPos(int x, int y) { pos_.set(x, y); }
	const Point& getPos() const { return pos_; }
	int x() { return pos_.x(); }
	int y() { return pos_.y(); }

	// �e�����Ă�悤�ɂ���
	void setParent(Mass* pParent, const Point& goal) { pParent_ = pParent; calcCost(goal); }
	Mass* getParent() { return pParent_; }

	void setListed(listed t) { listed_ = t; }
	bool isListed(listed t) const { return listed_ == t; }

	double getCost() const { return (double)steps_ + estimate_; }
};

// �\�[�g�p��r�֐��Aboard.cpp�Œ�`
bool asc(const Mass* o1, const Mass* o2);