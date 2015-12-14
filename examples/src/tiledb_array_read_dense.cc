/*
 * File: tiledb_array_read_dense.cc
 * 
 * Reading from a dense array. Follows the example of
 * <b>tiledb_array_write_dense.cc</b> 
 */

#include "tiledb.h"
#include <iostream>

int main() {
  /* Intialize context. */
  TileDB_CTX* tiledb_ctx;
  tiledb_ctx_init(&tiledb_ctx);

  /* Open the array in read mode. */
  int ad = tiledb_array_open(
               tiledb_ctx, 
               "my_workspace/B", 
               TILEDB_ARRAY_MODE_READ);

  /* 
   * Prepare to read cells in range [1,2], [2,4]. This will return 6 cells, each
   * having a single, <b>float</b> attribute value.
   */
  double range[4] = {1, 2, 2, 4};
  float buffer[6];  
  int buffer_size = 6*sizeof(float);
  const char** attributes = NULL;
  int attribute_num = 0;

  /* Read cells. */
  tiledb_array_read_dense(
      tiledb_ctx,
      ad,
      range,
      attributes,
      attribute_num,
      buffer,
      &buffer_size);

  /* 
   * Print the a1 value of the cells in [1,2], [2,4]  to stdout. 
   * The order of the coordinates is:
   * (1,2), (2,2), (1,3), (1,4), (2,3), (2,4). 
   */
  for(int i=0; i<6; ++i)
    std::cout << buffer[i] << "\n";

  /* Close the array. */
  tiledb_array_close(tiledb_ctx, ad);

  /* Finalize context. */
  tiledb_ctx_finalize(tiledb_ctx);

  return 0;
}
