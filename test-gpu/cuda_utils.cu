#include <algorithm>
#include <thrust/device_vector.h>
#include <iostream>
#include "cuda_utils.h"
#include "movie.h"

using namespace std;

int fillDataVectors(vector<int> &catLimit, vector<int> &start, vector<int> &end, vector<int> &cat)
{
    int totalMovies;
    int totalCategories;

    cin >> totalMovies >> totalCategories;

    // Fill category limit vector
    catLimit.reserve(totalCategories);
    int categoryLimit;
    for (int i = 0; i < totalCategories; i++)
    {
        cin >> categoryLimit;
        catLimit.push_back(categoryLimit);
    }

    // Fill start, end and cat vectors
    int startValue, endValue, catValue;
    vector<Movie> movies;
    int movieCount = 0;
    for (int i = 0; i < totalMovies; i++)
    {
        cin >> startValue >> endValue >> catValue;
        if (startValue >= endValue)
            continue;

        movies.push_back({i, endValue - startValue, catValue, startValue, endValue});
        movieCount++;
    }

    sort(movies.begin(), movies.end(), [](const Movie &lhs, const Movie &rhs)
         { return lhs.startTime < rhs.startTime; });

    for (auto movie : movies)
    {
        start.push_back(movie.startTime);
        end.push_back(movie.endTime);
        cat.push_back(movie.category);
    }

    return movieCount;
}

thrust::device_vector<bool> convertToBinaryVec(int n, int size)
{

    thrust::device_vector<bool> binaryVec(size);
    for (int i = 0; i < n; i++)
    {
        binaryVec[i] = n & (1 << i);
    }
    return binaryVec;
}

// struct sum_two
// {
//     __host__ __device__ int operator()(const int &x, const int &y)
//     {
//         return x + y;
//     }
// }

// struct validate_combination
// {
//     int a;
//     validate_combination(int a_) : a(a_) {};
//     __host__ __device__
//     int operator()(const int& x) {
//            if ()
//     }
// };
