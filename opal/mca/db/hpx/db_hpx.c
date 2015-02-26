/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2012-2013 Los Alamos National Security, LLC.  All rights
 *                         reserved. 
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 *
 */

#include "opal_config.h"
#include "opal/constants.h"


#include "opal_stdint.h"
#include "opal/class/opal_pointer_array.h"
#include "opal/dss/dss_types.h"
#include "opal/util/argv.h"
#include "opal/util/error.h"
#include "opal/util/output.h"
#include "opal/util/show_help.h"

#include "opal/mca/db/base/base.h"

#include "db_hpx_db.h"


static int init(void);
static void finalize(void);
static int store(const opal_identifier_t *id,
                 opal_scope_t scope,
                 const char *key, const void *object,
                 opal_data_type_t type);
static int store_pointer(const opal_identifier_t *proc,
                         opal_value_t *kv);
static int fetch(const opal_identifier_t *proc,
                 const char *key, void **data, opal_data_type_t type);
static int fetch_pointer(const opal_identifier_t *proc,
                         const char *key,
                         void **data, opal_data_type_t type);
static int fetch_multiple(const opal_identifier_t *proc,
                          opal_scope_t scope,
                          const char *key,
                          opal_list_t *kvs);
static int remove_data(const opal_identifier_t *proc, const char *key);

opal_db_base_module_t opal_db_hpx_module = {
    init,
    finalize,
    opal_db_base_set_id,
    store,
    store_pointer,
    NULL,
    fetch,
    fetch_pointer,
    fetch_multiple,
    remove_data,
    NULL
};


static int init(void)
{
    return OPAL_SUCCESS;
}

static void finalize(void)
{
    return;
}


static int store(const opal_identifier_t *uid,
                 opal_scope_t scope,
                 const char *key, const void *data, 
                 opal_data_type_t type)
{
    printf("opal/db/hpx --> store\n");

    opal_identifier_t id;

    /* to protect alignment, copy the data across */
    memcpy(&id, uid, sizeof(opal_identifier_t));

    return OPAL_SUCCESS; //opal_db_hpx_cpp_put(key, strlen(key)+1, data, strlen(data)+1);

}


static int store_pointer(const opal_identifier_t *uid,
                         opal_value_t *kv)
{
    opal_identifier_t proc;

    /* to protect alignment, copy the data across */
    memcpy(&proc, uid, sizeof(opal_identifier_t));

    return OPAL_SUCCESS;
}

static int fetch(const opal_identifier_t *uid,
                 const char *key, void **data,
                 opal_data_type_t type)
{
    opal_identifier_t proc;

    /* to protect alignment, copy the data across */
    memcpy(&proc, uid, sizeof(opal_identifier_t));

    return OPAL_SUCCESS;
}

static int fetch_pointer(const opal_identifier_t *uid,
                         const char *key,
                         void **data, opal_data_type_t type)
{
    opal_identifier_t proc;

    /* to protect alignment, copy the data across */
    memcpy(&proc, uid, sizeof(opal_identifier_t));
    
    return OPAL_SUCCESS;
}

static int fetch_multiple(const opal_identifier_t *uid,
                          opal_scope_t scope,
                          const char *key,
                          opal_list_t *kvs)
{
    opal_identifier_t proc;

    /* to protect alignment, copy the data across */
    memcpy(&proc, uid, sizeof(opal_identifier_t));

    return OPAL_SUCCESS;
}

static int remove_data(const opal_identifier_t *proc, const char *key)
{
    /* nothing to do here */
    return OPAL_SUCCESS;
}
