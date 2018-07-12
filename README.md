# inotify
Inotify 是一个 Linux特性，它监控文件系统操作，比如读取、写入和创建

/*在linux控制台执行以下命令*/
gcc inotify.c
mkdir tmp
./a.out tmp & /*在后台运行*/

cd tmp
/*控制台输入*/
touch 1 2
/*控制台输出*/
create file: 1
create file: 2

rm 1 2
delete file: 1
delete file: 2
