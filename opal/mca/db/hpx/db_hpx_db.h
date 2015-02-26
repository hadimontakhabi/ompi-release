#ifndef MCA_OMPI_RTE_HPX_DB_H
#define MCA_OMPI_DB_HPX_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#if defined(__cplusplus)

#include <hpx/hpx_main.hpp>
#include <hpx/hpx_finalize.hpp>
#include <hpx/include/lcos.hpp>
#include <hpx/include/actions.hpp>
#include <hpx/include/iostreams.hpp>

#include <vector>
#include <list>
#include <set>
#include <string>
#include <iostream>
#include <atomic>

#include <boost/ref.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>

#endif


#if defined(__cplusplus)
extern "C" {

struct Node{
  struct Node *next;
  char* key;
  std::vector<char> *value;
  int originator;
};
typedef struct Node Node;

void one(void);
int getlen(Node* node);
int gettotallen(Node* firstnode);
int vpid(void);
int num_localities(void);
int opal_db_hpx_cpp_put(char* key, int keysize, char* val, int valsize);
int put(std::string key, std::size_t keysize, std::vector<char> val, std::size_t valsize);
void local_map(void);
int opal_db_hpx_cpp_get(int vpid, char* key, char** value);
std::vector<char> get(std::string key);
void opal_hpx_db_barrier(void);

}
#endif


#endif
/* MCA_OMPI_DB_HPX_DB_H */
