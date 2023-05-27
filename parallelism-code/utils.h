#ifndef UTILS_H
#define UTILS_H

#include <tuple>
#include <vector>
#include "movie.h"

using namespace std;

tuple<int, int> getInputParameters();
vector<int> setCategoryVector(int totalCategories);
vector<Movie> setMovieVector(int totalMovies);

#endif