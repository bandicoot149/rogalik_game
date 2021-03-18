#include "lib/map_generator/map_generator.h"

#include <math.h>

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "hike/scenes/game_scene.h"
#include "lib/map_generator/space.h"

void MapGenerator::Generate(std::string map_path, int number, int width, int height, int number_iterations,
                            bool horizontally) {
  Space* first = new Space(0, 0, width, height, horizontally);
  std::vector<Space*> spaces;  // будет содержать конечные участки
  spaces.push_back(first);
  std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lanes;  // координаты дорожек
  std::pair<std::pair<int, int>, std::pair<int, int>> enter_exit;  // координаты входа и выхода
  std::vector<std::pair<int, int>> coins;                          // координаты монеток
  std::vector<std::pair<int, int>> enemies;
  // делим пространсто, создаем дорожки
  for (int i = 0; i < number_iterations; i++) {
    for (Space* space : spaces) {
      lanes.push_back(MapGenerator::CreateLane(space));
    }
    spaces = MapGenerator::Divide(spaces);
  }
  // теперь необходимо создать комнату в каждом участке, теперь уже проще рисовать реальную карту
  char generated_map[height][width];
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      generated_map[i][j] = '#';
    }
  }

  spaces = MapGenerator::DoBorder(spaces);  // добавим рамки каждому участку
  for (Space* space : spaces) {
    for (int i = space->y1_; i < space->y2_; i++) {
      for (int j = space->x1_; j < space->x2_; j++) {
        generated_map[i][j] = '.';
      }
    }
  }

  coins = MapGenerator::CreateCoins(spaces, 5);  // добавим монеток
  for (auto coin : coins) {
    generated_map[coin.first][coin.second] = '$';
  }

  enemies = MapGenerator::CreateEnemies(spaces, 5);
  for (auto enemy : enemies) {
    generated_map[enemy.first][enemy.second] = 'E';
  }

  // делаем дорожки
  for (auto lane : lanes) {
    generated_map[lane.first.first][lane.first.second] = '.';
    generated_map[lane.second.first][lane.second.second] = '.';
  }

  enter_exit = MapGenerator::CreateEnterExit(spaces);  // добавим вход и выход
  generated_map[enter_exit.first.first][enter_exit.first.second] = '@';
  generated_map[enter_exit.second.first][enter_exit.second.second] = '>';

  // запись в файл
  std::ofstream out;   // поток для записи
  out.open(map_path);  // окрываем файл для записи
  if (out.is_open()) {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        out << generated_map[i][j];
      }
      out << std::endl;
    }
  }
}

std::vector<Space*> MapGenerator::Divide(std::vector<Space*> spaces) {
  std::vector<Space*> newSpaces;
  for (Space* space : spaces) {
    newSpaces.push_back(space->GetFirst());
    newSpaces.push_back(space->GetSecond());
  }
  return newSpaces;
}
std::vector<Space*> MapGenerator::DoBorder(std::vector<Space*> spaces) {
  for (Space* space : spaces) {
    space->x1_++;
    space->x2_--;
    space->y1_++;
    space->y2_--;
  }
  return spaces;
}
std::pair<std::pair<int, int>, std::pair<int, int>> MapGenerator::CreateLane(Space* space) {
  std::pair<std::pair<int, int>, std::pair<int, int>> lanes;
  std::default_random_engine rng;
  std::uniform_int_distribution<int> dist_a_b(1, 2);
  if (space->horizontally_) {
    rng.seed(std::random_device()());
    int space_height = space->y2_ - space->y1_;
    float deviation =
        0.25;  // это максимальное отклонение от краев, чем больше итераций деления, тем меньше оно должно быть
    int first_limit;
    int second_limit;
    if (dist_a_b(rng) == 1) {
      first_limit = 1;
      second_limit = round(space_height * deviation);  //
    } else {
      first_limit = round((space_height - 1) * (1 - deviation));
      second_limit = space_height - 2;
    }
    std::uniform_int_distribution<int> dist_first_second(first_limit, second_limit);
    rng.seed(std::random_device()());
    int height_lane = space->GetFirst()->y1_ + dist_first_second(rng);
    lanes = std::make_pair(std::make_pair(height_lane, space->GetFirst()->x2_ - 1),
                           std::make_pair(height_lane, space->GetFirst()->x2_));
  } else {
    rng.seed(std::random_device()());
    int space_width = space->x2_ - space->x1_;
    int first_limit;
    int second_limit;
    if (dist_a_b(rng) == 1) {
      first_limit = 1;
      second_limit = round(space_width * 0.25);
    } else {
      first_limit = round(space_width * 0.75);
      second_limit = space_width - 2;
    }
    std::uniform_int_distribution<int> dist_first_second(first_limit, second_limit);
    rng.seed(std::random_device()());
    int width_lane = space->GetFirst()->x1_ + dist_first_second(rng);
    lanes = std::make_pair(std::make_pair(space->GetFirst()->y2_ - 1, width_lane),
                           std::make_pair(space->GetFirst()->y2_, width_lane));
  }
  return lanes;
}
std::pair<std::pair<int, int>, std::pair<int, int>> MapGenerator::CreateEnterExit(std::vector<Space*> spaces) {
  int room_number_enter;
  int room_number_exit;
  std::default_random_engine rng;
  std::uniform_int_distribution<int> dist_a_b(0, spaces.size() - 1);
  rng.seed(std::random_device()());
  room_number_enter = dist_a_b(rng);
  rng.seed(std::random_device()());
  room_number_exit = dist_a_b(rng);
  while (room_number_exit == room_number_enter) {
    rng.seed(std::random_device()());
    room_number_exit = dist_a_b(rng);
  }
  int enter_height;
  int enter_width;
  int exit_height;
  int exit_width;
  int room_iteration = 0;
  for (Space* space : spaces) {
    if (room_iteration == room_number_enter) {
      enter_height = space->y1_ + round((space->y2_ - space->y1_) / 2);
      enter_width = space->x1_ + round((space->x2_ - space->x1_) / 2);
    }

    if (room_iteration == room_number_exit) {
      exit_height = space->y1_ + round((space->y2_ - space->y1_) / 2);
      exit_width = space->x1_ + round((space->x2_ - space->x1_) / 2);
    }
    room_iteration++;
  }
  auto enter_exit = std::make_pair(std::make_pair(enter_height, enter_width), std::make_pair(exit_height, exit_width));
  return enter_exit;
}
std::vector<std::pair<int, int>> MapGenerator::CreateCoins(std::vector<Space*> spaces, int frequency) {
  auto coins = std::vector<std::pair<int, int>>();
  for (Space* space : spaces) {
    std::default_random_engine rng;
    std::uniform_int_distribution<int> dist_a_b(0, frequency);
    rng.seed(std::random_device()());
    for (int i = 0; i < dist_a_b(rng); i++) {
      std::uniform_int_distribution<int> dist_width(space->x1_, space->x2_ - 1);
      std::uniform_int_distribution<int> dist_height(space->y1_, space->y2_ - 1);
      rng.seed(std::random_device()());
      coins.push_back(std::make_pair(dist_height(rng), dist_width(rng)));
    }
  }
  return coins;
}
std::vector<std::pair<int, int>> MapGenerator::CreateEnemies(std::vector<Space*> spaces, int frequency) {
  auto enemies = std::vector<std::pair<int, int>>();
  for (Space* space : spaces) {
    std::default_random_engine rng;
    std::uniform_int_distribution<int> dist_a_b(1, frequency);
    rng.seed(std::random_device()());
    if (dist_a_b(rng) == 1) {
      std::uniform_int_distribution<int> dist_width(space->x1_, space->x2_ - 1);
      std::uniform_int_distribution<int> dist_height(space->y1_, space->y2_ - 1);
      rng.seed(std::random_device()());
      enemies.push_back(std::make_pair(dist_height(rng), dist_width(rng)));
    }
  }
  return enemies;
}
