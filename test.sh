
makers=("-GNinja" "")
buildtypes=("Release" "Debug" "MinSizeRel" "RelWithDebInfo")
lstdc=("11" "17" "23")
lstdcc=("17" "20" "23")

__ae2f_CXX=("ON" "OFF")
__ae2f_IS_SHARED=("ON" "OFF")


for buildtype in ${buildtypes[@]}; do
	for maker in ${makers[@]}; do
		for stdc in ${lstdc[@]}; do
			for stdcc in ${lstdcc[@]}; do
				for _ae2f_CXX in ${__ae2f_CXX[@]}; do
					for _ae2f_IS_SHARED in ${__ae2f_IS_SHARED[@]}; do
						cmake -S . -B build \
							-DCMAKE_C_STANDARD=$stdc \
							-DCMAKE_CXX_STANDARD=$stdcc \
							$maker $1 $2 \
							-Dae2f_CXX=$_ae2f_CXX \
							-Dae2f_IS_SHARED=$_ae2f_IS_SHARED

						cmake --build build --config $buildtype
						ctest --test-dir build -C $buildtype
						cmake -E remove_directory build
					done
				done
			done
		done
	done
done