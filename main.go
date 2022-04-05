package main

import (
	"Test/model"
	"Test/sql"
	"bytes"
	"flag"
	"fmt"
	"io"
	"log"
	"os"
	"os/exec"
	"path"
	"strings"
)

var fileChan chan *model.HeaderFile
var findMap map[string]bool

func FilterDir(dirPath string) error {
	dir, err := os.ReadDir(dirPath)
	if err != nil {
		return err
	}
	for _, f := range dir {
		log.Println(f.Name())
		info, err := f.Info()
		if err != nil {
			return err
		}
		if f.IsDir() {
			go func() {
				err := FilterDir(path.Join(dirPath, info.Name()))
				if err != nil {
					log.Fatal(err)
				}
			}()
		} else {
			if path.Ext(info.Name()) == ".h" {
				fInfo := new(model.HeaderFile)
				fInfo.Name = info.Name()
				fInfo.Path = path.Join(dirPath, info.Name())
				fileChan <- fInfo
			}
		}
	}
	return nil
}

func Consumer() {
	for info := range fileChan {
		//log.Println("add file", info.Path)
		err := sql.AddOneFileInfo(info)
		if err != nil {
			log.Fatal(err)
		}
	}
}

func FindHeaderFile(rootFilePath string, destDirName string) error {
	if findMap[rootFilePath] {
		return nil
	}
	log.Println("start find file:", rootFilePath)
	findMap[rootFilePath] = true

	_, err := copyFile(rootFilePath, path.Join(destDirName, path.Base(rootFilePath)))
	if err != nil {
		return err
	}
	command := exec.Command("/bin/sh", "-c", "grep -o \"\\\".*\\.h\\\"\""+" "+rootFilePath)
	command2 := exec.Command("/bin/sh", "-c", "grep -o \"<.*\\.h>\""+" "+rootFilePath)
	//command2 := exec.Command("grep", "-o", "\"\\\".*\\.h\\\"\"", rootFilePath)
	buffer := &bytes.Buffer{}
	command.Stdout = buffer
	command2.Stdout = buffer

	err = command.Run()
	if err != nil {
		log.Println("1", err)
		//return err
	}
	err = command2.Run()
	if err != nil {
		log.Println("2", err)
		//return err
	}
	fileList := command.Stdout.(*bytes.Buffer).String()
	//strings.Split("file")
	fileList = strings.TrimSpace(fileList)
	//log.Println("this file dont include", fileList)
	if len(fileList) == 0 {
		log.Println("this file dont include")
		return nil
	}
	fileList = strings.Replace(fileList, "\"", "", -1)
	fileList = strings.Replace(fileList, "<", "", -1)
	fileList = strings.Replace(fileList, ">", "", -1)
	fileListStr := strings.Split(strings.ReplaceAll(fileList, "\r\n", "\n"), "\n")

	for _, f := range fileListStr {
		fList, err := sql.QueryFileInfo(f)
		if err != nil {
			log.Fatal(err)
		}
		if len(fList) == 0 {
			log.Println(fmt.Sprintf("find %d %s \n", len(fList), f))
			continue
		}
		index := 0
		if len(fList) > 1 {
			_, _ = fmt.Print(fmt.Sprintf("find %d %s chose ?\n", len(fList), f))
			for i, fT := range fList {
				_, _ = fmt.Print(fmt.Sprintf("%d:%s\n", i, fT.Path))
			}
			_, err = fmt.Scanf("%d", &index)
			if err != nil {
				log.Fatal(err)
			}
		}
		err = FindHeaderFile(fList[index].Path, destDirName)
		if err != nil {
			log.Fatal(err)
		}
	}
	return nil
}

func main() {
	findMap = make(map[string]bool)
	isInit := flag.Bool("init", false, "")
	rootPath := flag.String("path", "./", "")
	filename := flag.String("filename", "./", "")
	destDir := flag.String("dest", "tmp", "")
	flag.Parse()
	fileChan = make(chan *model.HeaderFile, 10000)

	if *isInit {
		go Consumer()
		log.Printf("start init path:%s header file db", *rootPath)
		err := FilterDir(*rootPath)
		if err != nil {
			log.Fatal(err)
		}
	}
	err := FindHeaderFile(*filename, *destDir)
	if err != nil {
		log.Fatal(err)
	}
}

func copyFile(src, dst string) (int64, error) {
	sourceFileStat, err := os.Stat(src)
	if err != nil {
		return 0, err
	}

	if !sourceFileStat.Mode().IsRegular() {
		return 0, fmt.Errorf("%s is not a regular file", src)
	}

	source, err := os.Open(src)
	if err != nil {
		return 0, err
	}
	defer source.Close()

	destination, err := os.Create(dst)
	if err != nil {
		return 0, err
	}
	defer destination.Close()
	nBytes, err := io.Copy(destination, source)
	return nBytes, err
}
