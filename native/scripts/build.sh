#!/bin/sh -e
# shellcheck source=./env.sh
. "$(dirname "$(realpath "$0")")/env.sh"

BUILD_TYPE="Release"
BUILD_ARCH="default"
GENERATE="no"
BUILD="no"

while getopts ":t:a:gb" arg; do
  case ${arg} in
    t)
      BUILD_TYPE="${OPTARG}"
      ;;
    a)
      BUILD_ARCH="${OPTARG}"
      ;;
    g)
      GENERATE="yes"
      ;;
    b)
      BUILD="yes"
      ;;
    ?)
      echo "Invalid option: -${arg} ${OPTARG}"
      echo
      exit 187
      ;;
  esac
done

BUILD_TYPE=$(get_build_type "$BUILD_TYPE")
GENERATION_DIR="cmake-build-${BUILD_ARCH}-${BUILD_TYPE}"

echo "BUILD_TYPE: $BUILD_TYPE"
echo "BUILD_ARCH: $BUILD_ARCH"
echo "GENERATION_DIR: $GENERATION_DIR"
echo "GENERATE: $GENERATE"
echo "BUILD: $BUILD"

if [ "$GENERATE" = "yes" ];
then
  rm -rf "$GENERATION_DIR"
fi

if [ ! -e "$GENERATION_DIR/created-at" ];
then
  rm -rf "$GENERATION_DIR" \
    && mkdir "$GENERATION_DIR" \
    && cd "$GENERATION_DIR" \
    && cmake -DCMAKE_BUILD_TYPE="$1" --config "$BUILD_TYPE" .. \
    && date > "created-at" \
    && cd ..
fi
if [ "$BUILD" = "yes" ];
then
  cd "$GENERATION_DIR/.." \
    && pwd \
    && cmake --build "$GENERATION_DIR" --target all --config "$BUILD_TYPE" -- -j 8
fi
