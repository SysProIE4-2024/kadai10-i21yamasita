/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース
char *execpath="/bin/sh";
// system関数のクローン
int mysystem(char *command) {
  int status = 0; //　子プロセスの終了ステータスを格納するための変数
  int pid = 0;    // プロセスIDを格納するための変数
  if(command==NULL){  //　コマンドがNULLの場合はエラーとして1を返す
    return 1;
  }
  if((pid=fork())<0){   //　分身作成
    return -1;        //　親プロセスをエラー終了
  }
  if(pid!=0){         //　pidが0以外なら親プロセスと判定
    while (wait(&status)!=pid);   //　子プロセスの終了待機
  } 
  else {              //　pidが0なら子プロセスと判定
    execl(execpath,"sh", "-c" ,command ,NULL);    //　/bin/shを実行
    perror(execpath); //　execlが戻ったらエラー処理
    exit (127);
  }
  return status;      //　子プロセスの終了ステータスを返す
}

/* 実行例
% ls -l
total 616
-rw-r--r--  1 yamashita  staff     143  7  4 09:49 Makefile
-rw-r--r--  1 yamashita  staff    2795  7  4 09:49 README.md
-rw-r--r--@ 1 yamashita  staff  238232  7  4 09:49 README.pdf
-rwxr-xr-x  1 yamashita  staff   50392  7  9 23:36 mysysmain
-rw-r--r--  1 yamashita  staff     925  7  4 09:49 mysysmain.c
-rw-r--r--  1 yamashita  staff    1209  7  9 23:36 mysystem.c
-rw-r--r--  1 yamashita  staff      90  7  4 09:49 mysystem.h

% ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 yamashita  staff     143  7  4 09:49 Makefile
-rw-r--r--  1 yamashita  staff    2795  7  4 09:49 README.md
-rw-r--r--@ 1 yamashita  staff  238232  7  4 09:49 README.pdf
-rwxr-xr-x  1 yamashita  staff   50392  7  9 23:36 mysysmain
-rw-r--r--  1 yamashita  staff     925  7  4 09:49 mysysmain.c
-rw-r--r--  1 yamashita  staff    1209  7  9 23:36 mysystem.c
-rw-r--r--  1 yamashita  staff      90  7  4 09:49 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 yamashita  staff     143  7  4 09:49 Makefile
-rw-r--r--  1 yamashita  staff    2795  7  4 09:49 README.md
-rw-r--r--@ 1 yamashita  staff  238232  7  4 09:49 README.pdf
-rwxr-xr-x  1 yamashita  staff   50392  7  9 23:36 mysysmain
-rw-r--r--  1 yamashita  staff     925  7  4 09:49 mysysmain.c
-rw-r--r--  1 yamashita  staff    1209  7  9 23:36 mysystem.c
-rw-r--r--  1 yamashita  staff      90  7  4 09:49 mysystem.h
retval = 00000000

% ./mysysmain 
使い方 : ./mysysmain コマンド文字列


*/
