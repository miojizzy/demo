#!/usr/bin/env bash

# -------------------------------------------------------------------
# OO support functions
# Kludged by Pim van Riezen <pi@madscience.nl>
# -------------------------------------------------------------------
DEFCLASS=""
CLASS=""
THIS=0

class() {
  DEFCLASS="$1"
  eval CLASS_${DEFCLASS}_VARS=""
  eval CLASS_${DEFCLASS}_FUNCTIONS=""
}

func() {
  local varname="CLASS_${DEFCLASS}_FUNCTIONS"
  eval "$varname=\"\${$varname}$1 \""
}

var() {
  local varname="CLASS_${DEFCLASS}_VARS"
  eval $varname="\"\${$varname}$1 \""
}

loadvar() {
  eval "varlist=\"\$CLASS_${CLASS}_VARS\""
  for var in $varlist; do
    eval "$var=\"\$INSTANCE_${THIS}_$var\""
  done
}

loadfunc() {
  eval "funclist=\"\$CLASS_${CLASS}_FUNCTIONS\""
  for func in $funclist; do
    eval "${func}() { ${CLASS}::${func} \"\$*\"; return \$?; }"
  done
}

savevar() {
  eval "varlist=\"\$CLASS_${CLASS}_VARS\""
  for var in $varlist; do
    eval "INSTANCE_${THIS}_$var=\"\$$var\""
  done
}

typeof() {
  eval echo \$TYPEOF_$1
}

new() {
  local class="$1"
  local cvar="$2"
  shift 2
  local id=$(uuidgen | tr A-F a-f | sed -e "s/-//g")
  eval TYPEOF_${id}=$class
  eval $cvar=$id
  local funclist
  eval "funclist=\"\$CLASS_${class}_FUNCTIONS\""
  for func in $funclist; do
    eval "${cvar}.${func}() {
      local t=\$THIS; THIS=$id; local c=\$CLASS; CLASS=$class; loadvar;
      loadfunc; ${class}::${func} \"\$@\"; rt=\$?; savevar; CLASS=\$c;
      THIS=\$t; return $rt;
    }"

  done
  eval "${cvar}.${class} \"\$*\" || true"
}