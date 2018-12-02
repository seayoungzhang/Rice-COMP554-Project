#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[]) {
    float *a,*b,*c;
    long int i, j, k, t, size, num, m, n, sm, start, end;
    struct timeval time1,time2;

    if(argc<2) {
        printf("\n\tUsage:%s <innerloop> <start> <end> <num>\n", argv[0]);
        exit(-1);
    }

    start = atoi(argv[2]);
    end = atoi(argv[3]);
    for(size=start;size<end;size+=25) {
        a = (float*)malloc(sizeof(float)*size*size);
        b = (float*)malloc(sizeof(float)*size*size);
        c = (float*)malloc(sizeof(float)*size*size);
        for(i=0;i<size;i++) {
            for(j=0;j<size;j++) {
                a[i*size+j] = (float)(rand()%1000/100.0);
                b[i*size+j] = (float)(rand()%1000/100.0);
                c[i*size+j] = 0;
            }
        }

        printf("%ld,", size);
        num = atoi(argv[4]);
        for(t=0;t<num;++t) {
            if(strcmp(argv[1], "ijk") == 0) {
                gettimeofday(&time1,NULL);
                for(i=0;i<size;i++) {
                    for(j=0;j<size;j++) {
                        sm = 0;
                        for(k=0;k<size;k++) {
                            sm += a[i*size+k]*b[k*size+j];
                        }
                        c[i*size+j] += sm;
                    }
                }
                gettimeofday(&time2,NULL);
            }
            if(strcmp(argv[1], "jik") == 0) {
                gettimeofday(&time1,NULL);
                for(j=0;j<size;j++) {
                    for(i=0;i<size;i++) {
                        sm = 0;
                        for(k=0;k<size;k++) {
                            sm += a[i*size+k]*b[k*size+j];
                        }
                        c[i*size+j] += sm;
                    }
                }
                gettimeofday(&time2,NULL);
            }
            if(strcmp(argv[1], "ikj") == 0) {
                gettimeofday(&time1,NULL);
                for(i=0;i<size;i++) {
                    for(k=0;k<size;k++) {
                        m = a[i*size+k];
                        for(j=0;j<size;j++) {
                            c[i*size+j] += m*b[k*size+j];
                        }
                    }
                }
                gettimeofday(&time2,NULL);
            }
            if(strcmp(argv[1], "kij") == 0) {
                gettimeofday(&time1,NULL);
                for(k=0;k<size;k++) {
                    for(i=0;i<size;i++) {
                        m = a[i*size+k];
                        for(j=0;j<size;j++) {
                            c[i*size+j] += m*b[k*size+j];
                        }
                    }
                }
                gettimeofday(&time2,NULL);
            }
            if(strcmp(argv[1], "jki") == 0) {
                gettimeofday(&time1,NULL);
                for(j=0;j<size;j++) {
                    for(k=0;k<size;k++) {
                        n = b[k*size+j];
                        for(i=0;i<size;i++) {
                            c[i*size+j] += a[i*size+k]*n;
                        }
                    }
                }
                gettimeofday(&time2,NULL);
            }
            if(strcmp(argv[1], "kji") == 0) {
                gettimeofday(&time1,NULL);
                for(k=0;k<size;k++) {
                    for(j=0;j<size;j++) {
                        n = b[k*size+j];
                        for(i=0;i<size;i++) {
                            c[i*size+j] += a[i*size+k]*n;
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
            printf("%ld.%ld,",time2.tv_sec,time2.tv_usec);
        }
        printf("\n");
        free(a);
        free(b);
        free(c);
    }

    return(0);
}
