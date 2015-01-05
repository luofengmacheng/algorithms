## Berkeley DB数据库操作

### 1 Berkeley DB数据库简介

Berkeley DB是由sleepycat software开发的一款开放源代码的嵌入式数据库函数库。它为数据访问和管理提供了一种简单的API函数调用，并支持多种编程语言，包括C、C++、Java、Perl、Python和PHP。它是一个经典的C-library模式的toolkit，为应用程序开发者提供工业级强度的数据库服务，能为程序员提供广泛的丰富的函数集。在该函数库中可以完成对数据库的保存、查询、修改和删除等操作。

(注：以下所有代码忽略错误处理。)

### 2 Berkeley DB数据库操作

#### 2.1 创建数据库

在Berkeley DB中，一个表对应一个文件，一些数据库对应一个文件夹。在创建数据库之前，会创建一个环境(也即文件夹)。

``` C
/* 定义环境的指针 */
DB_ENV *dbenv;

/* 创建一个环境 */
db_env_create(&dbenv, 0);

/* 打开环境，my_databases为环境的文件夹 */
dbenv->opoen(dbenv,
	     "my_databases",
	     DB_CREATE | DB_INIT_MPOOL,
	     0644);
```

接下来，就可以创建表了：

``` C
/* dbp为表的句柄，通常每个打开的表都会有一个句柄 */
DB *dbp;
DB_ENV *dbenv;

/* 创建DB的数据结构 */
db_create(&dbp, dbenv, 0);

/*
 * "table.db": 表的对应文件名为table.db，存储在上述my_databases中
 * DB_BTREE:   使用B树作为主键索引
 * DB_CREATE:  当表不存在时，创建该表
 * DB_THREAD:  多个控制线程可以同时使用该句柄
 */
dbp->open(dbp,
	  NULL,
	  "table.db",
	  NULL,
	  DB_BTREE,
	  DB_AUTO_COMMIT | DB_CREATE | DB_THREAD,
	  0664);
```

### 2.2 表的插入

Berkeley DB是K/V数据库，数据库保存的是字节，字节由应用程序解释。

假设要插入的键值对类型为：

``` C
/* 学生表的键 */
typedef struct {
	int stu_num;
} stu_key;

/* 学生表的值，学生的相关信息 */
typedef struct {
	char name[5];
	int  age;
	int  grade;
} stu_data;
```

下面的代码就是向表中添加学号为100的学生信息：

``` C
DB *dbp;
DBT key, data;

stu_key skey;
stu_data sdata;

skey.stu_num = 100;
strcpy(sdata.name, "luo");
sdata.age = 12;
sdata.grade = 6;

memset(&key, 0, sizeof(key));
memset(&data, 0, sizeof(data));

key.data = &skey;
key.size = sizeof(skey);
data.data = &sdata;
data.size = sizeof(sdata);

dbp->put(dbp,
	 NULL,
	 &key,
	 &data,
	 0);
```

### 2.3 表的修改

当要对表的某个K/V对进行修改时，可以使用游标，游标相当于某个K/V的指针(指向该K/V对)。

``` C

DBC *dbc;
DB *dbp;

/* 创建游标 */
dbp->cursor(dbp,
	NULL,
	&dbc,
	0);

DBT key, data;
stu_key skey;
stu_data sdata;

/* 设置游标要找的位置的键 */
skey.stu_num = 100;
memset(&key, 0, sizeof(key));
memset(&data, 0, sizeof(data));
key.data = &skey;
key.size = sizeof(skey);

/* DB_SET表示将游标移动到对应的位置 */
dbc->get(dbc, &key, &data, DB_SET);

/* 修改数据项 */
(stu_data*)(data.data)->grade = 7;

/* 提交修改 */
dbc->put(dbc, &key, &data, DB_CURRENT);
```

参考资料：

1 [SQL 开发人员 Oracle Berkeley DB 指南](http://www.oracle.com/technetwork/cn/articles/seltzer-berkeleydb-sql-085418-zhs.html)
