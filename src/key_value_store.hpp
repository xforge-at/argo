#import "util.hpp"
#import <leveldb/db.h>

class KeyValueStore {
  public:
    virtual ~KeyValueStore() {}

    KeyValueStore(const string &path) : path(path) {}

    optional<string> getString(const string &key);
    void putString(const string &key, const string &value);

    optional<int32_t> getInt(const string &key);
    void putInt(const string &key, const int32_t &value);

  private:
    const string &path;

    void closeDB(leveldb::DB *db);
    leveldb::DB *openDB();

    optional<string> get(const string &key);
    void put(const string &key, const string &value);
};