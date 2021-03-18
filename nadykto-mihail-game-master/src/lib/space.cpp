#include "lib/map_generator/space.h"

#include <random>

/*
 * Этот класс основан на рекурсии. Мы создаем определенное пространсто с задными размерами, даее мы можем делить его
 * пополам до бесконечности. На данном этапе параметры рандома делаю с небольшим разбросом, чтобы не создавались слишком
 * маленькие участки, из тех же соображений чередуем горизонтальное и вертикальное деление. Пространство рассмативается
 * как координаты двух крайних точек.
 */
Space::Space(int x1, int y1, int x2, int y2, bool horizontally)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2), horizontally_(horizontally) {
  std::default_random_engine rng;
  std::uniform_int_distribution<int> dist_a_b(4, 6);  // эти параметры сделаю перемеными
  rng.seed(std::random_device()());
  if (horizontally_) {
    interval_ = x1 + round((x2 - x1) * dist_a_b(rng) / 10);
  } else {
    interval_ = y1 + round((y2 - y1) * dist_a_b(rng) / 10);
  }
}

Space* Space::GetFirst() {
  if (first_ == nullptr) {
    if (horizontally_) {
      first_ = new Space(x1_, y1_, interval_, y2_, !horizontally_);
    } else {
      first_ = new Space(x1_, y1_, x2_, interval_, !horizontally_);
    }
  }
  return first_;
}
Space* Space::GetSecond() {
  if (second_ == nullptr) {
    if (horizontally_) {
      second_ = new Space(interval_, y1_, x2_, y2_, !horizontally_);
    } else {
      second_ = new Space(x1_, interval_, x2_, y2_, !horizontally_);
    }
  }
  return second_;
}
