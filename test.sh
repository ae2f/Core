# $1, 	$2: compilers
# $3: 	buildtype
# $4 	stdc
# $5 	stdcc

makers=("-GNinja" "")
lstdc=("90")
lstdcc=("14" "17" "20" "23")

cmake --version
ninja --version

__ae2f_CXX=("ON")
__ae2f_IS_SHARED=("ON" "OFF")
__ae2f_MAC_BUILD=("ON" "OFF")

buildtype=$3

for stdc in ${lstdc[@]}; do
	for stdcc in ${lstdcc[@]}; do
		for maker in ${makers[@]}; do
			for _ae2f_CXX in ${__ae2f_CXX[@]}; do
				for _ae2f_IS_SHARED in ${__ae2f_IS_SHARED[@]}; do
					for _ae2f_MAC_BUILD in ${__ae2f_MAC_BUILD[@]}; do

						builddir=build/B$stdc$stdcc$makers$_ae2f_CXX$_ae2f_IS_SHARED

						cmake -S . -B $builddir \
							-DCMAKE_C_STANDARD=$stdc \
							-DCMAKE_CXX_STANDARD=$stdcc \
							$maker $1 $2 \
							-Dae2f_CXX=$_ae2f_CXX \
							-Dae2f_IS_SHARED=$_ae2f_IS_SHARED  \
							-Dae2f_MAC_BUILD=$_ae2f_MAC_BUILD \
							-Dae2fVK_needed=OFF \
							-Dae2fVK_need_clspv=OFF \
							|| { echo "Configuration failed"; exit 1; }

						cmake --build $builddir --config $buildtype || { echo "Build failed"; exit 1; }
						ctest --test-dir $builddir -C $buildtype || { echo "Test failed"; exit 1; }

						rm -rf $builddir
					done 
				done
			done
		done
	done
done
