#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/functional.h>
#include <thrust/adjacent_difference.h>
#include <thrust/count.h>
#include <thrust/transform_reduce.h>
#include <iostream>
#include <math.h>
#include "cuda_utils.h"

using namespace std;

struct validate
{
    const int movieCount;
    // thrust::device_vector<int> catLimit;
    thrust::device_ptr<const int> catLimit;
    thrust::device_ptr<const int> movieStart;
    thrust::device_ptr<const int> movieEnd;
    thrust::device_ptr<const int> movieCat;

    validate(
        const int movieCount_,
        // const thrust::device_vector<int> &catLimit_,
        thrust::device_ptr<const int> catLimit_,
        thrust::device_ptr<const int> movieStart_,
        thrust::device_ptr<const int> movieEnd_,
        thrust::device_ptr<const int> movieCat_)
        : movieCount(movieCount_),
          catLimit(catLimit_),
          movieStart(movieStart_),
          movieEnd(movieEnd_),
          movieCat(movieCat_){};

    __host__ __device__ int operator()(const int &binPrevious, const int &bin)
    {
        int lastIndex = -1;
        int result = 0;
        int localCatArr[20] = {0};

        for (int i = 0; i < movieCount; i++)
        {
            bool bit = (bin & (1 << i)) != 0;
            if (!bit)
                continue;

            if (lastIndex == -1)
            {
                lastIndex = i;
                result++;
                continue;
            }

            // if (localCatArr[movieCat[i] - 1] == catLimit[movieCat[i] - 1])
            // {
            //     result = 0;
            //     break;
            // }

            if (movieEnd[lastIndex] > movieStart[i])
            {
                result = 0;
                break;
            }

            // localCatArr[movieCat[i] - 1]++;
            lastIndex = i;
            result++;
        }

        return (result > binPrevious) ? result : binPrevious;
    }
};

int main()
{
    vector<int> catLimit;
    vector<int> movieStart;
    vector<int> movieEnd;
    vector<int> movieCat;

    int movieCount = fillDataVectors(catLimit, movieStart, movieEnd, movieCat);
    thrust::device_vector<int> devCatLimit(catLimit);
    thrust::device_vector<int> devStart(movieStart);
    thrust::device_vector<int> devEnd(movieEnd);
    thrust::device_vector<int> devCat(movieCat);

    thrust::counting_iterator<int> startBin(1);
    thrust::counting_iterator<int> endBin = startBin + (int)pow(2, movieCount) - 1;

    // validate validateFunctor(movieCount, devCatLimit.data(), devStart.data(), devEnd.data(), devCat.data());
    // validate validateFunctor(movieCount, devStart.data(), devEnd.data(), devCat.data());

    for (auto it = startBin; it != endBin; it++)
    {
        int bin = *it;
        int lastIndex = -1;
        int result = 0;
        int localCatArr[20] = {0};

        for (int i = 0; i < movieCount; i++)
        {
            bool bit = (bin & (1 << i)) != 0;
            if (!bit)
                continue;

            if (lastIndex == -1)
            {
                lastIndex = i;
                result++;
                continue;
            }

            // if (localCatArr[movieCat[i] - 1] == catLimit[movieCat[i] - 1])
            // {
            //     result = 0;
            //     break;
            // }

            if (movieEnd[lastIndex] > movieStart[i])
            {
                result = 0;
                break;
            }

            // localCatArr[movieCat[i] - 1]++;
            lastIndex = i;
            result++;
        }

        cout << bin << " " << result << endl;
    }

    int maxMovies = thrust::reduce(startBin, endBin, 0, validateFunctor);

    cout << maxMovies;

    return 0;
}
