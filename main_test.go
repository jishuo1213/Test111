package main

import (
	"os"
	"os/exec"
	"testing"
)

func TestFindHeaderFile(t *testing.T) {
	command := exec.Command("/bin/sh", "-c", "grep -o \"\\\".*\\.h\\\"\""+" "+"/home/fan/workspace/C/code/main.c")
	command.Stdout = os.Stdout
	err := command.Run()
	t.Log(err)
	//res, err := FindHeaderFile("/home/fan/workspace/C/code/src/leetcode.c")
	//if err != nil {
	//t.Log(err)
	//t.Log(err.Error())
	//t.Fatal(err)
	//}
	//t.Log(res)
	//t.Log(res)
}
