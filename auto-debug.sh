#########################################################################
# File Name: find_global.sh
# Author: Qichao
# Created Time: Sat 06 May 2017 04:53:24 PM CST
#########################################################################
#!/bin/bash

## notice : ensure the binary is debug-able, compile with -g option

echo "Runing programm is :$1"
programm_elf="$1.elf"
programm_gdb="$1.gdb"
programm_shell="debug-$1.sh"


# Prepare data
[[ -f ${programm_gdb} ]] && rm -rf ${programm_gdb}
[[ -f ${programm_shell} ]] && rm -rf ${programm_shell}
[[ -f ${programm_elf} ]] && rm -rf ${programm_elf}

# step 0: Generate elf file from binary
touch ${programm_elf}
readelf -a $1 >> ${programm_elf}

# step 1: Find start address of .data session
data_start=`cat ${programm_elf} | grep "\.data" | grep PROGBITS | awk '{print $4}'`
data_start="0x${data_start}"
echo "data start address is ${data_start}"

# step 2: Find end addrss of .data session
data_len=`cat ${programm_elf} | grep "\.data" | grep PROGBITS | awk '{print $5}'`
data_len="0x${data_len}"
echo "data len is ${data_len}"

((data_end=data_start+data_len))
echo "data_end is $data_end"

# step 3: Find all OBJECT  GLOBAL DEFAULT objects, should use read,while!!!
#buf=`cat ${programm_elf} | grep "OBJECT  GLOBAL DEFAULT"`
#echo "buf is $buf"
#echo $buf | while read i
cat ${programm_elf} | grep "OBJECT  GLOBAL DEFAULT" | while read i
do
    echo "Current line is $i"
	sym_addr=`echo $i | awk '{print $2}'`
	sym_addr="0x${sym_addr}"

# step 4: Find all global data which is in .data session, and
#   write it to the symbol list

	if ((sym_addr < data_end && sym_addr >= data_start))
	then
# step 5: Generate gdb file in which all 'p' commands will be in 
		sym_name=`echo $i | awk '{print $8}'`
		echo "p ${sym_name}" >> ${programm_gdb}
	fi
done

# step 6: generate bash script which will run gdb on the programm to debug
### step 6.1: find the running program according name $1 ####
echo "#/bin/bash" >> ${programm_shell}
echo "pid=\$(ps -aux | grep ./$1 | head -n 1 | awk '{print \$2}')" >> ${programm_shell}
echo "echo \"PID of the programm to debug is \${pid}\"" >> ${programm_shell}
echo "gdb -q -batch -x ${programm_gdb} attach \${pid}" >>  ${programm_shell}

## Run the gdb shell script periodically and record the output
chmod a+x  ${programm_shell}
source ./${programm_shell}

## TODO:
### 1. How to add global static data to gdb files;
### 2. 
