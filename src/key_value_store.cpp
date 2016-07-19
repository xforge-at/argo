#import "key_value_store.hpp"
#import <cassert>

// Setup from iOS/Android with file path for db
void KeyValueStore::setup(const std::string &path) {
    instance = make_shared<KeyValueStore>(path);
}

KeyValueStore::KeyValueStore(string &path) : path(path) {}

leveldb::DB *KeyValueStore::openDB() {
    assert(!path.empty());
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::DB::Open(options, path, &db);
    return db;
}
void KeyValueStore::closeDB(leveldb::DB *db) {
    delete db;
}

string KeyValueStore::get(string &key) {
    leveldb::DB *db = instance->openDB();
    string value;
    db->Get(leveldb::ReadOptions(), key, &value);
    instance->closeDB(db);
    return value;
}

void KeyValueStore::put(string &key, string &value) {
    leveldb::DB *db = instance->openDB();
    db->Put(leveldb::WriteOptions(), key, value);
    instance->closeDB(db);
}