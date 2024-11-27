#pragma once
#include"vector2d.h"
#include"timer.h"

class Camera {
public:
	Camera() {
		this->shakeTimer.setOneShot(true);
		this->shakeTimer.setOnFinishCallback([this]() {
			this->isShaking = false;
			reset();
			});
	}
	~Camera() = default;

	// 重置摄像机位置为(0,0)
	void reset() {
		this->position.x = 0;
		this->position.y = 0;
	}

	void onUpdate(int deltaTime) {
		this->shakeTimer.onUpdate(deltaTime);

		if (this->isShaking) {
			this->position.x = (rand() % 100 - 50) / 50 * this->shakeAmount;
			this->position.y = (rand() % 100 - 50) / 50 * this->shakeAmount;
		}
	}

	const Vector2D& getPosition() const {
		return this->position;
	}

	//抖动摄像机
	void shake(double amount, int duration) {
		this->shakeAmount = amount;
		this->isShaking = true;
		this->shakeTimer.setWaitTime(duration);
		this->shakeTimer.start();
	}
private:
	// 摄像机位置
	Vector2D position;

	// 摄像机抖动计时器
	Timer shakeTimer;

	// 摄像机抖动幅度
	double shakeAmount = 0;

	// 是否正在抖动
	bool isShaking = false;
};