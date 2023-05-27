#include <algorithm>
#include <iostream>
#include <math.h>
#include "movie.h"
#include "utils.h"

using namespace std;

int validateInput(int combinationCode, vector<Movie> movies, vector<int> categoryLimit, int movieCount);

int main()
{
    auto [totalMovies, totalCategories] = getInputParameters();
    vector<int> categoryLimit = setCategoryVector(totalCategories);
    vector<Movie> movies = setMovieVector(totalMovies);
    int movieCount = movies.size();

    // Define last binary for movie combinations
    int maxBin = (int)pow(2, movieCount) - 1;
    cout << "Max Binary: " << maxBin << endl;

    // sort movies by increasing end time
    sort(movies.begin(), movies.end(), [](Movie &i, Movie &j)
         { return i.endTime < j.endTime; });

    int maxMovies = 0;

#pragma omp parallel for reduction(max : maxMovies)
    for (int i = 1; i <= maxBin; i++)
    {
        if (__builtin_popcount(i) > 24)
            continue;
        maxMovies = max(maxMovies, validateInput(i, movies, categoryLimit, movieCount));
    }

    cout << maxMovies << endl;

    return 0;
}

int validateInput(int combinationCode, vector<Movie> dataVec, vector<int> catLimit, int movieCount)
{
    int lastIndex = -1;
    int result = 0;

    for (int i = 0; i < movieCount; i++)
    {
        bool bit = (combinationCode & (1 << i)) != 0;
        if (!bit)
            continue;

        if (lastIndex == -1)
        {
            lastIndex = i;
            result++;
            continue;
        }

        if (catLimit[dataVec[i].category - 1] == 0)
            return 0;
        if (dataVec[lastIndex].endTime > dataVec[i].startTime)
            return 0;

        catLimit[dataVec[i].category - 1]--;
        lastIndex = i;
        result++;
    }

    return result;
}