/*
    learn.h
*/
#ifndef LEARN_H
#define LEARN_H
#include <stdlib.h>
#include "feature.h"

#define RANDOM ((double)rand()/(double)RAND_MAX)

extern void lda_learn(document *data, double alpha, double beta, int nclass, int nlex, int dlenmax, int maxiter, double **phi, double **theta, FILE *likp);
#endif
