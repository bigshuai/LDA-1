/*
    lda.c
    Latent Dirichlet Allocation, main driver.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lda.h"
#include "learn.h"
#include "writer.h"
#include "feature.h"
#include "dmatrix.h"
#include "util.h"

int main(int argc, char **argv){
    document *data;
    FILE *pp, *tp, *likp; // for phi, theta, likelihood
    char c;
    int nlex, dlenmax;
    int ndoc;
    int nclass = CLASS_DEFAULT;
    int maxiter = MAXITER_DEFAULT;
    double alpha = ALPHA_DEFAULT;
    double beta = BETA_DEFAULT;
    double **phi;
    double **theta;
    
    while((c = getopt(argc, argv, "N:I:A:B:h")) != -1){
        switch(c){
            case 'N': nclass = atoi(optarg); break;
            case 'I': maxiter = atoi(optarg); break;
            case 'A': alpha = atof(optarg); break;
            case 'B': beta = atof(optarg); break;
            case 'h': usage(); break;
            default: usage(); break;
        }
    }
    if(!(argc - optind == 2))
        usage();
    
    // open data
    if((data = feature_matrix(argv[optind], &nlex, &dlenmax, &ndoc)) == NULL){
        fprintf(stderr, "lda:: cannot open training data.\n");
        exit(1);
    }
    
    // open model output
    if(((pp = fopen(strconcat(argv[optind+1], ".phi"),"w")) == NULL)
    || ((tp = fopen(strconcat(argv[optind+1], ".theta"),"w")) == NULL)
    || ((likp = fopen(strconcat(argv[optind+1], ".lik"),"w")) == NULL)){
        fprintf(stderr, "lda:: cannot open model outputs.\n");
        exit(1);
    }
    
    // allocate parameters
    if((phi = dmatrix(nlex, nclass)) == NULL){
        fprintf(stderr, "lda:: cannot allocate phi.\n");
        exit(1);
    }
    if((theta = dmatrix(ndoc, nclass)) == NULL){
        fprintf(stderr, "lda:: cannot allocate theta.\n");
        exit(1);
    }
    
    lda_learn(data, alpha, beta, nclass, nlex, dlenmax, maxiter, phi, theta, likp);
    lda_write(pp, tp, phi, theta, nclass, nlex, ndoc);
    
    free_feature_matrix(data);
    free_dmatrix(phi, nlex);
    free_dmatrix(theta, ndoc);
    
    fclose(pp);
    fclose(tp);
    
    exit(0);
}

void usage(void){
    printf("usage: %s -N classes [-I maxiter] [-A alpha] [-B beta] train model\n", "lda");
    exit(0);
}
