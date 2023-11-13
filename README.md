# HPC Study

## Overview

This project focuses on solving the Knapsack Problem in the context of scheduling movie-watching sessions. The objective is to maximize the number of movies watched in a day, given their start and end times and their categories. Various methods, including heuristics, brute force, and parallelized solutions, were explored to address the problem. The performance of each method was extensively compared and analyzed in the `relatorio/relatorio-final.ipynb` report.

## Problem Description

Given a limit of movies per category and a list of movies and their respective start and end times, and categories, the task is to find the optimal schedule that allows watching the maximum number of movies in a day, without exceeding the limit of movies per category.

## Methods

### Heuristic Methods
1. **Greedy Algorithm**: Implements a greedy strategy to select movies based on certain criteria. The movies are sorted by their end times in ascending order. The algorithm then selects the movies that start first and do not conflict with the movies already selected. It also checks if there are available slots in the category of the movie. 
   
2. **Greedy Algorithm with Added Randomness**: Extends the basic greedy approach by introducing randomization to enhance diversity. The algorithm selects a movie based on the greedy criteria. However, there is a 25% chance that the algorithm will select a random movie that does not conflict with the movies already selected.

### Brute Force Method

1. **Exhaustive Search**: Examines all possible combinations of movie schedules to find the optimal solution.

### Parallelized Solutions

1. **Threaded Exhaustive Search (OpenMP)**: Implements parallelization using threading to speed up the exhaustive search.

2. **GPU and CUDA Solution**: Utilizes GPU and CUDA for parallelization in the exhaustive search.

## Code Organization

The algorithms were all implemented in C++, except for the GPU solution, which was implemented in CUDA. The testing was automated using a Python script. The performance analysis was done using Jupyter notebook (Python).

- `code/`: Contains the C++ source code files for the greedy methods.
- `parallelism-code/`: Contains the C++ source code files for the threaded exhaustive search.
- `relatorio/relat-final-colab.ipynb`: Jupyter notebook with the GPU solution, as it was run on Google Colab.
- `input/`: Contains the input files for testing.
- `relatorio/relatorio-final.ipynb`: Jupyter notebook providing a detailed report and performance comparison.

## Testing

Testing was automated using a Python script that executed the test files for each solution. This ensured consistent and reproducible results.

## Performance Comparison

The performance of each method is thoroughly discussed and compared in the `relatorio-final.ipynb` report. Python data analysis tools such as pandas were employed for data manipulation, while matplotlib and seaborn were used for visualization. There was also a profiling step to identify the bottlenecks of the greedy algorithms. Also included in the report are the results of the GPU solution, which was run on Google Colab and compared to the OpenMP solution (which was also run on Google Colab).

For now the report is only available in Portuguese. An English version will be uploaded soon.

## Dependencies

- C++ compiler (for compiling C++ code)
- CUDA toolkit (for GPU solution)
- Python 3
- Required Python packages: pandas, matplotlib, seaborn