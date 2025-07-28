#include <Example.h>

struct UserExample : tvgexam::Example {
  int ballRadius = 50;
  uint32_t w, h;
  float ballX, ballY;
  float v_x, v_y;

  bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) override {
    // Initialize the ball position and velocity
    ballX = w / 2 - ballRadius;
    ballY = h / 2 - ballRadius;
    v_x = 10;
    v_y = 12;
    this->w = w;
    this->h = h;

    return update(canvas, 0);
  }

  bool update(tvg::Canvas* canvas, uint32_t elapsed) override {
    canvas->remove();  // clear previous content

    // Draw the background
    auto shape = tvg::Shape::gen();
    shape->appendRect(0, 0, w, h);
    shape->fill(255, 255, 255);
    canvas->push(shape);

    // Draw the bounding ball
    auto ball = tvg::Shape::gen();

    ballX += v_x;
    ballY += v_y;

    if (ballX <= ballRadius || ballX >= w - ballRadius) {
      v_x = -v_x;  // change direction on left/right walls
    }
    if (ballY <= ballRadius || ballY >= h - ballRadius) {
      v_y = -v_y;  // change direction on top/bottom walls
    }
    ball->appendCircle(ballX, ballY, ballRadius, ballRadius);
    ball->fill(0, 0, 255);
    canvas->push(ball);
    return true;
  }
};

int main(int argc, char** argv) {
  return tvgexam::main(new UserExample, argc, argv, false, 1024, 1024, 4, true);
}