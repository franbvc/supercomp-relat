#include <thrust/device_vector.h>
#include <thrust/transform.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/functional.h>
#include <thrust/adjacent_difference.h>
#include <thrust/count.h>
#include <thrust/transform_reduce.h>
#include <thrust/copy.h>
#include <iostream>
#include <math.h>
#include "cuda_utils.h"

using namespace std;

struct validate
{
    const int movieCount;
    thrust::device_ptr<const int> movieStart;
    thrust::device_ptr<const int> movieEnd;
    thrust::device_ptr<const int> movieCat;

    validate(
        const int movieCount_,
        thrust::device_ptr<const int> movieStart_,
        thrust::device_ptr<const int> movieEnd_,
        thrust::device_ptr<const int> movieCat_)
        : movieCount(movieCount_),
          movieStart(movieStart_),
          movieEnd(movieEnd_),
          movieCat(movieCat_){};

    __host__ __device__ int operator()(const int &bin)
    {
        int lastIndex = -1;
        int result = 0;

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

            if (movieEnd[lastIndex] > movieStart[i])
                return 0;

            lastIndex = i;
            result++;
        }

        return result;
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

    validate validateFunctor(movieCount, devStart.data(), devEnd.data(), devCat.data());

    thrust::device_vector<int> validCombinations;
    thrust::copy_if(startBin, endBin, validCombinations.begin(), validateFunctor);

    for (auto el : validCombinations)
    {
        cout << el << " ";
    }

    return 0;
}
