#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]) {
    float **a,**b,**c, sm, m, n;
    long int i, j, k, t, size, num, start, end;
    clock_t time1, time2;

    if(argc<2) {
        printf("\n\tUsage:%s <innerloop> <start> <end> <num>\n", argv[0]);
        exit(-1);
    }

    start = atoi(argv[2]);
    end = atoi(argv[3]);
    for(size=start;size<=end;size+=5) {
        a = (float**)malloc(size*sizeof(float*));
        a[0] = (float*)malloc(size*size*sizeof(float));
        for(i=1;i<size;i++) {
            a[i] = a[i-1] + size;
        }
        b = (float**)malloc(size*sizeof(float*));
        b[0] = (float*)malloc(size*size*sizeof(float));
        for(i=1;i<size;i++) {
            b[i] = b[i-1] + size;
        }
        c = (float**)malloc(size*sizeof(float*));
        c[0] = (float*)malloc(size*size*sizeof(float));
        for(i=1;i<size;i++) {
            c[i] = c[i-1] + size;
        }

        for(i=0;i<size;i++) {
            for(j=0;j<size;j++) {
                a[i][j] = (float)(rand()%1000/100.0);
                b[i][j] = (float)(rand()%1000/100.0);
                c[i][j] = 0.0;
            }
        }

        printf("%ld,", size);
        num = atoi(argv[4]);
        for(t=0;t<num;++t) {
            if(strcmp(argv[1], "ijk") == 0) {
                time1 = clock();
                for(i=0;i<size;i++) {
                    for(j=0;j<size;j++) {
                        sm = 0.0;
                        for(k=0;k<size;k++) {
                            sm += a[i][k]*b[k][j];
                        }
                        c[i][j] = sm;
                    }
                }
                time2 = clock();
            }
            if(strcmp(argv[1], "jik") == 0) {
                time1 = clock();
                for(j=0;j<size;j++) {
                    for(i=0;i<size;i++) {
                        sm = 0.0;
                        for(k=0;k<size;k++) {
                            sm += a[i][k]*b[k][j];
                        }
                        c[i][j] += sm;
                    }
                }
                time2 = clock();
            }
            if(strcmp(argv[1], "ikj") == 0) {
                time1 = clock();
                for(i=0;i<size;i++) {
                    for(k=0;k<size;k++) {
                        m = a[i][k];
                        for(j=0;j<size;j++) {
                            c[i][j] += m*b[k][j];
                        }
                    }
                }
                time2 = clock();
            }
            if(strcmp(argv[1], "kij") == 0) {
                time1 = clock();
                for(k=0;k<size;k++) {
                    for(i=0;i<size;i++) {
                        m = a[i][k];
                        for(j=0;j<size;j++) {
                            c[i][j] += m*b[k][j];
                        }
                    }
                }
                time2 = clock();
            }
            if(strcmp(argv[1], "jki") == 0) {
                time1 = clock();
                for(j=0;j<size;j++) {
                    for(k=0;k<size;k++) {
                        n = b[k][j];
                        for(i=0;i<size;i++) {
                            c[i][j] += a[i][k]*n;
                        }
                    }
                }
                time2 = clock();
            }
            if(strcmp(argv[1], "kji") == 0) {
                time1 = clock();
                for(k=0;k<size;k++) {
                    for(j=0;j<size;j++) {
                        n = b[k][j];
                        for(i=0;i<size;i++) {
                            c[i][j] += a[i][k]*n;
                        }
                    }
                }
                time2 = clock();
            }

            printf("%ld,",time2-time1);
        }
        printf("\n");
        free(a[0]);
        free(b[0]);
        free(c[0]);
        free(a);
        free(b);
        free(c);
    }

    return(0);
}
