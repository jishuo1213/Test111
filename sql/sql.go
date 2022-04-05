package sql

const CreateTable = `create table if not exists file_info
(
    id   integer
        constraint file_info_pk
            primary key autoincrement,
    name varchar(64),
    path varchar(512)
);

create unique index if not exists  file_info_id_uindex
    on file_info (id);

create index if not exists  file_info_name_index
    on file_info (name);
`

const InsertFile = `insert into file_info (name, path)
values (?,?);`

const QueryFile = `select name,path
from file_info where  name = ?;`
