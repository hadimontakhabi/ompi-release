#include "db_hpx_db.h"


Node *current, *first, *secondcurrent, *secondfirst;

std::atomic<int> sum(0);

void one()
{
  sum++;
}
HPX_PLAIN_ACTION(one, one_action);


int getlen(Node* node)
{
  return (sizeof(int) + (node->value)->size());
}


int gettotallen(Node* firstnode)
{
  Node* cur = firstnode;
  int totallen = 0;
  while(cur != NULL){
    totallen += getlen(cur);
    cur = cur->next;
  }
  return totallen;
}


int vpid()
{
  return (int) hpx::get_locality_id();
}


int num_localities()
{
  return hpx::get_initial_num_localities();
}


int opal_db_hpx_cpp_put(char* key, int keysize, char* val, int valsize)
{
  //std::cout << "opal_db_hpx_cpp_put: valsize = " << valsize << ", strlen(val) = " << strlen(val) << std::endl;
  std::vector<char> vectorval (val, val + valsize);
  put( (std::string) key, keysize, vectorval, valsize );
  //std::cout << "opal_db_hpx_cpp_put: ((std::string)val).length() = " << ((std::string)val).length() << std::endl;
  return 0;
}


int put(std::string key, std::size_t keysize, std::vector<char> val, std::size_t valsize)
{
  Node *temp;
  temp = (Node*) malloc(sizeof(Node));
  
  temp->key = (char*) malloc (keysize*sizeof(key));
  memcpy(temp->key, key.c_str(), keysize);
  
  temp->value = new std::vector <char>(1,0);
  (temp->value)->swap(val);
  //std::cout << "put: temp->value.size() = " << temp->value->size() << std::endl;

  temp->next = NULL;
  temp->originator = hpx::get_locality_id();

  if (first == NULL){
    first = temp;
  }
  else{
    current = first;
    while (current->next != NULL){
      current = current->next;
    }
    current->next = temp;
  }
  return 0;
}

std::vector<char> get(std::string key)
{
  //std::cout << "key = " << key << std::endl;
  std::vector<char> empty;
  current = first;
  if (current == NULL){
	std::cout << "List is empty" << std::endl;
    return empty;
  }
  while (current != NULL){
    if (current->key == key){   //key found
      // std::cout << "key found" << std::endl;
      return *(current->value);
    }
    current = current->next;
  }
  std::cout << "key not found" << std::endl;
  return empty;
}
HPX_PLAIN_ACTION(get, get_action);



hpx::naming::id_type* list;

void local_map()
{
  std::vector<hpx::naming::id_type> localities =
    hpx::find_all_localities();
  
  list = new hpx::naming::id_type[localities.size()];

  int i = 0;
  BOOST_FOREACH(hpx::naming::id_type const& node, localities) {
    list[i] = node;
    //std::cout << "list[" << i << "] = "<< list[i] << std::endl;
    i++;
  }
  return;  
}


int opal_db_hpx_cpp_get( int vpid, char* key, char** value )
{
  hpx::naming::id_type const& node = list[vpid];
  std::string stringkey = (std::string) key;

  *value = NULL;
  //  const char *temp_value = hpx::async<get_action>(node, stringkey).get().c_str();
  std::vector<char> temp_vector = hpx::async<get_action>(node, stringkey).get();
  char *temp_value = (char *) malloc (temp_vector.size());
  memcpy(temp_value, temp_vector.data(), temp_vector.size());
    
  //std::cout << "temp_value: " << temp_value << " and len = " << temp_vector.size() << std::endl;
  if(strcmp(temp_value, "")) {
    *value = temp_value;
  }
  return (int) temp_vector.size();
}


void opal_db_hpx_barrier()
{
  std::vector<hpx::naming::id_type> localities =
    hpx::find_all_localities();
  
  std::vector<hpx::lcos::future<void> > futures;
  futures.reserve(localities.size());
 
  BOOST_FOREACH(hpx::naming::id_type const& node, localities) {
	futures.push_back(hpx::async<one_action>(node));
  }
  hpx::wait_all(futures);
  
  while(sum != (int) localities.size()) {
    /*
    std::cout << "Inside Barrier -  sum= " << sum 
	      << " ,number of localities = " << localities.size() << std::endl;
    */
  }
  sum = 0;
  return;
}
