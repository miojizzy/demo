#!/bin/bash

###
# Usage
# example
#
# start.sh:
# #!/bin/bash
# psr_add_argument a,aaa 0 aaaname "desc of aaa"
# psr_add_argument ,bbb 1 bbbname "desc of bbb"
# psr_parse $@
# echo $psr_has_aaaname
# echo $psr_get_bbbname
#
# command line:
# $ sh start.sh -a --bbb qwert
# 

EXIT(){
    echo "[ERROR] $@"
    exit 1
}

_SHORT_STR=""
_LONG_STR=""
_KEY_STR=""
_CASE_STR=""
_USAGE_STR=""

###
# @funcnane: psr_add_argument()
# @brief: Add options for parser to initialise.
#
# @param 1: Short option and long option , seperate with ',' eg: 'h,help'
# @param 2: 0-No param required
#           1-Requires a param
#           2-Both ok //TODO
# @param 3: Value's name, afer call 'par_parse()',
#           use 'psr_has_${name}'(for no param) or 'psr_get_${name}'(for one param) 
#           to get parse result.
# @param 4: Describtion of this option, to generate usage //TODO
psr_add_argument(){

    ### check param 1 and get 's','l'
    local s=${1%,*}
    local l=${1#*,}
    if [[ ${#s} -ne 1 && ${#l} -lt 2 ]] ;then
        EXIT "short opt and long opt both empty!" $@ ;
    fi
    if [ ${#s} -eq 1 ] ;then
        if echo $_SHORT_STR | egrep -q -r ^$s$ ;then  
            EXIT "duplicate short!" $@ ;
        fi
    fi
    if [ ${#l} -gt 1 ] ;then
        if [[ ${#l} -eq 1 ]] ;then 
            EXIT "long opt length can not be 1!" $@ ;
        elif echo $_LONG_STR | egrep -q -r ^$l$ ;then 
            EXIT "duplicate long!" $@ ;
        fi
    fi

    # check param 2 and get 'p'
    case $2 in 
        0) p=""; break;;
        1) p=":"; break;;
        #2) p="::"; break;;
        *) EXIT "Param Error!" $@ ;;
    esac 
   
    # check param 3 get 'key'
    local key=""
    if echo $_KEY_STR | egrep -q -r ^$3$ ;then 
        EXIT "duplicate key!" $@ ;
    fi
    key=$3

    # generate part of getopt command
    local pair
    pair=""
    if [[ $s ]] ;then 
        _SHORT_STR=$_SHORT_STR${s}${p} ;
        pair=-$s
    fi
    if [[ $l ]] ;then 
        [[ $_LONG_STR ]] && _LONG_STR=$_LONG_STR,${l}${p} || _LONG_STR=$_LONG_STR${l}${p} 
        [[ $pair ]] && pair=$pair\|$l || pair=--$l
    fi

    # generate part of case command
    if [ "$p" == "" ] ;then
        _CASE_STR=${_CASE_STR}"$pair) psr_has_$key=1; echo data:\$psr_has_$key; shift;; "
    elif [ "$p" == ":" ] ;then
        _CASE_STR=${_CASE_STR}"$pair) psr_get_$key=\$2; echo data:\$psr_get_$key; shift 2;; "
    fi

}


###
# @funcnane: psr_parse()
# @brief: Pass all options to parser
#
# @params: use '$@'
psr_parse(){
    local args=`getopt -o $_SHORT_STR --long $_LONG_STR -- "$@"`
    if [ $? != 0 ]; then EXIT "Param error!" $@ ;fi

    eval set -- "${args}"
    
    local case_cmd="case \$1 in "${_CASE_STR}
    case_cmd=${case_cmd}"--) shift; break;; *) echo \"param error! \$1\"; exit 1;; esac"
    
    while true 
    do
        eval $case_cmd
    done
}



psr_print(){
    echo "SHORT_STR: $_SHORT_STR"
    echo "LONG_STR: $_LONG_STR"
    echo "KEY_STR: $_KEY_STR"
    echo "CASE_STR: $_CASE_STR"
}