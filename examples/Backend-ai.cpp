#include <Example.h>

struct BackendAI : tvgexam::Example {
  bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) override {
    auto shape = tvg::Shape::gen();
    shape->appendRect(0, 0, w, h);
    shape->fill(255, 255, 255);

    canvas->push(shape);

    auto picture = tvg::Picture::gen();

    if (!tvgexam::verify(picture->load(EXAMPLE_DIR "/svg/backend-ai.svg")))
      return false;

    float scale;
    float w2, h2;
    picture->size(&w2, &h2);

    if (w2 > h2) {
      scale = w / w2;
    } else {
      scale = h / h2;
    }
    scale *= 0.8f;  // 80% of the size
    picture->scale(scale);

    // 가운데 정렬
    float x = (w - w2 * scale) / 2.0f;
    float y = (h - h2 * scale) / 2.0f;
    picture->translate(x, y);

    canvas->push(picture);

    return true;
  }
};

int main(int argc, char** argv) {
  return tvgexam::main(new BackendAI, argc, argv, false, 1024, 1024, 4, true);
}