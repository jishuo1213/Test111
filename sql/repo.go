package sql

import (
	"Test/model"
	"database/sql"
	_ "github.com/mattn/go-sqlite3"
	"log"
)

var db *sql.DB

func init() {
	var err error
	db, err = sql.Open("sqlite3", "./fileinfo.sqlite")
	//checkErr(err)
	if err != nil {
		log.Fatal(err)
	}
	_, err = db.Exec(CreateTable)
	if err != nil {
		log.Printf("exec err:%v\n", err)
	}
}

func AddOneFileInfo(info *model.HeaderFile) error {
	_, err := db.Exec(InsertFile, info.Name, info.Path)
	return err
}

func QueryFileInfo(name string) ([]*model.HeaderFile, error) {
	row, err := db.Query(QueryFile, name)
	if err != nil {
		return nil, err
	}
	defer func() {
		_ = row.Close()
	}()
	res := make([]*model.HeaderFile, 0, 10)
	for row.Next() {
		hf := new(model.HeaderFile)
		err = row.Scan(&hf.Name, &hf.Path)
		if err != nil {
			return nil, err
		}
		res = append(res, hf)
	}
	return res, nil
}
