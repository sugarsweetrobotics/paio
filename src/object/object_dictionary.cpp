#include <paio/object/object_dictionary.h>



using namespace paio;

paio::ObjectDictionary_ptr paio::object_dictionary() {
  return paio::ObjectDictionary_ptr(new paio::ObjectDictionary());
}
