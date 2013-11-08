#ifndef PERFORMSEARCHES_H
#define PERFORMSEARCHES_H
#include <cstdlib>
#include <limits>

class PerformSearches
{
    public:
        PerformSearches();
        virtual ~PerformSearches();
        void shuffle(int* array, int size);
        int* makeSet(int size);
        double* performPre(int universe);
        double* performRemoves(int universe);
        double* performInserts(int universe);
        double* performMember(int universe);
    protected:
    private:
        timespec mStartTime;
        void getTime();
        void startClock();
        double stopClock();
};

#endif
