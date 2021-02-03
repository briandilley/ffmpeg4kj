#!/bin/sh -e
# shellcheck source=./env.sh
. "$(dirname "$(realpath "$0")")/env.sh"

BUILD_TYPE="Release"
BUILD_ARCH="default"
BUILD_OPTS=""

while getopts ":t:a:gb" arg; do
  case ${arg} in
    t)
      BUILD_TYPE="${OPTARG}"
      BUILD_OPTS="${BUILD_OPTS} -t ${BUILD_TYPE}"
      ;;
    a)
      BUILD_ARCH="${OPTARG}"
      BUILD_OPTS="${BUILD_OPTS} -a ${BUILD_ARCH}"
      ;;
    g)
      GENERATE="yes"
      BUILD_OPTS="${BUILD_OPTS} -g"
      ;;
    b)
      BUILD="yes"
      BUILD_OPTS="${BUILD_OPTS} -b"
      ;;
    ?)
      echo "Invalid option: -${arg} ${OPTARG}"
      echo
      exit 187
      ;;
  esac
done

cd "$PROJECT_DIR"
DOCK_CROSS_IMAGE=$BUILD_ARCH "./scripts/dockcross.sh" "./scripts/build.sh ${BUILD_OPTS}"

