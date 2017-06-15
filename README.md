# MallocTest
测试进程最大可以申请多少内存

## 编译命令
* gcc -DMEMSET test.c -o memset
* gcc -DMEMSET test.c -o alloc

# 测试环境
物理机
* i5-7400 centos7.3 x86_64
* disk:238G
* mem:16G 
* swap:8G

## 1、overcommit_memory=0
* 触发oom异常，被杀死
* alloc:2.47T,2.02T,1.54T
* alloc with memset:22.37G,21.74G,22.37G
## 2、overcommit_memory=1
* 触发oom异常，被杀死
* alloc:3.27T,2.08T,2.02T,2.35T,1.80T
* alloc with memset:22.37G,22.37G,22.37G,22.37G
## 3、overcommit_memory=2
* 未触发oom异常，分配指针为null
* alloc:固定14.55G
* alloc with memset:固定14.55G
