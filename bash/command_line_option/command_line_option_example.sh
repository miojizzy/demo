#!/bin/bash

ARGS=`getopt -o ab:c:: --long clong::,dlong:,elong -n 'example.sh' -- "$@"`
if [ $? != 0 ]; then
    echo "Terminating..."
    exit 1
fi

eval set -- "${ARGS}"

while true
do
    case "$1" in
        -a) 
            echo "Option a, do not need param";
            shift
            ;;
        -b)
            echo "Option b, need param, argument $2";
            shift 2
            ;;
        -c|--clong)
            case "$2" in
                "")
                    echo "Option c|clong, all ok, no argument";
                    shift 2  
                    ;;
                *)
                    echo "Option c|clong, all ok, argument $2";
                    shift 2;
                    ;;
            esac
            ;;
        --dlong) 
            echo "Option dlong, need param, argument $2";
            shift
            ;;
        -elong)
            echo "Option b,  do not need param";
            shift 2
            ;;
        --)
            # 退出位置
            shift
            break
            ;;
        *)
            echo "Internal error!"
            exit 1
            ;;
    esac
done

#处理剩余的参数
for arg in $@
do
    echo "processing $arg"
done