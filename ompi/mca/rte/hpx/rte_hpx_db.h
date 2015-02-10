#ifndef MCA_OMPI_RTE_HPX_DB_H
#define MCA_OMPI_RTE_HPX_DB_H

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

void rte_hpx_one(void);
int rte_hpx_vpid(void);
int rte_hpx_num_localities(void);
int rte_hpx_cpp_put(char* key, int keysize, char* val, int valsize);
int rte_hpx_put(std::string key, std::size_t keysize, std::vector<char> val, std::size_t valsize);
void rte_hpx_local_map(void);
int rte_hpx_cpp_get(int vpid, char* key, char** value);
std::vector<char> rte_hpx_get(std::string key);
void rte_hpx_barrier(void);
int rte_hpx_cpp_get_vpid_from_locality ( hpx::naming::id_type locality);
hpx::naming::id_type  rte_hpx_cpp_get_locality_from_vpid ( int vpid );
int rte_hpx_cpp_printf(char* out);
}
#endif


#endif
/* MCA_OMPI_RTE_HPX_DB_H */
