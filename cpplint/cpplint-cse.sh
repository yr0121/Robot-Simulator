#!/bin/bash

export root_dir=${1//--root=/} 
export cpplint_dir=/export/scratch/cpplint-$USER
rm -rf $cpplint_dir
export rel_path=$(realpath --relative-to=$root_dir .)
export cpplint_current_dir=$cpplint_dir/$rel_path
mkdir -p $cpplint_current_dir
export files=${@:2}

for f in $files
do
  echo "Processing $f"
  export file_dir=$(realpath --relative-to=. $f)
  export file_dir=$(dirname $file_dir)
  export file_dir=${file_dir//./}
  mkdir -p $cpplint_current_dir/$file_dir
  cp $f $cpplint_current_dir/$file_dir/
  cpplint.py --root=$cpplint_dir $cpplint_current_dir/$f
done

rm -rf $cpplint_dir
