#include <Example.h>

struct UserExample : tvgexam::Example {
  int ballRadius = 50;
  uint32_t w, h;
  float ballX, ballY;
  float v_x, v_y;
  uint32_t lastUpdateTime = 0;
  float prevBallX, prevBallY;

  bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) override {
    // Initialize the ball position and velocity
    prevBallX = ballX = w / 2 - ballRadius;
    prevBallY = ballY = h / 2 - ballRadius;
    v_x = 10;
    v_y = 12;
    this->w = w;
    this->h = h;

    return update(canvas, 0);
  }

  bool update(tvg::Canvas* canvas, uint32_t elapsed) override {
    if (elapsed - lastUpdateTime >= 16) {
      prevBallX = ballX;
      prevBallY = ballY;

      ballX += v_x;
      ballY += v_y;

      if (ballX <= ballRadius || ballX >= w - ballRadius) {
        v_x = -v_x;
      }
      if (ballY <= ballRadius || ballY >= h - ballRadius) {
        v_y = -v_y;
      }

      lastUpdateTime = elapsed;
    }

    float t = (float)(elapsed - lastUpdateTime) / 16.0f;  // 0.0 ~ 1.0
    float interpolatedX = prevBallX + (ballX - prevBallX) * t;
    float interpolatedY = prevBallY + (ballY - prevBallY) * t;

    canvas->remove();

    // Background
    auto shape = tvg::Shape::gen();
    shape->appendRect(0, 0, w, h);
    shape->fill(255, 255, 255);
    canvas->push(shape);

    // Ball with interpolated position
    auto ball = tvg::Shape::gen();
    ball->appendCircle(interpolatedX, interpolatedY, ballRadius, ballRadius);
    ball->fill(0, 0, 255);
    canvas->push(ball);

    return true;
  }
};

int main(int argc, char** argv) {
  return tvgexam::main(new UserExample, argc, argv, false, 1024, 1024, 4, true);
}