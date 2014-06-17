#usage: testify <executable> <test directory>
#alternate: create .testfile and insert ex and dir variables

if [ -e .testfile ]; then
	source .testfile
else
	if [ $# -ne 2 ]; then
		echo "Usage: testify <executable> <test directory>"
		exit 1
	fi
	ex=$1
	dir=${2%/}
fi

tput setaf 6
echo "Rebuilding executables"
tput sgr0
make -s
tput setaf 6
echo "Initializing tests: comparing $ex and $dir/$ex"
tput sgr0
shopt -s nullglob
for testcase in $dir/case*.in
do
	tput setaf 5
	echo "Testing $testcase"
	tput sgr0
	$dir/$ex < $testcase > ideal_output
	./$ex < $testcase > user_output 2> errors.log
	if [ $? -ne 0 ]; then
		tput setaf 1
		echo "$ex exited with errors:"
		tput sgr0
		cat errors.log
		break
	fi
	diff ideal_output user_output > diff
	if [ $? -ne 0 ]; then
		tput setaf 1
		echo "$ex differed from $dir/$ex on $testcase:"
		tput sgr0
		cat diff
		break
	else
		tput setaf 3
		echo "Passed diff-test..."
		tput sgr0
	fi
	#memory checking
	valgrind --leak-check=yes --error-exitcode=1 ./$ex < $testcase &> /dev/null
	if [ $? -ne 0 ]; then
		tput setaf 1
		echo "$ex failed memory checking on $testcase!"
		tput sgr0
		break
	else
		tput setaf 3
		echo "Passed mem-test..."
		tput sgr0 
	fi
	tput setaf 2
	echo "Success!"
	tput sgr0
done
tput setaf 6
echo "Cleaning up..."
tput sgr0
make -s clean
rm errors.log
rm user_output
rm ideal_output
rm diff
