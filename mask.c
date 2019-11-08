#include <stdio.h>
#include "mask.h"

// When completed this file will contain several versions of the
// mask() function and conditional compilation will be used to
// determine which version runs.  Each version will be named mask1,
// mask2, and so on. To select the version of the mask function to
// use, change the following declaration to the version of the mask()
// to be used.  All versions of mask() must produce a correct result.

// The provided Makefile also includes the possibility of creating an
// executable called "timemask-maskN" (replacing maskN with any
// version you'd like to test). You may compile it with "make
// timemask-maskN" then run "./timemask-maskN".

#ifndef MASK_VERSION
#define MASK_VERSION mask5
#endif

// You are only allowed to change the contents of this file with
// respect to improving the performance of this program. You may not
// change the data structure for each image or the parameters for the
// function mask. You may, however, change the structure of the code
// and the types/implementation of local variables (col, row, weight,
// etc.).


// You are required to document the changes you make in the README.txt
// file. For each entry in the README.txt file there is to be a
// version of the matching mask() function here such that the markers
// can see, and run if needed, the actual code that you used to
// produce your results for the logged change to the mask function.

static inline long mask0(long oldImage[N][N], long newImage[N][N], int rows, int cols) {
  return baseMask(oldImage, newImage, rows, cols);
}

// For each version of mask you are testing duplicate the function
// below, rename it to a different name, and make your changes. To use
// the new version, change the #define above to use the current version.

static inline long mask1(long oldImage[N][N], long newImage[N][N], int rows, int cols) {

  int i, j;
  int col, row;
  long check = 0;

  long (*weight)[N] = calloc(N * N, sizeof(long));

  //initialize the new image
  for (j = 0; j < rows; j++)
    for (i = 0; i < cols; i++) {
      newImage[j][i] = WEIGHT_CENTRE * oldImage[j][i];
      weight[j][i] = WEIGHT_CENTRE;
    }


  // Count the cells to the top left
  for (j = 1; j < rows; j++) {
    row = j - 1;
    for  (i = 1; i < cols; i++) {
      col = i - 1;
      newImage[j][i] += WEIGHT_CORNER * oldImage[row][col];
      weight[j][i] += WEIGHT_CORNER;
    }
  }

  // Count the cells immediately above
  for (j = 1; j < rows; j++) {
    row = j - 1;
    for (i = 0; i < cols; i++) {
      newImage[j][i] += WEIGHT_SIDE * oldImage[row][i];
      weight[j][i] += WEIGHT_SIDE;
    }
  }

  // Count the cells to the top right
  for (j = 1; j < rows; j++) {
    row = j - 1;
    for (i = 0; i < cols - 1; i++) {
      col = i + 1;
      newImage[j][i] += WEIGHT_CORNER * oldImage[row][col];
      weight[j][i] += WEIGHT_CORNER;
    }
  }

  // Count the cells to the immediate left
  for (j = 0; j < rows; j++) {
    for (i = 1; i < cols; i++) {
      col = i - 1;
      newImage[j][i] += WEIGHT_SIDE * oldImage[j][col];
      weight[j][i] += WEIGHT_SIDE;
    }
  }

  // Count the cells to the immediate right
  for  (j = 0; j < rows; j++){
    for (i = 0; i < cols - 1; i++) {
      col = i + 1;
      newImage[j][i] += WEIGHT_SIDE * oldImage[j][col];
      weight[j][i] += WEIGHT_SIDE;
    }
  }

  // Count the cells to the bottom left
  for (j = 0; j < rows - 1; j++) {
    row = j + 1;
    for (i = 1; i < cols; i++) {
      col = i - 1;
      newImage[j][i] += WEIGHT_CORNER * oldImage[row][col];
      weight[j][i] += WEIGHT_CORNER;
    }
  }

  // Count the cells immediately below
  for (j = 0; j < rows - 1; j++) {
    row = j + 1;
    for (i = 0; i < cols; i++) {
      newImage[j][i] += WEIGHT_SIDE * oldImage[row][i];
      weight[j][i] += WEIGHT_SIDE;
    }
  }

  // Count the cells to the bottom right
  for (j = 0; j < rows - 1; j++) {
    row = j + 1;
    for (i = 0; i < cols - 1; i++) {
      col = i + 1;
      newImage[j][i] += WEIGHT_CORNER * oldImage[row][col];
      weight[j][i] += WEIGHT_CORNER;
    }
  }

  // Produce the final result
  for (j = 0; j < rows; j++)
    for (i = 0; i < cols; i++) {
      newImage[j][i] = newImage[j][i] / weight[j][i];
      check += newImage[j][i];
    }

  return check;


}

static inline long mask2(long oldImage[N][N], long newImage[N][N], int rows, int cols) {


  int i, j;
  int col, row;
  long check = 0;

  long (*weight)[N] = calloc(N * N, sizeof(long));

  //initialize the new image
  for (j = 0; j < rows; j++)
    for (i = 0; i < cols; i++) {
      newImage[j][i] = WEIGHT_CENTRE * oldImage[j][i];
      weight[j][i] = WEIGHT_CENTRE;
    }


  // Count the cells to the top left
  for (j = 1; j < rows; j++) {
    row = j - 1;
    for  (i = 1; i < cols; i++) {
      col = i - 1;
      newImage[j][i] += WEIGHT_CORNER * oldImage[row][col];
      weight[j][i] += WEIGHT_CORNER;
    }
    for (i = 0; i < cols; i++) {
      newImage[j][i] += WEIGHT_SIDE * oldImage[row][i];
      weight[j][i] += WEIGHT_SIDE;
    }
    for (i = 0; i < cols - 1; i++) {
      col = i + 1;
      newImage[j][i] += WEIGHT_CORNER * oldImage[row][col];
      weight[j][i] += WEIGHT_CORNER;
    }
  }


  // Count the cells to the immediate left
  for (j = 0; j < rows; j++) {
    for (i = 1; i < cols; i++) {
      col = i - 1;
      newImage[j][i] += WEIGHT_SIDE * oldImage[j][col];
      weight[j][i] += WEIGHT_SIDE;
    }
    for (i = 0; i < cols - 1; i++) {
      col = i + 1;
      newImage[j][i] += WEIGHT_SIDE * oldImage[j][col];
      weight[j][i] += WEIGHT_SIDE;
    }
  }


  // Count the cells to the bottom left
  for (j = 0; j < rows - 1; j++) {
    row = j + 1;
    for (i = 1; i < cols; i++) {
      col = i - 1;
      newImage[j][i] += WEIGHT_CORNER * oldImage[row][col];
      weight[j][i] += WEIGHT_CORNER;
    }
    for (i = 0; i < cols; i++) {
      newImage[j][i] += WEIGHT_SIDE * oldImage[row][i];
      weight[j][i] += WEIGHT_SIDE;
    }
    for (i = 0; i < cols - 1; i++) {
      col = i + 1;
      newImage[j][i] += WEIGHT_CORNER * oldImage[row][col];
      weight[j][i] += WEIGHT_CORNER;
    }
  }

  // Produce the final result
  for (j = 0; j < rows; j++)
    for (i = 0; i < cols; i++) {
      newImage[j][i] = newImage[j][i] / weight[j][i];
      check += newImage[j][i];
    }

  return check;

}

static inline long mask3(long oldImage[N][N], long newImage[N][N], int rows, int cols) {


  int i, j;
  long check = 0;

  long (*weight)[N] = calloc(N * N, sizeof(long));

  //initialize the new image
  for (j = 0; j < rows; j++)
    for (i = 0; i < cols; i++) {
      newImage[j][i] = WEIGHT_CENTRE * oldImage[j][i];
      weight[j][i] = WEIGHT_CENTRE;
    }


  for (j = 1; j < rows; j++) {
    newImage[j][0] += WEIGHT_SIDE * oldImage[j-1][0];
    weight[j][0] += WEIGHT_SIDE;
    newImage[j][0] += WEIGHT_CORNER * oldImage[j-1][1];
    weight[j][0] += WEIGHT_CORNER;
    for  (i = 1; i < cols - 1; i++) {
      newImage[j][i] += WEIGHT_CORNER * oldImage[j-1][i-1];
      weight[j][i] += WEIGHT_CORNER;
      newImage[j][i] += WEIGHT_SIDE * oldImage[j-1][i];
      weight[j][i] += WEIGHT_SIDE;
      newImage[j][i] += WEIGHT_CORNER * oldImage[j-1][i+1];
      weight[j][i] += WEIGHT_CORNER;
    }
    newImage[j][cols-1] += WEIGHT_CORNER * oldImage[j-1][cols-2];
    weight[j][cols-1] += WEIGHT_CORNER;
    newImage[j][cols-1] += WEIGHT_SIDE * oldImage[j-1][cols-1];
    weight[j][cols-1] += WEIGHT_SIDE;

  }


  for (j = 0; j < rows; j++) {
    newImage[j][0] += WEIGHT_SIDE * oldImage[j][1];
    weight[j][0] += WEIGHT_SIDE;
    for (i = 1; i < cols -1; i++) {
      newImage[j][i] += WEIGHT_SIDE * oldImage[j][i-1];
      weight[j][i] += WEIGHT_SIDE;
      newImage[j][i] += WEIGHT_SIDE * oldImage[j][i+1];
      weight[j][i] += WEIGHT_SIDE;
    }
    newImage[j][cols-1] += WEIGHT_SIDE * oldImage[j][cols-2];
    weight[j][cols-1] += WEIGHT_SIDE;
  }


  // Count the cells to the bottom left
  for (j = 0; j < rows - 1; j++) {
    newImage[j][0] += WEIGHT_SIDE * oldImage[j+1][0];
    weight[j][0] += WEIGHT_SIDE;
    newImage[j][0] += WEIGHT_CORNER * oldImage[j+1][1];
    weight[j][0] += WEIGHT_CORNER;
    for (i = 1; i < cols-1; i++) {
      newImage[j][i] += WEIGHT_CORNER * oldImage[j+1][i-1];
      weight[j][i] += WEIGHT_CORNER;
      newImage[j][i] += WEIGHT_SIDE * oldImage[j+1][i];
      weight[j][i] += WEIGHT_SIDE;
      newImage[j][i] += WEIGHT_CORNER * oldImage[j+1][i+1];
      weight[j][i] += WEIGHT_CORNER;
    }
    newImage[j][cols-1] += WEIGHT_CORNER * oldImage[j+1][cols-2];
    weight[j][cols-1] += WEIGHT_CORNER;
    newImage[j][cols-1] += WEIGHT_SIDE * oldImage[j+1][cols-1];
    weight[j][cols-1] += WEIGHT_SIDE;
  }

  // Produce the final result
  for (j = 0; j < rows; j++)
    for (i = 0; i < cols; i++) {
      newImage[j][i] = newImage[j][i] / weight[j][i];
      check += newImage[j][i];
    }

  return check;

}

static inline long mask4(long oldImage[N][N], long newImage[N][N], int rows, int cols) {


  int i, j;
  long check = 0;

  long (*weight)[N] = calloc(N * N, sizeof(long));


    for (j = 0; j < rows; j++)
        for (i = 0; i < cols; i++) {
            newImage[j][i] = WEIGHT_CENTRE * oldImage[j][i];
            weight[j][i] = WEIGHT_CENTRE;
        }




  newImage[0][0] += WEIGHT_SIDE * (oldImage[0][1] + oldImage[1][0])
                    + WEIGHT_CORNER * oldImage[1][1];
  weight[0][0] += WEIGHT_SIDE*2 + WEIGHT_CORNER;


  for (i = 1; i < cols-1; i++) {
    newImage[0][i] += WEIGHT_SIDE * (oldImage[0][i-1] + oldImage[0][i+1] + oldImage[1][i])
                        + WEIGHT_CORNER * (oldImage[1][i-1] + oldImage[1][i+1]) ;
    weight[0][i] += WEIGHT_SIDE*3 + WEIGHT_CORNER*2;

    newImage[rows-1][i] += WEIGHT_CORNER * (oldImage[rows-2][i-1] + oldImage[rows-2][i+1])
                             + WEIGHT_SIDE * (oldImage[rows-2][i] + oldImage[rows-1][i-1]
                               + oldImage[rows-1][i+1]);
    weight[rows-1][i] += WEIGHT_CORNER *2 + WEIGHT_SIDE*3;

  }


  newImage[0][cols-1] += WEIGHT_SIDE * (oldImage[0][cols-2] + oldImage[1][cols-1])
                        + WEIGHT_CORNER * oldImage[1][cols-2];
  weight[0][cols-1] += WEIGHT_SIDE *2 + WEIGHT_CORNER;


  newImage[rows-1][0] += WEIGHT_SIDE * (oldImage[rows-2][0] +  oldImage[rows-1][1])
                            + WEIGHT_CORNER * oldImage[rows-2][1];
  weight[rows-1][0] += WEIGHT_SIDE*2 + WEIGHT_CORNER;



  newImage[rows-1][cols-1] += WEIGHT_CORNER * oldImage[rows-2][cols-2]
                                + WEIGHT_SIDE * (oldImage[rows-2][cols-1]
                                + oldImage[rows-1][cols-2]);
  weight[rows-1][cols-1] += WEIGHT_CORNER + WEIGHT_SIDE*2;




  for (j = 1; j < rows - 1; j++) {
    newImage[j][0] += WEIGHT_SIDE * (oldImage[j-1][0] + oldImage[j][1] +oldImage[j+1][0])
                        + WEIGHT_CORNER * (oldImage[j-1][1] +  oldImage[j+1][1]);
    weight[j][0] += WEIGHT_SIDE *3 + WEIGHT_CORNER*2;


    for  (i = 1; i < cols - 1; i++) {
      newImage[j][i] += WEIGHT_CORNER * (oldImage[j-1][i-1] + oldImage[j-1][i+1]
                                        + oldImage[j+1][i-1] + oldImage[j+1][i+1])
                        + WEIGHT_SIDE * (oldImage[j-1][i] + oldImage[j][i-1]
                                        + oldImage[j][i+1] + oldImage[j+1][i]);
      weight[j][i] += WEIGHT_CORNER *4 +WEIGHT_SIDE *4 ;
    }

    newImage[j][cols-1] += WEIGHT_CORNER * (oldImage[j-1][cols-2] +oldImage[j+1][cols-2])
                      +WEIGHT_SIDE * (oldImage[j-1][cols-1] + oldImage[j][cols-2]
                                        + oldImage[j+1][cols-1]);
    weight[j][cols-1] += WEIGHT_CORNER*2 + WEIGHT_SIDE*3;


  }



  // Produce the final result
  for (j = 0; j < rows; j++)
    for (i = 0; i < cols; i++) {
      newImage[j][i] = newImage[j][i] / weight[j][i];
      check += newImage[j][i];
    }

  return check;

}


static inline long mask5(long oldImage[N][N], long newImage[N][N], int rows, int cols) {


    int i, j;
    long check = 0;


    newImage[0][0] = (WEIGHT_CENTRE * oldImage[0][0] +
                    WEIGHT_SIDE * (oldImage[0][1] + oldImage[1][0])
                    + WEIGHT_CORNER * oldImage[1][1]) /
            (WEIGHT_CENTRE +  WEIGHT_SIDE*2 + WEIGHT_CORNER);
    check += newImage[0][0];




    for (i = 1; i < cols-1; i++) {
        newImage[0][i] = (WEIGHT_CENTRE * oldImage[0][i]
                        + WEIGHT_SIDE * (oldImage[0][i-1] + oldImage[0][i+1] + oldImage[1][i])
                          + WEIGHT_CORNER * (oldImage[1][i-1] + oldImage[1][i+1])) /
                (WEIGHT_CENTRE + WEIGHT_SIDE*3 + WEIGHT_CORNER*2);
        check += newImage[0][i];
        newImage[rows-1][i] = (WEIGHT_CENTRE * oldImage[rows-1][i]
                         + WEIGHT_CORNER * (oldImage[rows-2][i-1] + oldImage[rows-2][i+1])
                         + WEIGHT_SIDE * (oldImage[rows-2][i] + oldImage[rows-1][i-1]
                                   + oldImage[rows-1][i+1])) /
                (WEIGHT_CENTRE + WEIGHT_CORNER *2 + WEIGHT_SIDE*3);
        check += newImage[rows-1][i];

    }

    newImage[0][cols-1] = (WEIGHT_CENTRE * oldImage[0][cols-1]
                            + WEIGHT_SIDE * (oldImage[0][cols-2] + oldImage[1][cols-1])
                              + WEIGHT_CORNER * oldImage[1][cols-2]) /
            (WEIGHT_CENTRE + WEIGHT_SIDE *2 + WEIGHT_CORNER);
    check += newImage[0][cols-1];



    newImage[rows-1][0] = (WEIGHT_CENTRE * oldImage[rows-1][0]
                        + WEIGHT_SIDE * (oldImage[rows-2][0] +  oldImage[rows-1][1])
                          + WEIGHT_CORNER * oldImage[rows-2][1]) /
            (WEIGHT_CENTRE + WEIGHT_SIDE*2 + WEIGHT_CORNER);
    check += newImage[rows-1][0];


    newImage[rows-1][cols-1] = (WEIGHT_CENTRE * oldImage[rows-1][cols-1]
                            + WEIGHT_CORNER * oldImage[rows-2][cols-2]
                              + WEIGHT_SIDE * (oldImage[rows-2][cols-1]
                                               + oldImage[rows-1][cols-2])) /
            (WEIGHT_CENTRE + WEIGHT_CORNER + WEIGHT_SIDE*2);
    check += newImage[rows-1][cols-1];




    for (j = 1; j < rows - 1; j++) {


        newImage[j][0] = (WEIGHT_CENTRE * oldImage[j][0]
                        + WEIGHT_SIDE * (oldImage[j-1][0] + oldImage[j][1] +oldImage[j+1][0])
                          + WEIGHT_CORNER * (oldImage[j-1][1] +  oldImage[j+1][1])) /
                (WEIGHT_CENTRE + WEIGHT_SIDE *3 + WEIGHT_CORNER*2);
        check += newImage[j][0];



        for  (i = 1; i < cols - 1; i++) {

            newImage[j][i] = (WEIGHT_CENTRE * oldImage[j][i] +
                            WEIGHT_CORNER * (oldImage[j-1][i-1] + oldImage[j-1][i+1]
                                               + oldImage[j+1][i-1] + oldImage[j+1][i+1])
                              + WEIGHT_SIDE * (oldImage[j-1][i] + oldImage[j][i-1]
                                               + oldImage[j][i+1] + oldImage[j+1][i])) /
                    (WEIGHT_CENTRE + WEIGHT_CORNER *4 +WEIGHT_SIDE *4);
            check += newImage[j][i];

        }


        newImage[j][cols-1] = (WEIGHT_CENTRE * oldImage[j][cols-1] +
                        WEIGHT_CORNER * (oldImage[j-1][cols-2] +oldImage[j+1][cols-2])
                               +WEIGHT_SIDE * (oldImage[j-1][cols-1] + oldImage[j][cols-2]
                                               + oldImage[j+1][cols-1])) /
                                                       (WEIGHT_CENTRE + WEIGHT_CORNER*2 + WEIGHT_SIDE*3);
        check += newImage[j][cols-1];


    }



    return check;

}

long mask(long oldImage[N][N], long newImage[N][N], int rows, int cols) {
  return MASK_VERSION(oldImage, newImage, rows, cols);
}

