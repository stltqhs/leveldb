//
// Created by yuqing on 22-5-2.
//
#include <iostream>
#include <cassert>
#include "leveldb/db.h"

int main()
{
  leveldb::DB* db;
  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  assert(status.ok());
  std::string value;
  leveldb::Status s = db->Get(leveldb::ReadOptions(), "k001", &value);
  if (s.ok()) s = db->Put(leveldb::WriteOptions(), "k002", value);
  if (s.ok()) s = db->Delete(leveldb::WriteOptions(), "k001");

  delete db;
}