base_dir=src/


function list_srcs () {
	curdir=$1
	srcs=
	for f in `ls $curdir` ; do
		if [[ "$f" != "${f%.cpp}" || $f != "${f%.hpp}" ]] ; then
			if [ "$srcs" == "" ] ; then
				srcs="$srcs ${curdir}$f"
			else
				srcs="$srcs \\\\\n   ${curdir}$f"
			fi
		fi
	done

	if [ "$srcs" != "" ] ; then
		var_name=${curdir%%/}
		var_name=${var_name//\//_}
		echo -e $var_name =$srcs
	fi

	for folder in `ls -d ${curdir}*/ 2> /dev/null` ; do
		list_srcs $folder
	done
}

list_srcs $base_dir
