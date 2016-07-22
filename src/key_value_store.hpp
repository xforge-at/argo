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

    optional<double> getDouble(const string &key);
    void putDouble(const string &key, const double &value);

    optional<float> getFloat(const string &key);
    void putFloat(const string &key, const float &value);

    optional<Json> getJson(const string &key);
    void putJson(const string &key, const Json &value);

  private:
    const string &path;

    void closeDB(leveldb::DB *db);
    leveldb::DB *openDB();

    optional<string> get(const string &key);
    void put(const string &key, const string &value);
};