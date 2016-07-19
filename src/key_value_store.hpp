#import "generated/key_value_store_setup.hpp"
#import "util.hpp"
#import <leveldb/db.h>

class KeyValueStore : public Argo::KeyValueStoreSetup {
  public:
    virtual ~KeyValueStore() {}

    static void setup(const std::string &path);

    static string get(string &key);
    static void put(string &key, string &value);

  private:
    static shared_ptr<KeyValueStore> instance;

    string path;
    KeyValueStore(string &path);

    void closeDB(leveldb::DB *db);
    leveldb::DB *openDB();
};