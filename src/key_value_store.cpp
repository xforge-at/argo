#import "key_value_store.hpp"
#import <cassert>

// String

optional<string> KeyValueStore::getString(const string &key) {
    optional<string> stringValue = get(key);
    return stringValue;
}

void KeyValueStore::putString(const string &key, const string &value) {
    put(key, value);
}

// Int

optional<int32_t> KeyValueStore::getInt(const string &key) {
    optional<string> stringValue = get(key);
    if (!stringValue) return nullopt;

    optional<int32_t> intValue = nullopt;
    try {
        intValue = std::stoi(*stringValue);
    } catch (...) {
    }
    return intValue;
}

void KeyValueStore::putInt(const string &key, const int32_t &value) {
    put(key, std::to_string(value));
}

// Double

optional<double> KeyValueStore::getDouble(const string &key) {
    optional<string> stringValue = get(key);
    if (!stringValue) return nullopt;

    optional<double> doubleValue = nullopt;
    try {
        doubleValue = std::stod(*stringValue);
    } catch (...) {
    }
    return doubleValue;
}

void KeyValueStore::putDouble(const string &key, const double &value) {
    put(key, std::to_string(value));
}

// Float

optional<float> KeyValueStore::getFloat(const string &key) {
    optional<string> stringValue = get(key);
    if (!stringValue) return nullopt;

    optional<float> floatValue = nullopt;
    try {
        floatValue = std::stof(*stringValue);
    } catch (...) {
    }
    return floatValue;
}

void KeyValueStore::putFloat(const string &key, const float &value) {
    put(key, std::to_string(value));
}

// Json

optional<Json> KeyValueStore::getJson(const string &key) {
    optional<string> stringValue = get(key);
    if (!stringValue) return nullopt;

    optional<Json> jsonValue = nullopt;

    string err;
    jsonValue = Json::parse(*stringValue, err);
    if (!err.empty()) {
        return nullopt;
    }

    return jsonValue;
}

void KeyValueStore::putJson(const string &key, const Json &value) {
    put(key, value.dump());
}

// DB

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

// Helper

optional<string> KeyValueStore::get(const string &key) {
    leveldb::DB *db = openDB();
    string value;
    leveldb::Status status = db->Get(leveldb::ReadOptions(), key, &value);
    closeDB(db);

    if (status.ok()) {
        return make_optional(value);
    } else {
        return nullopt;
    }
}

void KeyValueStore::put(const string &key, const string &value) {
    leveldb::DB *db = openDB();
    db->Put(leveldb::WriteOptions(), key, value);
    closeDB(db);
}
