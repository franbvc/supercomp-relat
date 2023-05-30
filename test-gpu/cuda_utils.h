#ifndef CUDA_UTILS_H
#define CUDA_UTILS_H

#include <thrust/device_vector.h>
#include <vector>

using namespace std;

int fillDataVectors(vector<int> &catLimit, vector<int> &start, vector<int> &end, vector<int> &cat);
thrust::device_vector<bool> convertToBinaryVec(int n, int size);
struct sum_two
{
    __host__ __device__ int operator()(const int &x, const int &y)
    {
        return x + y;
    }
};

#endif