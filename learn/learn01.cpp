//
// Created by yuqing on 22-5-2.
//
#include <iostream>
#include <cassert>
#include "leveldb/db.h"

#define MAX_SIZE 5000000

void init_db(leveldb::DB* db);

int main()
{
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  assert(status.ok());
  std::string value;

//  init_db(db);

  char key_buf[20];
  float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  int key_num = static_cast<int> (r * MAX_SIZE);
  snprintf(key_buf, 20, "key_%07d", key_num);

  leveldb::Status s = db->Get(leveldb::ReadOptions(), key_buf, &value);

  delete db;
}

void init_db(leveldb::DB* db)
{
  int i;
  int max = MAX_SIZE;
  char key_buf[20];
  char value_buf[20];

  for (i = 0; i < max; i++) {
    snprintf(key_buf, 20, "key_%07d", i);
    snprintf(value_buf, 20, "value_%07d", i);
    leveldb::Slice key(key_buf);
    leveldb::Slice value(value_buf);

    db->Put(leveldb::WriteOptions(), key, value);
  }
}