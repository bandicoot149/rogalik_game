#ifndef INCLUDE_LIB_MAP_GENERATOR_SPACE_H_
#define INCLUDE_LIB_MAP_GENERATOR_SPACE_H_

class Space {
 public:
  int x1_;
  int y1_;
  int x2_;
  int y2_;
  bool horizontally_;
  int interval_;
  Space(int x1, int y1, int x2, int y2, bool horizontally);
  Space *GetFirst();
  Space *GetSecond();

 private:
  Space *first_ = nullptr;
  Space *second_ = nullptr;
};

#endif  // INCLUDE_LIB_MAP_GENERATOR_SPACE_H_
