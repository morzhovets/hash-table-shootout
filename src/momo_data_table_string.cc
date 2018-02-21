#include <inttypes.h>
#include <string>
#include "momo/DataTable.h"

MOMO_DATA_COLUMN_STRING(int64_t, cIntKey);
MOMO_DATA_COLUMN_STRING(std::string, cStrKey);
MOMO_DATA_COLUMN_STRING(int64_t, cValue);

typedef momo::experimental::DataColumnList<momo::experimental::DataColumnTraits<>,
  momo::experimental::DataSettings<false>> DataColumns;
typedef momo::experimental::DataTable<DataColumns> DataTable;

#define SETUP DataTable table(DataColumns(cIntKey, cValue)); auto ind = table.AddUniqueHashIndex(cIntKey); \
  DataTable str_table(DataColumns(cStrKey, cValue)); auto str_ind = str_table.AddUniqueHashIndex(cStrKey);

#define INSERT_INT(key, value) table.AddRow(cIntKey = key, cValue = value)
//#define DELETE_INT(key)
#define FIND_INT_EXISTING(key) if (table.FindByUniqueHash(ind, cIntKey == key).GetCount() != 1) { printf("error"); exit(1); }
#define FIND_INT_MISSING(key) if (table.FindByUniqueHash(ind, cIntKey == key).GetCount() != 0) { printf("error"); exit(2); }
#define CHECK_INT_VALUES(value) for (auto rowRef : table) if (rowRef[cValue] != value) { printf("error"); exit(3); }

#define INSERT_STR(key, value) str_table.AddRow(cStrKey = key, cValue = value)
//#define DELETE_STR(key)
#define FIND_STR_EXISTING(key) if (str_table.FindByUniqueHash(str_ind, cStrKey == key).GetCount() != 1) { printf("error"); exit(4); }
#define FIND_STR_MISSING(key) if (str_table.FindByUniqueHash(str_ind, cStrKey == key).GetCount() != 0) { printf("error"); exit(5); }

#include "template.c"

