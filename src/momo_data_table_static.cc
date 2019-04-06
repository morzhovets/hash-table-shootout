#include <inttypes.h>
#include <string>
#include "momo/DataTable.h"

struct StructInt
{
  int64_t cIntKey;
  int64_t cIValue;
};

MOMO_DATA_COLUMN_STRUCT(StructInt, cIntKey);
MOMO_DATA_COLUMN_STRUCT(StructInt, cIValue);

typedef momo::DataColumnListStatic<StructInt> DataColumnsInt;
typedef momo::DataTable<DataColumnsInt> DataTableInt;

struct StructStr
{
  std::string cStrKey;
  int64_t cSValue;
};

MOMO_DATA_COLUMN_STRUCT(StructStr, cStrKey);
MOMO_DATA_COLUMN_STRUCT(StructStr, cSValue);

typedef momo::DataColumnListStatic<StructStr> DataColumnsStr;
typedef momo::DataTable<DataColumnsStr> DataTableStr;

#define SETUP DataTableInt table; auto ind = table.AddUniqueHashIndex(cIntKey); \
  DataTableStr str_table; auto str_ind = str_table.AddUniqueHashIndex(cStrKey);

#define INSERT_INT(key, value) table.AddRow(cIntKey = key, cIValue = value)
#define DELETE_INT(key) table.RemoveRow(table.FindByUniqueHash(ind, cIntKey == key)->GetNumber(), false);
#define FIND_INT_EXISTING(key) if (table.FindByUniqueHash(ind, cIntKey == key).GetCount() != 1) { printf("error"); exit(1); }
#define FIND_INT_MISSING(key) if (table.FindByUniqueHash(ind, cIntKey == key).GetCount() != 0) { printf("error"); exit(2); }
#define CHECK_INT_VALUES(value) for (auto rowRef : table) if (rowRef[cIValue] != value) { printf("error"); exit(3); }

#define INSERT_STR(key, value) str_table.AddRow(cStrKey = key, cSValue = value)
#define DELETE_STR(key) str_table.RemoveRow(str_table.FindByUniqueHash(str_ind, cStrKey == key)->GetNumber(), false);
#define FIND_STR_EXISTING(key) if (str_table.FindByUniqueHash(str_ind, cStrKey == key).GetCount() != 1) { printf("error"); exit(4); }
#define FIND_STR_MISSING(key) if (str_table.FindByUniqueHash(str_ind, cStrKey == key).GetCount() != 0) { printf("error"); exit(5); }

#include "template.c"

