#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "movie.h"

using namespace std;

vector<int> setCategoryVector(int totalCategories);
vector<Movie> setMovieVector(int totalMovies);

bool tryToAddMovie(vector<Movie> &watchlist, Movie &movie, bool timetable[24], int &freeSlots);
bool sortSmallerDuration(Movie &i, Movie &j) { return i.duration < j.duration; };
bool sortSmallerEndTime(Movie &i, Movie &j) { return i.endTime < j.endTime; };
bool sortSmallerId(Movie &i, Movie &j) { return i.id < j.id; };

void printResult(vector<Movie> &watchlist, bool timetable[24]);

// Implementacao com heuristica gulosa
int main(int argc, char **argv)
{

    bool timetable[24] = {false};
    int freeTimetableSlots = 24;
    int totalMovies;
    int totalCategories;

    cin >> totalMovies >> totalCategories;

    vector<int> categoryCount = setCategoryVector(totalCategories);
    vector<Movie> movies = setMovieVector(totalMovies);
    vector<Movie> watchlist;

    sort(movies.begin(), movies.end(), sortSmallerEndTime);

    for (auto &movie : movies)
    {
        if (freeTimetableSlots == 0)
            break;
        if (movie.startTime > movie.endTime || movie.startTime == movie.endTime)
            continue;
        if (categoryCount[movie.category - 1] <= 0)
            continue;
        if (tryToAddMovie(watchlist, movie, timetable, freeTimetableSlots))
            categoryCount[movie.category - 1]--;
    }

    if (argc <= 1)
    {
        sort(watchlist.begin(), watchlist.end(), sortSmallerId);
        printResult(watchlist, timetable);
    }

    if (argc > 1 && argv[1] == string("--benchmark"))
    {
        cout << watchlist.size() << " " << count(timetable, timetable + 24, false);
    }
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

    for (int i = 0; i < totalMovies; i++)
    {
        cin >> startTime >> endTime >> category;
        id = i;
        duration = endTime - startTime;

        movieVector.push_back({id, duration, category, startTime, endTime});
    }
    return movieVector;
}

bool tryToAddMovie(vector<Movie> &watchlist, Movie &movie, bool timetable[24], int &freeSlots)
{
    for (int i = movie.startTime; i < movie.endTime; i++)
    {
        if (timetable[i])
            return false;
    }

    for (int i = movie.startTime; i < movie.endTime; i++)
    {
        timetable[i] = true;
        freeSlots--;
    }

    watchlist.push_back(movie);
    return true;
}

void printResult(vector<Movie> &watchlist, bool timetable[24])
{
    cout << "Movies to watch: " << watchlist.size() << "\n";
    cout << "Free timetable slots: " << count(timetable, timetable + 24, false) << "\n";

    cout << "\n";
    cout << "ID | Start Time | End Time | Category";
    cout << "\n";

    for (auto &movie : watchlist)
    {
        cout << movie.id << " | ";
        cout << setfill('0') << setw(2) << movie.startTime << " | ";
        cout << setfill('0') << setw(2) << movie.endTime << " | ";
        cout << movie.category << "\n";
    }
}