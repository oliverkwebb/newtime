#!/bin/sh
# Simple test harness infrastructure
# Copyright 2005 by Rob Landley
# The following environment varAiables enable optional behavior in "testc":
#    DEBUG - Show every command run by test script.
#    VERBOSE - "all"    continue after failed test
#              "fail"   show diff and stop at first failed test
#              "nopass" don't show successful tests
#              "quiet"  don't show diff -u for failures
#              "spam"   show passing test command lines
#
# "testc" takes three arguments:
#	$1) Description to display when running command
#	$2) Command line arguments to command
#	$3) Expected result (on stdout)
#

: "${SHOWPASS:=PASS}" "${SHOWFAIL:=FAIL}" "${SHOWSKIP:=SKIP}" "${TESTDIR:=$(mktemp -d)}"
[ "${TESTDIR#*tmp.}" != "${TESTDIR}" ] && trap "rm -rf $TESTDIR" 0
if tty -s <&1
then
  SHOWPASS="$(printf "\033[1;32m%s\033[0m" "$SHOWPASS")"
  SHOWFAIL="$(printf "\033[1;31m%s\033[0m" "$SHOWFAIL")"
  SHOWSKIP="$(printf "\033[1;33m%s\033[0m" "$SHOWSKIP")"
fi

verbose_has() {
  [ "${VERBOSE#*"$1"}" != "$VERBOSE" ]
}

do_pass() {
  verbose_has nopass || printf "%s\n" "$SHOWPASS: $NAME"
}

do_fail() {
  printf "%s\n" "$SHOWFAIL: $NAME"
  if [ -n "$CASE" ]
  then
    echo "Expected '$CASE'"
    echo "Got '$A'"
  fi
  ! verbose_has all && exit 1
}

# testing: "name" "args" "result"
testc() {
  [ -z "$1" ] && NAME="$2" || NAME="$1"
  [ "${NAME#"$CMDNAME "}" = "$NAME" ] && NAME="$CMDNAME $1"

  [ -n "$DEBUG" ] && set -x

  if [ -n "$SKIP" ]
  then
    verbose_has quiet || printf "%s\n" "$SHOWSKIP: $NAME"
    return 0
  fi

  echo -n "$3" > "$TESTDIR"/expected
  ${EVAL:-eval} "$PROG $2" > "$TESTDIR"/actual
  RETVAL=$?

  # Catch segfaults
  [ "$RETVAL" -ne "0" ] &&
    echo "exited with signal (or returned $RETVAL)" >> "$TESTDIR"/actual
  DIFF="$(diff --color=always -au${NOSPACE:+w} $TESTDIR/expected $TESTDIR/actual 2>&1)"
  [ -z "$DIFF" ] && do_pass || VERBOSE=all do_fail
  if ! verbose_has quiet && { [ -n "$DIFF" ] || verbose_has spam; }
  then
    printf "%s\n" "$EVAL $PROG $2"
    [ -n "$DIFF" ] && printf "%s\n" "$DIFF"
  fi

  [ -n "$DIFF" ] && ! verbose_has all && exit 1
  rm -f "$TESTDIR"/input "$TESTDIR/"expected "$TESTDIR"/actual


  return 0
}

LONGSTRING="$(printf -- "a%150s" potato)"

PROGRAM () {
	echo "PROGRAM: $1"
	$CC $CFLAGS -L lib/ test/$1.c -o test/tprogs/$1 -lnewtime
	PROG=test/tprogs/$1
}

test_group () {
	PROGRAM $1
	testc "GROUP $1" "" "$(cat test/files/${1}-desired)\n"
}

PROGRAM date
testc "date()" "" ""

PROGRAM sleep
testc "sleepf()" "" ""

PROGRAM wdayof
testc "wdayof()" "" "4\n5\n6\n5\n4\n"
