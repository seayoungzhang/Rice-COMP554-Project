#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]) {
    float **a,**b,**c, sm, m, n;
    long int i, j, k, t, size, num, start, end;
    struct timeval time1,time2;

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
                gettimeofday(&time1,NULL);
                for(i=0;i<size;i++) {
                    for(j=0;j<size;j++) {
                        sm = 0.0;
                        for(k=0;k<size;k++) {
                            sm += a[i][k]*b[k][j];
                        }
                        c[i][j] = sm;
                    }
                }
                gettimeofday(&time2,NULL);
            }
            if(strcmp(argv[1], "jik") == 0) {
                gettimeofday(&time1,NULL);
                for(j=0;j<size;j++) {
                    for(i=0;i<size;i++) {
                        sm = 0.0;
                        for(k=0;k<size;k++) {
                            sm += a[i][k]*b[k][j];
                        }
                        c[i][j] += sm;
                    }
                }
                gettimeofday(&time2,NULL);
            }
            if(strcmp(argv[1], "ikj") == 0) {
                gettimeofday(&time1,NULL);
                for(i=0;i<size;i++) {
                    for(k=0;k<size;k++) {
                        m = a[i][k];
                        for(j=0;j<size;j++) {
                            c[i][j] += m*b[k][j];
                        }
                    }
                }
                gettimeofday(&time2,NULL);
            }
            if(strcmp(argv[1], "kij") == 0) {
                gettimeofday(&time1,NULL);
                for(k=0;k<size;k++) {
                    for(i=0;i<size;i++) {
                        m = a[i][k];
                        for(j=0;j<size;j++) {
                            c[i][j] += m*b[k][j];
                        }
                    }
                }
                gettimeofday(&time2,NULL);
            }
            if(strcmp(argv[1], "jki") == 0) {
                gettimeofday(&time1,NULL);
                for(j=0;j<size;j++) {
                    for(k=0;k<size;k++) {
                        n = b[k][j];
                        for(i=0;i<size;i++) {
                            c[i][j] += a[i][k]*n;
                        }
                    }
                }
                gettimeofday(&time2,NULL);
            }
            if(strcmp(argv[1], "kji") == 0) {
                gettimeofday(&time1,NULL);
                for(k=0;k<size;k++) {
                    for(j=0;j<size;j++) {
                        n = b[k][j];
                        for(i=0;i<size;i++) {
                            c[i][j] += a[i][k]*n;
                        }
                    }
                }
                gettimeofday(&time2,NULL);
            }

            time2.tv_sec-=time1.tv_sec;
            time2.tv_usec-=time1.tv_usec;

            if (time2.tv_usec<0L){
                time2.tv_usec+=1000000L;
                time2.tv_sec-=1;
            }
            printf("%ld.%06ld,",time2.tv_sec,time2.tv_usec);
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
