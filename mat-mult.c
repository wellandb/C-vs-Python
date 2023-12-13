#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct matrix{
  int rows, cols;
  int** start_ptr; // points to start of matrix
};

typedef struct matrix matrix;

matrix* generate_mat(int row, int col){
  struct matrix* mat = malloc(sizeof(struct matrix));

  mat-> rows = row;
  mat-> cols = col;
  mat -> start_ptr = malloc(sizeof(int*)*row);
  // allocate a chunk of memory the size of a row for each row
  for(int i = 0; i < row; i++){
    mat-> start_ptr[i] = malloc(sizeof(int*)*col);
  }

  if(mat->start_ptr == NULL){
    printf("Failure when allocating memory.\n");
    return NULL;
  }

  for(int i = 0; i < row; i++){
      for(int j = 0; j < col; j++){
          mat -> start_ptr[i][j] = rand() % 100;
      }
  }

  return mat;
}

void print_mat(matrix* matr){
    for(int a = 0; a < matr->rows; a++){
        for(int b = 0; b < matr->cols; b++){
            printf("%d\t", matr->start_ptr[a][b]);
        }
        printf("\n");
    }
}

void mat_mult(matrix* m1, matrix* m2){
  // create result mat and make all items 0
  struct matrix* result_mat = generate_mat(m1->rows,m1->rows);
  for(int i = 0; i < result_mat->rows; i++){
      for(int j = 0; j < result_mat->cols; j++){
          result_mat -> start_ptr[i][j] = 0;
      }
  }

  // Multiply the matricies together
  for(int i = 0; i < m1->rows; i++){
      for(int k = 0; k < m2->cols; k++){
          for(int j = 0; j < m1->cols; j++){
              result_mat->start_ptr[i][k] = result_mat->start_ptr[i][k] + m1->start_ptr[i][j] * m2->start_ptr[j][k];
          }
      }
  }
  print_mat(result_mat);
}

int main(int argc, char** argv) {

    if(argc != 4){
      printf("Incorrect number of arguments given\n");
      return -1;
    }

    // start clock to work out execution time
    clock_t begin = clock();

    // get arguments
    int M, N;
    unsigned int seed;


    M = atoi(argv[1]);
    N = atoi(argv[2]);
    seed = atoi(argv[3]);

    // seed the random generator
    srand(seed);

    struct matrix* mat1 = generate_mat(M, N);
    struct matrix* mat2 = generate_mat(N, M);

    printf("MATRIX 1: \n");
    print_mat(mat1);

    printf("MATRIX 2: \n");
    print_mat(mat2);

    printf("RESULT:\n");
    mat_mult(mat1, mat2);

    // work out execution time
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("EXECUTION TIME: %f\n", time_spent);

    return 0;
}
