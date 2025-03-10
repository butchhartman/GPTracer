import os
import subprocess

testBuildDirectory = 'bin/tests'
ext = '.exe'

for filename in os.listdir(testBuildDirectory):
	if filename.endswith(ext):
		print("//////////////////////////////////////////////")
		print(filename)
		subprocess.call(testBuildDirectory + "/" + filename)
	else:
		continue