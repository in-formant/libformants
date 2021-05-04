#define FORMANTS_IMPLEMENTATION
#include "../include/libformants.h"

#include <stdio.h>
#include <sys/time.h>

int main()
{
    const double sampleRate = 48000.0;
    const double duration = 20.0 / 1000.0;

    const int length = (int) round(duration * sampleRate);
    const int order = (int) round(2.5 + sampleRate / 1000.0);
    const double margin = 100.0;

    sample *input = malloc(length * sizeof(sample));
    for (int i = 0; i < length; ++i) {
        const sample t = (sample) i / (sample) length;

        input[i] = 0.3 * sin(2.0 * PI * t * 200.0 / sampleRate)
                    + 0.7 * sin(2.0 * PI * t * 400.0 / sampleRate)
                    + 0.6 * sin(2.0 * PI * t * 600.0 / sampleRate);
    }

    formants_work_t *work = formants_make_work(length, order);

    struct timeval start, end;
    
    gettimeofday(&start, 0);

    for (unsigned long iteration = 0; iteration < 1000; ++iteration) {
        unsigned long formantCount;
        formant_t *formants = formants_analyze(work, input, length, order, sampleRate, margin, &formantCount);
        free(formants);
    }

    gettimeofday(&end, 0);

    long seconds = end.tv_sec - start.tv_sec;
    long microseconds = end.tv_usec - start.tv_usec;
    double elapsed = seconds + 1e-6 * microseconds;

    printf("1000 iterations of formants_analyze took %.6f seconds", elapsed);

    formants_destroy_work(work);

    return 0;
}