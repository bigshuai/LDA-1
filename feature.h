/*
    feature.h
    a header file for feature matrix
*/
#ifndef FEATURE_H
#define FEATURE_H
#include <stdio.h>

typedef struct {
    int len;
    int *id;
    int *cnt;
} document;


extern document *feature_matrix(char *filename, int *maxid, int *maxfeat,int *ndoc);
//文档特征矩阵   文件名，最大id，最大feat，ndoc
extern void free_feature_matrix(document *matrix);

#endif
