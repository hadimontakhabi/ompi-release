/*
 * Copyright (c) 2012-2013 Los Alamos National Security, LLC.
 *                         All rights reserved.
 * Copyright (c) 2013-2014 Intel, Inc. All rights reserved
 *
 * Copyright (c) 2014 Cisco Systems, Inc.  All rights reserved.
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 *
 * When this component is used, this file is included in the rest of
 * the OPAL/ORTE/OMPI code base via ompi/mca/rte/rte.h.  As such,
 * this header represents the public interface to this static component.
 */

#ifndef MCA_OMPI_RTE_HPX_H
#define MCA_OMPI_RTE_HPX_H

#include "ompi/constants.h"
#include "opal/threads/condition.h"

struct ompi_proc_t;

BEGIN_C_DECLS

/* Process name objects and operations */

typedef uint32_t ompi_jobid_t;
typedef uint32_t ompi_vpid_t;
struct ompi_process_name_t {
    ompi_jobid_t jobid;
    ompi_vpid_t vpid;
};
typedef struct ompi_process_name_t ompi_process_name_t;
typedef int ompi_rte_cmp_bitmask_t;
OMPI_DECLSPEC char* rte_hpx_print_process_name(const ompi_process_name_t *name);
#define OMPI_NAME_PRINT(a) rte_hpx_print_process_name(a)
#define OMPI_PROC_MY_NAME (&ompi_process_info.my_name)
OMPI_DECLSPEC int ompi_rte_compare_name_fields(ompi_rte_cmp_bitmask_t fields,
                                               const ompi_process_name_t *name1,
                                               const ompi_process_name_t *name2);
OMPI_DECLSPEC extern ompi_process_name_t ompi_rte_wildcard_process_name;
#define OMPI_NAME_WILDCARD (&ompi_rte_wildcard_process_name)
OMPI_DECLSPEC uint64_t ompi_rte_hash_name(const ompi_process_name_t *name);
#define OMPI_NAME (OPAL_DSS_ID_DYNAMIC + 2)

#define OMPI_LOCAL_RANK_INVALID UINT16_MAX
#define OMPI_RTE_CMP_JOBID 0x02
#define OMPI_RTE_CMP_VPID 0x04
#define OMPI_RTE_CMP_ALL 0x0f
#define OMPI_PROCESS_NAME_HTON(n)	    \
  do {					    \
    n.jobid = htonl(n.jobid);		    \
    n.vpid = htonl(n.vpid);		    \
  } while (0)
#define OMPI_PROCESS_NAME_NTOH(n)					\
  do {									\
    n.jobid = ntohl(n.jobid);						\
    n.vpid = ntohl(n.vpid);						\
  } while (0)

#define OMPI_RTE_NODE_ID  "rte.daemon.vpid"
#define OMPI_RTE_MY_NODEID (&ompi_process_info.my_name)->vpid

/* Collective objects and operations */
typedef struct {
  opal_list_item_t super;
  int32_t id;
  bool active;
} ompi_rte_collective_t;
OMPI_DECLSPEC OBJ_CLASS_DECLARATION(ompi_rte_collective_t);
OMPI_DECLSPEC int ompi_rte_modex(ompi_rte_collective_t *coll);
OMPI_DECLSPEC int ompi_rte_barrier(ompi_rte_collective_t *coll);

/* Process info struct and values */

typedef int ompi_node_rank_t;
typedef int ompi_local_rank_t;
struct ompi_process_info_t {
    ompi_process_name_t my_name; //this is not in the requirements  
    char *my_hnp_uri;              
    uint32_t app_num;        
    uint32_t num_procs;         
    char *nodename;                
    pid_t pid;                     
    int my_node_rank;              
    int my_local_rank;             
    int32_t num_local_peers;       
    char *job_session_dir;         
    char *proc_session_dir;        
    char *cpuset;                  
    int32_t peer_modex;  
    int32_t peer_init_barrier; 
    int32_t peer_fini_barrier; 
};
typedef struct ompi_process_info_t ompi_process_info_t;
OMPI_DECLSPEC extern ompi_process_info_t ompi_process_info;
OMPI_DECLSPEC extern bool ompi_rte_proc_is_bound;

/* Error handling objects and operations */

OMPI_DECLSPEC void ompi_rte_abort(int err_code, char *fmt, ...);
OMPI_DECLSPEC int ompi_rte_abort_peers(ompi_process_name_t *procs, size_t nprocs, int status);
OMPI_DECLSPEC int ompi_rte_error_log(const char *file, int line, const char *func, int ret);
#define OMPI_ERROR_LOG(ret) ompi_rte_error_log(__FILE__, __LINE__, __func__, ret)
typedef enum {
  OMPI_RTE_ERRHANDLER_LAST
} ompi_errmgr_error_order_t;
int ompi_rte_register_errhandler(int *cbfunc, ompi_errmgr_error_order_t order);
struct ompi_rte_error_report_t {
  int errcode;
};
typedef struct ompi_rte_error_report_t ompi_rte_error_report_t;

/* Init and finalize objects and operations */

int ompi_rte_init(int* pargc, char*** pargv);
int ompi_rte_finalize(void);
OMPI_DECLSPEC void ompi_rte_wait_for_debugger(void);

/* Database operations */

OMPI_DECLSPEC int ompi_rte_db_store(const ompi_process_name_t *nm, const char* key,
                                    const void *data, opal_data_type_t type);
OMPI_DECLSPEC int ompi_rte_db_fetch(const struct ompi_proc_t *proc,
                                    const char *key,
                                    void **data, opal_data_type_t type);
OMPI_DECLSPEC int ompi_rte_db_fetch_pointer(const struct ompi_proc_t *proc,
                                            const char *key,
                                            void **data, opal_data_type_t type);
OMPI_DECLSPEC int ompi_rte_db_fetch_multiple(const struct ompi_proc_t *proc,
                                             const char *key,
                                             opal_list_t *kvs);
#define OMPI_DB_HOSTNAME "rte.hostname"
#define OMPI_DB_LOCALITY "rte.locality"

/* Communications */

typedef uint32_t ompi_rml_tag_t;
typedef void (*ompi_rml_buffer_callback_fn_t)(int status,
                                              ompi_process_name_t* peer,
                                              struct opal_buffer_t* buffer,
                                              ompi_rml_tag_t tag,
                                              void* cbdata);
int ompi_rte_send_buffer_nb(ompi_process_name_t* peer,
							opal_buffer_t* buffer, 
							ompi_rml_tag_t tag, 
							ompi_rml_buffer_callback_fn_t cbfunc, 
							void* cbdata);
void ompi_rte_recv_buffer_nb(ompi_process_name_t* peer, 
							 ompi_rml_tag_t tag,
							 bool persistent, 
							 ompi_rml_buffer_callback_fn_t cbfunc, 
							 void* cbdata);
//void ompi_rte_recv_cancel(ompi_process_name_t* peer, ompi_rml_tag_t tag);
//int ompi_rte_parse_uris(const char* uri, ompi_process_name_t* peer, char*** uris);
void ompi_rte_send_cbfunc(int status, ompi_process_name_t *peer, 
						  opal_buffer_t* buffer, ompi_rml_tag_t tag,  
						  void* cbdata); 

/* Communication tags */

#define OMPI_RML_TAG_INVALID 0
#define OMPI_RML_TAG_BASE    100
#define OMPI_RML_NON_PERSISTENT  false

typedef struct {
    ompi_rte_component_t super;
    bool direct_modex;
    opal_mutex_t lock;
    opal_list_t modx_reqs;
} ompi_rte_hpx_component_t;

typedef struct {
    opal_list_item_t super;
    opal_mutex_t lock;
    opal_condition_t cond;
    bool active;
    ompi_process_name_t peer;
} ompi_hpx_tracker_t;
OBJ_CLASS_DECLARATION(ompi_hpx_tracker_t);


unsigned int PACX_crc32(unsigned int c, const unsigned char * buf, 
						unsigned int len);
  

END_C_DECLS

#endif
/* MCA_OMPI_RTE_HPX_H */
