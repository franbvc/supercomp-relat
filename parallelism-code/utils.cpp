#include <iostream>
#include "utils.h"

using namespace std;

tuple<int, int> getInputParameters()
{
    int totalMovies;
    int totalCategories;

    cin >> totalMovies >> totalCategories;

    return make_tuple(totalMovies, totalCategories);
}

vector<int> setCategoryVector(int totalCategories)
{
    vector<int> categoryVector;
    categoryVector.reserve(totalCategories);

    int categoryLimit;
    for (int i = 0; i < totalCategories; i++)
    {
        cin >> categoryLimit;
        categoryVector.push_back(categoryLimit);
    }

    return categoryVector;
}

vector<Movie> setMovieVector(int totalMovies)
{
    vector<Movie> movieVector;
    movieVector.reserve(totalMovies);

    int id, duration, category, startTime, endTime;

    int count = 0;
    for (int i = 0; i < totalMovies; i++)
    {
        cin >> startTime >> endTime >> category;
        id = count;
        duration = endTime - startTime;

        if (duration <= 0)
            continue;

        movieVector.push_back({id, duration, category, startTime, endTime});
    }
    return movieVector;
}